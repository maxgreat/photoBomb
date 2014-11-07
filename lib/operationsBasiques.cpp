#include "operationsBasiques.h"

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

double max(double a, double b)
{
    if(a > b)
        return a;
    return b;
}

int max(int a, double b)
{
    return max(a, (int)b);
}

double max(double a, int b)
{
    return max(a,(double)b);
}
int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

double min(double a, double b)
{
    if(a < b)
        return a;
    return b;
}

int min(int a, double b)
{
    return min(a, (int)b);
}

double min(double a, int b)
{
    return min(a, (double)b);
}



/************************************************************************************************
                                                                                                *
Fonction vers YUV                                                                               *
                                                                                                *
************************************************************************************************/


int toYUV_Y(int r, int g, int b)
{
    return min(255, max(0, 0.299*(double)r + 0.587*(double)g + 0.144*(double)b));
}

int toYUV_Cr(int r, int g, int b)
{
    return min(255, max(0, 0.5*(double)r - 0.4187*(double)g - 0.0813*(double)b + 128.0));
}

int toYUV_Cb(int r, int g, int b)
{
    return min(255, max(0, 0.5*(double)b + 128.0 - 0.1687*(double)r - 0.3313*(double)g));
}

int toYUV_Y(QRgb color)
{
    return min(255, max(0, 0.299*(double)qRed(color) + 0.587*(double)qGreen(color) + 0.144*(double)qBlue(color)));

}

int toYUV_Cr(QRgb color)
{
    return min(255, max(0, 0.5*(double)qRed(color) - 0.4187*(double)qGreen(color) - 0.0813*(double)qBlue(color) + 128.0));
}

int toYUV_Cb(QRgb color)
{
    return min(255, max(0, 0.5*(double)qBlue(color) + 128.0 - 0.1687*(double)qRed(color) - 0.3313*(double)qGreen(color)));
}

















