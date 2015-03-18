
#ifndef _LK_QUEUE_H_
#define _LK_QUEUE_H_

#include <QMutex>
#include <QQueue>
#include <QHash>

#include "LkTimestampBulider.h"
#include "LkAVUtil.h"

class LkAVQueue
{
public:
    LkAVQueue();
    ~LkAVQueue();

    static LkAVQueue *instance();
    static void destroy();

    void init();

    void enqueue(LkAVPacket * pkt);

    LkAVPacket * finPkt();

    void updatePkt(LkAVPacket * pkt);

    QQueue<LkAVPacket *> dequeue();

    inline LkTimestampBulider *timestampBuilder() { return m_timestampBulider; }

private:
    void fini();

private:
    LkTimestampBulider *m_timestampBulider;
    QMutex m_mutex;
    QList<LkAVPacket *> m_queue;
};

#endif // 
