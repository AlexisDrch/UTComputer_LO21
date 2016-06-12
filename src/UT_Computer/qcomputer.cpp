#include "qcomputer.h"
#include "operator.h"

QComputer::QComputer()
{
    vuePrincipale = new QFrame;
    vueVar = new QFrame;vueVar->setWindowTitle("Votre stock de variable");
    vueProg = new QFrame;
    vuePara = new QFrame;
    message= new QLineEdit;
    message->setDisabled(true);
    commande = new QLineEdit;
    mainLayout = new QVBoxLayout;
    secondLayout = new QVBoxLayout;
    coucheHaut =  new QVBoxLayout;
    coucheCommande = new QHBoxLayout;
    coucheClavier= new QVBoxLayout;
    coucheClavier1 = new QHBoxLayout;
    coucheClavier2 = new QHBoxLayout;
    pile = new Pile;
    setterNbAffiche = new QSpinBox;
    setterNbAffiche->setValue(pile->getNbItemsToAffiche());
    setterNbAffiche->setMaximum(20);
    setterNbAffiche->setMinimum(4);
    vuePile = new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    tableVar = new QTableWidget(5,1,this); //getNbtoAffiche
    Clavier1 = new QFrame;
    Clavier2 = new QFrame;
    LitteraleManager& lm = LitteraleManager::getInstance();
    stockVar = StockVariable::getInstance(); //Vue secondaire
    controleur = new Controleur(lm, *pile) ;


    message->setReadOnly(true);
    message->setText("Bienvenue");
    message->setStyleSheet("background: blue; color: white");

    //Pile
    QStringList nombres;
    for (unsigned int i=pile->getNbItemsToAffiche();i>0;i--){
        QString str=QString::number(i);
        str+=" :";
        nombres<<str;
    }
    vuePile->setVerticalHeaderLabels(nombres);

    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    for (unsigned int i=0;i<pile->getNbItemsToAffiche();i++)
        vuePile->setItem(i,0,new QTableWidgetItem(""));

//Vue secondaire
    //tableau Variable Stocké

    tableVar->setRowCount(stockVar->getNbItemsToAffiche());
    QStringList nombres2;
    for (unsigned int i= 1; i< stockVar->getNbItemsToAffiche()+1;i++){ // define avec le sV.getnNbToAFfiche
        QString str2=QString::number(i);
        str2+=" )";
        nombres2<<str2;
    }
    tableVar->setVerticalHeaderLabels(nombres2);

    tableVar->horizontalHeader()->setVisible(false);
    tableVar->horizontalHeader()->setStretchLastSection(true);
    for (unsigned int i=0;i<stockVar->getNbItemsToAffiche();i++){
        tableVar->setItem(i,0,new QTableWidgetItem(""));
    }
    secondLayout->addWidget(tableVar);
    vueVar->setLayout(secondLayout);


    // Création des menus
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
        QAction *actionQuitter = menuFichier->addAction("&Quitter");
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        actionQuitter->setIcon(QIcon("quitter.png"));

    QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
        QAction* actionVuePrinc = menuAffichage->addAction("Vue principale");
            connect(actionVuePrinc, SIGNAL(triggered()), this, SLOT(setVuePrinc()));
        QAction* actionVueVar = menuAffichage->addAction("Stock variables");
            connect(actionVueVar, SIGNAL(triggered()), this, SLOT(setVueVar()));
        QAction* actionVueProg = menuAffichage->addAction("Stock programmes");
            connect(actionVueProg, SIGNAL(triggered()), this, SLOT(setVueProg()));
        QAction* actionVuePara = menuAffichage->addAction("Paramètres");
            connect(actionVuePara, SIGNAL(triggered()), this, SLOT(setVuePara()));

    // Création de la barre d'outils
    QToolBar *toolBarFichier = addToolBar("Fichier");
    toolBarFichier->addAction(actionQuitter);

    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    //Style

    Clavier1->setFrameStyle(QFrame::Box);
    Clavier1->setFrameShadow(QFrame::Sunken);
    Clavier1->setLineWidth(2);
    Clavier1->setMidLineWidth(3);
    Clavier2->setFrameStyle(QFrame::Box);
    Clavier2->setFrameShadow(QFrame::Sunken);
    Clavier2->setLineWidth(2);
    Clavier2->setMidLineWidth(3);

    //Layout
        //Haut
        coucheMessage = new QHBoxLayout;
        coucheMessage->addWidget(message);
        coucheMessage->addWidget(setterNbAffiche);
        coucheHaut->addLayout(coucheMessage);
        coucheHaut->addWidget(vuePile);
        coucheCommande->addWidget(commande);
        buttonClavier1 = new QRadioButton("pad"); buttonClavier1->setMaximumWidth(55);
        coucheCommande->addWidget(buttonClavier1);
        coucheHaut->addLayout(coucheCommande);
        mainLayout->addLayout(coucheHaut);
        //Clavier Cliquable
        clavNum = new QVBoxLayout;
        clavLog = new QVBoxLayout;
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
            coucheClavier1->addLayout(clavNum);

            //ClavOP
            buttonplus = new QPushButton("+"); buttonplus->setShortcut(QKeySequence(Qt::Key_Plus));
            buttonmoins = new QPushButton("-");buttonmoins->setShortcut(QKeySequence(Qt::Key_Minus));
            buttonmul = new QPushButton("*");buttonmul->setShortcut(QKeySequence(Qt::Key_multiply));
            buttondiv = new QPushButton("/");buttondiv->setShortcut(QKeySequence(Qt::Key_division));
            buttonEnter = new QPushButton("Entrée");
            buttonOp = new QButtonGroup;
            buttonOp->addButton(buttonplus);buttonOp->setId(buttonplus,10);
            buttonOp->addButton(buttonmoins);buttonOp->setId(buttonmoins,11);
            buttonOp->addButton(buttonmul);buttonOp->setId(buttonmul,12);
            buttonOp->addButton(buttondiv);buttonOp->setId(buttondiv,13);
            clavOp->addWidget(buttonplus);
            clavOp->addWidget(buttonmoins);
            clavOp->addWidget(buttonmul);
            clavOp->addWidget(buttondiv);
            clavOp->addWidget(buttonEnter);
            clavOp->setSizeConstraint(QLayout::SetMinimumSize);
            coucheClavier1->addLayout(clavOp);

            //Clavlog

            clavPile = new QVBoxLayout;
            button17 = new QPushButton("=");
            button25 = new QPushButton("!=");
            button35 = new QPushButton("=<");
            button45 = new QPushButton(">=");
            button55 = new QPushButton("<");
            button65 = new QPushButton(">");
            buttonOp->addButton(button17);buttonOp->setId(button17,17);
            buttonOp->addButton(button25);buttonOp->setId(button25,25);
            buttonOp->addButton(button35);buttonOp->setId(button35,35);
            buttonOp->addButton(button45);buttonOp->setId(button45,45);
            buttonOp->addButton(button55);buttonOp->setId(button55,55);
            buttonOp->addButton(button65);buttonOp->setId(button65,65);
            clavLog->addWidget(button25);
            clavLog->addWidget(button35);
            clavLog->addWidget(button45);
            clavLog->addWidget(button55);
            clavLog->addWidget(button65);
            coucheClavier1->addLayout(clavLog);

            //ClavPile
            button27 = new QPushButton("DUP");
            button37 = new QPushButton("DROP");
            button47 = new QPushButton("CLEAR");
            button57 = new QPushButton("SWAP");
            button67 = new QPushButton("EDIT");
            buttonOp->addButton(button27);buttonOp->setId(button27,27);
            buttonOp->addButton(button37);buttonOp->setId(button37,37);
            buttonOp->addButton(button47);buttonOp->setId(button47,47);
            buttonOp->addButton(button57);buttonOp->setId(button57,57);
            buttonOp->addButton(button67);buttonOp->setId(button67,67);
            clavPile->addWidget(button27);
            clavPile->addWidget(button37);
            clavPile->addWidget(button47);
            clavPile->addWidget(button57);
            clavPile->addWidget(button67);
            coucheClavier1->addLayout(clavPile);

            coucheClavier->addLayout(coucheClavier1);
            Clavier1->setLayout(coucheClavier);
       mainLayout->addWidget(Clavier1);

       //Clavier2
       clavOp2 = new QVBoxLayout;
       clavLog2 = new QVBoxLayout;

           //ClavNum
           h1clavNum2 = new QHBoxLayout;
           h2clavNum2 = new QHBoxLayout;
           h3clavNum2 = new QHBoxLayout;
           button14 = new QPushButton("DIV");
           button22 = new QPushButton("MOD");
           button32 = new QPushButton("POW");
           button42 = new QPushButton("NEG");
           button52 = new QPushButton("SIN");
           button62 = new QPushButton("COS");
           button72 = new QPushButton("TAN");
           button82 = new QPushButton("ARCSIN");
           button92 = new QPushButton("ARCCOS");
           button15 = new QPushButton("SQRT");
           button23 = new QPushButton("EXP");
           button33 = new QPushButton("LN");
           button43 = new QPushButton("NUM");
           button53 = new QPushButton("DEN");
           button63 = new QPushButton("$");
           button73 = new QPushButton("RE");
           button83 = new QPushButton("IM");
           button93 = new QPushButton("ARG");
           button16 = new QPushButton("NORM");

           buttonNum->addButton(button14);buttonNum->setId(button14,14);
           buttonNum->addButton(button22);buttonNum->setId(button22,22);
           buttonNum->addButton(button32);buttonNum->setId(button32,32);
           buttonNum->addButton(button42);buttonNum->setId(button42,42);
           buttonNum->addButton(button52);buttonNum->setId(button52,52);
           buttonNum->addButton(button62);buttonNum->setId(button62,62);
           buttonNum->addButton(button72);buttonNum->setId(button72,72);
           buttonNum->addButton(button82);buttonNum->setId(button82,82);
           buttonNum->addButton(button92);buttonNum->setId(button92,92);
           buttonNum->addButton(button15);buttonNum->setId(button15,15);
           buttonNum->addButton(button16);buttonNum->setId(button16,16);
           buttonNum->addButton(button23);buttonNum->setId(button23,23);
           buttonNum->addButton(button33);buttonNum->setId(button33,33);
           buttonNum->addButton(button43);buttonNum->setId(button43,43);
           buttonNum->addButton(button53);buttonNum->setId(button53,53);
           buttonNum->addButton(button63);buttonNum->setId(button63,63);
           buttonNum->addButton(button73);buttonNum->setId(button73,73);
           buttonNum->addButton(button83);buttonNum->setId(button83,83);
           buttonNum->addButton(button93);buttonNum->setId(button93,93);

           h1clavNum2->addWidget(button14);
           h1clavNum2->addWidget(button22);
           h1clavNum2->addWidget(button32);
           h2clavNum2->addWidget(button42);
           h2clavNum2->addWidget(button52);
           h2clavNum2->addWidget(button62);
           h3clavNum2->addWidget(button72);
           h3clavNum2->addWidget(button82);
           h3clavNum2->addWidget(button92);

           h1clavNum2->addWidget(button15);
           h1clavNum2->addWidget(button16);
           h1clavNum2->addWidget(button23);
           h1clavNum2->addWidget(button33);
           h2clavNum2->addWidget(button43);
           h2clavNum2->addWidget(button53);
           h2clavNum2->addWidget(button63);
           h3clavNum2->addWidget(button73);
           h3clavNum2->addWidget(button83);
           h3clavNum2->addWidget(button93);
           clavOp2->addLayout(h1clavNum2);
           clavOp2->addLayout(h2clavNum2);
           clavOp2->addLayout(h3clavNum2);
           coucheClavier2->addLayout(clavOp2);
           //Clavlog2
           button24 = new QPushButton("AND");
           button34 = new QPushButton("OR");
           button44 = new QPushButton("NOT");
           button54 = new QPushButton("EVAL");
           button64 = new QPushButton("STO");
           buttonNum->addButton(button24);buttonNum->setId(button24,24);
           buttonNum->addButton(button34);buttonNum->setId(button34,34);
           buttonNum->addButton(button44);buttonNum->setId(button44,44);
           buttonNum->addButton(button54);buttonNum->setId(button54,54);
           buttonNum->addButton(button64);buttonNum->setId(button64,64);
           clavLog2->addWidget(button24);
           clavLog2->addWidget(button34);
           clavLog2->addWidget(button44);
           clavLog2->addWidget(button54);
           clavLog2->addWidget(button64);
           coucheClavier2->addLayout(clavLog2);
           Clavier2->setLayout(coucheClavier2),
           coucheClavier->addWidget(Clavier2);

    vuePrincipale->setLayout(mainLayout);
    setCentralWidget(vuePrincipale);

    //Connection SIGNAUX/SLOTS
   QObject::connect(buttonNum, SIGNAL(buttonClicked(int)),this, SLOT(setCommandeText(int)));
   QObject::connect(buttonOp, SIGNAL(buttonClicked(int)),this, SLOT(setCommandeText(int)));
   QObject::connect(buttonClavier1, SIGNAL(clicked(bool)), this, SLOT(hideClavier1()));
   QObject::connect(setterNbAffiche, SIGNAL(valueChanged(int)),this, SLOT(changeNbAffiche(int)));
   QObject::connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
   QObject::connect(buttonEnter,SIGNAL(clicked(bool)), this, SLOT(getNextCommande()));
   QObject::connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));  
   QObject::connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));

   refresh(); // permet d'initialiser l'affichage de la pile avec les valeurs stockées
}

