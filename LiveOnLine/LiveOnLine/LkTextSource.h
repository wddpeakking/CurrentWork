#ifndef _LK_TEXTSOURCE_H_
#define _LK_TEXTSOURCE_H_

#include <QObject>
#include <QTimer>
#include <QImage>

#include "LkSourceAbstract.h"

class LkTextSource : public QObject, public LkSourceAbstract
{
    Q_OBJECT
public:
    explicit LkTextSource(QObject *parent = 0);

    virtual LkImage getImage();
    virtual void stopCapture();

    void setText(const QString &text);

private slots:
    void onTimeout();

private:
    LkImage m_image;
    QTimer m_timer;
    QString m_text;
    QImage m_textImage;
};

#endif // LkTextSource_HPP
