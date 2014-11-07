#include "fenetretaille.h"

FenetreTaille::FenetreTaille(ImageRGB* image, QWidget *parent) :
    QDialog(parent)
{
    if(image != NULL)
    {
        setFixedSize(260,160);
        proportionnel = true;

        this->image = image;
        this->imagePrec = *image;

        this->valProp = (double)(image->width()) / (double)(image->height());

        QVBoxLayout *layout = new QVBoxLayout;

        QCheckBox* prop = new QCheckBox("Conserver les proportions", this);
        prop->setChecked(true);
        layout->addWidget(prop);
        connect(prop, SIGNAL(toggled(bool)), this, SLOT(changeProp(bool)));


        QLabel* text1 = new QLabel("hauteur", this);
        layout->addWidget(text1);

        BoxHauteur = new QSpinBox(this);
        BoxHauteur->setMinimum(1);
        BoxHauteur->setMaximum(10000);
        BoxHauteur->setValue(image->height());
        hauteurImage = image->height();
        layout->addWidget(BoxHauteur);
        connect(BoxHauteur, SIGNAL(valueChanged(int)), this, SLOT(changeHauteur(int)));


        QLabel* text2 = new QLabel("Largeur", this);
        layout->addWidget(text2);

        BoxLargeur = new QSpinBox(this);
        BoxLargeur->setMinimum(1);
        BoxLargeur->setMaximum(10000);
        BoxLargeur->setValue(image->width());
        largeurImage = image->width();
        layout->addWidget(BoxLargeur);
        connect(BoxLargeur, SIGNAL(valueChanged(int)), this, SLOT(changeLargeur(int)));


        QHBoxLayout* layout2 = new QHBoxLayout;
        QPushButton* bouton_annuler = new QPushButton("Annuler", this);
        layout2->addWidget(bouton_annuler);
        connect(bouton_annuler, SIGNAL(clicked()), this, SLOT(annuler()));

        QPushButton* bouton_ok = new QPushButton("OK", this);
        layout2->addWidget(bouton_ok);
        layout->addLayout(layout2);
        connect(bouton_ok, SIGNAL(clicked()), this, SLOT(valider()));

        this->changePourProp = false;

        this->setLayout(layout);
    }
    else
        this->close();
}



void FenetreTaille::changeProp(bool b)
{
    proportionnel = b;
}



void FenetreTaille::changeLargeur(int val)
{
    if(!changePourProp)
    {

        if(proportionnel)
        {
            largeurImage = val;
            hauteurImage = (int)((double)largeurImage / valProp);

            changePourProp = true;

            BoxHauteur->setValue(hauteurImage);
        }
        else
        {
            largeurImage = val;
        }
        changePourProp = false;
    }
}

void FenetreTaille::changeHauteur(int val)
{
    if(!changePourProp)
    {

        if(proportionnel)
        {
            hauteurImage = val;
            largeurImage = (int)((double)hauteurImage * valProp);
            changePourProp = true;
            BoxLargeur->setValue(largeurImage);
        }
        else
        {
            hauteurImage = val;
        }
        changePourProp = false;
    }
}




void FenetreTaille::valider()
{
    ImageRGB nIm = image->redimensionner(largeurImage,hauteurImage);
    emit changeImage(nIm);
}

void FenetreTaille::annuler()
{
    emit changeImage(imagePrec);
}

