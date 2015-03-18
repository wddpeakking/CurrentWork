#include "LkAVQueue.h"
#include "LkUtil.h"

#include <QDateTime>

qint64 startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

static LkAVQueue* gs_queue = NULL;

LkAVQueue::LkAVQueue()
{
    m_timestampBulider = new LkTimestampBulider;
    m_timestampBulider->setAudioCaptureInternal(23);
    m_timestampBulider->setVideoCaptureInternal(50);
}

LkAVQueue::~LkAVQueue()
{
    LkFree(m_timestampBulider);
}

LkAVQueue *LkAVQueue::instance()
{
    if (!gs_queue) {
        gs_queue = new LkAVQueue;
    }

    return gs_queue;
}

void LkAVQueue::destroy()
{
    if (gs_queue)
        gs_queue->fini();

    LkFree(gs_queue);
}

void LkAVQueue::enqueue(LkAVPacket *pkt)
{
    LkAutoLocker(m_mutex);

    m_queue << pkt;
}

LkAVPacket *LkAVQueue::finPkt()
{
    // find first un-ready video
    for (int i = 0; i < m_queue.size(); ++i) {
        LkAVPacket *pkt = m_queue.at(i);
        if (!pkt->ready) return pkt;
    }

    return NULL;
}

void LkAVQueue::updatePkt(LkAVPacket *pkt)
{
    LkAutoLocker(m_mutex);

    pkt->ready = true;
}

QQueue<LkAVPacket *> LkAVQueue::dequeue()
{
    LkAutoLocker(m_mutex);

    QQueue<LkAVPacket *> pkts;
    while (!m_queue.empty()) {
        LkAVPacket *pkt = m_queue.first();
        if (pkt->ready) {
            pkts << pkt;

            // erase from m_queue
            m_queue.removeFirst();
        } else
            break;
    }

    return pkts;
}

void LkAVQueue::fini()
{
    LkAutoLocker(m_mutex);

    for (int i = 0; i < m_queue.size(); ++i) {
        LkAVPacket *pkt = m_queue.at(i);
        LkFree(pkt);
    }
}
