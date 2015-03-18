
#include "LkContext.h"
#include "LkUtil.h"

LkContext::LkContext()
    : videoSH(NULL)
    , audioSH(NULL)
    , seiPkt(NULL)
{
}

void LkContext::setVideoSh(LkAVPacket *pkt)
{
    LkFree(videoSH);
    videoSH = pkt;
}

void LkContext::setAudioSh(LkAVPacket *pkt)
{
    LkFree(audioSH);
    audioSH = pkt;
}

void LkContext::setSei(LkAVPacket *pkt)
{
    LkFree(seiPkt);
    seiPkt = pkt;
}

LkContext *appCtx = new LkContext;
