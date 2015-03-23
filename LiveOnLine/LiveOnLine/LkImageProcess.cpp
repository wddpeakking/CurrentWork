
#include "LkImageProcess.h"

#include <QPainter>
#include <QPen>
#include <QEvent>
#include <QResizeEvent>

#include "LkLog.h"
#include "LkImageProcessThread.h"
#include "LkUtil.h"
#include "LkDefine.h"

QMutex mutex;
LkImageProcessWidget::LkImageProcessWidget(QWidget *parent)
    : QWidget(parent)
    , m_activePair(NULL)
    , m_startMove(false)
    , m_startResize(false)
    , m_resizeFromTopLeft(false)
    , m_resizeFromBottomRight(false)
    , m_processThread(NULL)
{
    connect(&m_refreshTimer, SIGNAL(timeout()), this, SLOT(onRefreshTimeout()));
    m_refreshTimer.start(60);

    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);
}

LkImageProcessWidget::~LkImageProcessWidget()
{
    for (int i = 0; i < m_sources.size(); ++i) {
        SourcePair & pair = m_sources[i];
        pair.source->stopCapture();
    }
}

void LkImageProcessWidget::setProcessThread(QThread *thread)
{
    m_processThread = thread;

    updateSources();
}

void LkImageProcessWidget::addCaptureSource(LkSourceAbstract *source, int x, int y, int w, int h)
{
    QRect rt = QRect(x, y, w, h);
    SourcePair pair = {source, rt};
    m_sources.append(pair);
    m_activePair = &m_sources.front();
    updateSources();
    update();
}


void LkImageProcessWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

	QPainter p(this);

	p.setRenderHint(QPainter::SmoothPixmapTransform);

	// back ground
	p.fillRect(rect(), QBrush(QColor(0, 0, 0)));

	  //  element draw
	for (int i = 0; i < m_sources.size(); ++i) {
		const SourcePair & pair = m_sources.at(i);
		LkSourceAbstract *s = pair.source;

		// TODO image data may be used by other thread
		LkImage image = s->getImage();

		if (image.dataSize <= 0) continue;

		QImage qimage;
		if (image.format == LkImage_Format_BGR24) {
			IplImage *oriImage = cvCreateImageHeader(cvSize(image.width, image.height), IPL_DEPTH_8U, 3);
			cvSetData(oriImage, image.data, image.width*3);

			IplImage *dstImage = cvCreateImageHeader(cvSize(image.width, image.height), IPL_DEPTH_8U, 3);
			cvSetData(dstImage, image.data, image.width*3);

			cvCvtColor(oriImage, dstImage, CV_BGR2RGB);

			cvReleaseImageHeader(&oriImage);
			cvReleaseImageHeader(&dstImage);
		}
		qimage = QImage((uchar*)image.data, image.width, image.height, QImage::Format_RGB888);

		QRect rectD = GetRect(pair.rect,GetDx(),GetDy());
		p.drawPixmap(rectD, QPixmap::fromImage(qimage));
		// p.drawImage(pair.rect, qimage);
	}

	
	if (m_activePair && m_activePair->rect.isValid()) {
		QPen pen(Qt::SolidLine);

		pen.setColor(Qt::white);
		pen.setWidth(2);
		pen.setStyle(Qt::DotLine);
		p.setPen(pen);
		QRect rectD = GetRect(m_activePair->rect,GetDx(),GetDy());
		p.drawRect(rectD);
		//p.drawRect(m_activePair->rect);

		QRect topLeftRect(rectD.x(), rectD.y(), 8, 8);
		//QRect topLeftRect(m_activePair->rect.x(), m_activePair->rect.y(), 8, 8);
		p.fillRect(topLeftRect, QBrush(Qt::red));

		QRect bottomRightRect(rectD.bottomRight().x(), rectD.bottomRight().y(), -8, -8);
		//QRect bottomRightRect(m_activePair->rect.bottomRight().x(), m_activePair->rect.bottomRight().y(), -8, -8);
		p.fillRect(bottomRightRect, QBrush(Qt::red));
	}
}

void LkImageProcessWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_activePair) return;

	QPoint pt = QPoint(event->pos().x()/GetDx(),event->pos().y()/GetDy());
    QRect topLeftRect(m_activePair->rect.x(), m_activePair->rect.y(), 8, 8);
    QRect bottomRightRect(m_activePair->rect.bottomRight().x() - 8, m_activePair->rect.bottomRight().y() - 8, 8, 8);

    if (topLeftRect.contains(pt)) {
        setCursor(Qt::SizeFDiagCursor);
    } else if (bottomRightRect.contains(pt)) {
        setCursor(Qt::SizeFDiagCursor);
    } else if (m_activePair->rect.contains(pt)) {
        setCursor(Qt::SizeAllCursor);
    } else {
        setCursor(Qt::ArrowCursor);
    }

    if (m_startResize) {
        if (m_resizeFromTopLeft) {
            m_activePair->rect.setTopLeft(pt);
        }

        if (m_resizeFromBottomRight){
            m_activePair->rect.setBottomRight(pt);
        }
    }

    if (m_startMove) {
        QPoint diff = QPoint(pt.x() - m_lastMovePoint.x(), pt.y() - m_lastMovePoint.y());

        int w = m_activePair->rect.width();
        int h = m_activePair->rect.height();
        m_activePair->rect.setTopLeft(QPoint(m_activePair->rect.x() + diff.x(), m_activePair->rect.y() + diff.y()));
        m_activePair->rect.setWidth(w);
        m_activePair->rect.setHeight(h);
    }

    if (m_startResize || m_startMove) {
        updateSources();
    }

    update();
    m_lastMovePoint = pt;
}

