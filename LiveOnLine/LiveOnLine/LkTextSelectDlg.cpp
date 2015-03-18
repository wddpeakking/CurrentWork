#include "LkTextSelectDlg.h"


LkTextSelectDlg::LkTextSelectDlg(QWidget* pWidget)
	:QDialog(pWidget)
{
	ui.setupUi(this);
}


LkTextSelectDlg::~LkTextSelectDlg(void)
{
}

QString LkTextSelectDlg::GetInputString()const
{
	return ui.lineEdit_Input->text();
}
