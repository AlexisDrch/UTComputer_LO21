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
    QFrame* Clavier1;
    QFrame* Clavier2;
    QHBoxLayout* coucheClavier1;
    QHBoxLayout* coucheClavier2;
    QVBoxLayout* coucheClavier;
    QVBoxLayout* clavNum;

    QVBoxLayout* clavOp;
    QVBoxLayout* clavLog;
    QVBoxLayout* clavLog2;
    QVBoxLayout* clavPile;
    QHBoxLayout* h1clavNum;
    QHBoxLayout* h2clavNum;
    QHBoxLayout* h3clavNum;

    QVBoxLayout* clavOp2;
    QHBoxLayout* h1clavNum2;
    QHBoxLayout* h2clavNum2;
    QHBoxLayout* h3clavNum2;
    QPushButton* button17;

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
    QPushButton* button14;
    QPushButton* button22;
    QPushButton* button32;
    QPushButton* button42;
    QPushButton* button52;
    QPushButton* button62;
    QPushButton* button72;
    QPushButton* button82;
    QPushButton* button92;
    QPushButton* button15;
    QPushButton* button16;
    QPushButton* button23;
    QPushButton* button33;
    QPushButton* button43;
    QPushButton* button53;
    QPushButton* button63;
    QPushButton* button73;
    QPushButton* button83;
    QPushButton* button93;
    QPushButton* button24;
    QPushButton* button34;
    QPushButton* button44;
    QPushButton* button54;
    QPushButton* button64;

    QPushButton* button25;
    QPushButton* button35;
    QPushButton* button45;
    QPushButton* button55;
    QPushButton* button65;

    QPushButton* button27;
    QPushButton* button37;
    QPushButton* button47;
    QPushButton* button57;
    QPushButton* button67;

    QPushButton* button0;
    QPushButton* buttonplus;
    QPushButton* buttonmoins;
    QPushButton* buttonmul;
    QPushButton* buttondiv;
    QPushButton* buttonEnter;
    QRadioButton* buttonClavier1;
    QButtonGroup* buttonNum;
    QButtonGroup* buttonOp;
public slots:
    void setCommandeText(int);
    void hideClavier1();
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
