
#ifndef _LK_IMAGE_PRC_THREAD_H_
#define _LK_IMAGE_PRC_THREAD_H_

#include "LkThread.h"
#include "LkSourceAbstract.h"
#include "LkTimestampBulider.h"

#include <QHash>
#include <QRect>
#include <QMutex>
#include <QQueue>

// opecv
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

class LkSourceAbstract;
struct LkImage;

class LkImageProcessThread : public LkThread
{
    Q_OBJECT

public:
    LkImageProcessThread(QObject * parent = 0);

    virtual void run();
    void updateSources(QList<SourcePair> & sources);
    LkImage *getImage();
    QQueue<LkImage *> getQueue();

private:

    QMutex m_modifyOutputMutex;
    QMutex m_updateMutex;

    QQueue<LkImage *> m_outputQueue;
    QList<SourcePair> m_sources;
    int m_internal;

    LkTimestampBulider m_timestampBuilder;

    IplImage *m_dstImage;
};

#endif // LkImageProcessThread_HPP
