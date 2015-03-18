#ifndef _LK_SETTING_H_
#define _LK_SETTING_H_

#include "qdialog.h"
#include "ui_LkSettingDlg.h"
class LkSettingDlg :
	public QDialog
{
	Q_OBJECT
public:
	LkSettingDlg(QWidget* pWidget = 0);
	~LkSettingDlg(void);
	private slots:
		void OnActionMore();
		void OnActionBack();
		void OnActionOk();

		void OnActionMLLXSelectChange(const QString &);

		void OnCheckSaveFlie();
		void OnActionSaveFlieSelect();

private:
	void Init();
private:
	Ui::LkSetting ui;
};

#endif