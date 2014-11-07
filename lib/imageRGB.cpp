#include "imageRGB.h"


/************************************************************************************************
                                                                                                *
Fonctions d'initialisation                                                                      *
                                                                                                *
************************************************************************************************/

ImageRGB::ImageRGB() :
    QImage()
{
    calculHisto();
}

ImageRGB::ImageRGB(int width, int height):
    QImage(width, height, QImage::Format_RGB32)
{
    fill(0);
    calculHisto();
}

ImageRGB::ImageRGB(const QImage & image) :
    QImage(image)
{
    convertToFormat(QImage::Format_RGB32);
    calculHisto();
}



/************************************************************************************************
                                                                                                *
Fonctions sur les histogrammes                                                                  *
                                                                                                *
************************************************************************************************/

void ImageRGB::calculHisto()
{
    int i;
    int j;
    for(i = 0; i < 256; i++)
    {
        rouge[i] = 0;
        bleu[i] = 0;
        vert[i] = 0;
        Y[i] = 0;
        U[i] = 0;
        V[i] = 0;
    }
    //Calcul des trois histogrammes
    for(i=0; i < width() ; i++)
    {
        for(j = 0; j < height() ; j++)
        {
            QRgb rgb = pixel(i,j);
            rouge[qRed(rgb)]++;
            bleu[qBlue(rgb)]++;
            vert[qGreen(rgb)]++;
            Y[toYUV_Y(rgb)]++;
            U[toYUV_Cr(rgb)]++;
            V[toYUV_Cb(rgb)]++;
        }
    }
}

int* ImageRGB::histoRouge()
{
    return rouge;
}
int* ImageRGB::histoBleu()
{
    return bleu;
}
int* ImageRGB::histoVert()
{
    return vert;
}

int* ImageRGB::histoY()
{
    return Y;
}
int* ImageRGB::histoU()
{
    return U;
}
int* ImageRGB::histoV()
{
    return V;
}


/*
Fonctions transformation d'image *******************************************************
*/


void ImageRGB::convertToNEtB()
{
    int i,j;

    unsigned int gris;

    for(i = 0; i < width(); i++)
    {
        for(j = 0; j < height(); j++)
        {
            QRgb p = pixel(i,j);
            gris = (unsigned int)((double)qRed(p)*0.2125 + (double)qGreen(p)*0.7154 + (double)qBlue(p)*0.0721);
            setPixel(i,j, qRgb(gris, gris, gris));
        }
    }
}




void ImageRGB::fusion(ImageRGB im1 , ImageRGB im2){
    QRgb couleur1;
    QRgb couleur2;
    QRgb nouveauPoint;

    int r,b,v,i,j;
    for(i=0;i<width();i++)
    {
        for(j=0;j<height();j++)
        {
        couleur1 = im1.pixel(i,j);
        couleur2 = im2.pixel(i,j);
        r =sqrt( (qRed(couleur1)  * qRed(couleur1)  ) + (qRed(couleur2)   * qRed(couleur2)));
        b =sqrt( (qBlue(couleur1) * qBlue(couleur1) ) + (qBlue(couleur2)  * qBlue(couleur2)));
        v= sqrt( (qGreen(couleur1)* qGreen(couleur1)) + (qGreen(couleur2) * qGreen(couleur2)));
        if(r>255){r = 255;}
        if(v>255){v = 255;}
        if(b>255){b = 255;}
        nouveauPoint = qRgb(r, v, b);
        setPixel(i,j,nouveauPoint);

        }
    }
}

void ImageRGB::operationImage(ImageRGB im1 , ImageRGB im2, int val){
    QRgb couleur1;
    QRgb couleur2;
    QRgb nouveauPoint;
    int r,b,v,j,i;

    for(i=0;i<width();i++)
    {
        for(j=0;j<height();j++)
        {
            couleur1 = im1.pixel(i,j);
            couleur2 = im2.pixel(i,j);
            r = qRed(couleur1) + val*qRed(couleur2);
            b = qBlue(couleur1) + val*qBlue(couleur2);
            v = qGreen(couleur1) + val*qGreen(couleur2);
            if(r<0){r = 0;}
            if(v<0){v = 0;}
            if(b<0){b = 0;}
            if(r>255){r = 255;}
            if(v>255){v = 255;}
            if(b>255){b = 255;}
            nouveauPoint = qRgb(r, v, b);
            setPixel(i,j,nouveauPoint);
        }
    }
}










