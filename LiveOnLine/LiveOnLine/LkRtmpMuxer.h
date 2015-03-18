#ifndef _LK_RTMPMUXER_H_
#define _LK_RTMPMUXER_H_

#include <string>

#include "LkStream.h"
#include "rtmp.h"
using namespace std;

#define CODECID_H264    (0x07)
#define CODECID_AAC     (0x0a)

/*!
    @brief the flv metadata
*/
struct FlvMetaData
{
    int audiocodecid;
    int audiodatarate;
    int audiodelay;
    int audiosamplerate;
    int audiosamplesize;
    bool canSeekToEnd;
    string creationdate;
    int duration;
    int filesize;
    int framerate;
    int height;
    bool stereo;
    int videocodecid;
    int videodatarate;
    int width;

    FlvMetaData();
};

/*!
    @brief RtmpAU rtmp access unit
*/
class RtmpAU
{
public:
	RtmpAU(const string& url);
	~RtmpAU();

	int connect();
	int close();
	int sendPacket(const string &data, unsigned long long timestamp, unsigned int pktType, int channel);

private:
	string m_rtmpUrl;
	RTMP* m_pRtmp;
}; 

/*!
    @brief Rtmp Muxer
*/
class LkRtmpMuxer
{
public:
    LkRtmpMuxer();

    /*!
        @param data point to one NALU
    */
    int addH264(const LkStream &data, unsigned long long dts);

    /*!
        @param data point to one audio frame
    */
    int addAAC(const LkStream &data, unsigned long long dts);

    int setMetaData(const FlvMetaData &metaData);

	int setMetaData(const FlvMetaData &metaData, LkStream &body_data);
    /*!
        @param url a complete RTMP URL
    */
    void setRtmpUrl(const string &url);

    /*!
        @brief do following:

        1. connect to server
        2. gen metadata
    */
    int start();

     /*!
        @brief stop muxer.
                       
      */
    int stop();

private:
    string genSequenceHeader();
    string genSPS();
    string genVideoFrame(char *data, int size, unsigned long long pts, unsigned long long dts, bool keyframe);
    string genAudioFrame(char *data, int size, bool sequence);
    int addH264Internal(char *data, int size, unsigned long long pts, unsigned long long dts);
    int addAACInternal(char *data, int size, unsigned long long pts);

private:
    RtmpAU *m_rtmpAU;
    string m_rtmpUrl;
    string m_metaData;
    string m_cachedSPS;
    string m_cachedPPS;
};

#define TRUE 1
#define FALSE 0

#endif // LkRtmpMuxer_H
