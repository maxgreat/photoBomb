#ifndef IMAGENETB_H
#define IMAGENETB_H

#include <QImage>
#include <QRgb>

class ImageNetB : public QImage
{
    Q_OBJECT
public:
    explicit ImageNetB(QObject *parent = 0);

signals:

public slots:

};

#endif // IMAGENETB_H
