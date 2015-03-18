#include "LkConfigOpt.h"
#include <QDir>
#include <QSettings>
#include <QVariant>
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

LkConfigOpt* LkConfigOpt::m_pConfigOpt = 0;

LkConfigOpt::LkConfigOpt(void)
{
	//audio
	n_Lk_Audio_DeviceId = 0;
	str_Lk_Audio_Format = "AAC";
	str_Lk_Audio_Channels = "Stereo";
	n_Lk_Audio_SampleRate = 44100;
	n_Lk_Audio_Bitrate = 96;

	//x264
	str_Lk_x264_Preset = "superfast";
	str_Lk_x264_Tune = "default";
	str_Lk_x264_Profile = "baseline";
	str_Lk_x264_BitrateMode = "CBR";
	n_Lk_x264_KeyFrameInterval = 9;
	n_Lk_x264_Quality = 29;
	n_Lk_x264_ThreadCount = 8;
	b_Lk_x264_EnableBFrame = true;

	//encoder
	str_Lk_Encoder_Format = "H264";
	size_Lk_Encoder_Scale = QSize(800,600);
	n_Lk_Encoder_Fps = 15;
	n_Lk_Encoder_Bitrate = 400;

	//network
	str_Lk_NetWork_URL = "rtmp://192.168.41.234/live/wdd";

	//other
	b_Lk_Min = false;
	b_Lk_Mouse = false;
	b_Lk_Aero = false;

	//Savepath
	str_Lk_SavePath = "d:/";
	b_Lk_SaveFile = false;
}


LkConfigOpt::~LkConfigOpt(void)
{
	if (m_pConfigOpt)
	{
		delete m_pConfigOpt;
		m_pConfigOpt = NULL;
	}
}

LkConfigOpt* LkConfigOpt::Instance()
{
	if (!m_pConfigOpt)
	{
		m_pConfigOpt = new LkConfigOpt();
	}
	return m_pConfigOpt;
}

int LkConfigOpt::GetWidth(const QString& str )
{
	int nWidth = -1;
	if (str.isEmpty())
	{
		return nWidth;
	}
	QString strVal = str.trimmed();
	nWidth = strVal.left(strVal.lastIndexOf("x")).toInt();
	return nWidth;
}

int LkConfigOpt::GetHeight(const QString& str )
{
	int nHeight = -1;
	if (str.isEmpty())
	{
		return nHeight;
	}
	QString strVal = str.trimmed();
	nHeight = strVal.right(strVal.length()-strVal.lastIndexOf("x")-1).toInt();
	return nHeight;
}


