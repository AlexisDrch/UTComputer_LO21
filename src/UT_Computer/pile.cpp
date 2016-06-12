#include "pile.h"
#include "computer.h"

//Pile
    Pile::Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(5){
        DbManager* db = DbManager::getInstance(); // permet d'être sûr qu'on est connecté à la bd
        LitteraleManager& lm = LitteraleManager::getInstance();
        QSqlQuery query;
        if(query.exec("SELECT value FROM pile")){
            while(query.next()){
                bool neg = false;
                QString q = query.value(0).toString();
                if (q.at(0) == '-') {
                    q = q.mid(2,q.size());
                    neg = true;
                }

                Litterale* l = lm.fabriqLitterale(q);
                l->setNeg(neg);
                if (nb==nbMax) agrandissementCapacite();
                items[nb].setLitterale(*l);
                nb++;

                // ajout dans le littérale manager
                lm.addLitterale(l);
            }
        }
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

        // stockage en bd de la litterale créée
        DbManager* db = DbManager::getInstance();
        db->addPile(e.toString());
    }

    void Pile::pop(){
        nb--;
        Litterale& l = items[nb].getLitterale();
        items[nb].raz();
        modificationEtat();

        // enlever la littérale de la bd
        DbManager* db = DbManager::getInstance();
        db->removePile(l.toString());
    }


    Pile::~Pile(){
        delete[] items;
    }

    Litterale& Pile::top() const {

        if (nb==0) throw ComputerException("aucune Litterale sur la pile");
        return items[nb-1].getLitterale();
    }




