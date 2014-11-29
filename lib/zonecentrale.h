#ifndef ZONECENTRALE_H
#define ZONECENTRALE_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QPixmap>
#include <QEvent>
#include <QMouseEvent>
#include <QFile>
#include <QTextStream>
#include <QScrollArea>
#include <QPoint>
#include <QCursor>
#include <QRubberBand>
#include <QToolTip>
#include "imageRGB.h"
#include "lumetcont.h"
#include "fenetretaille.h"
#include "operationsBasiques.h"
#include "preferences.h"
#include "fenetrehistogramme.h"
#include "fenetreinfo.h"

#include <stdio.h>



class ZoneCentrale : public QWidget
{
        Q_OBJECT
    public:
        ZoneCentrale();
        ZoneCentrale(QString path);
        void mousePressEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *);
        void mousePressEventOnLabel(QMouseEvent *);
        void mouseMoveEventOnLabel(QMouseEvent *);
        QPixmap* getImage();
        bool aImage();
        bool eventFilter(QObject *, QEvent *);

    signals:
        void imageChange(QPixmap* nouvelleImage);
        void modeChange(bool mode);

    public slots:
        //Update
        void nouvelleImage(QPixmap nImage);
        void nouvelleImage(ImageRGB nImage);

        //Menu File
        void ouvrir();
        void sauvegarde();

        //Menu Edition
        void annuler();
        void annulerSansMemoire();
        void passerModeDecoupage();
        void passerModeGrabcut();
        void ouvrirPreferences();
        void modeRGB(bool b);
        void modeInfo(bool b);

        //Menu Affichage
        void zoomIn();
        void zoomOut();
        void zoomIn(int val);
        void zoomOut(int val);
        void changeAfficheInfos(bool b);
        void ouvrirHistogramme();

        //Menu Image
        void convertToNEtB();
        void ouvrirLumEtCont();
        void ouvrirTaille();
        void seamCarving();
        void afficherSeamCarving();

        //Menu Filtre
        void moyenneur3x3();
        void moyenneur5x5();
        void gradient();
        void Rehaussement();
        void Contour();
        void Contour2();

    private:
        //Fonctions d'initialisations
        void initImages();
        void initImages(QString path);
        void initBool();
        void nouveauLayout(QPixmap im);

        //Fonctions de traitements internes
        void grabcutRect(); //Reservé au grabCut

        //Labels et images
        QLabel* label;
        QRubberBand* rectSelection;
        QPixmap* image;
        QPixmap* imageZoomZero;
        QPixmap* imagePrec;
        FenetreInfo* infos;

        //Booléen de mode de fonctionnement
        bool modeDecoupage;
        bool modeGrabcut;
        bool RGB;
        bool affichageInfos;
        bool boutonGauche;

        //Variables de traitements internes
        QPoint rect1; //Reservé au grabCut
        QPoint rect2; //Reservé au grabCut
        int moy3[3][3];
        int moy5[5][5];
        int matRehauss[3][3];

};

#endif // ZONECENTRALE_H
