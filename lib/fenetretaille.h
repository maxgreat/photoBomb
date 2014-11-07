#ifndef FENETRETAILLE_H
#define FENETRETAILLE_H

#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include "imageRGB.h"
#include <stdio.h>

class FenetreTaille : public QDialog
{
    Q_OBJECT
public:
    explicit FenetreTaille(ImageRGB* image = 0, QWidget *parent = 0);

signals:
    void changeImage(ImageRGB image);

public slots:
    void changeProp(bool b);
    void changeLargeur(int val);
    void changeHauteur(int val);
    void valider();
    void annuler();

private:
    bool proportionnel;
    ImageRGB imagePrec;
    ImageRGB* image;
    QSpinBox* BoxHauteur;
    QSpinBox* BoxLargeur;
    int largeurImage;
    int hauteurImage;
    double valProp;
    bool changePourProp;

};

#endif // FENETRETAILLE_H
