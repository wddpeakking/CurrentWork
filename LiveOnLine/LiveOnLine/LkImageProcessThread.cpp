
#include "LkImageProcessThread.h"

#include "LkLog.h"
#include "LkSourceAbstract.h"
#include "LkUtil.h"
#include "LkAVUtil.h"
#include "LkAVQueue.h"
#include "LkConfigOpt.h"

#include <QDateTime>
#include <QElapsedTimer>
#include <QElapsedTimer>

static CvRect QRect2CvRect(const QRect &rect)
{
    CvRect ret;
    ret.x = rect.x();
    ret.y = rect.y();
    ret.width = rect.width();
    ret.height = rect.height();

    return ret;
}

LkImageProcessThread::LkImageProcessThread(QObject *parent)
    : LkThread(parent)
    , m_internal(1000/LkConfigOpt::Instance()->n_Lk_Encoder_Fps)
    , m_dstImage(NULL)
{
}

void LkImageProcessThread::run()
{
    CvSize dstSize;
    dstSize.width = LkConfigOpt::Instance()->size_Lk_Encoder_Scale.width();
    dstSize.height = LkConfigOpt::Instance()->size_Lk_Encoder_Scale.height();
    IplImage* dstImg = cvCreateImage(dstSize, IPL_DEPTH_8U, 3);
    cvZero(dstImg);
    m_dstImage = dstImg;

    QRect dstRect(0, 0, dstSize.width, dstSize.height);

    while (!m_stop) {
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();

        m_updateMutex.lock();
        for (int i = 0; i < m_sources.size(); ++i) {
            SourcePair & pair = m_sources[i];

            LkImage LkImage = pair.source->getImage();
            if (LkImage.dataSize <= 0) continue;

            IplImage *cvImage = cvCreateImageHeader(cvSize(LkImage.width, LkImage.height), 8, 3);
            cvImage->imageData = LkImage.data;
            cvImage->imageDataOrigin = LkImage.data;

            // if the image size not qual to area size
            // then resize it.
            IplImage *resizedImage = cvImage;
            if (cvImage->width != pair.rect.width() ||
                    cvImage->height != pair.rect.height())
            {
                resizedImage = cvCreateImage(cvSize(pair.rect.width(), pair.rect.height()), cvImage->depth, cvImage->nChannels);
                cvResize(cvImage, resizedImage, CV_INTER_LINEAR);
            }

            if (LkImage.format == LkImage_Format_RGB24) {
                cvConvertImage(resizedImage, resizedImage, CV_CVTIMG_SWAP_RB);
            }

            // get the intersection of dst rect
            if (!dstRect.intersects(pair.rect)) continue;

            QRect intersectionRect_1 = dstRect.intersected(pair.rect);
            QRect intersectionRect_2 = pair.rect.intersected(dstRect);

            // intersectionRect_2 should relative to pair.rect
            intersectionRect_2.moveTopLeft(QPoint(intersectionRect_2.x() - pair.rect.x(),
                                       intersectionRect_2.y() - pair.rect.y()));

            cvSetImageROI(dstImg, QRect2CvRect(intersectionRect_1));
            cvSetImageROI(resizedImage, QRect2CvRect(intersectionRect_2));

            cvCopy(resizedImage, dstImg);

            cvResetImageROI(dstImg);
            cvResetImageROI(resizedImage);

            // if resizedImage is cvCreateImage created ?
            if (resizedImage != cvImage) {
                cvReleaseImage(&resizedImage);
            }
            cvReleaseImageHeader(&cvImage);
        }

//        IplImage *image=  cvLoadImage("d:\\123.png", CV_LOAD_IMAGE_UNCHANGED);
//        if (image) {
//            for (int x = 0; x < image->width; ++x) {
//                for (int y = 0; y < image->height; ++y) {

//                    //unsigned char *start = image->imageData + y*image->widthStep + x * 4;

//                    unsigned char B = (image->imageData + y*image->widthStep)[x * 4 + 0];
//                    unsigned char G = (image->imageData + y*image->widthStep)[x * 4 + 1];
//                    unsigned char R = (image->imageData + y*image->widthStep)[x * 4 + 2];
//                    unsigned char A = (image->imageData + y*image->widthStep)[x * 4 + 3];


//                    if (A == 0) continue;

//                    int newX = x + 400;
//                    int newY = y + 30;

//                    float A1 = A/255.00;

//                    unsigned char B1 = ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 0];
//                    unsigned char G1 = ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 1];
//                    unsigned char R1 = ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 2];

//                    ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 0] = (1-A1)*B1 + A1*B;
//                    ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 1] = (1-A1)*G1 + A1*G;
//                    ((dstImg->imageData + newY*dstImg->widthStep))[newX*3 + 2] = (1-A1)*R1 + A1*R;
//                }
//             }
//        }


        m_updateMutex.unlock();

        m_modifyOutputMutex.lock();

        // if delayed about 1s , then discard some image.
        // TODO make this to option
        // TODO check AVQueue size
        if (m_outputQueue.size() > 5) {
            log_trace("queue has many mang image, maybe your encoder is too slow!");
            goto end;
        }

        if (true) {
            // to LkImage
            LkImage *be = new LkImage;
            be->width = dstImg->width;
            be->height = dstImg->height;

            be->data = new char[dstImg->imageSize];
            memcpy(be->data, dstImg->imageData, dstImg->imageSize);

            be->dataSize = dstImg->imageSize;

            be->format = LkImage_Format_BGR24;

            m_timestampBuilder.setVideoCaptureInternal(m_internal);
            //be->pts = m_timestampBuilder.addVideoFrame();

            LkVideoPacket *pkt = new LkVideoPacket(Video_Type_H264);
            pkt->ready = false;
            pkt->dts = be->pts = LkAVQueue::instance()->timestampBuilder()->addVideoFrame();
            LkAVQueue::instance()->enqueue(pkt);

            m_outputQueue.enqueue(be);
        }

end:
        m_modifyOutputMutex.unlock();

        int elapsedMs = elapsedTimer.elapsed();
        int needSleepMs = m_internal - elapsedMs;
        if (needSleepMs < 0) {
            needSleepMs = 0;
        }
        msleep(needSleepMs);

        // reset bg image to black
        cvZero(dstImg);
    }
    m_dstImage = NULL;
    cvReleaseImage(&dstImg);

    // clean queue
    for (int i = 0; i < m_outputQueue.size(); ++i) {
        LkImage *img = m_outputQueue.at(i);
        LkFree(img);
    }

    log_trace("LkImageProcessThread exit normally.");
}



void LkImageProcessThread::updateSources(QList<SourcePair> &sources)
{
    LkAutoLocker(m_updateMutex);
    m_sources = sources;
}


LkImage *LkImageProcessThread::getImage()
{
    if (!m_dstImage) return NULL;

    LkAutoLocker(m_updateMutex);

    // to LkImage
    LkImage *be = new LkImage;
    be->width = m_dstImage->width;
    be->height = m_dstImage->height;

    be->data = new char[m_dstImage->imageSize];
    memcpy(be->data, m_dstImage->imageData, m_dstImage->imageSize);

    be->dataSize = m_dstImage->imageSize;

    be->format = LkImage_Format_BGR24;

    return be;
}

QQueue<LkImage *> LkImageProcessThread::getQueue()
{
    LkAutoLocker(m_modifyOutputMutex);

    QQueue<LkImage *> queue = m_outputQueue;
    m_outputQueue.clear();

    return queue;
}
