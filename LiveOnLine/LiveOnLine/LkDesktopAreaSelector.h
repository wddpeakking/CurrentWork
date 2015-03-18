#ifndef _LK_DESKTOP_SELECT_H_
#define _LK_DESKTOP_SELECT_H_

#include <QDialog>
class LkDesktopAreaSelector : public QDialog
{
    Q_OBJECT

public:
    explicit LkDesktopAreaSelector(QWidget *parent = 0);
    ~LkDesktopAreaSelector();

    virtual void paintEvent(QPaintEvent * event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void mouseDoubleClickEvent(QMouseEvent * e);

	const QRect& GetRect()const;
private:
	void Init();

private:
    bool m_startSelect;
    QRect m_selectedRect;
    QPoint m_startPoint;
};

#endif // LkDesktopAreaSelector_HPP