void LkImageProcessWidget::mousePressEvent(QMouseEvent *e)
{
	QPoint pt = QPoint(e->pos().x()/GetDx(),e->pos().y()/GetDy());
    int findIndex = -1;
    for (int i = m_sources.size() - 1; i >= 0; --i) {
        SourcePair & pair = m_sources[i];
         if (pair.rect.contains(pt)) {
             findIndex = i;
             break;
         }
    }

    if (findIndex != -1) {
        m_activePair = &m_sources[findIndex];
    } else {
        m_activePair = NULL;
    }

    if (!m_activePair) return;

    QRect topLeftRect(m_activePair->rect.x(), m_activePair->rect.y(), 8, 8);
    QRect bottomRightRect(m_activePair->rect.bottomRight().x(), m_activePair->rect.bottomRight().y(), -8, -8);

    if (m_activePair->rect.contains(pt)) {
        if (topLeftRect.contains(pt))
        {
            m_startResize = true;
            m_resizeFromTopLeft = true;
        } else if (bottomRightRect.contains(pt)) {
            m_startResize = true;
            m_resizeFromBottomRight = true;
        } else {
            m_startMove = true;
        }

    } else {
        m_startMove = false;
    }

    m_lastMovePoint = pt;
}

void LkImageProcessWidget::mouseReleaseEvent(QMouseEvent* /*e*/)
{
    m_startMove = false;
    m_startResize = false;
    m_resizeFromTopLeft = false;
    m_resizeFromBottomRight = false;
}

void LkImageProcessWidget::mouseDoubleClickEvent(QMouseEvent* /*e*/)
{
    if (!m_activePair) return;

    m_activePair->rect = QRect(rect().x()/GetDx(),rect().y()/GetDy(),rect().width()/GetDx(),rect().height()/GetDy());

    updateSources();
    update();
}

void LkImageProcessWidget::keyPressEvent(QKeyEvent *e)
{
    if (!m_activePair) return;

    int key = e->key();
    if (key == Qt::Key_Delete) {
        m_activePair->source->stopCapture();

        if (m_sources.contains(*m_activePair)) {
            m_sources.removeAll(*m_activePair);
            m_activePair = NULL;
        }
    } else if (key == Qt::Key_Up) {
        onUpBtnClicked();
    } else if (key == Qt::Key_Down) {
        onDownBtnClicked();
    } else if (key == Qt::Key_Left) {
        onLeftBtnClicked();
    } else if (key == Qt::Key_Right) {
        onRightBtnClicked();
    } else if (key == Qt::Key_PageUp) {
        onIncBtnClicked();
    } else if (key == Qt::Key_PageDown) {
        onDecBtnClicked();
    } else {
        QWidget::keyPressEvent(e);
    }
	updateSources();
	update();
}

void LkImageProcessWidget::focusOutEvent(QFocusEvent *e)
{
    Q_UNUSED(e);

    m_activePair = NULL;
}

void LkImageProcessWidget::onIncBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid()) {
        int w =  r.width();
        int h = r.height();
        r.setWidth(w + 5);
        r.setHeight(h + 5);
    }

    update();
}

void LkImageProcessWidget::onDecBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid() ) {
        int w =  r.width();
        int h = r.height();
		if (w - 5 > 0 )
		{
			 r.setWidth(w - 5);
		}
		if (h - 5)
		{
			 r.setHeight(h - 5);
		}
    }

    update();
}

void LkImageProcessWidget::onUpBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid()) {
        int y = r.y();
        r.moveTop(y - 1);
    }

    update();
}

void LkImageProcessWidget::onDownBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid()) {
        int y = r.y();
        r.moveBottom(y + r.height() + 1);
    }
    update();
}

void LkImageProcessWidget::onLeftBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid()) {
        int x =  r.x();
        r.moveLeft(x - 1);
    }
    update();
}

void LkImageProcessWidget::onRightBtnClicked()
{
    if (!m_activePair) return;

    QRect &r = m_activePair->rect;
    if (r.isValid()) {
        int x =  r.x();
        r.moveRight(x + r.width() + 1);
    }

    update();
}

void LkImageProcessWidget::onRefreshTimeout()
{
    if (!m_sources.empty())
        update();
}

void LkImageProcessWidget::onSettingChanged()
{
    QSize size = LkConfigOpt::Instance()->size_Lk_Encoder_Scale;
    setFixedSize(size);
}

void LkImageProcessWidget::updateSources()
{
    LkImageProcessThread *ipt = dynamic_cast<LkImageProcessThread*>(m_processThread);
    if (ipt) {
        ipt->updateSources(m_sources);
    }
}

int LkImageProcessWidget::getPairIndex(SourcePair *pair)
{
    if (!pair) return -1;
    QList<SourcePair> m_sources;

    for (int i = 0; i < m_sources.size(); ++i) {
        SourcePair *p = &m_sources[i];

        if (pair == p) {
            return i;
        }
    }

    return -1;
}
