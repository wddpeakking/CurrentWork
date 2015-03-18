
#include "LkCameraSelector.h"
#include <QtMultimedia/QCameraInfo>

LkCameraSelectorDlg::LkCameraSelectorDlg(QWidget* pWidget)
	:QDialog(pWidget)
{
	ui.setupUi(this);
	Init();
}
LkCameraSelectorDlg::~LkCameraSelectorDlg()
{
}

//≥ı ºªØ
void LkCameraSelectorDlg::Init()
{
	QList<QCameraInfo> infos = QCameraInfo::availableCameras();
	    for (int i = 0; i < infos.size(); ++i) {
	        QCameraInfo info = infos.at(i);
	        ui.comboBox->addItem(info.description(), info.deviceName());
	    }
}

QString LkCameraSelectorDlg::GetSelect()const
{
	return ui.comboBox->currentText();
}