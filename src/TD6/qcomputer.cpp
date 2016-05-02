#include "qcomputer.h"

QComputer::QComputer()
{
    message= new QLineEdit;
    vuePile = new QTableWidget;
    commande = new QLineEdit;
    mainLayout = new QVBoxLayout;
    coucheHaut =  new QVBoxLayout;
    coucheClavier = new QHBoxLayout;
    pile = new Pile;
    ExpressionManager& em = ExpressionManager::getInstance();
    controleur = new Controleur(em, *pile) ;

    //Layout
        //Haut
        coucheHaut->addWidget(message);
        coucheHaut->addWidget(vuePile);
        coucheHaut->addWidget(commande);
        mainLayout->addLayout(coucheHaut);
        //Clavier Cliquable
        clavNum = new QVBoxLayout;
        clavOp = new QVBoxLayout;
            //ClavNum
            h1clavNum = new QHBoxLayout;
            h2clavNum = new QHBoxLayout;
            h3clavNum = new QHBoxLayout;
            button1 = new QPushButton("1");
            button2 = new QPushButton("2");
            button4 = new QPushButton("3");
            button3 = new QPushButton("4");
            button5 = new QPushButton("5");
            button6 = new QPushButton("6");
            button7 = new QPushButton("7");
            button8 = new QPushButton("8");
            button9 = new QPushButton("9");
            button0 = new QPushButton("0");
            h1clavNum->addWidget(button1);
            h1clavNum->addWidget(button2);
            h1clavNum->addWidget(button3);
            h2clavNum->addWidget(button4);
            h2clavNum->addWidget(button5);
            h2clavNum->addWidget(button6);
            h3clavNum->addWidget(button7);
            h3clavNum->addWidget(button8);
            h3clavNum->addWidget(button9);
            clavNum->addLayout(h1clavNum);
            clavNum->addLayout(h2clavNum);
            clavNum->addLayout(h3clavNum);
            clavNum->addWidget(button0);
            coucheClavier->addLayout(clavNum);
            //ClavOP
            buttonplus = new QPushButton("+");
            buttonmoins = new QPushButton("-");
            buttonmul = new QPushButton("*");
            buttondiv = new QPushButton("/");
            buttonEnter = new QPushButton("Entrée");
            clavOp->addWidget(buttonplus);
            clavOp->addWidget(buttonmoins);
            clavOp->addWidget(buttonmul);
            clavOp->addWidget(buttondiv);
            clavOp->addWidget(buttonEnter);
            clavOp->setSizeConstraint(QLayout::SetMinimumSize);
            coucheClavier->addLayout(clavOp);

       mainLayout->addLayout(coucheClavier);

    setLayout(mainLayout);


}

void QComputer::refresh(){

}

void QComputer::getNextCommande(){


}
