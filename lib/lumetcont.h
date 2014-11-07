#ifndef LUMETCONT_H
#define LUMETCONT_H

#include <QDialog>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "imageRGB.h"

class LumEtCont : public QDialog
{
    Q_OBJECT
public:
    explicit LumEtCont(ImageRGB *image = 0, QWidget *parent = 0);


signals:
    void changeImage(ImageRGB image);

public slots:
    void majLum(int val);
    void majCont(int val);
    void valider();
    void annuler();

private:
    QSlider* barreLum;
    QSlider* barreCont;
    ImageRGB* image;
    int lumPrec;
    int contPrec;
    ImageRGB imagePrec;

};

#endif // LUMETCONT_H
