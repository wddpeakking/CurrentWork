#ifndef _LK_CONFIG_H_
#define  _LK_CONFIG_H_

#include "LkDefine.h"
class LkConfigOpt
{
public:
	LkConfigOpt(void);
	~LkConfigOpt(void);

	static LkConfigOpt* Instance();
	void ReadConfig();
	void WriteConfig();

	void ReadXmlConfig();
	void WriteXmlConfig();
	int GetWidth(const QString& str );
	int GetHeight(const QString& str );

public:
	static LkConfigOpt* m_pConfigOpt; //实例

	//video
	//audio
	int n_Lk_Audio_DeviceId;
	QString str_Lk_Audio_Format;
	QString str_Lk_Audio_Channels;
	int n_Lk_Audio_SampleRate;
	int n_Lk_Audio_Bitrate;

	//x264
	QString str_Lk_x264_Preset;
	QString str_Lk_x264_Tune;
	QString str_Lk_x264_Profile;
	QString str_Lk_x264_BitrateMode;
	int n_Lk_x264_KeyFrameInterval;
	int n_Lk_x264_Quality;
	int n_Lk_x264_ThreadCount;
	bool b_Lk_x264_EnableBFrame;

	//encoder
	QString str_Lk_Encoder_Format;
	QSize size_Lk_Encoder_Scale;
	int n_Lk_Encoder_Fps;
	int n_Lk_Encoder_Bitrate;

	//network
	QString str_Lk_NetWork_URL;

	//other
	bool b_Lk_Min;			//开始推送时是否最小化
	bool b_Lk_Mouse;		//是否隐藏鼠标
	bool b_Lk_Aero;			//是否关闭Aero特效
	bool b_Lk_DesktopMin;	//添加桌面源时自动最小化

	//save path
	QString str_Lk_SavePath;

	//是否保存
	bool b_Lk_SaveFile;

	//version
	QString str_Lk_Version;
};
#endif
