#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow()
{
    resize(400,400);
    //Central Region init
    centre = new ZoneCentrale();
    centre->installEventFilter(this);
    setMouseTracking(true);
    setCentralWidget(centre);


    //Menus creation
    //File menu
    QMenu *menuFichier = menuBar()->addMenu(tr("Fichier"));

        //Open
        QAction *actionOuvrir = new QAction(tr("Ouvrir"), this);
        menuFichier->addAction(actionOuvrir);
        connect(actionOuvrir, SIGNAL(triggered()), centre, SLOT(ouvrir()));

        //Save
        QAction *actionSauvegarde = new QAction(tr("Sauvegarder"), this);
        menuFichier->addAction(actionSauvegarde);
        connect(actionSauvegarde, SIGNAL(triggered()), centre, SLOT(sauvegarde()));

        //Quit
        QAction *actionQuitter = new QAction(tr("Quitter"), this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));


    //Menu Edition
    QMenu *menuEdition = menuBar()->addMenu(tr("Edition"));

        //Cancel
        QAction *actionAnnuler = new QAction(tr("Annuler"), this);
        menuEdition->addAction(actionAnnuler);
        connect(actionAnnuler, SIGNAL(triggered()), centre, SLOT(annuler()));

        //Decoupage
        QAction *actionDecoupage = new QAction(tr("Decoupage"), this);
        menuEdition->addAction(actionDecoupage);
        connect(actionDecoupage, SIGNAL(triggered()), centre, SLOT(passerModeDecoupage()));

        //Decoupage
		/* OpenCV function -> do not set if openCV not included */
        QAction *actionGrabcut = new QAction(tr("Decoupage inteligent"), this);
        menuEdition->addAction(actionGrabcut);
        connect(actionGrabcut, SIGNAL(triggered()), centre, SLOT(passerModeGrabcut()));

        //Separateur
        menuEdition->addSeparator();

        //Preference
        QAction *preferences = new QAction(tr("Preferences"), this);
        menuEdition->addAction(preferences);
        connect(preferences, SIGNAL(triggered()), centre, SLOT(ouvrirPreferences()));



    //Menu Affichage
    QMenu *menuAffichage = menuBar()->addMenu(tr("Affichage"));

        QAction *zoomIn = new QAction("Zoom++", this);
        menuAffichage->addAction(zoomIn);
        connect(zoomIn, SIGNAL(triggered()), centre, SLOT(zoomIn()));

        QAction *zoomOut = new QAction("Zoom--", this);
        menuAffichage->addAction(zoomOut);
        connect(zoomOut, SIGNAL(triggered()), centre, SLOT(zoomOut()));

        //Separateur
        menuEdition->addSeparator();

        //Fenetre avec infos
        QAction *infosPixel = new QAction(tr("Afficher Informations"), this);
        menuAffichage->addAction(infosPixel);
        infosPixel->setCheckable(true);
        connect(infosPixel, SIGNAL(toggled(bool)), centre, SLOT(changeAfficheInfos(bool)));

        //Histogramme
        QAction *actionHisto = new QAction(tr("Histogrammes"), this);
        menuAffichage->addAction(actionHisto);
        connect(actionHisto, SIGNAL(triggered()), centre, SLOT(ouvrirHistogramme()));



    //Menu Image
    QMenu *menuImage = menuBar()->addMenu(tr("Image"));

        //Taille
        QAction *actionTaille = new QAction(tr("Taille de l'image"), this);
        menuImage->addAction(actionTaille);
        connect(actionTaille, SIGNAL(triggered()), centre, SLOT(ouvrirTaille()));

        //Seam Carving
        QAction *seam = new QAction(tr("Redimensionnement intelligent"), this);
        menuImage->addAction(seam);
        connect(seam, SIGNAL(triggered()), centre, SLOT(seamCarving()));

        //Taille
        QAction *affSeam = new QAction(tr("Afficher ligne mini"), this);
        menuImage->addAction(affSeam);
        connect(affSeam, SIGNAL(triggered()), centre, SLOT(afficherSeamCarving()));

        //Niveau de gris
        QAction *actionNiveauDeGris = new QAction(tr("Niveau de gris"), this);
        menuImage->addAction(actionNiveauDeGris);
        connect(actionNiveauDeGris, SIGNAL(triggered()), centre, SLOT(convertToNEtB()));

        //Luminosité
        QAction *actionLuminosite = new QAction(tr("Luminosite et contraste"), this);
        menuImage->addAction(actionLuminosite);
        connect(actionLuminosite, SIGNAL(triggered()), centre, SLOT(ouvrirLumEtCont()));




    //Menu Filtre
    QMenu *menuFiltre = menuBar()->addMenu(tr("Filtre"));

        //Flou
        QMenu *flouteur = menuFiltre->addMenu(tr("Flou"));
            //Moyenneur 3x3
            QAction *actionMoyenneur3x3 = new QAction(tr("Moyenneur3x3"), this);
            flouteur->addAction(actionMoyenneur3x3);
            connect(actionMoyenneur3x3, SIGNAL(triggered()), centre, SLOT(moyenneur3x3()));

            //Moyenneur 5x5
            QAction *actionMoyenneur5x5 = new QAction(tr("Moyenneur5x5"), this);
            flouteur->addAction(actionMoyenneur5x5);
            connect(actionMoyenneur5x5, SIGNAL(triggered()), centre, SLOT(moyenneur5x5()));


       //Rehaussement
       QMenu *menuRehaussement = menuFiltre->addMenu(tr("Rehaussement"));
           QAction *actionRehaussement = new QAction(tr("Rehaussement"), this);
           menuRehaussement->addAction(actionRehaussement);
           connect(actionRehaussement, SIGNAL(triggered()), centre, SLOT(Rehaussement()));

           QAction *actionContour = new QAction(tr("Contour"), this);
           menuRehaussement->addAction(actionContour);
           connect(actionContour, SIGNAL(triggered()), centre, SLOT(Contour2()));

       //Gradient
       QAction* gradient = new QAction(tr("Gradient"), this);
       menuFiltre->addAction(gradient);
       connect(gradient, SIGNAL(triggered()), centre, SLOT(gradient()));

     //Descriptor Menu
     QMenu *descriptorMenu = menuBar()->addMenu("Descriptor");

        QMenu *drawDescriptor = descriptorMenu->addMenu("Draw Descriptor");
            //Draw SIFT action
            QAction *actionDrawSift = new QAction("Draw SIFT", this);
            drawDescriptor->addAction(actionDrawSift);
            //connect();

            //Draw ORB
            QAction *actionDrawORB = new QAction("Draw ORB", this);
            drawDescriptor->addAction(actionDrawORB);
            //connect();

            //Draw A-KAZE
            QAction *actionDrawAkaze = new QAction("Draw A-KAZE", this);
            drawDescriptor->addAction(actionDrawAkaze);
            //connect();

        QMenu *drawMatch = descriptorMenu->addMenu("Draw Matches");
            //Draw SIFT action
            QAction *actionDrawMatchSift = new QAction("Draw SIFT", this);
            drawMatch->addAction(actionDrawMatchSift);
            //connect();

            //Draw ORB
            QAction *actionDrawMatchORB = new QAction("Draw ORB", this);
            drawMatch->addAction(actionDrawMatchORB);
            //connect();

            //Draw A-KAZE
            QAction *actionDrawMatchAkaze = new QAction("Draw A-KAZE", this);
            drawMatch->addAction(actionDrawMatchAkaze);
            //connect();
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
