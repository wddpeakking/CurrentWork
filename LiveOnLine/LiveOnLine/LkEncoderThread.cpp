#include "LkEncoderThread.h"
#include "LkX264Encoder.h"
#include "LkUtil.h"

#include <QMutexLocker>
#include <QFile>
#include <QDateTime>
#include <QElapsedTimer>
#include <QDebug>
#include <QQueue>

#include "LkRtmpMuxer.h"
#include "LkImageProcessThread.h"

// opecv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include "LkAVQueue.h"

#define Max_Queue_Size     (20)

LkEncoderThread::LkEncoderThread(QObject *parent)
	: LkThread(parent)
	, m_x264Encoder(NULL)
	, m_imageProcessThread(NULL)
{
}

LkEncoderThread::~LkEncoderThread()
{
}

void LkEncoderThread::init()
{
	m_x264Encoder = new LkX264Encoder;
	m_x264Encoder->init();

	LkAVQueue::instance()->timestampBuilder()->
		setVideoCaptureInternal(m_x264Encoder->getFrameDuration());
}

void LkEncoderThread::fini()
{
	LkFree(m_x264Encoder);
}

void LkEncoderThread::run()
{
	LkImageProcessThread * imageProcessThread = dynamic_cast<LkImageProcessThread *> (m_imageProcessThread);
	LkAssert(imageProcessThread);

	while (!m_stop) {
		QQueue<LkImage*> images = imageProcessThread->getQueue();

		// if can't get image, then sleep 50 ms.
		if (images.isEmpty()) {
			msleep(10);
			continue;
		}

		while (!images.empty()) {
			LkImage * image = images.dequeue();
			LkAutoFree(LkImage, image);

			if (image->dataSize <= 0) continue;

			IplImage* imgYUV = cvCreateImage(cvSize(image->width, image->height * 3 / 2), IPL_DEPTH_8U, 1);
			IplImage *cvImage = cvCreateImageHeader(cvSize(image->width, image->height), IPL_DEPTH_8U, 3);
			cvImage->imageData = image->data;
			cvImage->imageDataOrigin = image->data;

			cvCvtColor(cvImage, imgYUV, CV_BGR2YUV_I420);

			m_x264Encoder->encode((uchar*)imgYUV->imageData, image->pts);

			cvReleaseImageHeader(&cvImage);
			cvReleaseImage(&imgYUV);

			if (m_stop) break;
		}

		// do clean
		for (int i = 0; i > images.size(); ++i) {
			LkImage *img = images.at(i);
			LkFree(img);
		}
	}

	log_trace("LkEncoderThread exit normally.");
}

void LkEncoderThread::setProcessThread(QThread *thread)
{
	m_imageProcessThread = thread;
}
