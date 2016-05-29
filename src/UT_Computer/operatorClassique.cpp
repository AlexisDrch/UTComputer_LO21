#include "operatorClassique.h"


Litterale* OpSymbole::fonctionNum(Nombres* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return fonctionNum2(conv, arg2);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return fonctionNum2(conv1, arg2);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return fonctionNum2(conv2, arg2);
}
Litterale* OpSymbole::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}
Litterale* OpSymbole::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}
Litterale* OpSymbole::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}

Litterale* OpSymbole::fonctionExpression(LitExpression* arg1, Litterale* arg2){
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


Litterale* OpCaractere::fonctionNum(Nombres* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return fonctionNum2(conv, arg2);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return fonctionNum2(conv1, arg2);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return fonctionNum2(conv2, arg2);
}
Litterale* OpCaractere::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}
Litterale* OpCaractere::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}
Litterale* OpCaractere::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
}

Litterale* OpCaractere::fonctionExpression(LitExpression* arg1, Litterale* arg2){
    QString str = this->getName();
    LitExpression* conv2 = dynamic_cast<LitExpression*>(arg2);
    if (conv2 != nullptr){
        QString valArg2 = arg2->toString();
        delete arg2;
        return (new LitExpression(str+"("+arg1->toString()+" , "+valArg2+")"));
    }
    else{
        //Ici le second argument doit être transformer en litterale expression avant.
        LitExpression* conv2 = new LitExpression(arg2->toString());
        Litterale* old = arg2;
        arg2 = conv2;
        delete old;
        return (new LitExpression(str+"("+arg1->toString()+","+arg2->toString()+")"));
    }
}

//OpPlus
Litterale* OpPlus::actionNum(Entier& arg1, Entier& arg2){
    long y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue();}
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue();}
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Entier* res = new Entier(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Entier& arg1, Reelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue();}
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Entier& arg1, Rationnelle& arg2){
    int num,den;
    bool neg;
    den = arg2.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=arg2.getNum() + arg1.getValue()*den; neg = true;}
    else if (arg1.getNeg()) {num=arg2.getNum() - arg1.getValue()*den;}
    else if (arg2.getNeg()) {num=-arg2.getNum() + arg1.getValue()*den;}
    else num=arg2.getNum() + arg1.getValue()*den;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}

Litterale* OpPlus::actionNum(Reelle& arg1, Reelle &arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Reelle& arg1, Entier& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue();  }
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Reelle& arg1, Rationnelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}

Litterale* OpPlus::actionNum(Rationnelle& arg1, Rationnelle& arg2){
    int num,den;
    bool neg = false;
    den = arg1.getDen() * arg2.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen(); neg = true;}
    else if (arg1.getNeg()) {num=-arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
    else if (arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();}
    else num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Rationnelle& arg1, Entier& arg2){
    int num,den;
    bool neg;
    den = arg1.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=arg1.getNum() + (int)arg2.getValue()*den; neg = true;}
    else if (arg1.getNeg()) {num=-arg1.getNum() + (int)arg2.getValue()*den;}
    else if (arg2.getNeg()) {num=arg1.getNum() - (int)arg2.getValue()*den;}
    else num=arg1.getNum() + (int)arg2.getValue()*den;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}
Litterale* OpPlus::actionNum(Rationnelle& arg1, Reelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
    else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
    else y = arg1.getValue() + arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
//OpMoins
Litterale* OpMoins::actionNum(Entier& arg1, Entier& arg2){
    long y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.getValue();}
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Entier* res = new Entier(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Entier& arg1, Reelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.getValue(); }
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Entier& arg1, Rationnelle& arg2){
    int num,den;
    bool neg;
    den = arg2.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=arg2.getNum() - arg1.getValue()*den;}
    else if (arg1.getNeg()) {num=-arg2.getNum() - arg1.getValue()*den;}
    else if (arg2.getNeg()) {num=arg2.getNum() + arg1.getValue()*den;}
    else num=-arg2.getNum() + (int)arg1.getValue()*den;
    int temp1 = -arg2.getNum();
    int temp2 = arg1.getValue();
    int temp3 = temp2*den;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Reelle& arg1, Reelle &arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.getValue();}
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Reelle& arg1, Entier& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue();}
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue();}
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Reelle& arg1, Rationnelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue(); }
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}

