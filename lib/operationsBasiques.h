#ifndef OPERATIONSBASIQUES_H
#define OPERATIONSBASIQUES_H

#include <QRgb>

//Functions min/max
inline int max(int a, int b) { return a > b ? a : b; }
inline int max(int a, double b) { return a > (int)b ? a : (int)b; }
inline double max(double a, double b) { return a > b ? a : b; }
inline double max(double a, int b) { return a > b ? a : (double)b; }

inline int min(int a, int b) { return a < b ? a : b; }
inline int min(int a, double b) { return a < (int)b ? a : (int)b; }
inline double min(double a, double b) { return a < b ? a : b; }
inline double min(double a, int b) { return a < b ? a : (double)b; }

//Functions RGB to YUV
inline int toYUV_Y(int r, int g, int b)
{
    return min(255, max(0, 0.299*(double)r + 0.587*(double)g + 0.144*(double)b));
}

inline int toYUV_Cr(int r, int g, int b)
{
    return min(255, max(0, 0.5*(double)r - 0.4187*(double)g - 0.0813*(double)b + 128.0));
}

inline int toYUV_Cb(int r, int g, int b)
{
    return min(255, max(0, 0.5*(double)b + 128.0 - 0.1687*(double)r - 0.3313*(double)g));
}

inline int toYUV_Y(QRgb color)
{
    return min(255, max(0, 0.299*(double)qRed(color) + 0.587*(double)qGreen(color) + 0.144*(double)qBlue(color)));

}

inline int toYUV_Cr(QRgb color)
{
    return min(255, max(0, 0.5*(double)qRed(color) - 0.4187*(double)qGreen(color) - 0.0813*(double)qBlue(color) + 128.0));
}

inline int toYUV_Cb(QRgb color)
{
    return min(255, max(0, 0.5*(double)qBlue(color) + 128.0 - 0.1687*(double)qRed(color) - 0.3313*(double)qGreen(color)));
}

inline void toYUV(QRgb color, int & y, int & cr, int & cb){
    y = toYUV_Y(color);
    cr = toYUV_Cr(color);
    cb = toYUV_Cb(color);
}


#endif // OPERATIONSBASIQUES_H
