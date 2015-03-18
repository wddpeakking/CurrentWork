#include "LkSendTime.h"
#include <QDateTime>
LkSendTime::LkSendTime(QObject *parent)
	:LkThread(parent)
{
}


LkSendTime::~LkSendTime(void)
{
}


void LkSendTime::run()
{
	while (!m_stop)
	{
		QDateTime time = QDateTime::currentDateTime();
		QString current_date = time.toString("\thh:mm:ss");
		emit SengCurrentTime(current_date);
	}
}