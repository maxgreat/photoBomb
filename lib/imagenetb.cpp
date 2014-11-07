#include "imagenetb.h"

ImageNetB::ImageNetB(QImage *parent) :
    QImage(parent)
{
    convertToFormat(QImage::Format_RGB32);

}
