#ifndef _LK_X264_H_
#define _LK_X264_H_

#include <stdint.h>
extern "C"{
#include "x264.h"
}

#include <QObject>
#include <QList>

#include "LkStream.h"
class LkVideoPacket;

class LkX264Encoder
{
public:
	LkX264Encoder(void);
	~LkX264Encoder(void);

	int init();
	int encode(unsigned char *rgbframe, mint64 pts);

	int getFrameDuration();

private:
	void fini();

private:
	x264_param_t * m_x264Param;
	x264_picture_t *m_pictureIn;
	x264_t *m_x264Encoder;
	int delayOffset;
	bool bFirstFrameProcessed;
	int frameShift;
};

#endif
