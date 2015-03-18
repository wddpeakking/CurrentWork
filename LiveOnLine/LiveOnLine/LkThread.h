#ifndef _LK_THREAD_H
#define _LK_THREAD_H

#include <QThread>

class LkThread :
	public QThread
{
	Q_OBJECT
public:
	explicit LkThread(QObject *parent = 0);
	~LkThread();

	virtual void stop();
	void start(Priority priority = InheritPriority);

protected:
	bool m_stop;
};

#endif