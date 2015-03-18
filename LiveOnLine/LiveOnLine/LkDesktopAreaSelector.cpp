#include "LkDesktopAreaSelector.h"
#include <QKeyEvent>
#include <QPen>
#include <QPainter>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

LkDesktopAreaSelector::LkDesktopAreaSelector(QWidget *parent)
    : QDialog(parent)
    , m_startSelect(false)
{
	Init();
}

LkDesktopAreaSelector::~LkDesktopAreaSelector()
{

}
void LkDesktopAreaSelector::Init()
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	this->setWindowOpacity(0.6);
	this->setMouseTracking(true);
	this->setStyleSheet("background-color:rgb(0,0,0,)");
	QDesktopWidget* pDestopWidget = QApplication::desktop();
	this->resize(pDestopWidget->width(),pDestopWidget->height());
}
const QRect& LkDesktopAreaSelector::GetRect()const
{
	return m_selectedRect;
}
void LkDesktopAreaSelector::paintEvent(QPaintEvent */*event*/)
{
    QPainter p(this);

    QPen pen(Qt::DotLine);
    pen.setWidth(3);
    pen.setColor(Qt::red);
    p.setPen(pen);
	p.drawText(QPoint(m_selectedRect.left()+m_selectedRect.width()/2-30,m_selectedRect.top()+m_selectedRect.height()/2),QStringLiteral("Ë«»÷Íê³É²Ù×÷"));
    p.drawRect(m_selectedRect);
}

void LkDesktopAreaSelector::keyPressEvent(QKeyEvent *event)
{
    // esc key pressed
    if (event->key() == Qt::Key_Escape) {
        this->close();
       // this->deleteLater();
    }
}

void LkDesktopAreaSelector::mouseMoveEvent(QMouseEvent *event)
{
    if (m_startSelect) {
        m_selectedRect = QRect(m_startPoint, event->pos());
        update();
    }
}

void LkDesktopAreaSelector::mousePressEvent(QMouseEvent *e)
{
    m_startSelect = true;
    m_startPoint = e->pos();
}

void LkDesktopAreaSelector::mouseReleaseEvent(QMouseEvent */*e*/)
{
    m_startSelect = false;
}

void LkDesktopAreaSelector::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    if (m_selectedRect.isValid()) {
		    accept();
    }
}
