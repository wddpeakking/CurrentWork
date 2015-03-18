#include "LkSettingDlg.h"
#include "RtAudio.h"
#include "LkDefine.h"
#include <QFileDialog>
LkSettingDlg::LkSettingDlg(QWidget* pWidget)
	:QDialog(pWidget)
{
	ui.setupUi(this);
	Init();
}


LkSettingDlg::~LkSettingDlg(void)
{
}

void LkSettingDlg::Init()
{
	ui.tabWidget->tabBar()->hide();
	ui.tabWidget->setCurrentIndex(0);
	connect(ui.pushButton_More,SIGNAL(clicked()),this,SLOT(OnActionMore()));
	connect(ui.pushButton_back,SIGNAL(clicked()),this,SLOT(OnActionBack()));
	connect(ui.okButton,SIGNAL(clicked()),this,SLOT(OnActionOk()));
	QStringList strVal;

	//this->setStyleSheet("background-color:rgb(255,255,255)");
	//this->setWindowFlags(Qt::FramelessWindowHint);
	//分辨率
	strVal<<"320x240"<<"480x360"<<"640x480"<<"800x600"<<"1024x768"<<"1280x800";
	ui.comboBox_LkFbl->addItems(strVal);
	ui.comboBox_LkFbl->setCurrentText(QString("%1x%2").arg(LkConfigOpt::Instance()->size_Lk_Encoder_Scale.width()).arg(LkConfigOpt::Instance()->size_Lk_Encoder_Scale.height()));

	//码率
	strVal.clear();
	strVal<<"400"<<"450"<<"500"<<"600"<<"800"<<"1000"<<"1200"<<"1500"<<"1800"<<"2000";
	ui.comboBox_LkMl->addItems(strVal);
	ui.comboBox_LkMl->setCurrentText(QString("%1").arg(LkConfigOpt::Instance()->n_Lk_Encoder_Bitrate));

	//FPS
	ui.spinBox_LkFPS->setSingleStep(1);
	ui.spinBox_LkFPS->setRange(1,60);
	ui.spinBox_LkFPS->setValue(LkConfigOpt::Instance()->n_Lk_Encoder_Fps);

	//启动是否最小化
	ui.checkBox_LkZxh->setChecked(LkConfigOpt::Instance()->b_Lk_Min);

	//是否显示鼠标
	ui.checkBox_LkXssb->setChecked(LkConfigOpt::Instance()->b_Lk_Mouse);
	
	//是否关闭aero
	ui.checkBox_LkAero->setChecked(LkConfigOpt::Instance()->b_Lk_Aero);

	//是否保存
	ui.checkBox_LkSaveFile->setChecked(LkConfigOpt::Instance()->b_Lk_SaveFile);
	if (!LkConfigOpt::Instance()->b_Lk_SaveFile)
	{
		ui.lineEdit_LkSavePath->setEnabled(false);
		ui.pushButton_SelectPath->setEnabled(false);
	}
	connect(ui.checkBox_LkSaveFile,SIGNAL(clicked()),this,SLOT(OnCheckSaveFlie()));
	connect(ui.pushButton_SelectPath,SIGNAL(clicked()),this,SLOT(OnActionSaveFlieSelect()));
	ui.lineEdit_LkSavePath->setText(LkConfigOpt::Instance()->str_Lk_SavePath);

	//添加桌面源时最小化
	ui.checkBox_LkDesktop->setChecked(LkConfigOpt::Instance()->b_Lk_DesktopMin);

	//高级

	//tonue
	strVal.clear();
	strVal<<"default"<<"film"<<"animation"<<"grain"<<"stillimage"<<"psnr"<<"ssim"<<"fastdecode"<<"zerolatency";
	ui.comboBox_LkPSYTj->addItems(strVal);
	ui.comboBox_LkPSYTj->setCurrentText(LkConfigOpt::Instance()->str_Lk_x264_Tune);

	//编码配置文件
	strVal.clear();
	strVal<<"default"<<"baseline"<<"main"<<"high"<<"high10"<<"high422"<<"high444";
	ui.comboBox_LkPzwj->addItems(strVal);
	ui.comboBox_LkPzwj->setCurrentText(LkConfigOpt::Instance()->str_Lk_x264_Profile);

	//关键帧数目
	strVal.clear();
	strVal<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
	ui.comboBox_LkGjzsm->addItems(strVal);
	ui.comboBox_LkGjzsm->setCurrentText(QString("%1").arg(LkConfigOpt::Instance()->n_Lk_x264_KeyFrameInterval));

	//x264 CPU 预设
	strVal.clear();
	strVal<<"ultrafast"<<"superfast"<<"veryfast"<<"faster"<<"fast"<<"medium"<<"slow"<<"slower"<<"veryslow"<<"placebo";
	ui.comboBox_LkCPUys->addItems(strVal);
	ui.comboBox_LkCPUys->setCurrentText(LkConfigOpt::Instance()->str_Lk_x264_Preset);


	//并行编码帧数
	strVal.clear();
	strVal<<"0"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"10";
	ui.comboBox_LkBxbmzs->addItems(strVal);
	ui.comboBox_LkBxbmzs->setCurrentText(QString("%1").arg(LkConfigOpt::Instance()->n_Lk_x264_ThreadCount));

	ui.checkBox_LkBgjz->setChecked(LkConfigOpt::Instance()->b_Lk_x264_EnableBFrame);

	//品质
	ui.spinBox_LkPz->setSingleStep(1);
	ui.spinBox_LkPz->setRange(1,50);
	ui.spinBox_LkPz->setValue(LkConfigOpt::Instance()->n_Lk_x264_Quality);

	//码率类型
	strVal.clear();
	strVal<<"CBR"<<"ABR";
	ui.comboBox_LkMllx->addItems(strVal);
	ui.comboBox_LkMllx->setCurrentText(LkConfigOpt::Instance()->str_Lk_x264_BitrateMode);
	if (LkConfigOpt::Instance()->str_Lk_x264_BitrateMode == "CBR")
	{
		ui.spinBox_LkPz->setEnabled(false);
	}
	else
	{
		ui.spinBox_LkPz->setEnabled(true);
	}
	connect(ui.comboBox_LkMllx,SIGNAL(currentTextChanged(const QString &)),this,SLOT(OnActionMLLXSelectChange(const QString &)));

	//设备
	RtAudio rtAudio;
	int deviceCount = rtAudio.getDeviceCount();
	RtAudio::DeviceInfo info;
	for (int i = 0; i < deviceCount; ++i) {
		info = rtAudio.getDeviceInfo(i);
		if (info.inputChannels > 0) {
			ui.comboBox_LkSb->addItem(QString::fromStdString(info.name));
		}
	}

	//编码格式
	strVal.clear();
	strVal<<"AAC"<<"MP3";
	ui.comboBox_LkBmgs->addItems(strVal);
	ui.comboBox_LkBmgs->setCurrentText(LkConfigOpt::Instance()->str_Lk_Audio_Format);

	//频道
	strVal.clear();
	strVal<<"Stereo"<<"Mono";
	ui.comboBox_LkPd->addItems(strVal);
	ui.comboBox_LkPd->setCurrentText(LkConfigOpt::Instance()->str_Lk_Audio_Channels);


	//采样率
	strVal.clear();
	strVal<<"44100"<<"22050"<<"48000";
	ui.comboBox_LkCyl->addItems(strVal);
	ui.comboBox_LkCyl->setCurrentText(QString("%1").arg(LkConfigOpt::Instance()->n_Lk_Audio_SampleRate));


	//别率
	strVal.clear();
	strVal<<"48"<<"64"<<"80"<<"96"<<"112"<<"128"<<"160"<<"196"<<"256"<<"320";
	ui.comboBox_LkBl->addItems(strVal);
	ui.comboBox_LkBl->setCurrentText(QString("%1").arg(LkConfigOpt::Instance()->n_Lk_Audio_Bitrate));


	//url
	ui.lineEdit_LkURL->setText(LkConfigOpt::Instance()->str_Lk_NetWork_URL);

	//下面代码可以启用和关闭Aero效果
	//HRESULT result = ::DwmEnableComposition(DWM_EC_DISABLECOMPOSITION);
	//HRESULT result = ::DwmEnableComposition(DWM_EC_ENABLECOMPOSITION);
}

