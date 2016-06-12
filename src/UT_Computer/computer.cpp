#include "computer.h"
#include <algorithm>
class ComputerException;
LitteraleManager::Handler LitteraleManager::handler=LitteraleManager::Handler();


LitteraleManager& LitteraleManager::getInstance(){
    if (handler.instance==nullptr) handler.instance=new LitteraleManager;
	return *handler.instance;
}

void LitteraleManager::libererInstance(){
	delete handler.instance;
	handler.instance=nullptr;
}


void LitteraleManager::agrandissementCapacite() {
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=lits[i];
    Litterale**  old=lits;
    lits=newtab;
	nbMax=(nbMax+1)*2;
	delete old;
}

Litterale* LitteraleManager::isRationnelle(const QString& v){

    bool rationnel = true, premiere_partie = true, seconde_partie = true;
    int i=0, temp, num, den;
    while (premiere_partie && i<v.size()-1) {
        if (!v.at(i).isNumber())
            premiere_partie = false;
        i++;
    }
    if (i==1 || v.at(i-1) != '/')
        rationnel = false;
    temp = i;
    num = v.left(i-1).toInt();
    while (rationnel && seconde_partie && i<v.size()) {
        if (!v.at(i).isNumber())
            seconde_partie = false;
        i++;
    }
    if (i+1 == v.size())
        rationnel = false;
    den = v.right(v.size()-(temp)).toInt();

    if (rationnel) {
        Rationnelle* r = new Rationnelle(num,den,num + "/" + den);
        Litterale *l = r->simplification();
        delete r;
        return l;
    }
    else return (nullptr);

}

bool isVariable(LitAtome* a){
      QString s = a->toString();
      StockVariable* sv = StockVariable::getInstance();
      //adapter de la map
      return sv->contains(s);
}

bool isVarProgramme(const QString s){
    //check in map var programme
    return false;
}
	
Litterale* LitteraleManager::isComplexe(const QString& v) {
    if(v.contains("$") && !v.contains("'") && !v.contains("[")) {
        bool neg = false;
        QString part1 = v.mid(0,v.indexOf("$"));
        if (part1.at(0) == '-') {
            part1 = part1.mid(2,part1.size());
            neg = true;
        }
        Litterale* l1 = fabriqLitterale(part1);
        LitNumerique* ln1 = dynamic_cast<LitNumerique*>(l1); // aucun risque car le complexe stocké est valide
        ln1->setNeg(neg);

        neg = false;
        QString part2 = v.mid(v.indexOf("$")+1,v.size());
        if (part2.at(0) == '-') {
            part2 = part2.mid(2,part2.size());
            neg = true;
        }
        Litterale* l2 = fabriqLitterale(part2);
        LitNumerique* ln2 = dynamic_cast<LitNumerique*>(l2); // aucun risque car le complexe stocké est valide
        ln2->setNeg(neg);

		if (ln1 != nullptr && ln2 != nullptr)
			return new Complexe(ln1,ln2);
		delete ln1, ln2;
    }
    return nullptr;
}

bool LitteraleManager::verifLitterale(QString& operande,QString& nouvelle, QVector<Operande*>& vectorExp){
    Litterale*res = fabriqLitterale(operande);
    if (res == nullptr) return false;
    LitAtome* a = dynamic_cast<LitAtome*>(res);
    //traitement des variables
    if (a != nullptr){
        if (isVariable(a)) {
            StockVariable* sv = StockVariable::getInstance();
            //on recupère la littérale stockée
            Nombres* resVar = sv->at(a->toString());
            delete a;
            vectorExp.push_back(resVar);
    }
            vectorExp.push_back(res);
    }
    else {
        vectorExp.push_back(res);
    }
    nouvelle.push_back(operande);
    operande ="";
    return true;
}

//EVAL
/*
 Algo recursif :
    fonction EVAL(LitteraleExpression* litExp) :
    if (op) {
        op->addArg(Litterale* res1 = EVAL(EXP1));
        if(Op.size>1){
            op->addArg(Litterale* res2 = EVAL(EXP2));
        }
        return op->exectuer
    }
    else return fabriqueLitterale(LitExp->toString());
 */

