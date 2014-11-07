#include "fenetrehistogramme.h"

FenetreHistogramme::FenetreHistogramme() :
    QWidget()
{
    setWindowTitle("Histogramme");
    setWindowFlags( Qt::WindowStaysOnTopHint ) ;
}

FenetreHistogramme::FenetreHistogramme(QPixmap* nouvelleImage) :
    QWidget()
{
    setWindowTitle("Histogramme");
    setWindowFlags( Qt::WindowStaysOnTopHint ) ;
    majHisto(nouvelleImage);
}


void FenetreHistogramme::changeMode(bool modeRGB)
{
    modeCouleur = modeRGB;
}


void FenetreHistogramme::majHisto(QPixmap* nouvelleImage)
{
    int i;
    int j;


    label = new QLabel(this);



    //Creation d'une image de 255 de largeur pour représenter l'histogramme
    //Pour trois couleurs : une image plus haute avec les trois histogrammes
    if(nouvelleImage != NULL)
    {
        //Recupération de l'image en format RGB32
        ImageRGB* imageT = new ImageRGB(nouvelleImage->toImage());
        if(imageT->isNull())
        {
            printf("Image null 1");
            return;
        }

        //Affichage de l'histogramme
        histogramme = new QImage(256, 304, QImage::Format_RGB32);
        histogramme->fill(qRgb(255,255,255));


        imageT->calculHisto();
        //Ajustement des histogrammes
        int maxR = 0;
        int maxB = 0;
        int maxV = 0;
        int* rouge;
        int* bleu;
        int* vert;

        if(modeCouleur)
        {
            rouge = imageT->histoRouge();
            bleu = imageT->histoBleu();
            vert = imageT->histoVert();
        }
        else
        {
            rouge = imageT->histoY();
            bleu = imageT->histoV();
            vert = imageT->histoU();
        }

        for(i = 0; i < 256 ; i++)
        {
            if(rouge[i] > maxR)
                maxR = rouge[i];
            if(bleu[i] > maxB)
                maxB = bleu[i];
            if(vert[i] > maxV)
                maxV = vert[i];
        }


        for( i = 0 ; i < 256; i++)
        {
            double pRouge = ((double)rouge[i]*100.0)/(double)maxR;
            double pBleu = ((double)bleu[i]*100.0)/(double)maxB;
            double pVert = ((double)vert[i]*100.0)/(double)maxV;

            //printf("%d : %lf, %lf, %lf\n", i, pRouge, pBleu, pVert);

            for(j = 0; j < pRouge ; j++)
            {
                if(modeCouleur)
                    histogramme->setPixel( i , 101-j , qRgb(255,0,0));
                else
                    histogramme->setPixel( i , 101-j , qRgb(0,0,0));
            }
            for(j = 0; j < pBleu ; j++)
            {
               histogramme->setPixel( i , 202-j , qRgb(0,0,255));
            }
            for(j = 0; j < pVert ; j++)
            {
                if(modeCouleur)
                    histogramme->setPixel( i , 303-j , qRgb(0,255,0));
                else
                   histogramme->setPixel( i , 303-j , qRgb(255,0,0));
            }
        }
        histoAfficher = new QPixmap(256, 304);
        histoAfficher->convertFromImage(*histogramme);
        label->setPixmap(*histoAfficher);


    }

    QHBoxLayout *HLayout = new QHBoxLayout;
    QVBoxLayout *VLayout = new QVBoxLayout;
    VLayout->addWidget(label);

    HLayout->addLayout(VLayout);

    if(layout() != 0)
        delete layout();
    setLayout(HLayout);
}
