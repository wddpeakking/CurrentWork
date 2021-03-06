#ifndef _LK_TOPWIDGET_H_
#define _LK_TOPWIDGET_H_
#include <QWidget>
#include <QPoint>
#include "LkDefine.h"
class QMouseEvent;
class QTopWidget :
	public QWidget
{
	Q_OBJECT
public:
	QTopWidget(QWidget* parent=0);
	~QTopWidget(void);

	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	//virtual void paintEvent(QPaintEvent *);

signals:
	void MovePostion(const QPoint& pt);
private:
	QPoint m_point;
};
#endif

