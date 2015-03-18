#include "LkTextSource.h"
//#include "LkImageDisplayArea.h"
#include <QPainter>

LkTextSource::LkTextSource(QObject *parent)
    : QObject(parent)
{
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    m_textImage = QImage(100, 30, QImage::Format_RGB888);
    m_textImage.fill(Qt::black);
}

LkImage LkTextSource::getImage()
{
    return m_image.clone();
}

void LkTextSource::stopCapture()
{

}

void LkTextSource::setText(const QString &text)
{
    m_text = text;

    onTimeout();
}

void LkTextSource::onTimeout()
{
	int nLen = m_text.length()*12;
	m_textImage = m_textImage.scaled(nLen,20);
    QPainter painter(&m_textImage);

    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    QPen pen = painter.pen();
    pen.setColor(Qt::red);
    QFont font = painter.font();
    font.setBold(true);//加粗

    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(m_textImage.rect(),Qt::AlignCenter,m_text);

    LkImage be;
    be.width = m_textImage.width();
    be.height = m_textImage.height();

    be.data = new char[m_textImage.byteCount()];
    memcpy(be.data, m_textImage.bits(), m_textImage.byteCount());

    be.dataSize = m_textImage.byteCount();
    be.format = LkImage_Format_BGR24;

    m_image = be;
}
