#include "LkTimestampBulider.h"

#include "LkUtil.h"

static double growTimestamp(double & timestamp, float internal, double & otherTimestamp)
{
    if (timestamp < otherTimestamp) {
        while (timestamp < otherTimestamp) {
            timestamp += internal;
        }
    } else {
       timestamp += internal;
    }

    return timestamp;
}

LkTimestampBulider::LkTimestampBulider()
    : m_videoInternal(66.66666666666667)        // default 15fps
    , m_audiInternal(23.2199546485261)          // default aac 44100Hz
    , m_videoTimestamp(0.00)
    , m_audioTimestamp(0.00)
{
}

void LkTimestampBulider::setVideoCaptureInternal(int internal)
{
    m_videoInternal = internal;
}

void LkTimestampBulider::setAudioCaptureInternal(int internal)
{
    m_audiInternal = internal;
}

double LkTimestampBulider::addVideoFrame()
{
    LkAutoLocker(m_mutex);

    return growTimestamp(m_videoTimestamp, m_videoInternal, m_audioTimestamp);;
}

double LkTimestampBulider::addAudioFrame()
{
    LkAutoLocker(m_mutex);

    return growTimestamp(m_audioTimestamp, m_audiInternal, m_videoTimestamp);;
}