/*
 Fonctions de filtres **************************************************
*/


ImageRGB ImageRGB::filtrecinq(int convolution[5][5],int val){
    int i,j,k,l;
    int r , v , b;
    int somme = 0;
    ImageRGB* newIm = new ImageRGB(*this);
    QRgb nouveauPoint;
    QRgb couleur;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            somme += convolution[i][j];
        }
    }
    for(i=2;i<width()-2;i++)
    {
        for(j=2;j<height()-2;j++)
        {
            r = 0;v=0;b=0;
            for(k=0;k<5;k++)
            {
                for(l=0;l<5;l++)
                {
                    couleur = pixel(i-2+k,j-2+l);
                    r += convolution[k][l]*qRed(couleur);
                    b += convolution[k][l]*qBlue(couleur);
                    v += convolution[k][l]*qGreen(couleur);
                }
            }
            if(val != 0)
            {
                r = r / val;
                v = v / val;
                b = b / val;
            }

            if(r<0){r = 0;}
            if(v<0){v = 0;}
            if(b<0){b = 0;}
            if(r>255){r = 255;}
            if(v>255){v = 255;}
            if(b>255){b = 255;}

            nouveauPoint = qRgb(r, v, b);
            newIm->setPixel(i,j,nouveauPoint);

        }
    }
    return *newIm;
}

ImageRGB ImageRGB::filtretrois(int convolution[3][3], int val)
{
    int i,j,k,l;
    int r , v , b;
    ImageRGB* newIm = new ImageRGB(*this);
    QRgb nouveauPoint;
    QRgb couleur;

    for(i=1; i < width()-1; i++)
    {
        for(j=1; j < height()-1; j++)
        {
            r=0;
            v=0;
            b=0;
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                {
                    couleur = pixel(i-1+k,j-1+l);
                    r += convolution[k][l]*qRed(couleur);
                    b += convolution[k][l]*qBlue(couleur);
                    v += convolution[k][l]*qGreen(couleur);
                }
            }
            if(val != 0)
            {
                r = r / val;
                v = v / val;
                b = b / val;
            }
            if(r<0){r = 0;}
            if(v<0){v = 0;}
            if(b<0){b = 0;}
            if(r>255){r = 255;}
            if(v>255){v = 255;}
            if(b>255){b = 255;}

            nouveauPoint = qRgb(r, v, b);
            newIm->setPixel(i,j,nouveauPoint);
        }
    }

    return *newIm;
}

ImageRGB ImageRGB::filtretroisNetB(int convolution[3][3], int val)
{
    int i,j,k,l;
    int r;
    ImageRGB* newIm = new ImageRGB(*this);
    QRgb couleur;

    if(val == 0)
        val = 1;

    for(i=1; i < width()-1; i++)
    {
        for(j=1; j < height()-1; j++)
        {
            r=0;
            for(k=0;k<3;k++)
            {
                for(l=0;l<3;l++)
                {
                    couleur = pixel(i-1+k,j-1+l);
                    r += convolution[k][l]*qRed(couleur);
                }
            }
            r = min(255, max(0, r/val));

            newIm->setPixel(i,j, qRgb(r,r,r));
        }
    }

    return *newIm;
}

