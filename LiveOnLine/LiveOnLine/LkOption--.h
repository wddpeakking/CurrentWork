#ifndef _LK_OPTION_H_
#define _LK_OPTION_H_

#include <QObject>
#include <QVariant>
#include <QSettings>
#include <QMutex>
#include <QHash>

enum interfaceOptions
{
	OPTION_WindowBGPixmap,
	OPTION_WindowBGColor,
	OPTION_AeroTransparent,
	OPTION_WidgetTransparent,
	OPTION_Recommand,
	OPTION_WindowBGPixmapType,
	OPTION_RemeberPasswd,
	OPTION_AutoLogin,
	OPTION_NOTREMIND,
	OPTION_QUITORHIDE,
	OPTION_MINTOTRAY,
	OPTION_SHORTCUTS,
	OPTION_MainWindowBootAutoLogin,
	OPTION_USER_PASS,
	OPTION_AVERAGE_COLOR,
	OPTION_REFRESH_AUTO,
	OPTION_REFRESH_BY_HAND,
	OPTION_REFRESH_TIME,

	OPTIONS_NUM
};

enum interfaceOptions_Group
{
	OPTION_GROUP_Main,
	OPTION_GROUP_Theme,

	OPTIONS_GROUP_NUM
};

#define Key_Thread_Count    "ThreadCount"
#define Key_Enable_B_Frame  "EnableBFrame"

#define Group_X264          "x264"

class LkOption : public QObject
{
	Q_OBJECT
protected:
	explicit LkOption(QObject *parent = 0);
	~LkOption();

public:
	QVariant option(const QString &key, const QString &group);
	QVariant option(const int &key, const int &group);
	void setOption(const QVariant& value, const QString &key, const QString &group);
	void setOption(const QVariant& value, const int &key, const int &group);

	static LkOption* instance();
	static void destroy();

protected:
	void setDefaultValue();
	QVariant defaultValue(const QString &key);

private:
	static LkOption *m_theOptions;

	QSettings *m_settings;
	QHash<QString, QVariant> m_defaultValue;

	QMutex m_mutex;

};

#endif
