
#ifndef _LK_CONTEXT_H_
#define _LK_CONTEXT_H_

#include "LkAVUtil.h"

class LkContext
{
public:
    LkContext();

    void setVideoSh(LkAVPacket *pkt);
    void setAudioSh(LkAVPacket *pkt);
    void setSei(LkAVPacket *pkt);

    inline LkAVPacket *videoSh()   { return videoSH; }
    inline LkAVPacket *audioSh()   { return audioSH; }
    inline LkAVPacket *sei()       { return seiPkt; }

private:
    LkAVPacket *videoSH;
    LkAVPacket *audioSH;
    LkAVPacket *seiPkt;
};

extern LkContext *appCtx;

#endif // LkContext_HPP
