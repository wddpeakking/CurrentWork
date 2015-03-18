#ifndef _LK_ENCODER_H_
#define _LK_ENCODER_H_

#include "lkthread.h"
class LkX264Encoder;
class LkEncoderThread :
	public LkThread
{
	Q_OBJECT
public:
	explicit LkEncoderThread(QObject *parent = 0);
	~LkEncoderThread();

	void init();
	void fini();
	void run();
	void setProcessThread(QThread *thread);

private:
	LkX264Encoder *m_x264Encoder;
	QThread * m_imageProcessThread;
};
#endif
