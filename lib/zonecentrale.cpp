#include "zonecentrale.h"



/************************************************************************************************
                                                                                                *
Fonctions d'initialisation                                                                      *
                                                                                                *
************************************************************************************************/

ZoneCentrale::ZoneCentrale(QString path)
{
    label=NULL;
    initBool();
    initImages(path);
}


ZoneCentrale::ZoneCentrale()
{
    label=NULL;
    initBool();
    image = 0;
    QFile fichier("save.data");
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        if(!flux.atEnd())
        {
            QString path = flux.readLine();
            if(!path.isNull())
            {
                initImages(path);
            }
            else
            {
                initImages();
            }
        }
        else
        {
            initImages();
        }
    }
    else
    {
        initImages();
    }
}


void ZoneCentrale::initBool()
{
    modeDecoupage = false;
    modeGrabcut = false;
    RGB = true;
    boutonGauche = false;
    affichageInfos = true;
    rect1 = QPoint();
    rect2 = QPoint();

   // setMouseTracking(true);
  //  grabMouse();


    //Moyenneur 3*3
    for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
            moy3[i][j] = 1;

    //Moyenneur 5*5
    for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
			moy5[i][j] = 1;

    //rehaussement
    matRehauss[0][0] = -1;
    matRehauss[0][1] = -1;
    matRehauss[0][2] = -1;
    matRehauss[1][0] = -1;
    matRehauss[1][1] = 16;
    matRehauss[1][2] = -1;
    matRehauss[2][0] = -1;
    matRehauss[2][1] = -1;
    matRehauss[2][2] = -1;
}

void ZoneCentrale::initImages()
{
    image = NULL;
    imageZoomZero = NULL;
    imagePrec = NULL;
}

void ZoneCentrale::initImages(QString path)
{
    nouvelleImage(QPixmap(path));
}

QPixmap* ZoneCentrale::getImage()
{
    return image;
}

bool ZoneCentrale::aImage()
{
    return image != NULL;
}


bool ZoneCentrale::eventFilter(QObject *o, QEvent *e)
{
    if(o == label)
    {
        if(e->type() == QEvent::MouseMove)
            mouseMoveEventOnLabel(static_cast<QMouseEvent*>(e));
        else if(e->type() == QEvent::MouseButtonPress)
            mousePressEventOnLabel(static_cast<QMouseEvent*>(e));
        else if(e->type() == QEvent::MouseButtonRelease)
            mouseReleaseEvent(static_cast<QMouseEvent*>(e));
    }
    return false;
}


/************************************************************************************************
                                                                                                *
Procédures pour l'affichage d'images                                                            *
                                                                                                *
************************************************************************************************/


void ZoneCentrale::nouveauLayout(QPixmap im)
{
    if(label == NULL){
        printf("Ici");
        label = new QLabel(this);
        label->setMouseTracking(true);
        label->installEventFilter(this);
        label->setPixmap(im);

        QVBoxLayout* imageLayout = new QVBoxLayout();

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        scrollArea->setWidget(label);

        imageLayout->addWidget(scrollArea);
        //imageLayout->addWidget(label);
        //imageLayout->setWidget(label);
        if(layout() != 0)
            delete layout();
        setLayout(imageLayout);
    }
    else{
        //TODO : resize layout to fit the image
        label->setPixmap(im);
    }
}


void ZoneCentrale::nouvelleImage(QPixmap nImage)
{

    if(image != 0)
        imagePrec = new QPixmap(*image);
    image = new QPixmap(nImage);
    emit imageChange(image);

    nouveauLayout(*image);
}

void ZoneCentrale::nouvelleImage(ImageRGB nImage)
{

    if(image != 0)
        imagePrec = new QPixmap(*image);
    image = new QPixmap();
    image->convertFromImage(nImage);


    //Emmission d'un signal comme quoi l'image à changée
    emit imageChange(image);


    //Affichage de l'image
    if(image->isNull())
    {
        QMessageBox::warning(this, "Erreur ouverture fichier", "Fichier image non trouvé");
        return;
    }
    else
        nouveauLayout(*image);
}