QString LitteraleManager::verifExpressionValide(QString v, QVector<Operande*>& vectorExp){

    QString nouvelle;
    // vectorExp : Dedans possedera tous les operateurs de l'expression correctement initialisée avec les litteraux en arguments
    QMap<QString, OperateurFactory*> factories = OperateurFactory::getFactoriesMap();
    QString::const_iterator fin = v.end(); fin--; //on retire le ' finale
    QString::const_iterator deb = v.begin();     //on retire le ' debut

    unsigned int sizeNewOp=0;
    bool binaryToFull = true;
    unsigned int k =0;

        while (deb != fin){
            if(*deb != ' '){
                QString operande;
                // On parcourt le string tant que non Fin à la recherche d'operateur (contenu dans la facorie) ou de chaine de caractère
                while (deb !=fin && !factories.contains(*deb) && !factories.contains(operande) && *deb != ' ' && *deb !='(' && *deb != ')' ) {
                    operande.push_back(*deb);
                    ++deb;
                }
                if(deb==fin){
                    if(operande!=""){
                        if(!verifLitterale(operande,nouvelle,vectorExp)) return "false";
                    }

                    return nouvelle;
                }//Cas ou le curseur s'est arrete car on a trouvé un operateur
                if(factories.contains(operande)){
                    OperateurFactory* fact= factories.operator [](operande);
                    Operateur* newOp = (fact->getOperateur());
                    sizeNewOp = newOp->getTaille();
                    if(sizeNewOp == 1)
                        vectorExp.push_back(newOp);
                    else if(sizeNewOp == 2){
                        vectorExp.push_front(newOp); k=1;}
                    nouvelle.push_back(operande);
                    operande ="";
                }
                else {//Cas ou le curseur s'est arrete car on a trouvé un operande potentiel
                    if(operande!=""){
                        if(!verifLitterale(operande,nouvelle,vectorExp)) return "false";
                    }
                    //Cas ou le curseur s'est arrete car on a trouvé un espace ou parenthèse : recursivité apparait
                     if(*deb=='(' ){
                         nouvelle.push_back(*deb);deb++;
                         QString newOperand;
                         while(*deb!= ')'&& deb !=fin) {
                             newOperand +=*deb;deb++;
                         }
                         if(deb == fin) return false;
                         newOperand+=*deb;
                         QVector<Operande*> *vectExp = new QVector<Operande*>;
                         QString str = verifExpressionValide(newOperand,*vectExp);
                         if (str != "false"){                         //Si faux : on renvoie en ligne de commande
                          LitExpression* newLit = new LitExpression(str);
                          newLit->setVector(*vectExp);
                          nouvelle.push_back(newOperand);
                          vectorExp.push_back(newLit);
                          //k==1 ? vectorExp.push_front(newLit): vectorExp.push_back(newLit);
                          k=0;
                          deb++;
                         }
                         else return "false";
                     }
                     else if (factories.contains(*deb)){
                         OperateurFactory* fact= factories.operator [](*deb);
                         Operateur* newOp = (fact->getOperateur());
                         sizeNewOp = newOp->getTaille();
                         if(sizeNewOp == 1)
                             vectorExp.push_back(newOp);
                         else if(sizeNewOp == 2){
                             vectorExp.push_front(newOp);k=1;} // On push le nouvel operateur symbole au début de de la pile +(1,1)
                         nouvelle.push_back(*deb); deb++;
                     }
                }
            }else deb ++;
        }
    return nouvelle;
}