ImageRGB ImageRGB::gradient()
{
    int i,j;
    ImageRGB newIm(*this);
    newIm.convertToNEtB();
    QRgb couleur1;
    QRgb couleur2;
    int conv1[3][3];
    int conv2[3][3];

    //Convolution 1 : horizontale
    conv1[0][0] = 1;
    conv1[0][1] = 2;
    conv1[0][2] = 1;
    conv1[1][0] = 0;
    conv1[1][1] = 0;
    conv1[1][2] = 0;
    conv1[2][0] = -1;
    conv1[2][1] = -2;
    conv1[2][2] = -1;

    //Convolution 2 : verticale
    conv2[0][0] = -1;
    conv2[0][1] = 0;
    conv2[0][2] = 1;
    conv2[1][0] = -2;
    conv2[1][1] = 0;
    conv2[1][2] = 2;
    conv2[2][0] = -1;
    conv2[2][1] = 0;
    conv2[2][2] = 1;


    ImageRGB gradientHor = newIm.filtretroisNetB(conv1,4);
    ImageRGB gradientVer = newIm.filtretroisNetB(conv2,4);

    for(i=0;i<width();i++)
    {
        for(j=0;j<height();j++)
        {
            couleur1 = gradientHor.pixel(i,j);
            couleur2 = gradientVer.pixel(i,j);
            int c = (int)sqrt(qRed(couleur1)*qRed(couleur1) + qRed(couleur2)*qRed(couleur2)) ;
            if(c > 255)
                c = 255;
            newIm.setPixel(i,j, qRgb(c,c,c));
        }
    }

    return newIm;
}












/*
Fonction Luminosité contraste *****************************************************
*/

void ImageRGB::luminosite(int change)
{
    int newR, newB, newG;
    int oldR, oldG, oldB;
    double lumi, Cr, Cb;
    for(int i = 0; i < width(); i++)
    {
        for(int j = 0; j < height() ; j++)
        {
            QRgb couleur = pixel(i,j);
            oldR = qRed(couleur);
            oldG = qGreen(couleur);
            oldB = qBlue(couleur);
            lumi = toYUV_Y(oldR, oldG, oldB);
            lumi += change;
            Cr = toYUV_Cr(oldR, oldG, oldB);
            Cb = toYUV_Cb(oldR, oldG, oldB);

            newR = min(255, max(0,(int)(lumi + 1.402*(Cr - 128.0))));
            newG = min(255, max(0,(int)(lumi - 0.34414*(Cb - 128.0) - 0.71414*(Cr - 128.0))));
            newB = min(255, max(0,(int)(lumi + 1.772*(Cb - 128.0))));
            setPixel(i,j, qRgb(newR, newG, newB));
        }
    }
}
void ImageRGB::contraste(int change)
{
    int minR = 255;
    int maxR = 0;
    int minG = 255, maxG = 0;
    int minB = 255, maxB = 0;
    QRgb couleur;

    for(int i = 0; i < width(); i++)
    {
        for(int j = 0; j < height() ; j++)
        {
            couleur = pixel(i,j);
            if(qRed(couleur) < minR)
                minR = qRed(couleur);
            else
            {
                if(qRed(couleur) > maxR)
                    maxR = qRed(couleur);
            }

            if(qGreen(couleur) < minG)
                minG = qGreen(couleur);
            else
            {
                if(qGreen(couleur) > maxG)
                    maxG = qGreen(couleur);
            }

            if(qBlue(couleur) < minB)
                minB = qBlue(couleur);
            else
            {
                if(qBlue(couleur) > maxB)
                    maxB = qBlue(couleur);
            }
        }
    }

    int maxR2 = maxR + change;
    int maxG2 = maxG + change;
    int maxB2 = maxB + change;
    int minR2 = minR + change;
    int minG2 = minG + change;
    int minB2 = minB + change;


    double coefR = (double)(maxR2 - minR2) / (double)(maxR - minR);
    double coefG = (double)(maxG2 - minG2) / (double)(maxG - minG);
    double coefB = (double)(maxB2 - minB2) / (double)(maxB - minB);

    double ajustR = ((double)(minR2*maxR) - (double)(maxR2*minR)) / (double)(maxR - minR);
    double ajustG = ((double)(minG2*maxG) - (double)(maxG2*minG)) / (double)(maxG - minG);
    double ajustB = ((double)(minB2*maxB) - (double)(maxB2*minB)) / (double)(maxB - minB);

    int rouge, vert, bleu;


    for(int i = 0; i < width(); i++)
    {
        for(int j = 0; j < height() ; j++)
        {
            couleur = pixel(i,j);
            rouge = qRed(couleur)*coefR + ajustR;
            vert = qGreen(couleur)*coefG + ajustG;
            bleu = qBlue(couleur)*coefB + ajustB;
            setPixel(i,j, qRgb(rouge, vert, bleu));
        }
    }
}