void ZoneCentrale::annulerSansMemoire()
{
    nouvelleImage(*imagePrec);
}




/************************************************************************************************
                                                                                                *
Fonctions de traitement de souris                                                               *
                                                                                                *
************************************************************************************************/


void ZoneCentrale::mousePressEvent(QMouseEvent* event)
{
    if(modeDecoupage)
    {
        //TODO
        modeDecoupage = false;
    }
    else if(affichageInfos && !modeGrabcut)
    {
        QToolTip::showText(event->globalPos(), QString("Valeur pixel : "), this);
    }
    else if(modeGrabcut)
    {
        if(event->button() == Qt::LeftButton && !boutonGauche)
        {
            if(rect1.isNull())
            {
                rect1 = QPoint(event->x() - label->pos().x(), event->y() - label->pos().y());
                printf("Clic en %d, %d\n", rect1.x(), rect1.y());
           //     setMouseTracking(true);
                  boutonGauche = true;
           //       grabMouse();
            }
            else
            {
                rect2 = QPoint(event->x() - label->pos().x(), event->y() - label->pos().y());

                //Verification du rectangle de selection

                //verification de l'ordre des points
                int tmpX = rect1.x();
                int tmpY = rect1.y();

                rect1.setX(min(rect1.x(), rect2.x()));
                rect2.setX(max(tmpX, rect2.x()));

                rect1.setY(min(rect1.y(), rect2.y()));
                rect2.setY(max(tmpY, rect2.y()));




                //Verification qu'on ne sort pas du terrain
                if(rect1.x() < 0)
                    rect1.setX(0);
                else if(rect1.x() > label->pos().x() + label->width())
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }

                if(rect1.y() < 0)
                    rect1.setY(0);
                else if(rect1.y() >= label->pos().y() + label->width())
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }


                if(rect2.x() < 0)
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }
                rect2.setX(min(rect2.x(), label->pos().x() + label->width()-1));

                if(rect2.y() < 0)
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }
                rect2.setY(min(rect2.y(),label->pos().y() + label->height() - 1 ));
                printf("Rectangle : %d, %d à %d, %d\n", rect1.x(), rect1.y(), rect2.x(), rect2.y());
                grabcutRect();
                setMouseTracking(false);
                rect1 = QPoint();
                rect2 = QPoint();
                modeGrabcut = false;
            }
        }
        else if(event->button() == Qt::RightButton)
        {
            rect1 = QPoint();
            rect2 = QPoint();
       //     setMouseTracking(false);
            releaseMouse();
            rectSelection->setVisible(false);
        }
    }
}

void ZoneCentrale::mousePressEventOnLabel(QMouseEvent* event)
{
    if(modeDecoupage)
    {
        //TODO
        modeDecoupage = false;
    }
    else if(affichageInfos && !modeGrabcut)
    {
        QToolTip::showText(event->globalPos(), QString("Valeur pixel : "), this);
    }
    else if(modeGrabcut)
    {
        if(event->button() == Qt::LeftButton && !boutonGauche)
        {
            if(rect1.isNull())
            {
                rect1 = QPoint(event->x(), event->y());
                printf("Clic en %d, %d\n", rect1.x(), rect1.y());
                boutonGauche = true;
            }
            else
            {
                rect2 = QPoint(event->x(), event->y());

                //Verification du rectangle de selection

                //verification de l'ordre des points
                int tmpX = rect1.x();
                int tmpY = rect1.y();

                rect1.setX(min(rect1.x(), rect2.x()));
                rect2.setX(max(tmpX, rect2.x()));

                rect1.setY(min(rect1.y(), rect2.y()));
                rect2.setY(max(tmpY, rect2.y()));




                //Verification qu'on ne sort pas du terrain
                if(rect1.x() < 0)
                    rect1.setX(0);
                else if(rect1.x() > label->width())
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }

                if(rect1.y() < 0)
                    rect1.setY(0);
                else if(rect1.y() >= label->width())
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }


                if(rect2.x() < 0)
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }
                rect2.setX(min(rect2.x(), label->width()-1));

                if(rect2.y() < 0)
                {
                    QMessageBox::warning(this, "Erreur Selection", "Erreur lors du selection du carré");
                    return;
                }
                rect2.setY(min(rect2.y(), label->height() - 1 ));
                printf("Rectangle : %d, %d à %d, %d\n", rect1.x(), rect1.y(), rect2.x(), rect2.y());
                grabcutRect();
                setMouseTracking(false);
                rect1 = QPoint();
                rect2 = QPoint();
                modeGrabcut = false;
            }
        }
        else if(event->button() == Qt::RightButton)
        {
            rect1 = QPoint();
            rect2 = QPoint();
       //     setMouseTracking(false);
            releaseMouse();
            rectSelection->setVisible(false);
        }
    }
}



