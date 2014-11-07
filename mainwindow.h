#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtGui>
#include <QMdiArea>
#include <QString>
#include <QMessageBox>
#include <QEvent>
#include "lib/zonecentrale.h"
#include "lib/fenetrehistogramme.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow();
    bool eventFilter(QObject *, QEvent *);

public slots:    

private:
    //Variable global qui représente le centre de la zone, là où vont les images
    ZoneCentrale *centre;
    FenetreHistogramme* fenetreHisto;


};

#endif // MAINWINDOW_H
