#include "operatorLogique.h"

//OpLogiqueBinaire
OpLogiqueBinaire::~OpLogiqueBinaire(){}

Litterale* OpLogiqueBinaire::fonctionNum(Nombres* arg1, Litterale* arg2){
    LitNumerique* conv1 = dynamic_cast<LitNumerique*>(arg1);
    LitNumerique* conv2 = dynamic_cast<LitNumerique*>(arg2);
    if (conv1 != nullptr  && conv2 != nullptr) return actionLogiNumerique(conv1, conv2);
    else throw ComputerException("Operation < impossible sur ces littéraux");
}

Litterale* OpLogiqueBinaire::fonctionExpression(LitExpression* arg1, Litterale* arg2){
    QString symb = this->getName();
    LitExpression* conv2 = dynamic_cast<LitExpression*>(arg2);
    if (conv2 != nullptr){
        QString valArg2 = arg2->toString();
        delete arg2;
        return (new LitExpression("("+arg1->toString()+")"+" "+symb+" "+"("+valArg2+")"));
    }
    else{
        //Ici le second argument doit être transformer en litterale expression avant.
        LitExpression* conv2 = new LitExpression(arg2->toString());
        Litterale* old = arg2;
        arg2 = conv2;
        delete old;
        return (new LitExpression("("+arg1->toString()+")"+" "+symb+" "+"("+arg2->toString()+")"));
    }
}

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
