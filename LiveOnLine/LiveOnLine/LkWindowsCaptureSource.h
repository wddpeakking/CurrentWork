#ifndef _LK_WINDOW_H_
#define _LK_WINDOW_H_

#include <QWidget>
#include <QMutex>

#include "LkThread.h"
#include "LkSourceAbstract.h"

class LkWindowsCaptureSource : public LkThread, public LkSourceAbstract
{
    Q_OBJECT
public:
    explicit LkWindowsCaptureSource(QObject *parent = 0);
    ~LkWindowsCaptureSource();

    virtual LkImage getImage();
    virtual void stopCapture();
    virtual void run();

    void setGrabInfo(WId window = 0, int x = 0, int y = 0, int w = -1, int h = -1);
    virtual void setCaptureInterval(int interval);

private:
    void drawCursor(QPaintDevice *pd);
    QPixmap cursorPixmap();

private:
    WId m_wid;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    int m_interval;

    LkImage m_image;
    QMutex m_modifyMutex;
};

#endif // LkWindowsCaptureSource_HPP
