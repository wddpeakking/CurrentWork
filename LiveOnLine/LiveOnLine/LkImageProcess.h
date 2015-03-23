#ifndef _LK_IMAGEPOCESS_H_
#define _LK_IMAGEPOCESS_H_

#include <QWidget>
#include <QTimer>
#include <QThread>

#include "LkSourceAbstract.h"
#include "LkConfigOpt.h"

class LkImageProcessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LkImageProcessWidget(QWidget *parent = 0);
    ~LkImageProcessWidget();

    void setProcessThread(QThread *thread);
    void addCaptureSource(LkSourceAbstract *source, int x, int y, int w, int h);

    virtual void paintEvent(QPaintEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void mouseDoubleClickEvent(QMouseEvent * e);
    virtual void keyPressEvent(QKeyEvent * e);
    virtual void focusOutEvent(QFocusEvent * e);

private slots:
    void onIncBtnClicked();
    void onDecBtnClicked();
    void onUpBtnClicked();
    void onDownBtnClicked();
    void onLeftBtnClicked();
    void onRightBtnClicked();
    void onRefreshTimeout();
    void onSettingChanged();

private:
    void updateSources();
    int getPairIndex(SourcePair *pair);

	inline QRect GetRect(QRect rect,double dX,double dY)
	{
		return QRect(rect.x()*dX,rect.y()*dY,rect.width()*dX,rect.height()*dY);
	}
	inline double GetDx()
	{
		return rect().width()/static_cast<double>(LkConfigOpt::Instance()->size_Lk_Encoder_Scale.width());
	}
	inline double GetDy()
	{
		return rect().height()/static_cast<double>(LkConfigOpt::Instance()->size_Lk_Encoder_Scale.height());
	}

private:
    QSize m_parentSize;
    QRect m_activeRect;
    SourcePair * m_activePair;
    bool m_startMove;
    bool m_startResize;
    bool m_resizeFromTopLeft;
    bool m_resizeFromBottomRight;
    QPoint m_lastMovePoint;
    QList<SourcePair> m_sources;

    // refresh timer to update pixmap
    QTimer m_refreshTimer;
    QThread * m_processThread;
};



#endif // LkImageProcess_H
