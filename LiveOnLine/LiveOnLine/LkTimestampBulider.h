#ifndef _LK_TIMESTAMP_H_
#define _LK_TIMESTAMP_H_

#include <QMutex>

class LkTimestampBulider
{
public:
    LkTimestampBulider();

    void setVideoCaptureInternal(int internal);
    void setAudioCaptureInternal(int internal);

    double addVideoFrame();
    double addAudioFrame();

private:
    QMutex m_mutex;

    float m_videoInternal;
    float m_audiInternal;

    double m_videoTimestamp;
    double m_audioTimestamp;
};

#endif // 
