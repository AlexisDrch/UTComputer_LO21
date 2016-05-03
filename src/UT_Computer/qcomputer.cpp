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
            button1 = new QPushButton("1"); button1->setShortcut(QKeySequence(Qt::Key_1));
            button2 = new QPushButton("2"); button2->setShortcut(QKeySequence(Qt::Key_2));
            button3 = new QPushButton("3"); button3->setShortcut(QKeySequence(Qt::Key_3));
            button4 = new QPushButton("4"); button4->setShortcut(QKeySequence(Qt::Key_4));
            button5 = new QPushButton("5"); button5->setShortcut(QKeySequence(Qt::Key_5));
            button6 = new QPushButton("6"); button6->setShortcut(QKeySequence(Qt::Key_6));
            button7 = new QPushButton("7"); button7->setShortcut(QKeySequence(Qt::Key_7));
            button8 = new QPushButton("8"); button8->setShortcut(QKeySequence(Qt::Key_8));
            button9 = new QPushButton("9"); button9->setShortcut(QKeySequence(Qt::Key_9));
            button0 = new QPushButton("0"); button0->setShortcut(QKeySequence(Qt::Key_0));
            buttonNum = new QButtonGroup;
            buttonNum->addButton(button0);buttonNum->setId(button0,0);
            buttonNum->addButton(button1);buttonNum->setId(button1,1);
            buttonNum->addButton(button2);buttonNum->setId(button2,2);
            buttonNum->addButton(button3);buttonNum->setId(button3,3);
            buttonNum->addButton(button4);buttonNum->setId(button4,4);
            buttonNum->addButton(button5);buttonNum->setId(button5,5);
            buttonNum->addButton(button6);buttonNum->setId(button6,6);
            buttonNum->addButton(button7);buttonNum->setId(button7,7);
            buttonNum->addButton(button8);buttonNum->setId(button8,8);
            buttonNum->addButton(button9);buttonNum->setId(button9,9);

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
            buttonplus = new QPushButton("+"); //buttonplus->setShortcut(QKeySequence(Qt::Key_Plus));
            buttonmoins = new QPushButton("-");//buttonmoins->setShortcut(QKeySequence(Qt::Key_Minus));
            buttonmul = new QPushButton("*");//buttonmul->setShortcut(QKeySequence(Qt::Key_multiply));
            buttondiv = new QPushButton("/");//buttondiv->setShortcut(QKeySequence(Qt::Key_division));
            buttonEnter = new QPushButton("Entrée");//buttonEnter->setShortcut(QKeySequence(Qt::Key_Enter));
            buttonOp = new QButtonGroup;
            buttonOp->addButton(buttonplus);buttonOp->setId(buttonplus,10);
            buttonOp->addButton(buttonmoins);buttonOp->setId(buttonmoins,11);
            buttonOp->addButton(buttonmul);buttonOp->setId(buttonmul,12);
            buttonOp->addButton(buttondiv);buttonOp->setId(buttondiv,13);
            buttonOp->addButton(buttonEnter);buttonOp->setId(buttonEnter,14);
            clavOp->addWidget(buttonplus);
            clavOp->addWidget(buttonmoins);
            clavOp->addWidget(buttonmul);
            clavOp->addWidget(buttondiv);
            clavOp->addWidget(buttonEnter);
            clavOp->setSizeConstraint(QLayout::SetMinimumSize);
            coucheClavier->addLayout(clavOp);

       mainLayout->addLayout(coucheClavier);

    setLayout(mainLayout);

    //Connection SIGNAUX/SLOTS
   QObject::connect(buttonNum, SIGNAL(buttonClicked(int)),this, SLOT(setCommandeText(int)));
   QObject::connect(buttonOp, SIGNAL(buttonClicked(int)),this, SLOT(setCommandeText(int)));


}

void QComputer::refresh(){

}

void QComputer::getNextCommande(){


}

void QComputer::setCommandeText(int s){
    QString str;
    if (s<10){
    str = QString::number(s);
    }
    else {
        if(s==10) str="+";
        if(s==11) str="-";
        if(s==12) str="*";
        if(s==13) str="/";
        if(s==14) str="ENTER";
    }
    commande->setText(str);

}
