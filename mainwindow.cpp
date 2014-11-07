#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow()
{
    resize(400,400);
    //Creation de la zone centrale
    centre = new ZoneCentrale();
    centre->installEventFilter(this);
    setMouseTracking(true);
    setCentralWidget(centre);


    //Creation des menus
    //Menu fichier
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

        //Ouvrir
        QAction *actionOuvrir = new QAction("&Ouvrir", this);
        menuFichier->addAction(actionOuvrir);
        connect(actionOuvrir, SIGNAL(triggered()), centre, SLOT(ouvrir()));

        //Enregistrer
        QAction *actionSauvegarde = new QAction("Sauvegarder", this);
        menuFichier->addAction(actionSauvegarde);
        connect(actionSauvegarde, SIGNAL(triggered()), centre, SLOT(sauvegarde()));

        //Quitter
        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));


    //Menu Edition
    QMenu *menuEdition = menuBar()->addMenu("&Edition");

        //Annuler
        QAction *actionAnnuler = new QAction("Annuler", this);
        menuEdition->addAction(actionAnnuler);
        connect(actionAnnuler, SIGNAL(triggered()), centre, SLOT(annuler()));

        //Decoupage
        QAction *actionDecoupage = new QAction("&Decoupage", this);
        menuEdition->addAction(actionDecoupage);
        connect(actionDecoupage, SIGNAL(triggered()), centre, SLOT(passerModeDecoupage()));

        //Decoupage
        QAction *actionGrabcut = new QAction("&Decoupage inteligent", this);
        menuEdition->addAction(actionGrabcut);
        connect(actionGrabcut, SIGNAL(triggered()), centre, SLOT(passerModeGrabcut()));

        //Separateur
        menuEdition->addSeparator();

        //Preference
        QAction *preferences = new QAction("Preferences", this);
        menuEdition->addAction(preferences);
        connect(preferences, SIGNAL(triggered()), centre, SLOT(ouvrirPreferences()));



    //Menu Affichage
    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

        QAction *zoomIn = new QAction("Zoom++", this);
        menuAffichage->addAction(zoomIn);
        connect(zoomIn, SIGNAL(triggered()), centre, SLOT(zoomIn()));

        QAction *zoomOut = new QAction("Zoom--", this);
        menuAffichage->addAction(zoomOut);
        connect(zoomOut, SIGNAL(triggered()), centre, SLOT(zoomOut()));

        //Separateur
        menuEdition->addSeparator();

        //Fenetre avec infos
        QAction *infosPixel = new QAction("Afficher Informations", this);
        menuAffichage->addAction(infosPixel);
        infosPixel->setCheckable(true);
        connect(infosPixel, SIGNAL(toggled(bool)), centre, SLOT(changeAfficheInfos(bool)));

        //Histogramme
        QAction *actionHisto = new QAction("&Histogrammes", this);
        menuAffichage->addAction(actionHisto);
        connect(actionHisto, SIGNAL(triggered()), centre, SLOT(ouvrirHistogramme()));



    //Menu Image
    QMenu *menuImage = menuBar()->addMenu("&Image");

        //Taille
        QAction *actionTaille = new QAction("Taille de l'image", this);
        menuImage->addAction(actionTaille);
        connect(actionTaille, SIGNAL(triggered()), centre, SLOT(ouvrirTaille()));

        //Seam Carving
        QAction *seam = new QAction("Redimensionnement intelligent", this);
        menuImage->addAction(seam);
        connect(seam, SIGNAL(triggered()), centre, SLOT(seamCarving()));

        //Taille
        QAction *affSeam = new QAction("Afficher ligne mini", this);
        menuImage->addAction(affSeam);
        connect(affSeam, SIGNAL(triggered()), centre, SLOT(afficherSeamCarving()));

        //Niveau de gris
        QAction *actionNiveauDeGris = new QAction("&Niveau de gris", this);
        menuImage->addAction(actionNiveauDeGris);
        connect(actionNiveauDeGris, SIGNAL(triggered()), centre, SLOT(convertToNEtB()));

        //Luminosité
        QAction *actionLuminosite = new QAction("Luminosite et contraste", this);
        menuImage->addAction(actionLuminosite);
        connect(actionLuminosite, SIGNAL(triggered()), centre, SLOT(ouvrirLumEtCont()));




    //Menu Filtre
    QMenu *menuFiltre = menuBar()->addMenu("&Filtre");

        //Flou
        QMenu *flouteur = menuFiltre->addMenu("Flou");
            //Moyenneur 3x3
            QAction *actionMoyenneur3x3 = new QAction("Moyenneur3x3", this);
            flouteur->addAction(actionMoyenneur3x3);
            connect(actionMoyenneur3x3, SIGNAL(triggered()), centre, SLOT(moyenneur3x3()));

            //Moyenneur 5x5
            QAction *actionMoyenneur5x5 = new QAction("Moyenneur5x5", this);
            flouteur->addAction(actionMoyenneur5x5);
            connect(actionMoyenneur5x5, SIGNAL(triggered()), centre, SLOT(moyenneur5x5()));


       //Rehaussement
       QMenu *menuRehaussement = menuFiltre->addMenu("Rehaussement");
           QAction *actionRehaussement = new QAction("Rehaussement", this);
           menuRehaussement->addAction(actionRehaussement);
           connect(actionRehaussement, SIGNAL(triggered()), centre, SLOT(Rehaussement()));

           QAction *actionContour = new QAction("Contour", this);
           menuRehaussement->addAction(actionContour);
           connect(actionContour, SIGNAL(triggered()), centre, SLOT(Contour2()));

       //Gradient
       QAction* gradient = new QAction("Gradient", this);
       menuFiltre->addAction(gradient);
       connect(gradient, SIGNAL(triggered()), centre, SLOT(gradient()));
}


bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    if(o == centre)
    {
        if(e->type() == QEvent::MouseButtonPress)
            centre->mousePressEvent(static_cast<QMouseEvent*>(e));
        else if(e->type() == QEvent::MouseMove)
            centre->mouseMoveEvent(static_cast<QMouseEvent*>(e));
        else if(e->type() == QEvent::Wheel)
        {
            QWheelEvent* we = static_cast<QWheelEvent*>(e);
            int numDegrees = we->delta() / 8;
            int numStep = numDegrees / 15;
            if(numDegrees > 0)
                centre->zoomIn(numStep);
            else
                centre->zoomOut(numStep);
        }
        return true;
    }
    else
        return QMainWindow::eventFilter(o,e);
}
