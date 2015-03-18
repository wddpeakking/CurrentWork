#include "liveonline.h"
#include <QtWidgets/QApplication>
#include <QTranslator>
#include <QIcon>
#include <QDir>

#include "LkLog.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString strConfigPath = QApplication::applicationDirPath();
	/*QString dir = QApplication::applicationDirPath();  
	QDir::setCurrent(dir);  
	QApplication::addLibraryPath("./plugins");  */
	a.setWindowIcon(QIcon(strConfigPath+"/image/titlenew.ico")); 


#ifndef Q_OS_WIN
	g_logCtx->setEnableColorPrint(false);
#endif
	g_logCtx->setLog2File(true);
	
	//Ö÷½çÃæ
	LiveOnLine w;
	w.show();
	return a.exec();
}