void ZoneCentrale::mouseReleaseEvent(QMouseEvent *event)
{
    printf("Release\n");
    boutonGauche = false;
}

void ZoneCentrale::mouseMoveEvent(QMouseEvent * event)
{
    if(affichageInfos && !modeGrabcut)
    {

    }
    if(modeGrabcut && !rect1.isNull())
    {
        if(rect2.isNull())
        {
            rectSelection = new QRubberBand(QRubberBand::Rectangle, this);
        }
        rect2 = QPoint(event->x() - label->pos().x(), event->y() - label->pos().y());

        //verification de l'ordre des points
        int tmpX = rect1.x();
        int tmpY = rect1.y();

        rect1.setX(min(rect1.x(), rect2.x()));
        rect2.setX(max(tmpX, rect2.x()));

        rect1.setY(min(rect1.y(), rect2.y()));
        rect2.setY(max(tmpY, rect2.y()));

        rectSelection->setGeometry(rect1.x()+label->pos().x(), rect1.y()+label->pos().y(), rect2.x() - rect1.x(), rect2.y() - rect1.y());
        rectSelection->show();
    }
}

void ZoneCentrale::mouseMoveEventOnLabel(QMouseEvent * event)
{
    if(affichageInfos && !modeGrabcut)
    {/*
        ImageRGB* im = new ImageRGB(image->toImage());
        QString str;
        QRgb couleur = im->pixel(event->x(), event->y());
        if(RGB)
            str = QString("Valeur pixel: R%1, V%2, B%3").arg(qRed(couleur)).arg(qGreen(couleur)).arg(qBlue(couleur));
        else
            str = QString("Valeur pixel: Y%1, U%2, V%3").arg(toYUV_Y(couleur)).arg(toYUV_Cr(couleur)).arg(toYUV_Cb(couleur));
        QToolTip::showText(event->globalPos(), str, this);*/
    }
    if(modeGrabcut && !rect1.isNull())
    {
        if(rect2.isNull())
        {
            rectSelection = new QRubberBand(QRubberBand::Rectangle, this);
        }
        rect2 = QPoint(event->x(), event->y());

        //verification de l'ordre des points
        int tmpX = rect1.x();
        int tmpY = rect1.y();

        rect1.setX(min(rect1.x(), rect2.x()));
        rect2.setX(max(tmpX, rect2.x()));

        rect1.setY(min(rect1.y(), rect2.y()));
        rect2.setY(max(tmpY, rect2.y()));

        rectSelection->setGeometry(rect1.x()+label->pos().x(), rect1.y()+label->pos().y(), rect2.x() - rect1.x(), rect2.y() - rect1.y());
        rectSelection->show();
    }
}

/************************************************************************************************
                                                                                                *
Fonctions menu fichier                                                                          *
                                                                                                *
************************************************************************************************/


