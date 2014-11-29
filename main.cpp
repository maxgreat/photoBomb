/****************************************************************
* Autors : Maxime PORTAZ
*   (past) Pierre BANWARTH
*
* Version actuelle : 1.0
*
*
*****************************************************************/



#include "mainwindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
