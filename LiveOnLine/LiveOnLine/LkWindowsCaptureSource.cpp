#include "LkWindowsCaptureSource.h"

#include <windows.h>
#include <winuser.h>
#include <qwindowdefs.h>
#include <QGuiApplication>
#include <QScreen>
#include <QImage>
#include <QElapsedTimer>
#include <QCursor>
#include <QPainter>
#include <QtWin>
#include <QBitmap>

#include "LkLog.h"
#include "LkUtil.h"
#include "LkConfigOpt.h"

// opecv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#define Default_Capture_Interval    50      // default is 20 fps

LkWindowsCaptureSource::LkWindowsCaptureSource(QObject *parent)
    : LkThread(parent)
    , m_wid(0)
    , m_x(0)
    , m_y(0)
    , m_width(320)
    , m_height(240)
    , m_interval(Default_Capture_Interval)
{
}

LkWindowsCaptureSource::~LkWindowsCaptureSource()
{

}

LkImage LkWindowsCaptureSource::getImage()
{
    LkAutoLocker(m_modifyMutex);

//    LkImage be;
//    be = m_image;
    return m_image.clone();
}

void LkWindowsCaptureSource::stopCapture()
{
    this->stop();
    this->wait();
    this->deleteLater();
}

void LkWindowsCaptureSource::run()
{
    // TODO make could select screen
    // QGuiApplication::screens();
    while (!m_stop) {
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();

        QScreen *screen = QGuiApplication::primaryScreen();

        if (screen) 
		{
            QPixmap pixmap = screen->grabWindow(m_wid, m_x, m_y, m_width, m_height);
			if (LkConfigOpt::Instance()->b_Lk_Mouse)
			{
				// TODO to draw cursor to image
				QRect desktopRect = QRect(QPoint(0, 0), screen->size());
				if (desktopRect.contains(QCursor::pos())) 
				{
					drawCursor(&pixmap);
				}
			}
		
            QImage image = pixmap.toImage();

            LkImage be;
            be.width = image.width();
            be.height = image.height();

            int imageSize = be.width * be.height * 3;
            be.data = new char[imageSize];

            IplImage *oriImage = cvCreateImageHeader(cvSize(image.width(), image.height()), IPL_DEPTH_8U, 4);
            cvSetData(oriImage, image.bits(), image.bytesPerLine());

            IplImage *dstImage = cvCreateImageHeader(cvSize(image.width(), image.height()), IPL_DEPTH_8U, 3);
            cvSetData(dstImage, be.data, be.width * 3);

            cvCvtColor(oriImage, dstImage, CV_BGRA2BGR);

            be.dataSize = imageSize;
            be.format = LkImage_Format_BGR24;
			m_modifyMutex.lock();           // Start lock
            m_image = be;    
			m_modifyMutex.unlock();        // End unlock
            cvReleaseImageHeader(&oriImage);
            cvReleaseImageHeader(&dstImage);

      
        }

        int elapsedMs = elapsedTimer.elapsed();
        int needSleepMs = m_interval - elapsedMs;
        if (needSleepMs < 0) {
            needSleepMs = 0;
        }
        msleep(needSleepMs);
    }

    log_trace("LkWindowsCaptureSource exit normally.");
}

void LkWindowsCaptureSource::setGrabInfo(WId window, int x, int y, int w, int h)
{
    m_wid = window;
    m_x = x;
    m_y = y;
    m_width = w;
    m_height = h;

    // force align to 4 for color cvt performance
    m_width = m_width / 4 *4;
}

void LkWindowsCaptureSource::setCaptureInterval(int interval)
{
    m_interval = interval;
}

void LkWindowsCaptureSource::drawCursor(QPaintDevice *pd)
{
    QPainter p(pd);
    QPixmap pix = cursorPixmap();

    QPoint point = QCursor::pos();
    p.drawPixmap(point.x() - m_x, point.y() - m_y, pix.width(), pix.height(), pix);
}

#ifdef Q_OS_WIN
QPixmap LkWindowsCaptureSource::cursorPixmap()
{
    static HCURSOR cursor = NULL;
    static QPixmap cachedCursor = QPixmap();

    QPixmap cursorPixmap;
    HICON icon;
    CURSORINFO cursorInfo;
    ICONINFO iconInfo;
    cursorInfo.cbSize = sizeof(CURSORINFO);

    if(GetCursorInfo(&cursorInfo))
    {
        if (cursor == cursorInfo.hCursor)
            return cachedCursor;

        if (cursorInfo.flags == CURSOR_SHOWING)
        {
            icon = CopyIcon(cursorInfo.hCursor);
            if (GetIconInfo(icon, &iconInfo))
            {
                if (iconInfo.hbmColor != NULL) {
                    cursorPixmap = QtWin::fromHBITMAP(iconInfo.hbmColor, QtWin::HBitmapAlpha);
                } else if (iconInfo.hbmMask != NULL){//if the cursor hasn't color image (for example, Ibeam cursor)
                    cursorPixmap = QtWin::fromHBITMAP(iconInfo.hbmMask, QtWin::HBitmapAlpha).mask();

                    //replace white color with transparent
                    QImage cursorImage = cursorPixmap.copy(0, cursorPixmap.height() / 2, cursorPixmap.width(), cursorPixmap.height() / 2).toImage();
                    cursorImage.setColor(0, Qt::transparent);
                    cursorPixmap = QPixmap::fromImage(cursorImage);
                }
            }
        }
    }

    cursor = cursorInfo.hCursor;
    cachedCursor = cursorPixmap;

    return cursorPixmap;
}
#endif // Q_OS_WIN
