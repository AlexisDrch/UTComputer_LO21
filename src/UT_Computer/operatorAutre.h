#ifndef OPERATEURAUTRE
#define OPERATEURAUTRE

#include "operator.h"

class OpAutre : public OpBinaire {
public:
    virtual ~OpAutre();
    OpAutre(const QString& na) : OpBinaire(na) {}
    virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2) =0;
    virtual Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2) =0;
};



class OpSto : public OpAutre {
public:
    OpSto(): OpAutre("STO"){}
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);
};


class OpDol : public OpAutre {
public:
    OpDol(): OpAutre("$"){}
    ~OpDol();
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);
};



class OpDivent : public OpAutre{
public:
    OpDivent() : OpAutre("DIV"){}
    ~OpDivent();
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);
};


class OpMod : public OpAutre{
public:
    OpMod() : OpAutre("MOD"){}
    ~OpMod();
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);
};


#endif // OPERATEURAUTRE

