#ifndef FENETREINFO_H
#define FENETREINFO_H

#include <QWidget>

class FenetreInfo : public QWidget
{
    Q_OBJECT
public:
    explicit FenetreInfo(QWidget *parent = 0);

signals:

public slots:
    void changePosition(int x, int y);
};

#endif // FENETREINFO_H