/*
Fonctions de redimensionnement *******************************************************
*/



ImageRGB ImageRGB::redimensionner(int largeur, int hauteur)
{
    ImageRGB* nImage = new ImageRGB(largeur, hauteur);
    int i,j;
    double pL, pH;
    double pL2, pH2;
    int partieEntiereL;
    int partieReelleL;
    int partieEntiereH;
    int partieReelleH;
    double pPixelHG, pPixelHD, pPixelBG, pPixelBD;
    int pRouge, pBleu, pVert;
    QRgb couleurHG, couleurHD, couleurBG, couleurBD;
    int nb_noir = 0, nb_couleur = 0;

    for(i = 0; i < largeur; i++)
    {
        for(j = 0; j < hauteur; j++)
        {
            pL2 = (double)i / (double)largeur; //pourcentage distance à la gauche de la nouvelle image
            pH2 = (double)j / (double)hauteur; //pourcentage distance au sommet de la nouvelle image

            pL = pL2 * (double)width(); //distance à la gauche sur l'image d'origine
            pH = pH2 * (double)height(); //distance au sommet sur l'image d'origine


            partieEntiereL = floor(pL); //calcul des parties entières pour pouvoir avoir les parties reelles
            partieEntiereH = floor(pH); //La partie entière correspond aussi au pixel en haut à gauche

            partieReelleH = partieEntiereH - pH; //Calcul des parties reelles pour avoir la pondération
            partieReelleL = partieEntiereL - pL;

            //Calcul des ponderations des 4 pixels autour
            pPixelHG = (1.0-partieReelleL + 1.0-partieReelleH) / 2.0;
            pPixelHD = (partieReelleL + 1.0-partieReelleH) / 2.0;
            pPixelBG = (1.0-partieReelleL + partieReelleH) / 2.0;
            pPixelBD = (partieReelleL + (partieReelleH)) / 2.0;

            if(partieEntiereH >= 0 && partieEntiereL >= 0 && partieEntiereL < width()-1 && partieEntiereH < height()-1 )
            {
                couleurHG = pixel(partieEntiereL, partieEntiereH);
                couleurBD = pixel(partieEntiereL + 1, partieEntiereH + 1);
                couleurHD = pixel(partieEntiereL + 1, partieEntiereH);
                couleurBG = pixel(partieEntiereL, partieEntiereH+1);
                nb_couleur++;
            }
            else
            {
                couleurHG = 0;
                couleurBD = 0;
                couleurHD = 0;
                couleurBG = 0;
                nb_noir++;
            }

            pRouge = (int)((double)qRed(couleurHG) * pPixelHG + (double)qRed(couleurHD) * pPixelHD + (double)qRed(couleurBG) * pPixelBG + (double)qRed(couleurBD) * pPixelBD) / 2;
            if(pRouge > 255)
                pRouge = 255;
            if(pRouge < 0)
                pRouge = 0;

            pVert = (int)((double)qGreen(couleurHG) * pPixelHG + (double)qGreen(couleurHD) * pPixelHD + (double)qGreen(couleurBG) * pPixelBG + (double)qGreen(couleurBD) * pPixelBD) / 2;
            if(pVert > 255)
                pVert = 255;
            if(pVert < 0)
                pVert = 0;

            pBleu = (int)((double)qBlue(couleurHG) * pPixelHG + (double)qBlue(couleurHD) * pPixelHD + (double)qBlue(couleurBG) * pPixelBG + (double)qBlue(couleurBD) * pPixelBD) / 2;
            if(pBleu > 255)
                pBleu = 255;
            if(pBleu < 0)
                pBleu = 0;

         // couleurHG = pixel(partieEntiereL, partieEntiereH);
            nImage->setPixel(i,j, qRgb(pRouge, pVert, pBleu));
        }

    }

    printf("NB noir : %d, NB couleur : %d\n", nb_noir, nb_couleur);
    return *nImage;
}


