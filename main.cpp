/****************************************************************
* Auteurs : Maxime PORTAZ                                       *
            Pierre BANWARTH                                     *
*                                                               *
* Version actuelle : Release 1.0                                *
*                                                               *
*                                                               *
*                                                               *
*                                                               *
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