Litterale* OpMoins::actionNum(Rationnelle& arg1, Rationnelle& arg2){
    int num,den;
    bool neg = false;
    den = arg1.getDen() * arg2.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=-arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
    else if (arg1.getNeg()) {num=-arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();}
    else if (arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
    else num=arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Rationnelle& arg1, Entier& arg2){
    int num,den;
    bool neg;
    den = arg1.getDen();
    if(arg1.getNeg() && arg2.getNeg()) {num=-arg1.getNum() + (int)arg2.getValue()*den;}
    else if (arg1.getNeg()) {num=-arg1.getNum() - (int)arg2.getValue()*den;}
    else if (arg2.getNeg()) {num=arg1.getNum() + (int)arg2.getValue()*den;}
    else num=arg1.getNum() - (int)arg2.getValue()*den;
    if(num<0) {num=-num; neg = true;}
    Rationnelle* temp = new Rationnelle(num,den);
    Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
}
Litterale* OpMoins::actionNum(Rationnelle& arg1, Reelle& arg2){
    float y; bool neg =false;
    if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue(); }
    else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
    else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
    else y = arg1.getValue() - arg2.getValue();
    if(y<0) {y=-y; neg = true;}
    Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
}
//OpDiv
Litterale* OpDiv::fonctionNum(Nombres* arg1, Litterale* arg2){
    LitNumerique* conv = dynamic_cast<LitNumerique*>(arg2);
    if (conv!= nullptr) if(conv->getValue() ==0) throw ComputerException("Error : div par 0 impossible");
    OpSymbole::fonctionNum(arg1, arg2);//sinon on reappelle la division classique.
}

Litterale* OpDiv::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Litterale *res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res;}
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpDiv::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpDiv::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}

Litterale* OpDiv::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
    return (new Reelle(arg1.getValue()/(float)arg2.getValue()));
}
Litterale* OpDiv::actionNum(Entier& arg1, Reelle& arg2){
    return (new Reelle(arg1.getValue()/arg2.getValue()));
}
Litterale* OpDiv::actionNum(Entier& arg1, Rationnelle& arg2){
    Rationnelle* r = new Rationnelle(arg1.getValue()*arg2.getDen(),arg2.getNum());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpDiv::actionNum(Reelle& arg1, Reelle &arg2){
    return (new Reelle(arg1.getValue()/arg2.getValue()));
}
Litterale* OpDiv::actionNum(Reelle& arg1, Entier& arg2){
    return (new Reelle(arg1.getValue()/arg2.getValue()));
}
Litterale* OpDiv::actionNum(Reelle& arg1, Rationnelle& arg2){
    return (new Reelle(arg1.getValue()/arg2.getValue()));
}

Litterale* OpDiv::actionNum(Rationnelle& arg1, Rationnelle& arg2){
    Rationnelle* r = new Rationnelle(arg1.getNum()*arg2.getDen(),arg1.getDen()*arg2.getNum());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpDiv::actionNum(Rationnelle& arg1, Entier& arg2){
    Rationnelle* r = new Rationnelle(arg2.getValue()*arg1.getDen(),arg1.getNum());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpDiv::actionNum(Rationnelle& arg1, Reelle& arg2){
    return (new Reelle(arg1.getValue()/arg2.getValue()));
}

//OpMul
Litterale* OpMul::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Litterale *res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res;}
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpMul::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpMul::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}

Litterale* OpMul::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
    return (new Entier(arg1.getValue()*(float)arg2.getValue()));
}
Litterale* OpMul::actionNum(Entier& arg1, Reelle& arg2){
    return (new Reelle(arg1.getValue()*arg2.getValue()));
}
Litterale* OpMul::actionNum(Entier& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
    Rationnelle* r = new Rationnelle(arg1.getValue()*arg2.getNum(),arg2.getDen());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpMul::actionNum(Reelle& arg1, Reelle &arg2){
    return (new Reelle(arg1.getValue()*arg2.getValue()));
}
Litterale* OpMul::actionNum(Reelle& arg1, Entier& arg2){
    return (new Reelle(arg1.getValue()*arg2.getValue()));
}
Litterale* OpMul::actionNum(Reelle& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
    return (new Reelle(arg1.getValue()*arg2.getValue()));
}

Litterale* OpMul::actionNum(Rationnelle& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
    Rationnelle* r = new Rationnelle(arg1.getNum()*arg2.getNum(),arg1.getDen()*arg2.getDen());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpMul::actionNum(Rationnelle& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
    Rationnelle* r = new Rationnelle(arg2.getValue()*arg1.getNum(),arg1.getDen());
    Litterale* res = r->simplification(); delete r;
    return res;
}
Litterale* OpMul::actionNum(Rationnelle& arg1, Reelle& arg2){ // Reelle ou Rationnelle return ?
    return (new Reelle(arg1.getValue()*arg2.getValue()));
}
