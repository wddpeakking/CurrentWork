#include "LkX264Encoder.h"

#include "LkUtil.h"
#include "LkAVUtil.h"
#include "LkAVQueue.h"
#include "LkContext.h"
#include "LkErrno.h"
#include "LkDefine.h"

#include <QSize>
#include <QDebug>

LkX264Encoder::LkX264Encoder()
	: m_x264Param(NULL)
	, m_pictureIn(NULL)
	, m_x264Encoder(NULL)
	, bFirstFrameProcessed(false)
	, frameShift(0)
{
}

LkX264Encoder::~LkX264Encoder()
{
	fini();
}

int LkX264Encoder::init()
{
	QString presetName  = LkConfigOpt::Instance()->str_Lk_x264_Preset;
	QString tuneName    = LkConfigOpt::Instance()->str_Lk_x264_Tune;
	QString profileName = LkConfigOpt::Instance()->str_Lk_x264_Profile;
	int fps = LkConfigOpt::Instance()->n_Lk_Encoder_Fps;
	int kbps = LkConfigOpt::Instance()->n_Lk_Encoder_Bitrate;

	//QSize wh = option->option("res", "encoder").toSize();
	QSize wh = LkConfigOpt::Instance()->size_Lk_Encoder_Scale;
	int width = wh.width();
	int height = wh.height();

	int maxBitRate = kbps;
	int bufferSize = maxBitRate;
	bool bUseCBR = (LkConfigOpt::Instance()->str_Lk_x264_BitrateMode == "CBR");
	int quality = LkConfigOpt::Instance()->n_Lk_x264_Quality;
	int KeyFrameInterval = LkConfigOpt::Instance()->n_Lk_x264_KeyFrameInterval;
	int threadCount = LkConfigOpt::Instance()->n_Lk_x264_ThreadCount;
	bool enableBFrame = LkConfigOpt::Instance()->b_Lk_x264_EnableBFrame;
	

	m_x264Param = new x264_param_t;

	if (tuneName == "default" || tuneName.isEmpty()) {
		x264_param_default_preset(m_x264Param , presetName.toStdString().c_str(), NULL);
		log_trace("libx264 preset set to %s, tune set to NULL"
			, presetName.toStdString().c_str());
	} else {
		x264_param_default_preset(m_x264Param , presetName.toStdString().c_str(), tuneName.toStdString().c_str());
		log_trace("libx264 preset set to %s, tune set to %s"\
			, presetName.toStdString().c_str(), tuneName.toStdString().c_str());
	}

	if (profileName != "default") {
		x264_param_apply_profile(m_x264Param, profileName.toStdString().c_str());
		log_trace("libx264 profile set to %s", profileName.toStdString().c_str());
	} else {
		log_trace("libx264 profile set to Default");
	}

	if(bUseCBR)
	{
		m_x264Param->rc.i_bitrate          = maxBitRate;
		m_x264Param->rc.i_vbv_max_bitrate  = maxBitRate; // vbv-maxrate
		m_x264Param->rc.i_vbv_buffer_size  = bufferSize; // vbv-bufsize
		m_x264Param->i_nal_hrd             = X264_NAL_HRD_CBR;
		m_x264Param->rc.i_rc_method        = X264_RC_ABR;
		m_x264Param->rc.f_rf_constant      = 0.0f;
	}
	else
	{
		m_x264Param->rc.i_vbv_max_bitrate  = maxBitRate;  // vbv-maxrate
		m_x264Param->rc.i_vbv_buffer_size  = bufferSize;  // vbv-bufsize
		m_x264Param->rc.i_rc_method        = X264_RC_CRF; // X264_RC_CRF;
		m_x264Param->rc.f_rf_constant      = quality;

		log_trace("libx264 quality set to %d", quality);
	}

	m_x264Param->b_vfr_input           = 1;
	m_x264Param->i_keyint_max          = fps * KeyFrameInterval;
	m_x264Param->i_width               = width;
	m_x264Param->i_height              = height;
	m_x264Param->vui.b_fullrange       = 0;          //specify full range input levels

	m_x264Param->i_fps_num = fps;
	m_x264Param->i_fps_den = 1;

	m_x264Param->i_timebase_num = 1;
	m_x264Param->i_timebase_den = 1000;

	// disable start code 00 00 00 01 before NAL
	// instead of nalu size
	m_x264Param->b_repeat_headers = 0;
	m_x264Param->b_annexb = 0;

	if (enableBFrame)
		m_x264Param->i_bframe = 3;
	else
		m_x264Param->i_bframe = 0;

	if (threadCount > 0)
		m_x264Param->i_threads = threadCount;

	// @note
	// never use cpu capabilities.
	// let libx264 to choose.
#if 0
	m_x264Param->cpu = 0;
	m_x264Param->cpu |=X264_CPU_MMX;
	m_x264Param->cpu |=X264_CPU_MMXEXT;
	m_x264Param->cpu |=X264_CPU_SSE;
#endif

	m_x264Encoder = x264_encoder_open(m_x264Param);

	// update video sh
	x264_nal_t *nalOut;
	int nalNum;
	x264_encoder_headers(m_x264Encoder, &nalOut, &nalNum);

	for (int i = 0; i < nalNum; ++i) {
		x264_nal_t &nal = nalOut[i];
		if (nal.i_type == NAL_SPS) {
			LkVideoPacket *pkt = new LkVideoPacket(Video_Type_H264);
			pkt->dts = 0;

			LkStream &body = pkt->data;

			// SPS Serialize
			body.write1Bytes(0x17);
			body.write1Bytes(0x00);
			body.write3Bytes(0x00);
			body.write1Bytes(0x01);
			body.writeString((char*)nal.p_payload + 5, 3);
			body.write1Bytes(0xff);
			body.write1Bytes(0xe1);
			body.write2Bytes(nal.i_payload - 4);
			body.writeString((char*)nal.p_payload + 4, nal.i_payload - 4);

			//the PPS always comes after the SPS
			x264_nal_t &pps = nalOut[++i];

			// PPS Serialize
			body.write1Bytes(0x01);
			body.write2Bytes(pps.i_payload - 4);
			body.writeString(LkString((char*)pps.p_payload + 4, pps.i_payload - 4));

			appCtx->setVideoSh(pkt);
		} else if (nal.i_type == NAL_SEI) {
			LkVideoPacket *seiPkt = new LkVideoPacket(Video_Type_H264);
			seiPkt->dts = 0;
			seiPkt->ready = true;

			LkStream &seiBody = seiPkt->data;
			int skipBytes = 4;
			int newPayloadSize = (nal.i_payload - skipBytes);

			unsigned char flshFrameType = 0x17;
			seiBody.write1Bytes(flshFrameType);
			seiBody.write1Bytes(0x01);
			seiBody.write3Bytes(0x00);
			seiBody.write4Bytes(newPayloadSize);
			seiBody.writeString((char*)nal.p_payload + skipBytes, newPayloadSize);

			LkAVQueue::instance()->enqueue(seiPkt);
		}
	}

	m_pictureIn = new x264_picture_t;
	m_pictureIn->i_pts = 0;

	return LK_SUCESS;
}

