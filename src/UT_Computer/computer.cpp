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

bool LitteraleManager::verifLitterale(QString& operande,QString& nouvelle, QVector<Operande*>& vectorExp){
    Litterale*res = fabriqLitterale(operande);
    if (res == nullptr) return false;
    nouvelle.push_back(operande);
    vectorExp.push_back(res);
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

QString LitteraleManager::verifExpressionValide(const QString& v, QVector<Operande*>& vectorExp){

    QString nouvelle;
    // vectorExp : Dedans possedera tous les operateurs de l'expression correctement initialisée avec les litteraux en arguments
    QMap<QString, OperateurFactory*> factories = OperateurFactory::getFactoriesMap();
    QString::const_iterator fin = v.end(); fin--; //on retire le ' finale
    QString::const_iterator deb = v.begin(); deb++;    //on retire le ' debut
    unsigned int sizeNewOp=0;
    bool binaryToFull = true;

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
                    else if(sizeNewOp == 2)
                        vectorExp.push_front(newOp);
                    nouvelle.push_back(operande);
                    operande ="";
                }
                else {//Cas ou le curseur s'est arrete car on a trouvé un operande potentiel
                    if(operande!=""){
                        if(!verifLitterale(operande,nouvelle,vectorExp)) return "false";
                    }
                    //Cas ou le curseur s'est arrete car on a trouvé un espace ou parenthèse
                     if(*deb=='(' || *deb==')') { nouvelle.push_back(*deb); deb++;}
                     else if (factories.contains(*deb)){
                         OperateurFactory* fact= factories.operator [](*deb);
                         Operateur* newOp = (fact->getOperateur());
                         sizeNewOp = newOp->getTaille();
                         if(sizeNewOp == 1)
                             vectorExp.push_back(newOp);
                         else if(sizeNewOp == 2)
                             vectorExp.push_front(newOp); // On push le nouvel operateur symbole au début de de la pile +(1,1)
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
    verif=true;

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
    }
       //Expression ou Programme
       QString::const_iterator it = v.end(); it--;

       //Expression
       if ( ((*v.begin()) == '\'') && ((*it) == '\'')){
           QVector<Operande*> *vectExp = new QVector<Operande*>;
           QString str = verifExpressionValide(v,*vectExp);
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


bool isVariable(const QString s){
    //check in map var
    return false;
}

bool isVarProgramme(const QString s){
    //check in map var programme
    return false;
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
                temp.push_back(&litAff.top()); //POURQUOI PAS LITERALE MANAGER ?
                op->addArg(&litAff); // ici on récupère l'item de la pile ou la pile pour l'operateur pile -- ON AJOUTE PLUS DANS LITTERALEMANAGER?
                litAff.pop();
            }
            for(unsigned int i =0; i <opSize; i++){
                litAff.push(*temp.at(temp.size()-(i+1)));//On les remet temporairement  // ICI ON REMOVERAIT LE LIT MANA
            }
            Litterale* res = op->executer();
                if(conv1 == nullptr && !(v=="STO" && res == nullptr)){ //POURQUOI NE PAS GERER DANS L'OPERATEUR DIRECTEMENT ??
                //Seulement si execution sans déclenchement d'exception :
                    for(unsigned int i =0; i <opSize; i++){
                        litMng.removeLitterale(litAff.top()); //si tout s'est bien passé on pop la pile deux fois + littmanager
                        litAff.pop();
                    }
                    if (v!="STO" && res != nullptr) {
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
        if(res != nullptr){
            litAff.push(*res);
            litAff.setMessage(litMng.messageNouvelleCreation(litAff.top()));
        }else if (isVariable(c)){
            // recherche dans la bdd (map variable)
            //recup litterale
            //empiler res dans la pile
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



