#include "LkPictureSource.h"

// opecv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include "LkLog.h"

LkPictureSource::LkPictureSource(const QString &picName)
{
    IplImage * pImg = cvLoadImage(picName.toLocal8Bit().data());
    if (pImg) {
        LkImage be;
        be.width = pImg->width;
        be.height = pImg->height;

        be.data = new char[pImg->imageSize];
        memcpy(be.data, pImg->imageData, pImg->imageSize);

        be.dataSize = pImg->imageSize;
        be.format = LkImage_Format_BGR24;

        m_image = be;

        cvReleaseImage(&pImg);
    } else {
        log_error("cvLoadImage %s failed.", picName.toStdString().c_str());
    }
}

LkImage LkPictureSource::getImage()
{
    return m_image.clone();
}

void LkPictureSource::stopCapture()
{

}

void LkPictureSource::setCaptureInterval(int interval)
{
    Q_UNUSED(interval);
}
