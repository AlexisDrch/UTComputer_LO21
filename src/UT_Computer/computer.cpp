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

Litterale* LitteraleManager::isRationelle(const QString& v){

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
        Litterale *l = (new Rationelle(num,den,num + "/" + den))->simplification();
        return l;
    }
    else return (nullptr);

}

bool LitteraleManager::verifLitterale(const QString& v){
    //Todo
    return true;
}

// Fabrique des litterales selon l'étude de la string input en commande
Litterale* LitteraleManager::fabriqLitterale(const QString& v) {
    bool ok=false;

       unsigned int val = v.toLongLong(&ok); if(ok){return (new Entier(val));}
       float val2 = v.toFloat(&ok) ; if(ok){return (new Reelle(val2));}

       // Factorielle : to do
       QString::const_iterator it = v.end(); it--;
       if ( ((*v.begin()) == "'") && ((*it) == "'") ) return(new LitExpression(v));
       if ( ((*v.begin()) == '[') && ((*it) == ']') ) return(new LitProgramme(v));
       Litterale* l = isRationelle(v); if ( l != nullptr) return l; else delete l;

    return (new LitAtome(v+"dead"));
}

Litterale& LitteraleManager::addLitterale(const QString& v){
    if(verifLitterale(v)){ // surement pas utile car test déjà effectuer dans commande du controleur
        if (nb==nbMax) agrandissementCapacite();
        Litterale* newLit = fabriqLitterale(v);
        lits[nb++] = newLit;
        return *lits[nb-1];
    }
   else throw ComputerException("Error instance impossible");
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
    Rationelle* newe5 = dynamic_cast<Rationelle*>(&lit);if (newe5 != nullptr){return "New : RATIONNELLE" ;}
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
        if ( ( (*it == "'") && (*it2 == "'")) || ((*it == '[') && (*it2 == ']')) ) return c;
        it2++;
        QString sPart;
        while (it != it2 && *it !=' '){
            sPart.push_back(*it); it++;
        }
        return sPart;

    }

    QString Controleur::commande(QString& v){

    QString newe = v;
    QString c= getFirst(v);
    newe.replace(0, c.size()+1, "");


    bool test;
    test = true;

    try {
        QVector<Litterale*> temp; // stockage temporaire des littérales passées en argument de l'opérateur
        Operateur* op = getOperateur(c);
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
                if(conv1 == nullptr){ //POURQUOI NE PAS GERER DANS L'OPERATEUR DIRECTEMENT ??
                //Seulement si execution sans déclenchement d'exception :
                for(unsigned int i =0; i <opSize; i++){
                    litMng.removeLitterale(litAff.top()); //si tout s'est bien passé on pop la pile deux fois + littmanager
                    litAff.pop();
                }
                Litterale& e=litMng.addLitterale(res);
                litAff.push(e);
                litAff.setMessage(litAff.getMessage() + " *** "+ litMng.messageNouvelleCreation(e));
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

    }catch(ComputerException& ex) {

        litAff.setMessage(ex.getInfo());
        if (test){

            litAff.setMessage(ex.getInfo() + " passage test");
        if (litMng.verifLitterale(c)){ //nombre or expression or Programme

        litAff.push(litMng.addLitterale(c));
        litAff.setMessage(litMng.messageNouvelleCreation(litAff.top()));

        }else if (isVariable(c)){ // recherche dans la bdd (map variable)
            //recup litterale
            //empiler res dans la pile
        }else if (isVarProgramme(c)){ // recherche dans la bdd (map programme)
            // recup litterale programme
            // evaluation
            // empiler res dans la pile
        } // sinon creation d'une nouvelle litterale Expression
        }
        else {
            return v;
            //litAff.setMessage("Erreur : commande inconnue");
        }
    }

    return newe;
}



