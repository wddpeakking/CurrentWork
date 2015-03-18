
#ifndef _LK_FILESOURCE_H_
#define _LK_FILESOURCE_H_

#include "LkSourceAbstract.h"
#include "LkThread.h"

#include <QMutex>

class LkFileSource : public LkThread, public LkSourceAbstract
{
    Q_OBJECT
public:
    LkFileSource(QObject * parent = 0);

    virtual LkImage getImage();
    virtual void stopCapture();
    virtual void run();

    virtual void setCaptureInterval(int interval);

    void setFileName(const QString &fileName);

private:
    QString m_fileName;
    LkImage m_image;
    QMutex m_modifyMutex;
    int m_interval;
};

#endif // LkFileSource_HPP
