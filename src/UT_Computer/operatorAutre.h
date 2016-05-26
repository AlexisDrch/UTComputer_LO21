#ifndef OPERATEURAUTRE
#define OPERATEURAUTRE

#include "operator.h"

class OpAutre : public OpBinaire {
public:
    OpAutre(const QString& na) : OpBinaire(na) {}
};

class OpDivent : public OpAutre{
public:
    OpDivent() : OpAutre("DIV"){}
    Litterale* fonctionNum2(Entier* arg1, Litterale* arg2){}
    Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2){}
    Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2){}
    Litterale* actionNum(Entier& arg1, Entier& arg2){}
    Litterale* actionNum(Entier& arg1, Reelle& arg2){}
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2){}
    Litterale* actionNum(Reelle& arg1, Reelle& arg2){}
    Litterale* actionNum(Reelle& arg1, Entier& arg2){}
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2){}
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2){}
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2){}
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2){}
};

/*
class OpMod : public OpAutre{
public:
    OpMod() : OpBinaire("%"){}
    Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
};*/


#endif // OPERATEURAUTRE

