#include "LkCameraSource.h"


#include "LkErrno.h"
#include "LkUtil.h"
#include "LkLog.h"

// opencv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <QElapsedTimer>
#include "LkConfigOpt.h"

LkCameraSource::LkCameraSource(QObject *parent)
    : LkThread(parent)
    , m_interval(1000/LkConfigOpt::Instance()->n_Lk_Encoder_Fps)
    , m_cameraIndex(-1)
{
}

LkImage LkCameraSource::getImage()
{
    LkAutoLocker(m_modifyMutex);
    return m_image.clone();
}

void LkCameraSource::stopCapture()
{
    this->stop();
    this->wait();
    this->deleteLater();
}

void LkCameraSource::run()
{
    IplImage *pImg = NULL;
    CvCapture *cap = cvCreateCameraCapture(m_cameraIndex);
    if (!cap) {
        log_error("open camera failed.");
        return;
    }
    log_trace("open camera %d success, name = %s", m_cameraIndex, m_cameraName.toStdString().c_str());

    while (!m_stop) {
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();

        pImg = cvQueryFrame(cap);
        if (!pImg) continue;

     

        LkImage be;
        be.width = pImg->width;
        be.height = pImg->height;

        be.data = new char[pImg->imageSize];
        memcpy(be.data, pImg->imageData, pImg->imageSize);

        be.dataSize = pImg->imageSize;
        be.format = LkImage_Format_BGR24;

		m_modifyMutex.lock();           // Start lock
        m_image = be;
        m_modifyMutex.unlock();        // Start unlock


        int elapsedMs = elapsedTimer.elapsed();
        int needSleepMs = m_interval - elapsedMs;
        if (needSleepMs < 0) {
            needSleepMs = 0;
        }
        msleep(needSleepMs);
    }
    cvReleaseCapture(&cap);

    log_trace("BleCameraCapture exit normally.");
}

void LkCameraSource::setCaptureInterval(int interval)
{
    m_interval = interval;
}

void LkCameraSource::setCameraInfo(int index, const QString &name)
{
    m_cameraIndex = index;
    m_cameraName = name;
}
