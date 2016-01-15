#ifndef OPERATIONSBASIQUES_H
#define OPERATIONSBASIQUES_H

#include <QRgb>

//Fonctions min/max
inline int max(int a, int b) { return a > b ? a : b; }
inline int max(int a, double b) { return a > b ? a : b; }
inline double max(double a, double b) { return a > b ? a : b; }
inline double max(double a, int b) { return a > b ? a : b; }

inline int min(int a, int b) { return a < b ? a : b; }
inline int min(int a, double b) { return a < b ? a : b; }
inline double min(double a, double b) { return a < b ? a : b; }
inline double min(double a, double b) { return a < b ? a : b; }

//Fonctions vers YUV
inline int toYUV_Y(int r, int g, int b);
inline int toYUV_Cr(int r, int g, int b);
inline int toYUV_Cb(int r, int g, int b);
inline int toYUV_Y(QRgb color);
inline int toYUV_Cr(QRgb color);
inline int toYUV_Cb(QRgb color);
inline void toYUV(QRgb color, int & y, int & cr, int & cb);

#endif // OPERATIONSBASIQUES_H