void ZoneCentrale::ouvrir()
{
    QString path = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    QFile file("save.data");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream flux(&file);
    flux << path << endl;

    nouvelleImage(path);

}


void ZoneCentrale::sauvegarde()
{
    QString path = QFileDialog::getSaveFileName(this, "Sauvegarder l'image", QString(), "Images (*.png *.gif *.jpg *.jpeg)");

    image->save(path);
}


/************************************************************************************************
                                                                                                *
Fonctions menu édition                                                                          *
                                                                                                *
************************************************************************************************/


void ZoneCentrale::annuler()
{
    QPixmap* t = imagePrec;
    imagePrec = image;
    image = t;

    emit imageChange(image);

    nouveauLayout(*image);
}


void ZoneCentrale::passerModeDecoupage()
{
    modeDecoupage = true;
}

void ZoneCentrale::passerModeGrabcut()
{
    modeGrabcut = true;
}

void ZoneCentrale::grabcutRect()
{
    //ImageRGB* im = new ImageRGB(image->toImage());
    //nouvelleImage(im->grabcut(rect1, rect2));
}

void ZoneCentrale::ouvrirPreferences()
{
    Preferences* p = new Preferences(affichageInfos, RGB, this);
    connect(p, SIGNAL(changeMode(bool)), this,  SLOT(modeRGB(bool)));
    connect(p, SIGNAL(changeInfo(bool)), this, SLOT(modeInfo(bool)));
    p->show();
}

void ZoneCentrale::modeRGB(bool b)
{
    RGB = b;
    emit modeChange(RGB);
    emit imageChange(this->image);
}

void ZoneCentrale::modeInfo(bool b)
{
    RGB = b;
}


/************************************************************************************************
                                                                                                *
Fonctions menu affichage                                                                        *
                                                                                                *
************************************************************************************************/


void ZoneCentrale::zoomIn()
{
    nouvelleImage(image->scaled(image->size()*1.2));
}

void ZoneCentrale::zoomOut()
{
    nouvelleImage(image->scaled(image->size()*0.8));
}

void ZoneCentrale::zoomIn(int val)
{
    for(int i = 0; i < val; i++)
        nouvelleImage(image->scaled(image->size()*1.2));
}

void ZoneCentrale::zoomOut(int val)
{
    for(int i = 0; i < val; i++)
        nouvelleImage(image->scaled(image->size()*0.8));
}







void ZoneCentrale::changeAfficheInfos(bool b)
{
    affichageInfos = b;
}

void ZoneCentrale::ouvrirHistogramme()
{
    FenetreHistogramme* fen = new FenetreHistogramme(this->image);
    fen->show();
    connect(this, SIGNAL(imageChange(QPixmap*)), fen, SLOT(majHisto(QPixmap*)));
    connect(this, SIGNAL(modeChange(bool)), fen, SLOT(changeMode(bool)));
}






/************************************************************************************************
                                                                                                *
Fonctions menu image                                                                            *
                                                                                                *
************************************************************************************************/

void ZoneCentrale::convertToNEtB()
{
    if(image != NULL)
    {
        imagePrec = new QPixmap(*image);
        ImageRGB* newIm = new ImageRGB(image->toImage());
        newIm->convertToNEtB();
        image->convertFromImage(*newIm);
        imageZoomZero = new QPixmap(*image);



        emit imageChange(image);

        nouvelleImage(*image);
    }
}


void ZoneCentrale::ouvrirTaille()
{
    FenetreTaille* taille = new FenetreTaille(new ImageRGB(image->toImage()), this);
    taille->show();
    connect(taille, SIGNAL(changeImage(ImageRGB)), this,  SLOT(nouvelleImage(ImageRGB)));
}