ImageRGB ImageRGB::seamCarvingHauteur()
{
    //Pour le moment : marquage d'une ligne
    ImageRGB im = ImageRGB(gradient().copy());
    QVector< QVector<int> > chemin(im.width());
    int largeur;
    int hauteur;
    int i,j;

    largeur = im.width();
    hauteur = im.height();

    ImageRGB* nouvelleImage = new ImageRGB(largeur, hauteur-1);

    int grad1;
    int grad2;
    int grad3;


    //Init chemin
    for(i = 0; i < largeur; i++)
    {
        chemin[i] = QVector<int>(hauteur, 0);
        chemin[i][0] = qRed(im.pixel(i,0));
    }

    //Parcours de l'image pour le calcul des chemins
    for(i = 1; i < largeur ; i++)
    {
        for(j = 0; j < hauteur; j++)
        {
            grad2 = chemin[i-1][j];
            if(j == 0)
            {
                grad3 = chemin[i-1][j+1];
                chemin[i][j] = min(grad2, grad3) + qRed(im.pixel(i,j));

            }
            else if( j == hauteur-1)
            {
                grad1 = chemin[i][j-1];
                chemin[i][j] = min(grad2, grad1) + qRed(im.pixel(i,j));
            }
            else
            {
                grad3 = chemin[i-1][j+1];
                grad1 = chemin[i][j-1];

                chemin[i][j] = min(grad1, min(grad2, grad3)) + qRed(im.pixel(i,j));
            }
        }
    }

    //Recherche du minimum sur la dernière ligne
    int posMin = 0;
    for(j = 1; j < hauteur; j++)
    {
        if(chemin[largeur-1][j] < chemin[largeur-1][posMin])
            posMin = j;
    }


    //Remonte du chemin
    for(i = largeur-2; i >= 0; i--)
    {

        if(posMin > 0 && posMin < hauteur-1)
        {
            if(chemin[i][posMin] > chemin[i][posMin-1])
            {
                if(chemin[i][posMin-1] > chemin[i][posMin+1])
                    posMin++;
                else
                    posMin--;
            }
            else //chemin[i][posMin] < chemin[i][posMin-1]
            {
                if(chemin[i][posMin] > chemin[i][posMin+1])
                    posMin++;
                //Sinon, on laisse posMin où il est
            }
        }
        else if(posMin == 0)
        {
            if(chemin[i][posMin] > chemin[i][posMin+1])
                posMin++;
            //Sinon, on laisse posMin où il est
        }
        else if(posMin == hauteur-1)
        {
            if(chemin[i][posMin] > chemin[i][posMin-1])
                posMin--;
            //Sinon, on laisse posMin où il est
        }
        else
        {
            printf("Non pris en charge ! \n");
            exit(0);
        }

        //Recopie de la colonne, sans le pixel qui est sur le chemin
        for(int k = 0; k < hauteur-1; k++)
        {
            if(k < posMin)
                nouvelleImage->setPixel(i,k, pixel(i,k));
            else
                nouvelleImage->setPixel(i,k, pixel(i,k+1));
        }
    }


    for(i = 0; i < largeur; i++)
    {
        chemin[i].clear();
    }
    chemin.clear();

    return ImageRGB(*nouvelleImage);
}



