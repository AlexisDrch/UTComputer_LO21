#include "operatorLogique.h"

//OpLogiqueBinaire
OpLogiqueBinaire::~OpLogiqueBinaire(){}

Litterale* OpLogiqueBinaire::fonctionNum(Nombres* arg1, Litterale* arg2){
    LitNumerique* conv1 = dynamic_cast<LitNumerique*>(arg1);
    LitNumerique* conv2 = dynamic_cast<LitNumerique*>(arg2);
    if (conv1 != nullptr  && conv2 != nullptr) return actionLogiNumerique(conv1, conv2);
    else throw ComputerException("Operation < impossible sur ces littéraux");
}

Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Entier& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Reelle& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Rationnelle& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Reelle& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Entier& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Rationnelle& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Rationnelle& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Entier& arg2){ throw ("Error ");}
Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Reelle& arg2){ throw ("Error ");}


//OpInf
Litterale* OpInf::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2)  { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue()< arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpSup
Litterale* OpSup::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue()> arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpEg
Litterale* OpEg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue() == arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpDif
Litterale* OpDiff::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue() != arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpInfeg
Litterale* OpInfeg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue()<= arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpSupeg
Litterale* OpSupeg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue()>= arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpAnd
Litterale* OpAnd::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue() && arg2->getValue())? (new Entier(1)) :new Entier(0));
}
//OpOr
Litterale* OpOr::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
     return ((arg1->getValue() || arg2->getValue())? (new Entier(1)) :new Entier(0));
}
