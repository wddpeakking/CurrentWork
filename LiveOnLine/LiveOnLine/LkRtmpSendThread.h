#ifndef LkRtmpSendThread_H
#define LkRtmpSendThread_H

#include "LkThread.h"

#include <QMutex>
#include <QTimer>
#include <QList>
#include <QElapsedTimer>
#include "LkStream.h"
class LkRtmpMuxer;
class QFile;

class LkRtmpSendThread : public LkThread
{
	Q_OBJECT
public:
	LkRtmpSendThread(QObject * parent = 0);
	~LkRtmpSendThread();

	virtual void run();

private:
#ifdef Q_OS_WIN
	int wsaStart();
#endif
	int service(LkRtmpMuxer & muxer);

private:
	int sendVideoSh(LkRtmpMuxer & muxer);
	int sendAudioSh(LkRtmpMuxer & muxer);
	int sendMetadata(LkRtmpMuxer &muxer, LkStream &body);

	private slots:
		void onTimeout();

private:
	enum {
		FLV_TAG_METADATA = 0x12,
		FLV_TAG_VIDEO = 0x09,
		FLV_TAG_AUDIO = 0x08
	};

private:
	int on_record();
	int record(LkStream &data, qint64 dts, int flv_tag_type);
	int on_un_record();

private:
	int m_audio_send_bytes;
	int m_video_send_bytes;
	int m_fps;
	qint64 m_data_send_bytes;
	QMutex m_mutex;
	QTimer m_timer;

	struct kbps
	{
		float audio_avg;
		float video_avg;
		float fps;
	};

	QList<kbps> m_kbps;
	QElapsedTimer m_elapsed_timer;
	bool m_record_error;
	QFile *m_record_file;

signals:
	void status(int audioKbps, int videoKbps, int fps, qint64 sendDataCount);
};

#endif // LkRtmpSendThread_H