int LkX264Encoder::encode(unsigned char *rgbframe, mint64 pts)
{
	unsigned char *src_buf = rgbframe;
	x264_picture_init(m_pictureIn);

	m_pictureIn->img.i_csp = X264_CSP_I420;
	m_pictureIn->img.i_plane = 3;
	m_pictureIn->i_type = X264_TYPE_AUTO;
	m_pictureIn->i_qpplus1 = 0;

	m_pictureIn->i_pts = pts;

	m_pictureIn->img.plane[0] = src_buf;
	m_pictureIn->img.plane[1] = src_buf + m_x264Param->i_height * m_x264Param->i_width;
	m_pictureIn->img.plane[2] = src_buf + m_x264Param->i_height * m_x264Param->i_width * 5 / 4;
	m_pictureIn->img.i_stride[0] = m_x264Param->i_width;
	m_pictureIn->img.i_stride[1] = m_x264Param->i_width >> 1;
	m_pictureIn->img.i_stride[2] = m_x264Param->i_width >> 1;

	x264_picture_t picOut;
	int nalNum;
	x264_nal_t* nalOut;
	int len = x264_encoder_encode(m_x264Encoder, &nalOut, &nalNum, m_pictureIn, &picOut);
	if (len < 0) {
		log_error("x264 encode failed");
		return -1;
	}

	if (nalNum <= 0) {
		log_warn("frame delayed in encoder.");
		return -2;
	}

	if(!bFirstFrameProcessed && nalNum)
	{
		if(picOut.i_dts < 0)
			delayOffset = int(-picOut.i_dts);

		bFirstFrameProcessed = true;
	}

	// @see OBS Encoder_x264.cpp
	//
	int timeOffset = int(picOut.i_pts - picOut.i_dts);

	LkVideoPacket *pkt = dynamic_cast<LkVideoPacket *> (LkAVQueue::instance()->finPkt());
	LkAssert(pkt != NULL);

	LkStream &body = pkt->data;
	unsigned char frameType;
	if (IS_X264_TYPE_I(picOut.i_type)) {
		frameType = 0x17;
	} else {
		frameType = 0x27;
	}

	body.write1Bytes(frameType);
	body.write1Bytes(0x01);
	body.write3Bytes(timeOffset);

	// NALU payload : 4bytes size + payload
	// NALU payload size : 4bytes size + payload size
	// for b_repeat_headers = 0 in x264_param_t
	// so NALU type is only IDR, SLICE(P or B frame)
	// so you must get SPS PPS before encoding any frame.
	for (int i = 0; i < nalNum; ++i) {
		x264_nal_t &nal = nalOut[i];
		body.writeString((char*)nal.p_payload, nal.i_payload);
	}

	LkAVQueue::instance()->updatePkt(pkt);

	return 0;
}

int LkX264Encoder::getFrameDuration()
{
	int fps = LkConfigOpt::Instance()->n_Lk_Encoder_Fps;

	if (fps > 0) {
		return 1000 / fps;
	}

	// 40 ms : default duration
	return 40;
}

void LkX264Encoder::fini()
{
	LkFree(m_pictureIn);
	if (m_x264Encoder) {
		x264_encoder_close(m_x264Encoder);
	}
	LkFree(m_x264Param);
}
