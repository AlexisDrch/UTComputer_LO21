#include "pile.h"

//Pile
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


    Pile::~Pile(){
        delete[] items;
    }

    Litterale& Pile::top() const {

        if (nb==0) throw ComputerException("aucune Litterale sur la pile");
        return items[nb-1].getLitterale();
    }




