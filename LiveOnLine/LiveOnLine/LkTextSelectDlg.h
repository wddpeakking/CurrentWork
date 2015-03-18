#ifndef _H_TEXTSLECT_H_
#define _H_TEXTSLECT_H_
#include <QDialog>
#include "ui_TextSelect.h"
class LkTextSelectDlg :
	public QDialog
{
public:
	LkTextSelectDlg(QWidget* pWidget = 0);
	~LkTextSelectDlg(void);

	QString GetInputString()const;
private:
	Ui::TextDlg ui;
};

#endif