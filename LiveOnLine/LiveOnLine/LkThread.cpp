#include "LkThread.h"

LkThread::LkThread(QObject *parent)
	: QThread(parent)
	, m_stop(false)
{
}

LkThread::~LkThread()
{

}

void LkThread::stop()
{
	m_stop = true;
}

void LkThread::start(QThread::Priority priority)
{
	m_stop = false;
	QThread::start(priority);
}
