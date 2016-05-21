#include "computer.h"
#include <algorithm>

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
       if ( ((*v.begin()) == "[") && ((*it) == "]") ) return(new LitProgramme(v));

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

void Pile::agrandissementCapacite() {
	Item* newtab=new Item[(nbMax+1)*2];
	for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
	Item*  old=items;
	items=newtab;
	nbMax=(nbMax+1)*2;
	delete[] old;
}

void Pile::push(Litterale& e){
	if (nb==nbMax) agrandissementCapacite();
    items[nb].setLitterale(e);
	nb++;
    modificationEtat();
}

void Pile::pop(){
	nb--;
	items[nb].raz();
    modificationEtat();
}
/*
void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
	for(int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getLitterale().toString()<<"\n";
        else f<<i<<": \n";
	}
    f<<"---------------------------------------------\n";
}*/


Pile::~Pile(){
	delete[] items;
}

Litterale& Pile::top() const {
	
    if (nb==0) throw ComputerException("aucune Litterale sur la pile");
    return items[nb-1].getLitterale();
}
	

bool isVariable(const QString s){
    //check in map var
    return false;
}

bool isVarProgramme(const QString s){
    //check in map var programme
    return false;
}

bool estUnOperateur(const QString s){
	if (s=="+") return true;
	if (s=="-") return true;
	if (s=="*") return true;
	if (s=="/") return true;
	return false;
}

bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}

Operateur* Controleur::getOperateur(const QString &v) {
    if(factories.contains(v)){
        litAff.setMessage(v+" execution");
        OperateurFactory* fact= factories.operator [](v);
        return fact->getOperateur();
    }
    else throw(ComputerException("Not an operator"));
}

void Controleur::commande(const QString& c){

bool test;
test = true;

try {
    Operateur* op = getOperateur(c);
    unsigned int opSize = op->getTaille();
    if(litAff.taille() >= opSize){

        for(unsigned int i =0; i <opSize; i++){
            op->addArg(litAff.top()); // ici on récupère l'item de la pile
            litMng.removeLitterale(litAff.top());
            litAff.pop();
        }
        Litterale* res = op->executer();        
        test = false;
        Litterale& e=litMng.addLitterale(res);
        litAff.push(e);
        litAff.setMessage(litAff.getMessage() + " *** "+ litMng.messageNouvelleCreation(e));
        delete op; //detruit les litterales qui ne sont plus à jour

     }else{
            litAff.setMessage("Erreur : pas assez d'arguments");
     }

}catch(ComputerException& ex) {

    litAff.setMessage(ex.getInfo());
    if (test){
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
        litAff.setMessage("Erreur : commande inconnue");
    }

}
}



