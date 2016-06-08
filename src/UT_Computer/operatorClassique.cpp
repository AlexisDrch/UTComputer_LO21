#include "operatorClassique.h"


Litterale* OpSymbole::fonctionNum(Nombres* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return fonctionNum2(conv, arg2);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return fonctionNum2(conv1, arg2);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return fonctionNum2(conv2, arg2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg1); if(conv3 != nullptr) return fonctionNum2(conv3, arg2);
}
Litterale* OpSymbole::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpSymbole::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpSymbole::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpSymbole::fonctionNum2(Complexe* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
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
    Complexe* conv3 = dynamic_cast<Complexe*>(arg1); if(conv3 != nullptr) return fonctionNum2(conv3, arg2);
}
Litterale* OpCaractere::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpCaractere::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpCaractere::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
}
Litterale* OpCaractere::fonctionNum2(Complexe* arg1, Litterale *arg2) {
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) return actionNum(*arg1, *conv3);
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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

Litterale* OpPlus::actionNum(LitNumerique& arg1, Complexe& arg2){
    LitNumerique* p = arg2.getPRe();
    OpPlus op;
    op.addArg(&arg1);
    op.addArg(p);
    LitNumerique* temp = dynamic_cast<LitNumerique*>(op.executer());
    Complexe restemp(temp,arg2.getPIm());
    Litterale* res = restemp.simplification();
    op.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    return res;
}
Litterale* OpPlus::actionNum(Complexe& arg1, LitNumerique& arg2){
    LitNumerique* p1 = arg1.getPRe();
    OpPlus op;
    op.addArg(p1);
    op.addArg(&arg2);
    LitNumerique* temp = dynamic_cast<LitNumerique*>(op.executer());
    Complexe restemp(temp,arg1.getPIm());
    Litterale* res = restemp.simplification();
    op.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    return res;
}
Litterale* OpPlus::actionNum(Complexe& arg1, Complexe& arg2){
    LitNumerique* p1 = arg1.getPRe();
    LitNumerique* p2 = arg2.getPRe();
    OpPlus op1;
    op1.addArg(p1);
    op1.addArg(p2);
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(op1.executer());
    LitNumerique* p3 = arg1.getPIm();
    LitNumerique* p4 = arg2.getPIm();
    OpPlus op2;
    op2.addArg(p3);
    op2.addArg(p4);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(op2.executer());
    Complexe restemp(temp1,temp2);
    Litterale* res = restemp.simplification();
    op1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    op2.setTaille(0);
    return res;
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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
    Litterale* res = temp->simplification(); delete temp; if (neg) res->setNeg(true); return res;
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

Litterale* OpMoins::actionNum(LitNumerique& arg1, Complexe& arg2){
    LitNumerique* p = arg2.getPRe();
    OpMoins op;
    op.addArg(p);
    op.addArg(&arg1);
    LitNumerique* temp = dynamic_cast<LitNumerique*>(op.executer());
    arg2.getPIm()->setNeg(!arg2.getPIm()->getNeg());
    Complexe restemp(temp,arg2.getPIm());
    Litterale* res = restemp.simplification();
    op.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    return res;
}
Litterale* OpMoins::actionNum(Complexe& arg1, LitNumerique& arg2){
    LitNumerique* p1 = arg1.getPRe();
    OpMoins op;
    op.addArg(p1);
    op.addArg(&arg2);
    LitNumerique* temp = dynamic_cast<LitNumerique*>(op.executer());
    Complexe restemp(temp,arg1.getPIm());
    Litterale* res = restemp.simplification();
    op.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    return res;
}
Litterale* OpMoins::actionNum(Complexe& arg1, Complexe& arg2){
    LitNumerique* p1 = arg1.getPRe();
    LitNumerique* p2 = arg2.getPRe();
    OpMoins op1;
    op1.addArg(p2);
    op1.addArg(p1);
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(op1.executer());
    LitNumerique* p3 = arg1.getPIm();
    LitNumerique* p4 = arg2.getPIm();
    OpMoins op2;
    op2.addArg(p4);
    op2.addArg(p3);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(op2.executer());
    Complexe restemp(temp1,temp2);
    Litterale* res = restemp.simplification();
    op1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    op2.setTaille(0);
    return res;
}

//OpDiv
Litterale* OpDiv::fonctionNum(Nombres* arg1, Litterale* arg2){
    LitNumerique* conv = dynamic_cast<LitNumerique*>(arg2);
    if (conv!= nullptr) if(conv->getValue() ==0) throw ComputerException("Error : div par 0 impossible");
    Complexe* conv2 = dynamic_cast<Complexe*>(arg2);
    if (conv2!= nullptr) if(conv2->getPRe()==0 || conv2->getPIm()==0) throw ComputerException("Error : div par 0 impossible");
    OpSymbole::fonctionNum(arg1, arg2);//sinon on reappelle la division classique.
}

Litterale* OpDiv::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Litterale *res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res;}
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpDiv::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpDiv::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpDiv::fonctionNum2(Complexe* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
    return res;
}

Litterale* OpDiv::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
    Rationnelle temp(arg1,arg2);
    Litterale* res = temp.simplification();
    return res;
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

