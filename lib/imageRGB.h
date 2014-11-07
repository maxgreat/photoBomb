#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QRgb>
#include <stdio.h>
#include <math.h>
//#include "opencv2/opencv.hpp"
#include "operationsBasiques.h"


class ImageRGB : public QImage
{
public:
    //Initialisation
    explicit ImageRGB();
    explicit ImageRGB(int width, int height);
    explicit ImageRGB(const QImage & image);

    //Histogrammes
    void calculHisto();
    int* histoRouge();
    int* histoBleu();
    int* histoVert();
    int* histoY();
    int* histoU();
    int* histoV();

    //Action sur image
    void convertToNEtB();
    void fusion(ImageRGB im1 , ImageRGB im2);
    void luminosite(int change);
    void contraste(int change);
    void operationImage(ImageRGB im1 , ImageRGB im2,int val);
    void drawRect(QPoint p1, QPoint p2);


    //Convolution
    ImageRGB filtretrois(int convolution[3][3], int val);
    ImageRGB filtretroisNetB(int convolution[3][3], int val);
    ImageRGB filtrecinq(int convolution[5][5],int val);

    //Modification d'image
    ImageRGB gradient();    
    ImageRGB redimensionner(int largeur, int hauteur);
    ImageRGB seamCarvingHauteur();
    ImageRGB affichageSeamCarvingHauteur();
    ImageRGB seamCarvingHauteur(int nb);


    //Fonctions pour opencv
   /* cv::Mat toMat();
    ImageRGB fromMat(cv::Mat m);
    ImageRGB grabcut(QPoint p1, QPoint p2);
*/


private:
    int rouge[256];
    int bleu[256];
    int vert[256];
    int Y[256];
    int U[256];
    int V[256];

};

#endif // IMAGE_H
