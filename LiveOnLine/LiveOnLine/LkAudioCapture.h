#ifndef _LK_AUDIO_CAPTURE_H_
#define _LK_AUDIO_CAPTURE_H_

#include <QHash>
#include <QMutex>
#include <QWaitCondition>

#include "LkThread.h"
#include "RtAudio.h"


class LkAudioEncoderAbstract;

class LkAudioCapture : public LkThread
{
    Q_OBJECT
public:
    LkAudioCapture(QObject * parent = 0);
    ~LkAudioCapture();

    virtual void run();

    static QHash<int, QString> availableDevices();

private:
    void onDataCaptured(char *data, int size);

private:
    RtAudio *m_grabEngine;
    LkAudioEncoderAbstract *m_audioEncoder;
    QMutex m_mutex;
    QWaitCondition m_waitCondtion;

    QByteArray m_bytesCache;
    bool m_hasSendHeader;
    int m_bitDepth;
    int m_sampleRate;
    int m_channels;
    int m_bitrate;

public:
    friend int handleAudioData(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                          double streamTime, RtAudioStreamStatus status, void *data);

    int startCapture(int bitrate = 96000, int sampleRate = 44100, int channels = 2, int deviceID = -1);
    int stopCapture();

};

#endif // LkAudioCapture_HPP