void QComputer::refresh(){

    message->setText(pile->getMessage());
    //Pile principale
    for (unsigned int i=0; i<pile->getNbItemsToAffiche(); i++)
        vuePile->item(i,0)->setText("");

    unsigned int nb=0;
    for (Pile::iterator it = pile->begin(); it != pile->end() && nb < pile->getNbItemsToAffiche();++it){
        vuePile->item(pile->getNbItemsToAffiche()-nb-1,0)->setText((*it).toString());
        nb++;
    }

    //Stock variable
    for (unsigned int i=0; i<stockVar->getNbItemsToAffiche(); i++)
        tableVar->item(i,0)->setText("");

    unsigned int nb1=0;
    for (QMap<QString,Nombres*>::iterator it = stockVar->listeVar.begin(); it != stockVar->listeVar.end() && nb1 < stockVar->getNbItemsToAffiche();++it){
        QString val = it.key() + " | " + ((*it))->toString();
        tableVar->item(nb1,0)->setText(val);
        nb1++;
    }

}

void QComputer::getNextCommande(){

    pile->setMessage("");
    QString s = commande->text();
    commande->setText(controleur->commande(s));
    //commande->clear();
}

void QComputer::changeNbAffiche(int i){

    pile->setNbItemsToAffiche(i);
    vuePile->setRowCount(pile->getNbItemsToAffiche());
    QStringList nombres;
    for (unsigned int i=pile->getNbItemsToAffiche();i>0;i--){
        QString str=QString::number(i);
        str+=" :";
        nombres<<str;
    }
    vuePile->setVerticalHeaderLabels(nombres);

    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    for (unsigned int i=0;i<pile->getNbItemsToAffiche();i++)
        vuePile->setItem(i,0,new QTableWidgetItem(""));
    refresh();
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

        if(s==14) str="DIV";
        if(s==15) str="SQRT";
        if(s==16) str="NORM";
        if(s==17) str="=";

        if(s==22) str="MOD";
        if(s==32) str="POW";
        if(s==42) str="NEG";
        if(s==52) str="SIN";
        if(s==62) str="COS";
        if(s==72) str="TAN";
        if(s==82) str="ARCSIN";
        if(s==92) str="ARCCOS";

        if(s==23) str="EXP";
        if(s==33) str="LN";
        if(s==43) str="NUM";
        if(s==53) str="DEN";
        if(s==63) str="$";
        if(s==73) str="RE";
        if(s==83) str="IM";
        if(s==93) str="ARG";

        if(s==24) str="AND";
        if(s==34) str="OR";
        if(s==44) str="NOT";
        if(s==54) str="EVAL";
        if(s==63) str="STO";

        if(s==25) str="!=";
        if(s==35) str="=<";
        if(s==45) str=">=";
        if(s==55) str="<";
        if(s==65) str=">";


        if(s==27) str="DUP";
        if(s==37) str="DROP";
        if(s==47) str="CLEAR";
        if(s==57) str="SWAP";
        if(s==67) str="EDIT";

    }
    commande->setText(str);

}
void QComputer::hideClavier1(){
    if(buttonClavier1->isChecked()){
    buttonClavier1->setText("+");
    Clavier1->hide();
    }else {
        buttonClavier1->setText("-");
        //Clavier2->hide();
        Clavier1->show();
    }

}

void QComputer::setVuePrinc(){
    //vueVar->hide();
    vuePrincipale->show();
}
void QComputer::setVueVar(){
    //vuePrincipale->hide();
    vueVar->show();
}
void QComputer::setVueProg(){
    vuePrincipale->hide();
}
void QComputer::setVuePara(){
    vuePrincipale->hide();
}
