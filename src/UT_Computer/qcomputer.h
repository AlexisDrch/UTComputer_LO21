#ifndef QCOMPUTER_H
#define QCOMPUTER_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QKeyEvent>
#include <QDebug>
#include <QObject>
#include "computer.h"

class QComputer : public QWidget{
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* mainLayout;
    QVBoxLayout* coucheHaut;
    Pile* pile;
    Controleur* controleur;

    //Clavier cliquable
    QHBoxLayout* coucheClavier;
    QVBoxLayout* clavNum;
    QVBoxLayout* clavOp;
    QHBoxLayout* h1clavNum;
    QHBoxLayout* h2clavNum;
    QHBoxLayout* h3clavNum;
    QPushButton* button1;
    QPushButton* button2;
    QPushButton* button3;
    QPushButton* button4;
    QPushButton* button5;
    QPushButton* button6;
    QPushButton* button7;
    QPushButton* button8;
    QPushButton* button9;
    QPushButton* button0;
    QPushButton* buttonplus;
    QPushButton* buttonmoins;
    QPushButton* buttonmul;
    QPushButton* buttondiv;
    QPushButton* buttonEnter;
    QButtonGroup* buttonNum;
    QButtonGroup* buttonOp;
public slots:
    void setCommandeText(int s);

public:
    explicit QComputer();
    public slots: void refresh();
    void getNextCommande();


};

#endif // QCOMPUTER_H