ImageRGB ImageRGB::seamCarvingHauteur(int nb)
{
    //Pour le moment : marquage d'une ligne
    ImageRGB im = ImageRGB(gradient().copy());
    QVector< QVector<int> > chemin(im.width());
    int largeur;
    int hauteur;
    int i,j;

    largeur = im.width();
    hauteur = im.height();
    int grad1;
    int grad2;
    int grad3;

    ImageRGB* nouvelleImage = new ImageRGB(largeur, hauteur-nb);
    ImageRGB* tmp;


    for(int n = 1; n <= nb; n++)
    {
        tmp = new ImageRGB(largeur, hauteur-nb);

        //Init chemin
        for(i = 0; i < largeur; i++)
        {
            chemin[i] = QVector<int>(hauteur-nb, 0);
            chemin[i][0] = qRed(im.pixel(i,0));
        }

        //Parcours de l'image pour le calcul des chemins
        for(i = 1; i < largeur ; i++)
        {
            for(j = 0; j < hauteur-nb+1; j++)
            {
                grad2 = chemin[i-1][j];
                if(j == 0)
                {
                    grad3 = chemin[i-1][j+1];
                    chemin[i][j] = min(grad2, grad3) + qRed(im.pixel(i,j));

                }
                else if( j == hauteur-1)
                {
                    grad1 = chemin[i][j-1];
                    chemin[i][j] = min(grad2, grad1) + qRed(im.pixel(i,j));
                }
                else
                {
                    grad3 = chemin[i-1][j+1];
                    grad1 = chemin[i][j-1];

                    chemin[i][j] = min(grad1, min(grad2, grad3)) + qRed(im.pixel(i,j));
                }
            }
        }

        //Recherche du minimum sur la dernière ligne
        int posMin = 0;
        for(j = 1; j < hauteur-nb+1; j++)
        {
            if(chemin[largeur-1][j] < chemin[largeur-1][posMin])
                posMin = j;
        }


        //Remonte du chemin
        for(i = largeur-2; i >= 0; i--)
        {

            if(posMin > 0 && posMin < hauteur-nb)
            {
                if(chemin[i][posMin] > chemin[i][posMin-1])
                {
                    if(chemin[i][posMin-1] > chemin[i][posMin+1])
                        posMin++;
                    else
                        posMin--;
                }
                else //chemin[i][posMin] < chemin[i][posMin-1]
                {
                    if(chemin[i][posMin] > chemin[i][posMin+1])
                        posMin++;
                    //Sinon, on laisse posMin où il est
                }
            }
            else if(posMin == 0)
            {
                if(chemin[i][posMin] > chemin[i][posMin+1])
                    posMin++;
                //Sinon, on laisse posMin où il est
            }
            else if(posMin == hauteur-nb)
            {
                if(chemin[i][posMin] > chemin[i][posMin-1])
                    posMin--;
                //Sinon, on laisse posMin où il est
            }
            else
            {
                printf("Non pris en charge ! \n");
                exit(0);
            }

            //Recopie de la colonne, sans le pixel qui est sur le chemin
            for(int k = 0; k < hauteur-nb; k++)
            {
                if(k < posMin)
                    tmp->setPixel(i,k, pixel(i,k));
                else if(k == posMin)
                {   //Mise à jour du gradient
                    if(i > 2 && i < hauteur-nb-2)
                    {
                        if(posMin > 2)
                        {

                        }
                    }
                }
                else
                    tmp->setPixel(i,k, pixel(i,k+1));
            }
        }
    }

    for(i = 0; i < largeur; i++)
    {
        chemin[i].clear();
    }
    chemin.clear();

    return ImageRGB(*nouvelleImage);
}