Litterale* OpDiv::actionNum(LitNumerique& arg1, Complexe& arg2){
    LitNumerique* l = arg2.getPIm();
    l->setNeg(true);
    Complexe* c = new Complexe(arg2.getPRe(),l); // conjugué

    OpMul op1;
    op1.addArg(&arg1);
    op1.addArg(c);
    Litterale* temp1 = op1.executer(); // normalement un complexe

    OpMul op2;
    op2.addArg(&arg2);
    op2.addArg(c);
    Litterale* temp2 = op2.executer(); // littérale numérique

    OpDiv op3;
    op3.addArg(temp1);
    op3.addArg(temp2);
    Litterale* res = op3.executer(); // normalement un complexe

    delete c;
    return res;
}
Litterale* OpDiv::actionNum(Complexe& arg1, LitNumerique& arg2){
    LitNumerique* pr = arg1.getPRe();
    LitNumerique* pi = arg1.getPIm();

    OpDiv op1;
    op1.addArg(&arg2);
    op1.addArg(pr);
    Litterale* li = op1.executer();
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(li);
    //LitNumerique* temp1 = dynamic_cast<LitNumerique*>(op1.executer());

    OpDiv op2;
    op2.addArg(&arg2);
    op2.addArg(pi);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(op2.executer());

    Complexe restemp(temp1,temp2);
    Litterale* res = restemp.simplification();
    op1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    op2.setTaille(0);
    return res;
}

Litterale* OpDiv::actionNum(Complexe &arg1, Complexe &arg2){
    LitNumerique* l = arg2.getPIm();
    l->setNeg(true);
    Complexe* c = new Complexe(arg2.getPRe(),l); // conjugué

    OpMul op1;
    op1.addArg(&arg1);
    op1.addArg(c);
    Litterale* temp1 = op1.executer(); // normalement complexe, sinon du type des parties réelles

    OpMul op2;
    op2.addArg(&arg2);
    op2.addArg(c);
    Litterale* temp2 = op2.executer(); // entier, propriété du conjugué

    OpDiv op3;
    op3.addArg(temp2);
    op3.addArg(temp1);

    op1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    op2.setTaille(0);

    delete c;

    Complexe* conv = dynamic_cast<Complexe*>(temp1);
    if (conv != nullptr) {
        Complexe* restemp = dynamic_cast<Complexe*>(op3.executer());
        op3.setTaille(0);
        Litterale* res = restemp->simplification();
        return res;
    }
    Litterale* res = op3.executer();
    op3.setTaille(0);
    return res;
}

//OpMul
Litterale* OpMul::fonctionNum2(Entier* arg1, Litterale *arg2) {
    Litterale *res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res;}
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpMul::fonctionNum2(Reelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpMul::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
    if(arg1->getNeg() && arg2->getNeg()){ return res; }
    else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
    return res;
}
Litterale* OpMul::fonctionNum2(Complexe* arg1, Litterale *arg2) {
    Litterale* res;
    Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
    Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
    Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
    Complexe* conv3 = dynamic_cast<Complexe*>(arg2); if(conv3 != nullptr) { res = actionNum(*arg1, *conv3); return res; }
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

Litterale* OpMul::actionNum(LitNumerique& arg1, Complexe& arg2){
    LitNumerique* p1 = arg2.getPRe();
    OpMul op1;
    op1.addArg(&arg1);
    op1.addArg(p1);
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(op1.executer());
    LitNumerique* p2 = arg2.getPIm();
    OpMul op2;
    op2.addArg(&arg1);
    op2.addArg(p2);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(op2.executer());
    Complexe restemp(temp1,temp2);
    Litterale* res = restemp.simplification();
    op1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    op2.setTaille(0);
    return res;
}
Litterale* OpMul::actionNum(Complexe& arg1, LitNumerique& arg2){
    LitNumerique* p1 = arg1.getPRe();
    OpMul op1;
    op1.addArg(p1);
    op1.addArg(&arg2);
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(op1.executer());
    LitNumerique* p2 = arg1.getPIm();
    OpMul op2;
    op2.addArg(p2);
    op2.addArg(&arg2);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(op2.executer());
    Complexe restemp(temp1,temp2);
    Litterale* res = restemp.simplification();
    op1.setTaille(0);
    op2.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    return res;
}
Litterale* OpMul::actionNum(Complexe &arg1, Complexe &arg2){
    LitNumerique* pr1 = arg1.getPRe();
    LitNumerique* pr2 = arg2.getPRe();
    LitNumerique* pi1 = arg1.getPIm();
    LitNumerique* pi2 = arg2.getPIm();

    OpMul opm1;
    opm1.addArg(pr1);
    opm1.addArg(pr2);
    LitNumerique* temp1 = dynamic_cast<LitNumerique*>(opm1.executer());

    OpMul opm2;
    opm2.addArg(pi1);
    opm2.addArg(pi2);
    LitNumerique* temp2 = dynamic_cast<LitNumerique*>(opm2.executer());

    OpPlus opp1;
    opp1.addArg(temp1);
    opp1.addArg(temp2);
    LitNumerique* tempr = dynamic_cast<LitNumerique*>(opp1.executer());


    OpMul opm3;
    opm3.addArg(pr1);
    opm3.addArg(pi2);
    LitNumerique* temp3 = dynamic_cast<LitNumerique*>(opm3.executer());

    OpMul opm4;
    opm4.addArg(pi1);
    opm4.addArg(pr2);
    LitNumerique* temp4 = dynamic_cast<LitNumerique*>(opm4.executer());

    OpPlus opp2;
    opp2.addArg(temp3);
    opp2.addArg(temp4);
    LitNumerique* tempi = dynamic_cast<LitNumerique*>(opp2.executer());

    Complexe restemp(tempr,tempi);
    Litterale* res = restemp.simplification();
    opm1.setTaille(0); // pour ne pas supprimer les arguments dans le destructeurs (ils seront supprimés après)
    opm2.setTaille(0);
    opm3.setTaille(0);
    opm4.setTaille(0);
    opp1.setTaille(0);
    opp2.setTaille(0);
    return res;
}
