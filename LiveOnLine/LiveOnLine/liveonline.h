#ifndef LIVEONLINE_H
#define LIVEONLINE_H

#include <QtWidgets/QWidget>
#include <QThread>
#include <QLabel>
#include <QDateTime>
class LkImageProcessWidget;
class LkImageProcessThread;
class LkEncoderThread;
class LkRtmpSendThread;
class LkAudioCapture;
class LkButton;
class QPushButton;
class LkSendTime;
class QLabel;
class QTopWidget;
class ShowTime;

class LiveOnLine : public QWidget
{
	Q_OBJECT

public:
	LiveOnLine(QWidget *parent = 0);
	~LiveOnLine();

	friend class ShowTime;
	public slots:
		void OnActionAddText();			//相应添加文字
		void OnActionAddImage();		//相应添加图片
		void OnActionAddCamera();		//相应添加相机
		void OnActionAddDesktop();		//相应添加桌面
		void OnActionAddVideoFile();	//相应添加视频文件
		void OnActionStartorEndRtmp();	//响应开始推流
		void OnActionSetting();			//设置

		void MouseMovePos(const QPoint& pt);


private:
	void Init(); //初始参数

	void Update(bool b);	//更新界面

	//void ShowCurrentTime(const QString& str){m_pLabelMsg->setText(str);};


private:
	LkImageProcessWidget* m_pImageProcessWidget;	//显示对话框
	LkImageProcessThread* m_pImageThread;	//传输线程
	LkEncoderThread* m_pEncoderThread;		//编码线程
	LkRtmpSendThread* m_pRtmpThread;		//rtmp线程
	LkAudioCapture *m_pAudioCaptureThread;	//音频线程

	bool m_bSnedToRtmp;						//发送、停止推流
	LkButton* m_pPushToRtmpBtn;				//推送，停止按钮	
	LkButton* m_pBtnSetting;				//设置按钮
	//QLabel* m_pLabelMsg;					//显示消息

	LkSendTime* m_pCurrentSendTime;			//获取发送时间
	QString m_strSentStartTime;				//开始发送时间

	QTopWidget* m_pTopWidget;				//上部标题栏
	QWidget* m_pBottomWidget;				//上部标题栏

};

//显示时间
class ShowTime : public QThread
{
	Q_OBJECT
public:
	ShowTime(){};
	~ShowTime(){};
signals:
	void currentTime(const QString& str);
public:
	void run()
	{
		while (true)
		{
			QDateTime time = QDateTime::currentDateTime();
			QString current_date = time.toString("\thh:mm:ss");
			emit currentTime(current_date);
		}
	};
};

#endif // LIVEONLINE_H
