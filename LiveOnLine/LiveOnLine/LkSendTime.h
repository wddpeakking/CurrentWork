#ifndef _LK_SENDTIME_H_
#define _LK_SENDTIME_H_

#include "lkthread.h"
#include <QTime>
class LkSendTime :
	public LkThread
{
	Q_OBJECT
public:
	LkSendTime(QObject *parent = 0);
	~LkSendTime(void);
	void run();

signals:
	void SengCurrentTime(const QString&);

private:
};

#endif

