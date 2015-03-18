#ifndef _LK_AUDIOENCODER_ACC_H_
#define _LK_AUDIOENCODER_ACC_H_

#include <QByteArray>

#include "faac.h"
#include "LkAudioEncoderAbstract.h"

class LkAudioEncoder_AAC : public LkAudioEncoderAbstract
{
public:
    LkAudioEncoder_AAC();

    virtual bool init(int samplerate, int channel, int bitrate);
    virtual void fini();
    virtual bool encode(const QByteArray &data, QByteArray &output);\
    virtual int getFrameSize();
    virtual float getFrameDuration();

    QByteArray getHeader();

public:
    //int sample_rate;
    int m_nFrameSize;
    int m_channels;

    unsigned long m_samplesInputSize;
    unsigned long m_maxOutputSize;

    faacEncHandle   m_faacHandle;
    int*            m_pInBuf;
    unsigned char *m_outputBuffer;
    QByteArray m_header;
};

#endif // LkAudioEncoder_AAC_HPP
