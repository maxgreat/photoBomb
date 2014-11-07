#ifndef OPERATIONSBASIQUES_H
#define OPERATIONSBASIQUES_H


#include <QRgb>

//Fonctions min/max
int max(int a, int b);
int max(int a, double b);
double max(double a, double b);
double max(double a, int b);

int min(int a, int b);
int min(int a, double b);
double min(double a, double b);
double min(double a, double b);

//Fonctions vers YUV
int toYUV_Y(int r, int g, int b);
int toYUV_Cr(int r, int g, int b);
int toYUV_Cb(int r, int g, int b);
int toYUV_Y(QRgb color);
int toYUV_Cr(QRgb color);
int toYUV_Cb(QRgb color);


#endif // OPERATIONSBASIQUES_H
