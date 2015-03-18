#include "LkFileSource.h"

#include <QDebug>
#include <QElapsedTimer>

// opencv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include "LkUtil.h"

LkFileSource::LkFileSource(QObject *parent)
    : LkThread(parent)
    , m_interval(40)
{
}

LkImage LkFileSource::getImage()
{
    LkAutoLocker(m_modifyMutex);
    return m_image.clone();
}

void LkFileSource::stopCapture()
{
    this->stop();
    this->wait();
    this->deleteLater();
}

void LkFileSource::run()
{
    LkAssert(!m_fileName.isEmpty());

    CvCapture* capture = cvCreateFileCapture(m_fileName.toStdString().c_str());
    LkAssert(capture);

    IplImage* frame;
    while(!m_stop)
    {
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();

        frame = cvQueryFrame(capture);
        if(!frame) break ;

        m_modifyMutex.lock();           // Start lock

        LkImage be;
        be.width = frame->width;
        be.height = frame->height;

        be.data = new char[frame->imageSize];
        memcpy(be.data, frame->imageData, frame->imageSize);

        be.dataSize = frame->imageSize;
        be.format = LkImage_Format_BGR24;

        m_image = be;

        m_modifyMutex.unlock();        // End unlock

        int elapsedMs = elapsedTimer.elapsed();
        int needSleepMs = m_interval - elapsedMs;
        if (needSleepMs < 0) {
            needSleepMs = 0;
        }
        msleep(needSleepMs);
    }
    cvReleaseCapture(&capture);

    log_trace("LkFileSource Thread exit normally.");
}

void LkFileSource::setCaptureInterval(int interval)
{
    m_interval = interval;
}

void LkFileSource::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}
