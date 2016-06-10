#ifndef QCOMPUTER_H
#define QCOMPUTER_H
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QApplication>
#include <QTableWidget>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QVBoxLayout>
#include<QMdiArea>
#include <QHeaderView>
#include <QMainWindow>
#include <QKeyEvent>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QObject>
#include <QLCDNumber>
#include <QSpinBox>
#include "computer.h"

class QComputer : public QMainWindow {
    Q_OBJECT
    QFrame* vuePrincipale;
    QFrame* vueProg;
    QFrame* vuePara;
    QLineEdit* message;
    QSpinBox* setterNbAffiche;
    QHBoxLayout* coucheMessage;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* mainLayout;
    QVBoxLayout* coucheHaut;
    Pile* pile;
    Controleur* controleur;

    //Vue secondaire
    StockVariable* stockVar;
    QVBoxLayout* secondLayout;
    QFrame* vueVar ;
    QTableWidget* tableVar;

    //Clavier cliquable
    QFrame* pad;
    QHBoxLayout* coucheClavier;
    QVBoxLayout* clavNum;
    QVBoxLayout* clavOp;
    QHBoxLayout* h1clavNum;
    QHBoxLayout* h2clavNum;
    QHBoxLayout* h3clavNum;
    QHBoxLayout* coucheCommande; 
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
    QRadioButton* buttonPad;
    QButtonGroup* buttonNum;
    QButtonGroup* buttonOp;
public slots:
    void setCommandeText(int);
    void hidePad();
    void setVuePrinc();
    void setVueVar();
    void setVueProg();
    void setVuePara();

public:
    explicit QComputer();
    public slots: void refresh();
    void getNextCommande();
    void changeNbAffiche(int i);


};

#endif // QCOMPUTER_H
