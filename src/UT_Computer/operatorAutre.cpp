#include "operatorAutre.h"


OpAutre::~OpAutre(){

}

//STO
Litterale* OpSto::fonctionNum(Nombres* arg1, Litterale* arg2){
    LitExpression* le = dynamic_cast<LitExpression*>(arg2);

    if (le != nullptr) {

        QVector<Operande*>& vector = le->getVector();

        if (vector.size() == 1) {
            LitAtome* la = dynamic_cast<LitAtome*>(vector.at(0));
            if (la != nullptr) {
                StockVariable* s = StockVariable::getInstance();
                s->addVariable(la->getValue(),arg1);
                return new Entier(0);
            }
        }
    }
    return nullptr;
}

Litterale* OpSto::fonctionExpression(LitExpression *arg1, Litterale *arg2) {
    throw ComputerException("Arguments invalides");
}


//Dol
OpDol::~OpDol(){

}

Litterale* OpDol::fonctionExpression(LitExpression *arg1, Litterale *arg2) {
    throw ComputerException("Arguments invalides");
}

Litterale* OpDol::fonctionNum(Nombres *arg1, Litterale *arg2) {
    LitNumerique* conv1 = dynamic_cast<LitNumerique*>(arg1);
    LitNumerique* conv2 = dynamic_cast<LitNumerique*>(arg2);
    if (conv1 == nullptr || conv2 == nullptr)
        throw ComputerException("Arguments invalides");

    Complexe* c = new Complexe(conv1,conv2);
    return c;
}


//DIV
OpDivent::~OpDivent(){

}

Litterale* OpDivent::fonctionExpression(LitExpression *arg1, Litterale *arg2) {
    throw ComputerException("Arguments invalides");
}

Litterale* OpDivent::fonctionNum(Nombres *arg1, Litterale *arg2){
    Entier* n1 = dynamic_cast<Entier*>(arg1);
    Entier* n2 = dynamic_cast<Entier*>(arg2);
    if (n1 == nullptr || n2 == nullptr)
        throw ComputerException("Arguments invalides");

    int val = n1->getValue()/n2->getValue();
    Entier* res = new Entier(val);
    if (n1->getNeg() || n2->getNeg())
        res->setNeg(true);

    return res;
}


//MOD
OpMod::~OpMod(){

}

Litterale* OpMod::fonctionExpression(LitExpression *arg1, Litterale *arg2) {
    throw ComputerException("Arguments invalides");
}

Litterale* OpMod::fonctionNum(Nombres *arg1, Litterale *arg2){
    Entier* n1 = dynamic_cast<Entier*>(arg1);
    Entier* n2 = dynamic_cast<Entier*>(arg2);
    if (n1 == nullptr || n2 == nullptr)
        throw ComputerException("Arguments invalides");

    int val = (int)n1->getValue()%(int)n2->getValue();
    Entier* res = new Entier(val);
    if (n1->getNeg() || n2->getNeg())
        res->setNeg(true);

    return res;
}
