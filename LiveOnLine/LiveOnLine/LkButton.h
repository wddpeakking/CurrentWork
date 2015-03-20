#ifndef _LK_BUTTON_H_
#define _LK_BUTTON_H_

#include <QWidget>
#include <QPixmap>
#include <QSize>
#include <QLabel>

class LkButton :
	public QLabel
{
	Q_OBJECT
public:

	LkButton(QWidget* widget = 0);
	LkButton(QPixmap image,QWidget* widget = 0);
	LkButton(QPixmap image,QColor color,QWidget* widget = 0);
	LkButton(QPixmap imageNormal,QPixmap imagePress,QWidget* widget = 0);

	~LkButton(void);

	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	virtual void enterEvent(QEvent *e);
	virtual void leaveEvent(QEvent *e);

	void SetNormalColor(QColor color){m_colorNormal = color;};
	void SetPressColor(QColor color){m_colorPress = color;};

	void SetNormalImage(QPixmap image){m_imageNormal = image;};
	void SetPressImage(QPixmap image){m_imagePress = image;};

	void UpdateNormalImage(QPixmap image)
	{
		m_imageNormal = image;
		this->setPixmap(image);
	};
	void UpdatePressImage(QPixmap image)
	{
		m_imagePress = image;
		this->setPixmap(image);
	};
	void UpdateImage(QPixmap image)
	{
		this->setPixmap(image);
	};
	void UpdateImage()
	{
		this->setPixmap(m_imageNormal);
	};


signals:
	void pressWidget();
	void releaseWidget();

private:
	void Init();

private:
	QColor m_colorNormal;
	QColor m_colorPress;
	QPixmap m_imageNormal;
	QPixmap m_imagePress;

};
#endif
