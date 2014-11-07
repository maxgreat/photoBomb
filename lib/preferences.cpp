#include "preferences.h"

Preferences::Preferences(bool inf, bool mode,QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(200,150);

    QVBoxLayout* vLayout = new QVBoxLayout;


    QCheckBox* infos = new QCheckBox("Afficher informations?", this);
    vLayout->addWidget(infos);
    infos->setChecked(inf);
    connect(infos, SIGNAL(toggled(bool)), this, SLOT(afficherInfos(bool)));

    QLabel* text1 = new QLabel("Représentation des couleurs : ", this);
    vLayout->addWidget(text1);

    QComboBox* couleur = new QComboBox(this);
    couleur->addItem("RGB");
    couleur->addItem("YUV");
    if(mode)
        couleur->setCurrentText("RGB");
    else
        couleur->setCurrentText("YUV");
    vLayout->addWidget(couleur);
    connect(couleur, SIGNAL(currentIndexChanged(QString)), this, SLOT(choixRGB(QString)));


    QCheckBox* def = new QCheckBox("Choix par défaut?", this);
    vLayout->addWidget(def);
    connect(def, SIGNAL(toggled(bool)), this, SLOT(parDefaut(bool)));


    QHBoxLayout* hLayout = new QHBoxLayout;

    QPushButton* bouton_annuler = new QPushButton("Annuler", this);
    hLayout->addWidget(bouton_annuler);
    connect(bouton_annuler, SIGNAL(clicked()), this, SLOT(annuler()));

    QPushButton* bouton_ok = new QPushButton("OK", this);
    hLayout->addWidget(bouton_ok);
    vLayout->addLayout(hLayout);

    connect(bouton_ok, SIGNAL(clicked()), this, SLOT(valider()));

    this->setLayout(vLayout);
}

void Preferences::valider()
{
    emit changeMode(modeCouleur);
    this->close();
}

void Preferences::annuler()
{
    this->close();
}

void Preferences::choixRGB(QString s)
{
    if(s.compare("rgb", Qt::CaseInsensitive) == 0)
        modeCouleur = true;
    else
        modeCouleur = false;
}


void Preferences::parDefaut(bool b)
{
    sauvegarde = b;
}

void Preferences::afficherInfos(bool b)
{
    informations = b;
    emit changeInfo(b);
}



