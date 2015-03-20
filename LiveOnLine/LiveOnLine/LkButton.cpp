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

LkButton::LkButton(QPixmap imageNormal,QPixmap imagePress,QWidget* widget)
	:QLabel(widget)
{
	Init();
	this->setPixmap(imageNormal);
	m_imageNormal = imageNormal;
	m_imagePress = imagePress;
	this->setStyleSheet(GetStyle(m_colorNormal));
}

void LkButton::Init()
{
	this->setMouseTracking(true);
	m_colorNormal = g_BtnNormalColor;
	m_colorPress = QColor(0,0,0);
	this->setAutoFillBackground(true);
	this->setAlignment(Qt::AlignCenter);	
	this->setAutoFillBackground(true);
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
	//this->setStyleSheet(GetStyle(m_colorPress));
	this->setPixmap(m_imagePress);
}
void LkButton::leaveEvent(QEvent *e)
{
	//this->setStyleSheet(GetStyle(m_colorNormal));
	this->setPixmap(m_imageNormal);
}