ImageRGB ImageRGB::affichageSeamCarvingHauteur()
{
    //Pour le moment : marquage d'une ligne
    ImageRGB im = ImageRGB(gradient().copy());
    QVector< QVector<int> > chemin(im.width());
    int largeur;
    int hauteur;
    int i,j;

    largeur = im.width();
    hauteur = im.height();

    int grad1;
    int grad2;
    int grad3;


    //Init chemin
    for(i = 0; i < largeur; i++)
    {
        chemin[i] = QVector<int>(hauteur, 0);
        chemin[i][0] = qRed(im.pixel(i,0));
    }

    //Parcours de l'image pour le calcul des chemins
    for(i = 1; i < largeur ; i++)
    {
        for(j = 0; j < hauteur; j++)
        {
            grad2 = chemin[i-1][j];
            if(j == 0)
            {
                grad3 = chemin[i-1][j+1];
                chemin[i][j] = min(grad2, grad3) + qRed(im.pixel(i,j));

            }
            else if( j == hauteur-1)
            {
                grad1 = chemin[i][j-1];
                chemin[i][j] = min(grad2, grad1) + qRed(im.pixel(i,j));
            }
            else
            {
                grad3 = chemin[i-1][j+1];
                grad1 = chemin[i][j-1];

                chemin[i][j] = min(grad1, min(grad2, grad3)) + qRed(im.pixel(i,j));
            }
        }
    }

    //Recherche du minimum sur la dernière ligne
    int posMin = 0;
    for(j = 0; j < hauteur; j++)
    {
        if(chemin[largeur-1][j] < chemin[largeur-1][posMin])
            posMin = j;
    }


    //Remonte du chemin
    for(i = largeur-2; i >= 0; i--)
    {

        if(posMin > 0 && posMin < hauteur-1)
        {
            if(chemin[i][posMin] > chemin[i][posMin-1])
            {
                if(chemin[i][posMin-1] > chemin[i][posMin+1])
                    posMin++;
                else
                    posMin--;
            }
            else //chemin[i][posMin] < chemin[i][posMin-1]
            {
                if(chemin[i][posMin] > chemin[i][posMin+1])
                    posMin++;
                //Sinon, on laisse posMin où il est
            }
        }
        else if(posMin == 0)
        {
            if(chemin[i][posMin] > chemin[i][posMin+1])
                posMin++;
            //Sinon, on laisse posMin où il est
        }
        else if(posMin == hauteur-1)
        {
            if(chemin[i][posMin] > chemin[i][posMin-1])
                posMin--;
            //Sinon, on laisse posMin où il est
        }

        im.setPixel(i, posMin, qRgb(0,0,255));
    }


    for(i = 0; i < largeur; i++)
    {
        chemin[i].clear();
    }
    chemin.clear();

    return im;
}


/*
Fonctions pour opencv ***********************************************************************
*/
/*


cv::Mat ImageRGB::toMat()
{
    this->convertToFormat(QImage::Format_RGB888);
    cv::Mat tmp(height(),width(),CV_8UC3,(uchar*)bits(),bytesPerLine());
    return tmp;
}

ImageRGB ImageRGB::fromMat(cv::Mat m)
{
    QImage dest((uchar*) m.data, m.cols, m.rows, m.step1(), QImage::Format_RGB32);
    ImageRGB dest2(dest);
    dest2.detach(); // enforce deep copy

    return dest2;
}

ImageRGB ImageRGB::grabcut(QPoint p1, QPoint p2)
{

 //   cv::Mat matrice = toMat();
    this->save("temp.jpg");
    cv::Mat matrice;
    matrice= cv::imread("temp.jpg");

    cv::Rect rectangle(p1.x(), p1.y(),p2.x() - p1.x(), p2.y() - p1.y());

    cv::Mat result; // segmentation result (4 possible values)
    cv::Mat bgModel,fgModel; // the models (internally used)

    // GrabCut segmentation
    cv::grabCut(matrice,    // input image
        result,   // segmentation result
        rectangle,// rectangle containing foreground
        bgModel,fgModel, // models
        3,        // number of iterations
        cv::GC_INIT_WITH_RECT); // use rectangle

    cv::Mat im;
    // Get the pixels marked as likely foreground
    cv::compare(result,cv::GC_PR_FGD,im,cv::CMP_EQ);
    // Generate output image
    cv::Mat foreground(matrice.size(),CV_8UC3,cv::Scalar(255,255,255));
    matrice.copyTo(foreground,im); // bg pixels not copied
 //   return fromMat(foreground);
    cv::imwrite("temp.jpg", foreground);
    load("temp.jpg");
    return *this;
}

*/
