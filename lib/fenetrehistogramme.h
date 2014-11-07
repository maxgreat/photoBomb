#ifndef FENETREHISTOGRAMME_H
#define FENETREHISTOGRAMME_H

#include <QLabel>
#include <QDialog>
#include <QImage>
#include <QPixmap>
#include <QGridLayout>
#include <QRgb>
#include "imageRGB.h"
#include "zonecentrale.h"

class FenetreHistogramme : public QWidget
{
    Q_OBJECT
public:
    explicit FenetreHistogramme();
    explicit FenetreHistogramme(QPixmap* image);

signals:
    
public slots:
    void majHisto(QPixmap* nouvelleImage);
    void changeMode(bool modeRGB);

private:
    QLabel* label;
    QImage* histogramme;
    QPixmap* histoAfficher;
    bool modeCouleur;
    
};

#endif // FENETREHISTOGRAMME_H
