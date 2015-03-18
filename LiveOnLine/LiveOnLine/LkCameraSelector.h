
#ifndef _LK_CAMREASELECTOR_H_
#define _LK_CAMREASELECTOR_H_

#include <QWidget>
#include <QDialog>
#include "ui_cameraSelect.h"

class LkCameraSelectorDlg : public QDialog
{
	Q_OBJECT
public:
	LkCameraSelectorDlg(QWidget* pWidget=0);
	~LkCameraSelectorDlg();

	QString GetSelect()const;

private:
	void Init();

private:
	Ui::cameraSelect ui;
};
#endif // BLECAMERASELECTOR_HPP