// Fabrique des litterales selon l'étude de la string input en commande
Litterale* LitteraleManager::fabriqLitterale(const QString& v) {
    bool ok=false;
    //verif=true;

    if(v.at(0).isNumber()){
       unsigned int val = v.toLongLong(&ok); if(ok){return (new Entier(val));}
       float val2 = v.toFloat(&ok) ; if(ok){
           Reelle r(val2);
           Litterale* res = r.simplification();
           return res;
       }

       QString::const_iterator it = v.end(); it--;
       if ( ((*v.begin()) == '\'') && ((*it) == '\'') ) return(new LitExpression(v));
       if ( ((*v.begin()) == '[') && ((*it) == ']') ) return(new LitProgramme(v));
       Litterale* l = isRationnelle(v); if ( l != nullptr) return l; else delete l;
       Litterale* c = isComplexe(v); if ( c != nullptr) return c; else delete c;
    }


   //Expression ou Programme
   QString::const_iterator it = v.end(); it--;

    //Expression
    if ( ((*v.begin()) == '\'') && ((*it) == '\'')){
       QString v2 = v; v2.remove(0,1); v2.remove(v2.size()+1,1);
       QVector<Operande*> *vectExp = new QVector<Operande*>;
       QString str = verifExpressionValide(v2,*vectExp);
       if (str != "false"){                         //Si faux : on renvoie en ligne de commande
        LitExpression* newLit = new LitExpression(str);
        newLit->setVector(*vectExp);
        return newLit;
       }
       else return nullptr;
    }
    //Programme
    if ( ((*v.begin()) == '[') && ((*it) == ']') ){
        return(new LitProgramme(v));
    }

    //Atome
    bool atome = false;
    if (v.at(0).isUpper()) {
        atome = true;
        int i = 0;
        while (i<v.size() && atome) {
           if (!(v.at(i).isUpper() || v.at(i).isNumber())) {
               atome = false;
           }
           i++;
        }
    }
    if (atome)
    return new LitAtome(v);

    //setVerif(false);
    return nullptr;//(new LitExpression(v+"dead")); //car atome beug pour l'instant
}

Litterale* LitteraleManager::addLitterale(const QString& v){
    //if(verifLitterale(v)){ // surement pas utile car test déjà effectuer dans commande du controleur
        if (nb==nbMax) agrandissementCapacite();
        Litterale* newLit = fabriqLitterale(v);
        lits[nb++] = newLit;
        return lits[nb-1];
    //}
   //else throw ComputerException("Error instance impossible");
}

Litterale& LitteraleManager::addLitterale(Litterale* res){
        if (nb==nbMax) agrandissementCapacite();
        Litterale* newLit = res;
        lits[nb++] = newLit;
        return *lits[nb-1];
}

