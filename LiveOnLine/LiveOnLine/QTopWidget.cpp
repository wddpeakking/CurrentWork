#include "QTopWidget.h"
#include <QMouseEvent>
QTopWidget::QTopWidget(QWidget* parent)
	:QWidget(parent)
{
	/*this->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, g_TopColor);
	this->setPalette(palette);*/
}


QTopWidget::~QTopWidget(void)
{
}

void QTopWidget::mousePressEvent(QMouseEvent *e)
{
	if (e)
	{
		m_point = e->globalPos();
	}

}
void QTopWidget::mouseReleaseEvent(QMouseEvent *e)
{

}
void QTopWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (e)
	{
		QPoint pt = e->globalPos();
		emit MovePostion(QPoint(pt.x()-m_point.x(),pt.y()-m_point.y()));
		m_point = e->globalPos();
	}
}
//void QTopWidget::paintEvent(QPaintEvent *e)
//{
//
//}