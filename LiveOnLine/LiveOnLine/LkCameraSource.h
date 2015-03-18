#ifndef _LK_CAMERA_H_
#define _LK_CAMERA_H_

#include "LkThread.h"
#include "LkSourceAbstract.h"

#include <QMutex>

class LkCameraSource : public LkThread, public LkSourceAbstract
{
    Q_OBJECT
public:
    explicit LkCameraSource(QObject *parent = 0);

    virtual LkImage getImage();
    virtual void stopCapture();
    virtual void run();

    virtual void setCaptureInterval(int interval);
    void setCameraInfo(int index, const QString &name);

private:
    int m_interval;

    LkImage m_image;
    QMutex m_modifyMutex;
    int m_cameraIndex;
    QString m_cameraName;
};

#endif // 
