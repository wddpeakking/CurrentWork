#include "LkTopWidget.h"
#include <QMouseEvent>
LkTopWidget::LkTopWidget(QWidget* parent)
	:QWidget(parent)
{
	/*this->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, g_TopColor);
	this->setPalette(palette);*/
}


LkTopWidget::~LkTopWidget(void)
{
}

void LkTopWidget::mousePressEvent(QMouseEvent *e)
{
	if (e)
	{
		m_point = e->globalPos();
	}

}
void LkTopWidget::mouseReleaseEvent(QMouseEvent *e)
{

}
void LkTopWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (e)
	{
		QPoint pt = e->globalPos();
		emit MovePostion(QPoint(pt.x()-m_point.x(),pt.y()-m_point.y()));
		m_point = e->globalPos();
	}
}
//void LkTopWidget::paintEvent(QPaintEvent *e)
//{
//
//}