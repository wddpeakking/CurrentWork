

#include "LkAudioCapture.h"

#include <QString>
#include "LkUtil.h"
#include "LkLog.h"
#include "LkAVQueue.h"
#include "LkAudioEncoder_AAC.h"
#include "LkErrno.h"
#include "LkContext.h"
#include "LkDefine.h"
#include "LkAudioEncoder_MP3.h"

int handleAudioData(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *data)
{
    Q_UNUSED(outputBuffer)
    Q_UNUSED(streamTime)
    Q_UNUSED(status)

    LkAudioCapture *grabber = static_cast<LkAudioCapture *>(data);

    int bytesReady = nBufferFrames * 16 / 8 * grabber->m_channels;

    grabber->onDataCaptured((char*)inputBuffer, bytesReady);

    return LK_SUCESS;
}

LkAudioCapture::LkAudioCapture(QObject *parent)
    : LkThread(parent)
    , m_grabEngine(NULL)
    , m_audioEncoder(NULL)
    , m_hasSendHeader(false)
    , m_bitDepth(RTAUDIO_SINT16)
    , m_sampleRate(44100)
    , m_channels(2)
    , m_bitrate(96000)
{

}

LkAudioCapture::~LkAudioCapture()
{

}

void LkAudioCapture::run()
{
    m_stop = false;

    while (!m_stop) {
        int frameSize = m_audioEncoder->getFrameSize();

        m_mutex.lock();

        if (m_bytesCache.size() < frameSize) {
            m_mutex.unlock();
            msleep(10);
            continue;
        }

        while (m_bytesCache.size() >= frameSize) {
            QByteArray frame = m_bytesCache.mid(0, frameSize);
            m_bytesCache.remove(0, frameSize);

            QByteArray outputArray;
            if (!m_audioEncoder->encode(frame, outputArray)) {
                stopCapture();
                log_error("encode audio failed.");
                return;
            }

            if (outputArray.size() > 2) {
                LkAudioPacket *pkt = new LkAudioPacket(Audio_Type_AAC);
                pkt->data.writeString(LkString(outputArray.data(), outputArray.size()));
                pkt->dts = LkAVQueue::instance()->timestampBuilder()->addAudioFrame();
                pkt->ready = true;
                LkAVQueue::instance()->enqueue(pkt);
            }
        }

        m_mutex.unlock();
    }

    log_trace("LkAudioCapture Thread exit normally");
}

QHash<int, QString> LkAudioCapture::availableDevices()
{
    RtAudio rtAudio;
    int deviceCount = rtAudio.getDeviceCount();
    RtAudio::DeviceInfo info;
    QHash<int, QString> devices;

    for (int i = 0; i < deviceCount; ++i) {
        info = rtAudio.getDeviceInfo(i);

        if (info.inputChannels > 0) {
            devices.insert(i, QString::fromStdString(info.name));
        }
    }

    return devices;
}

int LkAudioCapture::startCapture(int bitrate, int sampleRate, int channels, int deviceID)
{
    m_bitrate = bitrate;
    m_sampleRate = sampleRate;
    m_channels = channels;

    //QString audioFormat = LkOption::instance()->option("format", "audio").toString();
	QString audioFormat = LkConfigOpt::Instance()->str_Lk_Audio_Format;
    if (audioFormat == "AAC") {
        m_audioEncoder = new LkAudioEncoder_AAC;
    } else if (audioFormat == "MP3") {
        // TODO impl
		m_audioEncoder = new LkAudioEncoder_MP3;
    }

    LkAssert(m_audioEncoder);

    if (!m_audioEncoder->init(m_sampleRate, m_channels, m_bitrate)) {
        log_error("audio encoder error");
        return LK_AUDIO_INIT_ERROR;
    }

    if (m_audioEncoder->encoderType() == LkAudioEncoderAbstract::AAC) {
        // update audio sh
        LkAudioPacket *pkt = new LkAudioPacket(Audio_Type_AAC);
        QByteArray arr = dynamic_cast<LkAudioEncoder_AAC*>(m_audioEncoder)->getHeader();
        pkt->data.writeString(arr.data(), arr.size());
        pkt->ready = true;
        pkt->dts = 0;

        appCtx->setAudioSh(pkt);
    }

    m_grabEngine = new RtAudio;

    unsigned int bufferFrames = 2048;
    RtAudio::StreamParameters params;

    if (deviceID == -1) {
        deviceID = m_grabEngine->getDefaultInputDevice();
    }
    params.deviceId = deviceID;
    params.nChannels = m_channels;
    params.firstChannel = 0;

    try {
        m_grabEngine->openStream(NULL, &params, m_bitDepth, m_sampleRate, &bufferFrames, &handleAudioData, this);
        m_grabEngine->startStream();
    } catch (RtError& e) {
        e.printMessage();
        LkFree(m_grabEngine);

        return LK_AUDIO_DEVICE_OPEN_ERROR;
    }

    LkAVQueue::instance()->timestampBuilder()->
            setAudioCaptureInternal(m_audioEncoder->getFrameDuration());

    start();

    return LK_SUCESS;
}

int LkAudioCapture::stopCapture()
{
    if (m_grabEngine)
        m_grabEngine->closeStream();

    LkFree(m_grabEngine);

    if (m_audioEncoder) {
        m_audioEncoder->fini();
    }
    LkFree(m_audioEncoder);

    return LK_SUCESS;
}

void LkAudioCapture::onDataCaptured(char *data, int size)
{
    m_mutex.lock();
    m_bytesCache.append(data, size);

    if (m_bytesCache.size() >= m_audioEncoder->getFrameSize()) {
        m_mutex.unlock();

        m_waitCondtion.wakeOne();
    } else {
        m_mutex.unlock();
    }
}