void LkSettingDlg::OnActionMore()
{
	ui.tabWidget->setCurrentIndex(1);
}
void LkSettingDlg::OnActionBack()
{
	ui.tabWidget->setCurrentIndex(0);
}


void LkSettingDlg::OnCheckSaveFlie()
{
	if(ui.checkBox_LkSaveFile->isChecked() == true?true:false)
	{
		ui.lineEdit_LkSavePath->setEnabled(true);
		ui.pushButton_SelectPath->setEnabled(true);
	}
	else
	{
		ui.lineEdit_LkSavePath->setEnabled(false);
		ui.pushButton_SelectPath->setEnabled(false);
	}
}
void LkSettingDlg::OnActionSaveFlieSelect()
{
	QString dir_name = QFileDialog::getExistingDirectory(0, QStringLiteral("请选择你要保存的文件夹"));
	if (dir_name.isEmpty()) return;
	ui.lineEdit_LkSavePath->setText(dir_name);
}

void LkSettingDlg::OnActionOk()
{
	//设置参数
	QString strVal = ui.comboBox_LkFbl->currentText();
	LkConfigOpt::Instance()->size_Lk_Encoder_Scale = QSize(LkConfigOpt::Instance()->GetWidth(strVal),LkConfigOpt::Instance()->GetHeight(strVal));

	//码率
	strVal = ui.comboBox_LkMl->currentText();
	LkConfigOpt::Instance()->n_Lk_Encoder_Bitrate = strVal.toInt();

	//FPS
	int nVal = ui.spinBox_LkFPS->value();
	LkConfigOpt::Instance()->n_Lk_Encoder_Fps = nVal;

	//启动是否最小化
	LkConfigOpt::Instance()->b_Lk_Min = ui.checkBox_LkZxh->isChecked() == true?true:false;

	//是否显示鼠标
	LkConfigOpt::Instance()->b_Lk_Mouse = ui.checkBox_LkXssb->isChecked() == true?true:false;

	//是否关闭aero
	LkConfigOpt::Instance()->b_Lk_Aero = ui.checkBox_LkAero->isChecked() == true?true:false;

	//保存文件
	LkConfigOpt::Instance()->b_Lk_SaveFile = ui.checkBox_LkSaveFile->isChecked() == true?true:false;

	//截屏最小化
	LkConfigOpt::Instance()->b_Lk_DesktopMin = ui.checkBox_LkDesktop->isChecked() == true?true:false;

	//文件路径
	LkConfigOpt::Instance()->str_Lk_SavePath = ui.lineEdit_LkSavePath->text();

	//***********高级**********//
	//tonue
	strVal = ui.comboBox_LkPSYTj->currentText();
	LkConfigOpt::Instance()->str_Lk_x264_Tune = strVal;

	//编码配置文件
	strVal = ui.comboBox_LkPzwj->currentText();
	LkConfigOpt::Instance()->str_Lk_x264_Profile = strVal;

	//关键帧数目
	nVal = ui.comboBox_LkGjzsm->currentText().toInt();
	LkConfigOpt::Instance()->n_Lk_x264_KeyFrameInterval = nVal;

	//x264 CPU 预设
	strVal = ui.comboBox_LkCPUys->currentText();
	LkConfigOpt::Instance()->str_Lk_x264_Preset = strVal;

	//并行编码帧数
	nVal = ui.comboBox_LkBxbmzs->currentText().toInt();
	LkConfigOpt::Instance()->n_Lk_x264_ThreadCount = nVal;

	//B关键帧
	LkConfigOpt::Instance()->b_Lk_x264_EnableBFrame = ui.checkBox_LkBgjz->isChecked() == true?true:false;

	//品质
	nVal = ui.spinBox_LkPz->value();
	LkConfigOpt::Instance()->n_Lk_x264_Quality = nVal;

	//码率类型
	strVal = ui.comboBox_LkMllx->currentText();
	LkConfigOpt::Instance()->str_Lk_x264_BitrateMode = strVal;

	//设备ID
	nVal = ui.comboBox_LkSb->currentIndex();
	LkConfigOpt::Instance()->n_Lk_Audio_DeviceId = nVal;

	//编码格式
	strVal = ui.comboBox_LkBmgs->currentText();
	LkConfigOpt::Instance()->str_Lk_Audio_Format = strVal;

	//频道
	strVal = ui.comboBox_LkPd->currentText();
	LkConfigOpt::Instance()->str_Lk_Audio_Channels = strVal;

	//采样率
	nVal = ui.comboBox_LkPd->currentText().toInt();
	LkConfigOpt::Instance()->n_Lk_Audio_SampleRate = nVal;

	//别率
	nVal = ui.comboBox_LkBl->currentText().toInt();
	LkConfigOpt::Instance()->n_Lk_Audio_Bitrate = nVal;

	//url
	strVal = ui.lineEdit_LkURL->text();
	LkConfigOpt::Instance()->str_Lk_NetWork_URL = strVal;
	

	LkConfigOpt::Instance()->WriteXmlConfig();
	this->accept();
}

void LkSettingDlg::OnActionMLLXSelectChange(const QString &)
{
	QString str = ui.comboBox_LkMllx->currentText();
	if (str == "CBR")
	{
		ui.spinBox_LkPz->setEnabled(false);
	}
	else
	{
		ui.spinBox_LkPz->setEnabled(true);
	}
}