#ifndef _LK_LKDEFINE_H_
#define _LK_LKDEFINE_H_
#include <QString>
#include <QSize>
#include <QColor>
#include "LkConfigOpt.h"

//配置文件
static const QString g_strConfigName = "/config.xml";


//自定义界面颜色
static QColor g_MainColor = QColor(0,0,0);
static QColor g_LeftColor = QColor(60,80,100);
static QColor g_MidleColor = QColor(0,0,0);
static QColor g_BottomColor = QColor(0,0,0); //QColor(140,200,100);
static QColor g_TopColor = QColor(40,40,40);//QColor(140,200,100);
static QColor g_BtnNormalColor = QColor(40,40,40);//QColor(140,200,100);


static	QString GetStyle(QColor color)
{
	return QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());
};

//版本信息
static QString g_LogoText = QStringLiteral("当面淘直播客户端v_0.4");
#define LK_VERSION_STR     "0.4"
#define LK_VERSION         (0x000410)
#define LK_AUTHORS         "linekong"
#define LK_NAME            "DMT" LK_VERSION_STR"(https://www.linekong.com)"


#endif