void LkConfigOpt::ReadXmlConfig()
{
	QString strConfigPath = QDir::currentPath()+g_strConfigName;
	QFile file(strConfigPath);
	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		QDomDocument    document;
		int nCol = -1;
		int nRow = -1;
		QString strError;
		if( document.setContent(&file, false, &strError, &nRow, &nCol) ) 
		{
			if (!document.isNull())
			{
				QString strValue = "";
				QDomElement root = document.documentElement();
				if (root.tagName() == "config")
				{
					strValue  = root.attribute("version","0.0");
					str_Lk_Version = strValue;
					QDomElement firstChild = root.firstChildElement();
					while (!firstChild.isNull())
					{
						 for(int i = 0;i < firstChild.childNodes().size();i++)
						 {
							QDomElement element =   firstChild.childNodes().at(i).toElement();
							if (element.tagName() == "size")
							{
								strValue  = element.attribute("value","800x600");
								size_Lk_Encoder_Scale = QSize(GetWidth(strValue),GetHeight(strValue));
							}
							else if (element.tagName() == "fps")
							{
								n_Lk_Encoder_Fps  = element.attribute("value","15").toInt();
							}
							else if (element.tagName() == "rate")
							{
								n_Lk_Encoder_Bitrate  = element.attribute("value","500").toInt();
							}
							else if (element.tagName() == "min")
							{
								b_Lk_Min  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "mouse")
							{
								b_Lk_Mouse  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "aero")
							{
								b_Lk_Aero  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "desktopMin")
							{
								b_Lk_DesktopMin  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "savefile")
							{
								b_Lk_SaveFile  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "savepath")
							{
								str_Lk_SavePath  = element.attribute("value","");
							}
							else if (element.tagName() == "encoder")
							{
								str_Lk_Encoder_Format  = element.attribute("value","h264");
							}
							else if (element.tagName() == "psy")
							{
								str_Lk_x264_Tune  = element.attribute("value","default");
							}
							else if (element.tagName() == "profile")
							{
								str_Lk_x264_Profile  = element.attribute("value","default");
							}
							else if (element.tagName() == "keyframe")
							{
								n_Lk_x264_KeyFrameInterval  = element.attribute("value","6").toInt();
							}
							else if (element.tagName() == "threadcount")
							{
								n_Lk_x264_ThreadCount  = element.attribute("value","8").toInt();
							}
							else if (element.tagName() == "mode")
							{
								str_Lk_x264_BitrateMode  = element.attribute("value","CBR");
							}
							else if (element.tagName() == "Bkeyframe")
							{
								b_Lk_x264_EnableBFrame  = element.attribute("value","true") == "true"?true:false;
							}
							else if (element.tagName() == "quality")
							{
								n_Lk_x264_Quality  = element.attribute("value","35").toInt();
							}
							else if (element.tagName() == "audiodevice")
							{
								n_Lk_Audio_DeviceId  = element.attribute("value","0").toInt();
							}
							else if (element.tagName() == "audioencoder")
							{
								str_Lk_Audio_Format  = element.attribute("value","AAC");
							}
							else if (element.tagName() == "channel")
							{
								str_Lk_Audio_Channels  = element.attribute("value","Stereo");
							}
							else if (element.tagName() == "samplingrate")
							{
								n_Lk_Audio_SampleRate  = element.attribute("value","44100").toInt();
							}
							else if (element.tagName() == "audiorate")
							{
								n_Lk_Audio_Bitrate  = element.attribute("value","96").toInt();
							}
							else if (element.tagName() == "url")
							{
								str_Lk_NetWork_URL  = element.attribute("value","");
							}
							else
							{

							}
							
						 }
							
						 firstChild = firstChild.nextSiblingElement();
					 }
				}
			}
				
		}
		file.close();
	}
		
}
void LkConfigOpt::WriteXmlConfig()
{
	QString strConfigPath = QDir::currentPath()+g_strConfigName;
	QFile file(strConfigPath);
	if(file.open(QFile::ReadOnly | QFile::Text))
	{
		QDomDocument    document;
		int nCol = -1;
		int nRow = -1;
		QString strError;
		if( document.setContent(&file, false, &strError, &nRow, &nCol) ) 
		{
			if (!document.isNull())
			{
				QString strValue = "";
				QDomElement root = document.documentElement();
				if (root.tagName() == "config")
				{
					QDomElement firstChild = root.firstChildElement();
					while (!firstChild.isNull())
					{
						for(int i = 0;i < firstChild.childNodes().size();i++)
						{
							QDomElement element =   firstChild.childNodes().at(i).toElement();
							if (element.tagName() == "size")
							{
								element.setAttribute("value",QString("%1x%2").arg(size_Lk_Encoder_Scale.width()).arg(size_Lk_Encoder_Scale.height()));
							}
							else if (element.tagName() == "fps")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_Encoder_Fps));
							}
							else if (element.tagName() == "rate")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_Encoder_Bitrate));
							}
							else if (element.tagName() == "min")
							{
								element.setAttribute("value",b_Lk_Min == true?"true":"false");
							}
							else if (element.tagName() == "mouse")
							{
								element.setAttribute("value",b_Lk_Mouse == true?"true":"false");
							}
							else if (element.tagName() == "aero")
							{
								element.setAttribute("value",b_Lk_Aero == true?"true":"false");
							}
							else if (element.tagName() == "desktopMin")
							{
								element.setAttribute("value",b_Lk_DesktopMin == true?"true":"false");
							}
							else if (element.tagName() == "savefile")
							{
								element.setAttribute("value",b_Lk_SaveFile == true?"true":"false");
							}
							else if (element.tagName() == "savepath")
							{
								element.setAttribute("value",str_Lk_SavePath);
							}
							else if (element.tagName() == "encoder")
							{
								element.setAttribute("value",str_Lk_Encoder_Format);
							}
							else if (element.tagName() == "psy")
							{
								element.setAttribute("value",str_Lk_x264_Tune);
							}
							else if (element.tagName() == "profile")
							{
								element.setAttribute("value",str_Lk_x264_Profile);
							}
							else if (element.tagName() == "keyframe")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_x264_KeyFrameInterval));
							}
							else if (element.tagName() == "threadcount")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_x264_ThreadCount));
							}
							else if (element.tagName() == "mode")
							{
								element.setAttribute("value",str_Lk_x264_BitrateMode);
							}
							else if (element.tagName() == "Bkeyframe")
							{
								element.setAttribute("value",b_Lk_x264_EnableBFrame == true?"true":"false");
							}
							else if (element.tagName() == "quality")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_x264_Quality));
							}
							else if (element.tagName() == "audiodevice")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_Audio_DeviceId));
							}
							else if (element.tagName() == "audioencoder")
							{
								element.setAttribute("value",str_Lk_Audio_Format);
							}
							else if (element.tagName() == "channel")
							{
								element.setAttribute("value",str_Lk_Audio_Channels);
							}
							else if (element.tagName() == "samplingrate")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_Audio_SampleRate));
							}
							else if (element.tagName() == "audiorate")
							{
								element.setAttribute("value",QString("%1").arg(n_Lk_Audio_Bitrate));
							}
							else if (element.tagName() == "url")
							{
								element.setAttribute("value",str_Lk_NetWork_URL);
							}
							else
							{

							}
						}
						firstChild = firstChild.nextSiblingElement();
					}
				}
			}
		}
		file.close();
		QFile fileModify(strConfigPath);  
		if (fileModify.open(QFile::WriteOnly | QFile::Text))
		{  
			QTextStream out(&fileModify);  
			document.save(out,4);  
			fileModify.close();  
		}  
	}
}
