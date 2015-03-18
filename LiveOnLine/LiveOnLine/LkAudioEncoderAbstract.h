#ifndef _LK_AUDIOABS_H_
#define _LK_AUDIOABS_H_

#include <QByteArray>

class LkAudioEncoderAbstract
{
public:
    enum AudioEncoderType
    {
        AAC,
        MP3
    };

public:
    LkAudioEncoderAbstract();
    virtual ~LkAudioEncoderAbstract();

    virtual bool init(int samplerate, int channel, int bitrate) = 0;
    virtual void fini() = 0;
    virtual bool encode(const QByteArray &data, QByteArray &output) = 0;
    virtual int getFrameSize() = 0;
    virtual float getFrameDuration() = 0;
    inline AudioEncoderType encoderType() { return m_encoderType; }

protected:
    int m_samplerate;
    int m_channels;
    int m_bitrate;
    AudioEncoderType m_encoderType;
};

#endif // LkAudioEncoderAbstract_HPP
