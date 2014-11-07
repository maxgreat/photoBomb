#include "fenetreinfo.h"

FenetreInfo::FenetreInfo(QWidget *parent) :
    QWidget(parent, Qt::ToolTip)
{
    setFixedSize(50,50);
}


void FenetreInfo::changePosition(int x, int y)
{
    move(x,y);
}
