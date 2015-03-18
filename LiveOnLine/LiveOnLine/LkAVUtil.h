#ifndef _LK_AVUTIL_H_
#define _LK_AVUTIL_H_

#include <QByteArray>
#include "LkStream.h"

#define Packet_Type_Audio 0x08
#define Packet_Type_Video 0x09

#define Audio_Type_AAC 0x01
#define Audio_Type_MP3 0x02

#define Video_Type_H264 0x17

class LkAVPacket
{
public:
    LkAVPacket(char type)
        : pktType(type)
        , pts(0)
        , dts(0)
        , ready(false)
    {

    }
    virtual ~LkAVPacket() {}

    LkStream data;
    char pktType;
    qint64 pts;
    qint64 dts;
    bool ready;
};

class LkAudioPacket : public LkAVPacket
{
public:
    LkAudioPacket(char at)
        : LkAVPacket(Packet_Type_Audio)
        , audioType(at)
    {

    }
    ~LkAudioPacket() {}

    char audioType;
};

class LkVideoPacket : public LkAVPacket
{
public:
    LkVideoPacket(char vt)
        : LkAVPacket(Packet_Type_Video)
        , videoType(vt)
    {

    }
    ~LkVideoPacket() {}

    char videoType;
};

#endif // LkAVPacket_HPP
