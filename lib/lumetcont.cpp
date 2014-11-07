#include "lumetcont.h"

LumEtCont::LumEtCont(ImageRGB* image, QWidget *parent) :
    QDialog(parent)
{
    if(image != NULL)
    {
        setFixedSize(200,150);

        this->image = image;
        this->imagePrec = *image;

        QLabel* text1 = new QLabel("Luminosité", this);
        QLabel* text2 = new QLabel("Contrastes", this);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(text1);

        barreLum = new QSlider(Qt::Horizontal, this);
        barreLum->setRange(-20,20);
        barreLum->setValue(0);
        lumPrec = 0;
        layout->addWidget(barreLum);
        connect(barreLum, SIGNAL(valueChanged(int)), this, SLOT(majLum(int)));


        layout->addWidget(text2);

        barreCont = new QSlider(Qt::Horizontal, this);
        barreCont->setRange(-100,100);
        barreLum->setValue(0);
        contPrec = 0;
        layout->addWidget(barreCont);
        connect(barreCont, SIGNAL(valueChanged(int)), this, SLOT(majLum(int)));


        QHBoxLayout* layout2 = new QHBoxLayout;
        QPushButton* bouton_annuler = new QPushButton("Annuler", this);
        layout2->addWidget(bouton_annuler);
        connect(bouton_annuler, SIGNAL(clicked()), this, SLOT(annuler()));

        QPushButton* bouton_ok = new QPushButton("OK", this);
        layout2->addWidget(bouton_ok);
        layout->addLayout(layout2);
        connect(bouton_ok, SIGNAL(clicked()), this, SLOT(valider()));

        this->setLayout(layout);
    }
    else
        this->close();
}

void LumEtCont::majLum(int val)
{
    image->luminosite(val - lumPrec);
    lumPrec = val;
    emit changeImage(*image);
}

void LumEtCont::majCont(int val)
{
    image->contraste(val - contPrec);
    contPrec = val;
    emit changeImage(*image);
}

void LumEtCont::valider()
{

}

void LumEtCont::annuler()
{
    emit changeImage(imagePrec);
    this->close();
}



