void LitteraleManager::removeLitterale(Litterale& e){
    unsigned int i=0;
    while(i<nb && lits[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Litterale inexistante");
    lits[i]=0; // le litterale sera reellement détruit avec l'operateur dans algo commande du controler
	i++;
    while(i<nb) { lits[i-1]=lits[i]; i++; }
	nb--;
}

LitteraleManager::~LitteraleManager(){
    for(unsigned int i=0; i<nb; i++) delete lits[i];
    delete[] lits;
}

Litterale& Item::getLitterale() const {
        if (lit==nullptr) throw ComputerException("Item : tentative d'acces a une Litterale inexistante");
        return *lit;
}


QString LitteraleManager::messageNouvelleCreation(Litterale& lit){
    LitExpression* newe = dynamic_cast<LitExpression*>(&lit); if (newe != nullptr){return "New : EXPRESSION";}
    LitProgramme* newe2 = dynamic_cast<LitProgramme*>(&lit); if (newe2 != nullptr){return "New : PROGRAMME";}
    Entier* newe3 = dynamic_cast<Entier*>(&lit); if (newe3 != nullptr){return "New : ENTIER";}
    Reelle* newe4 = dynamic_cast<Reelle*>(&lit); if (newe4 != nullptr){return "New : REELLE";}
    Rationnelle* newe5 = dynamic_cast<Rationnelle*>(&lit);if (newe5 != nullptr){return "New : Rationnelle" ;}
    Complexe* newe6 = dynamic_cast<Complexe*>(&lit);if (newe6 != nullptr){return "New : Complexe" ;}
    LitAtome* newe7 = dynamic_cast<LitAtome*>(&lit);if (newe7 != nullptr){return "New : Atome" ;}
    return "";
}



//III] Controleur
    Operateur* Controleur::getOperateur(const QString &v) {
        if(factories.contains(v)){
            litAff.setMessage(v+" execution");
            OperateurFactory* fact= factories.operator [](v);
            return fact->getOperateur();
        }
        else throw(ComputerException("Not an operator"));
    }

    QString Controleur::getFirst(QString& c){

        QString::const_iterator it = c.begin(); QString::const_iterator it2 = c.end();
        if (it == it2){ return "";}
        it2--;
        if ( ( (*it == '\'') && (*it2 == '\'')) || ((*it == '[') && (*it2 == ']')) ) return c;
        it2++;
        QString sPart;
        while (it != it2 && *it !=' '){
            sPart.push_back(*it); it++;
        }
        return sPart;

    }

    QString Controleur::commande(QString& v){
    if(v!=""){

    QString newe = v;
    QString c= getFirst(v);
    newe.replace(0, c.size()+1, "");


    bool test;
    test = true;

    try {
        Operateur* op = getOperateur(c);
        QVector<Litterale*> temp; // stockage temporaire des littérales passées en argument de l'opérateur
        OpPile* conv1 = dynamic_cast<OpPile*>(op);//Va changer le comportement de l'algorithme sur la pile

        test = false;
        unsigned int opSize = op->getTaille();
        if(litAff.taille() >= opSize){

            for(unsigned int i =0; i <opSize; i++){
                temp.push_back(&litAff.top());
                //Eval on renvoie simplemement
                LitProgramme* conv3 = dynamic_cast<LitProgramme*>(temp.at(0));
                if(conv3 != nullptr && op->getName()=="EVAL"){
                     litAff.pop();
                     litMng.removeLitterale(litAff.top());
                    return conv3->getValueProg();
                }
                op->addArg(&litAff); // ici on récupère l'item de la pile ou la pile pour l'operateur pile -- ON AJOUTE PLUS DANS LITTERALEMANAGER?
                litAff.pop();
            }
            for(unsigned int i =0; i <opSize; i++){
                litAff.push(*temp.at(temp.size()-(i+1)));
            }
            Litterale* res = op->executer();
            LitExpression* conv2 = dynamic_cast<LitExpression*>(res);

            if(conv1 == nullptr && !(v=="STO" && res == nullptr)){ //POURQUOI NE PAS GERER DANS L'OPERATEUR DIRECTEMENT ??
           //Seulement si execution sans déclenchement d'exception :
               for(unsigned int i =0; i <opSize; i++){
                   litMng.removeLitterale(litAff.top()); //si tout s'est bien passé on pop la pile deux fois + littmanager
                   litAff.pop();
               }
               if(conv2 != nullptr){//Cas des expressions
                   QString v2 ='\''+conv2->toString()+'\'';
                   commande(v2);
                   delete conv2;
               }
               else if (v!="STO" && res != nullptr) {
                   Litterale& e=litMng.addLitterale(res);
                   litAff.push(e);
                   litAff.setMessage(litAff.getMessage() + " *** "+ litMng.messageNouvelleCreation(e));
               }
          }
            delete op; //detruit les litterales qui ne sont plus à jour


         }else{
                if(bip->state() == QMediaPlayer::PlayingState){
                    bip->setPosition(0);
                }
                else if(bip->state() == QMediaPlayer::StoppedState){
                    bip->play(); // play error sound
                }
                litAff.setMessage("Erreur : pas assez d'arguments");
                return v;
         }

    }catch(ComputerException& ex) { //PB sur le ln avec reel !!

        litAff.setMessage(ex.getInfo());
        if (test){

        litAff.setMessage(ex.getInfo() + " passage test");

        Litterale* res = litMng.addLitterale(c);
        LitAtome* a = dynamic_cast<LitAtome*>(res);
        //traitement des variables
        if (a != nullptr){
            if (isVariable(a)) {
                StockVariable* sv = StockVariable::getInstance();
                //on recupère la littérale stockée
                Nombres* resVar = sv->at(a->toString());
                litMng.removeLitterale(*res);
                delete a;
                litAff.push(*resVar);
                litMng.addLitterale(resVar);
                litAff.setMessage(litMng.messageNouvelleCreation(litAff.top()));
            } else if (isVarProgramme(c)) {

            }
            else {

                litAff.setMessage("Erreur : impossible de saisir un atome qui n'est pas un identificateur");
                delete a;
                return v;
            }
        }
        else if(res != nullptr){
            litAff.push(*res);
            litAff.setMessage(litMng.messageNouvelleCreation(litAff.top()));
        }else if (isVarProgramme(c)){
            // recherche dans la bdd (map programme)
            // recup litterale programme
            // evaluation
            // empiler res dans la pile
        }else {
            litAff.setMessage("Erreur : vérifier la validité de votre syntaxe");
            return v; // sinon creation d'une nouvelle litterale Expression
        }}
        else {
            return v;
            //litAff.setMessage("Erreur : commande inconnue");
        }
    }

    return newe;
    }
    return "";
}

