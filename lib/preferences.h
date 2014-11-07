#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include "zonecentrale.h"

class Preferences : public QDialog
{
    Q_OBJECT
public:
    explicit Preferences(bool inf, bool mode, QWidget *parent = 0);

signals:
    void changeMode(bool mode);
    void changeInfo(bool mode);

public slots:
    void valider();
    void annuler();
    void choixRGB(QString s);
    void parDefaut(bool);
    void afficherInfos(bool);

private:
    bool modeCouleur;
    bool sauvegarde;
    bool informations;

};

#endif // PREFERENCES_H
