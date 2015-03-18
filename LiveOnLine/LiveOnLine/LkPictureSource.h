#ifndef _LK_PICTURESOURCE_H_
#define _LK_PICTURESOURCE_H_

#include "LkSourceAbstract.h"

class LkPictureSource : public LkSourceAbstract
{
public:
    LkPictureSource(const QString &picName);

    virtual LkImage getImage();
    virtual void stopCapture();
    virtual void setCaptureInterval(int interval);

private:
    LkImage m_image;
};

#endif // LkPictureSource_HPP
