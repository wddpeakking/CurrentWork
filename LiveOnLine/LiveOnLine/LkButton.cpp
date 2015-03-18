#include "LkButton.h"
#include <QPalette>
#include <QColor>
#include "LkDefine.h"


LkButton::LkButton(QWidget* widget)
	:QLabel(widget)
{
	Init();
}

LkButton::LkButton(QPixmap image,QWidget* widget)
	:QLabel(widget)
{
	Init();
	this->setPixmap(image);
	m_imageNormal = image;
	this->setStyleSheet(GetStyle(m_colorNormal));

}

LkButton::LkButton(QPixmap image,QColor color,QWidget* widget)
	:QLabel(widget)
{
	Init();
	this->setPixmap(image);
	m_imageNormal = image;
	QString str = GetStyle(color);
	this->setStyleSheet(str);
	m_colorNormal = color;
}

void LkButton::Init()
{
	this->setMouseTracking(true);
	m_colorNormal = g_LeftColor;
	m_colorPress = QColor(250,200,30);
	this->setAutoFillBackground(true);
	this->setAlignment(Qt::AlignCenter);	
}
LkButton::~LkButton(void)
{
}

void LkButton::mousePressEvent(QMouseEvent *e)
{
	this->setStyleSheet(GetStyle(m_colorPress));
	this->setPixmap(m_imagePress);
	emit pressWidget();
}
void LkButton::mouseReleaseEvent(QMouseEvent *e)
{
	this->setStyleSheet(GetStyle(m_colorNormal));
	this->setPixmap(m_imageNormal);
	emit releaseWidget();
}
void LkButton::enterEvent(QEvent *e)
{
	this->setStyleSheet(GetStyle(m_colorPress));
}
void LkButton::leaveEvent(QEvent *e)
{
	this->setStyleSheet(GetStyle(m_colorNormal));
}

//QString LkButton::GetStyle(QColor color)
//{
//	return QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
//}