#include "LkRtmpSendThread.h"

#include <QElapsedTimer>
#include <QDebug>
#include <QDateTime>
#include <QSize>
#include <QFile>
#include <QDir>

#include "LkRtmpMuxer.h"
#include "LkEncoderThread.h"
#include "LkLog.h"
#include "LkUtil.h"
#include "LkErrno.h"

#include "LkContext.h"
#include "LkDefine.h"
#ifdef Q_OS_WIN
#include "windows.h"
#endif

#include "LkAVQueue.h"

static char flv_header[] = {'F', 'L', 'V',
	0x01, 0x05, 0x00, 0x00, 0x00, 0x09,
	0x00, 0x00, 0x00, 0x00};

LkRtmpSendThread::LkRtmpSendThread(QObject * parent)
	: LkThread(parent)
	, m_audio_send_bytes(0)
	, m_video_send_bytes(0)
	, m_fps(0)
	, m_data_send_bytes(0)
{
	connect(&m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
	m_timer.setInterval(1000 * 1);
	m_timer.start();
	m_elapsed_timer.start();
}

LkRtmpSendThread::~LkRtmpSendThread()
{
	if (m_timer.isActive()) {
		m_timer.stop();
	}
}

void LkRtmpSendThread::run()
{
#ifdef Q_OS_WIN
	if (wsaStart()) {
		return;
	}
#endif

	int ret = LK_SUCESS;
	while (!m_stop) {
		QString url = LkConfigOpt::Instance()->str_Lk_NetWork_URL;

		if (url.isEmpty()) {
			log_error("no url was set, please input your rtmp url !");
			sleep(5);
			continue;
		}

		LkRtmpMuxer *muxer = new LkRtmpMuxer;
		LkAutoFree(LkRtmpMuxer, muxer);

		muxer->setRtmpUrl(url.toStdString());
		ret = muxer->start();
		if (ret != TRUE) {
			ret = LK_RTMPCONNECT_ERROR;
			log_error("connect to %s error, after 1s to retry", url.toStdString().c_str());

			muxer->stop();
			sleep(1);

			continue;
		}

		log_trace("connect to %s success.", url.toStdString().c_str());
		ret = service(*muxer);
		muxer->stop();

		if (ret != LK_SUCESS) {
			log_error("rtmp send error, ret = %d", ret);
			continue;
		}
	}

#ifdef Q_OS_WIN
	WSACleanup();
#endif

	log_trace("Ble RtmpSendThread exit normally.");
}

#ifdef Q_OS_WIN
int LkRtmpSendThread::wsaStart()
{
	WORD versionRequested;
	WSADATA wsaData;
	versionRequested = MAKEWORD(1, 1);

	return WSAStartup(versionRequested, &wsaData);
}
#endif

int LkRtmpSendThread::service(LkRtmpMuxer & muxer)
{
	int ret = LK_SUCESS;

	if (on_record() != LK_SUCESS) {
		log_trace("flv on_record error");
	}

	LkStream metadata_body;
	if ((ret = sendMetadata(muxer, metadata_body)) != LK_SUCESS) {
		return ret;
	}

	if ((ret = sendVideoSh(muxer)) != LK_SUCESS) {
		return ret;
	}

	if ((ret = sendAudioSh(muxer)) != LK_SUCESS) {
		return ret;
	}

	// write metadata
	record(metadata_body, 0, FLV_TAG_METADATA);

	// write video sh
	LkAVPacket *vs = appCtx->videoSh();
	if (vs) {
		record(vs->data, 0, FLV_TAG_VIDEO);
	}

	// write audio sh
	LkAVPacket *as = appCtx->audioSh();
	if (as) {
		record(as->data, 0, FLV_TAG_AUDIO);
	}

	while (!m_stop) {
		QQueue<LkAVPacket *> pkts = LkAVQueue::instance()->dequeue();
		if (pkts.isEmpty()) {
			msleep(50);
			continue;
		}

		LkAutoLocker(m_mutex);

		while (!pkts.empty()) {
			LkAVPacket *pkt = pkts.dequeue();
			LkAutoFree(LkAVPacket, pkt);

			LkStream &data = pkt->data;

			if (pkt->pktType == Packet_Type_Video) {
				if (muxer.addH264(data, pkt->dts) != TRUE ) {
					ret = LK_RTMPSEND_ERROR;
					break;
				}
				record(data, pkt->dts, FLV_TAG_VIDEO);

				m_video_send_bytes += data.size();
				m_fps += 1;
			} else if (pkt->pktType == Packet_Type_Audio) {
				if (muxer.addAAC(data, pkt->dts) != TRUE ) {
					ret = LK_RTMPSEND_ERROR;
					break;
				}
				record(data, pkt->dts, FLV_TAG_AUDIO);

				m_audio_send_bytes += data.size();
			}

			m_data_send_bytes += data.size();
		}

		// if send failed, then pkts may has some pkt
		// we should delete it.
		for (int i = 0; i < pkts.size(); ++i) {
			LkAVPacket *pkt = pkts.at(i);
			LkFree(pkt);
		}
	}
	on_un_record();

	return ret;
}

int LkRtmpSendThread::sendVideoSh(LkRtmpMuxer &muxer)
{
	int ret = LK_SUCESS;

	// if H264 send video sh
	LkAVPacket *pkt = appCtx->videoSh();
	if (pkt) {
		LkStream &data = pkt->data;
		if (muxer.addH264(data, pkt->dts) != TRUE ) {
			ret = LK_RTMPSEND_ERROR;
			return ret;
		}

		log_trace("H264 send video sh success");
	}

	return ret;
}

int LkRtmpSendThread::sendAudioSh(LkRtmpMuxer &muxer)
{
	int ret = LK_SUCESS;

	// if AAC, send audio sh
	LkAVPacket *pkt = appCtx->audioSh();
	if (pkt) {
		LkStream &data = pkt->data;
		if (muxer.addAAC(data, pkt->dts) != TRUE ) {
			ret = LK_RTMPSEND_ERROR;
			return ret;
		}

		log_trace("AAC send audio sh success");
	}

	return ret;
}

void LkRtmpSendThread::onTimeout()
{
	if (!m_mutex.tryLock()) return;

	int elapsed_ms = m_elapsed_timer.elapsed();

	float audioKbps = m_audio_send_bytes * 1000 / elapsed_ms;
	float videoKbps = m_video_send_bytes * 1000 / elapsed_ms;
	float fps = (float)m_fps * 1000.00 / (float)elapsed_ms;

	m_audio_send_bytes = 0;
	m_video_send_bytes = 0;
	m_fps = 0;

	m_elapsed_timer.restart();
	m_mutex.unlock();

	kbps bs = {audioKbps, videoKbps, fps};
	m_kbps.append(bs);

	// average value
	if (m_kbps.size() > 10) m_kbps.removeFirst();

	float audioKbpsAll = 0;
	float videoKbpsAll = 0;
	float fpsALl = 0;
	for (int i = 0; i < m_kbps.size(); ++i) {
		const kbps &bs = m_kbps.at(i);
		audioKbpsAll += bs.audio_avg;
		videoKbpsAll += bs.video_avg;
		fpsALl += bs.fps;
	}

	audioKbps = audioKbpsAll / m_kbps.size();
	videoKbps = videoKbpsAll / m_kbps.size();
	fps = fpsALl / m_kbps.size();

	emit status(audioKbps, videoKbps, fps, m_data_send_bytes);
}

int LkRtmpSendThread::on_record()
{

	if (!LkConfigOpt::Instance()->b_Lk_SaveFile)
	{
		m_record_error = true;
		return -1;
	}
	m_record_error = false;

	// video save
	QString dir = LkConfigOpt::Instance()->str_Lk_SavePath;
	if (dir.isEmpty()) {
		m_record_error = true;
		log_error("record dir is not set.");
		return -1;
	}

	QDir temp;
	if (!temp.mkpath(dir)) {
		log_error("mkdir error, dir=%s", dir.toStdString().c_str());
		m_record_error = true;
		return -1;
	}

	QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
	QString flv_name = dir + "/" + current_time + ".flv";
	m_record_file = new QFile(flv_name);
	if (!m_record_file->open(QIODevice::WriteOnly)) {
		log_error("open flv file error, file=%s", flv_name.toStdString().c_str());
		m_record_error = true;
		LkFree(m_record_file);
		return -1;
	}

	// write flv header
	if (m_record_file->write(flv_header, 13) < 0) {
		m_record_error = true;
		m_record_file->close();
		LkFree(m_record_file);
		return -1;
	}

	return LK_SUCESS;
}

int LkRtmpSendThread::record(LkStream &data, qint64 dts, int flv_tag_type)
{
	if (m_record_error) return LK_SUCESS;

	LkStream stream;

	// tag header
	mint8 type = flv_tag_type;

	int payload_size = data.length();

	stream.write1Bytes(type);
	stream.write3Bytes(payload_size);
	stream.write3Bytes(dts);
	stream.write1Bytes(dts >> 24 & 0xFF);
	stream.write3Bytes(0);
	stream.writeString(data);

	// pre tag size
	int preTagSize = payload_size + 11;
	stream.write4Bytes(preTagSize);

	// write flv tag
	if (m_record_file->write(stream.data(), stream.length()) < 0) {
		log_error("write flv tag error, disable record.");
		m_record_error = true;
		m_record_file->close();
		LkFree(m_record_file);
		return -1;
	}
	m_record_file->flush();

	return LK_SUCESS;
}

int LkRtmpSendThread::on_un_record()
{
	if (m_record_error) return LK_SUCESS;

	if (m_record_file && m_record_file->isOpen()) {
		log_trace("record finished. file save to %s"
			, m_record_file->fileName().toStdString().c_str());

		m_record_file->close();
		LkFree(m_record_file);
	}

	m_record_error = false;

	return LK_SUCESS;
}

int LkRtmpSendThread::sendMetadata(LkRtmpMuxer & muxer, LkStream &body)
{
	int ret = LK_SUCESS;

	QSize wh = LkConfigOpt::Instance()->size_Lk_Encoder_Scale;

	int audiocodecid = CODECID_AAC;
	int audiodatarate = LkConfigOpt::Instance()->n_Lk_Encoder_Bitrate;
	int audiodelay = 0;
	int audiosamplerate = LkConfigOpt::Instance()->n_Lk_Audio_SampleRate;
	int audiosamplesize = 1024;
	bool canSeekToEnd = false;

	int duration = 0;
	int filesize = 0;
	int framerate = LkConfigOpt::Instance()->n_Lk_Encoder_Fps;
	int height = wh.height();
	bool stereo = LkConfigOpt::Instance()->str_Lk_Audio_Channels == "Stereo" ? true : false;
	int videocodecid = CODECID_H264;
	int videodatarate = LkConfigOpt::Instance()->n_Lk_Encoder_Bitrate;
	int width = wh.width();;

	FlvMetaData *meta = new FlvMetaData;
	LkAutoFree(FlvMetaData, meta);
	meta->audiocodecid = audiocodecid;
	meta->audiodatarate = audiodatarate;
	meta->audiodelay = audiodelay;
	meta->audiosamplerate = audiosamplerate;
	meta->audiosamplesize = audiosamplesize;
	meta->canSeekToEnd = canSeekToEnd;
	meta->duration = duration;
	meta->filesize = filesize;
	meta->framerate = framerate;
	meta->height = height;
	meta->stereo = stereo;
	meta->videocodecid = videocodecid;
	meta->videodatarate = videodatarate;
	meta->width = width;
	meta->creationdate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();

	if ((ret = muxer.setMetaData(*meta, body)) != TRUE) {
		return LK_RTMPSEND_ERROR;
	}

	return LK_SUCESS;
}
