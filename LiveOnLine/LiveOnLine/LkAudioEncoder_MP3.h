#ifndef _LK_AUDIO_MP3_H_
#define _LK_AUDIO_MP3_H_

#include "LkAudioEncoderAbstract.h"
#include "lame.h"

class LkAudioEncoder_MP3 : public LkAudioEncoderAbstract
{
public:
    LkAudioEncoder_MP3();

    virtual bool init(int samplerate, int channel, int bitrate);
    virtual void fini();
    virtual bool encode(const QByteArray &data, QByteArray &output);
    virtual int getFrameSize();
    virtual float getFrameDuration();

private:
    lame_global_flags *m_lame_global_flags;
};

#endif // LkAudioEncoder_MP3_HPP