void ZoneCentrale::seamCarving()
{
    imagePrec = new QPixmap(*image);
    ImageRGB* newIm = new ImageRGB(image->toImage());

    for(int i = 0; i < 20 ; i++)
        newIm = new ImageRGB(newIm->seamCarvingHauteur());
    nouvelleImage(newIm->seamCarvingHauteur());

 //   nouvelleImage(newIm->seamCarvingHauteur(20));
}

void ZoneCentrale::afficherSeamCarving()
{
    imagePrec = new QPixmap(*image);
    ImageRGB* newIm = new ImageRGB(image->toImage());
    nouvelleImage(newIm->affichageSeamCarvingHauteur());
}

void ZoneCentrale::ouvrirLumEtCont()
{
    LumEtCont* lum = new LumEtCont(new ImageRGB(image->toImage()), this);
    lum->show();
    connect(lum, SIGNAL(changeImage(ImageRGB)), this,  SLOT(nouvelleImage(ImageRGB)));
}





/************************************************************************************************
                                                                                                *
Fonctions menu filtre                                                                           *
                                                                                                *
************************************************************************************************/


//utilisation du laplacien
void ZoneCentrale::Rehaussement()
{
    ImageRGB* lisse   = new ImageRGB(image->toImage());
    nouvelleImage(lisse->filtretrois(matRehauss,8));
}



//utilisation du laplacien
void ZoneCentrale::Contour2()
{
    // http://www.optique-ingenieur.org/fr/cours/OPI_fr_M04_C05/co/Contenu.html
    ImageRGB* origine = new ImageRGB(image->toImage());
    ImageRGB* sortie = new ImageRGB(image->toImage());
    ImageRGB* lissage = new ImageRGB(image->toImage());

    int convolution1[3][3];

    convolution1[0][0] = -1;
    convolution1[0][1] = -1;
    convolution1[0][2] = -1;

    convolution1[1][0] = -1;
    convolution1[1][1] =  16;
    convolution1[1][2] = -1;

    convolution1[2][0] = -1;
    convolution1[2][1] = -1;
    convolution1[2][2] = -1;


    *lissage = lissage->filtretrois(convolution1 ,8);
    sortie->operationImage(*origine,*lissage,-1);

    nouvelleImage(*sortie);


}




//utilisation du gradient
void ZoneCentrale::Contour()
{
/*    // http://www.optique-ingenieur.org/fr/cours/OPI_fr_M04_C05/co/Contenu.html
    ImageRGB* sortie = new ImageRGB(image->toImage());

    int convolution1[3][3];
    int convolution2[3][3];

    int alpha = 2;
    convolution1[0][0] = 1;
    convolution1[0][1] = alpha;
    convolution1[0][2] = 1;

    convolution1[1][0] = 0;
    convolution1[1][1] = 0;
    convolution1[1][2] = 0;

    convolution1[2][0] = -1;
    convolution1[2][1] = -alpha;
    convolution1[2][2] = -1;

    convolution2[0][0] = 1;
    convolution2[0][1] = 0;
    convolution2[0][2] = -1;

    convolution2[1][0] = alpha;
    convolution2[1][1] = 0;
    convolution2[1][2] = -alpha;

    convolution2[2][0] = 1;
    convolution2[2][1] = 0;
    convolution2[2][2] = -1;


    sortie->gradient(convolution1 ,convolution2,2+alpha);
    imagePrec = new QPixmap(*image);
    image = new QPixmap();
    image->convertFromImage(*sortie);
    emit imageChange(image);
    nouveauLayout(*image);
    this->update();*/
}



void ZoneCentrale::moyenneur3x3()
{
    ImageRGB* im = new ImageRGB(image->toImage());
    nouvelleImage(im->filtretrois(moy3,9));
}


void ZoneCentrale::moyenneur5x5()
{
    ImageRGB* im = new ImageRGB(image->toImage());
    nouvelleImage(im->filtrecinq(moy5,25));
}

void ZoneCentrale::gradient()
{
    ImageRGB* im = new ImageRGB(image->toImage());
    nouvelleImage(im->gradient());
}




