#ifndef OPERATEURCLASSIQUE
#define OPERATEURCLASSIQUE

#include "operator.h"



/* ****** BINAIRE ******* */


class OpClassique : public OpBinaire {
public:
    OpClassique(const QString& na) : OpBinaire(na) {}

    virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2)=0;
    virtual Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2) =0;
};


class OpSymbole : public OpClassique{
public:
    OpSymbole(const QString& na) : OpClassique(na) {}
    virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Complexe* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);

    virtual Litterale* actionNum(Entier& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Entier& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(Entier& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(LitNumerique& arg1, Complexe& arg2) =0;
    virtual Litterale* actionNum(Complexe& arg1, LitNumerique& arg2) =0;
    virtual Litterale* actionNum(Complexe& arg1, Complexe& arg2) =0;
};

class OpCaractere : public OpClassique{
public:
    OpCaractere(const QString& na) : OpClassique(na) {}
    virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    virtual Litterale* fonctionNum2(Complexe* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2);

    virtual Litterale* actionNum(Entier& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Entier& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(Entier& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Reelle& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Entier& arg2) =0;
    virtual Litterale* actionNum(Rationnelle& arg1, Reelle& arg2) =0;
    virtual Litterale* actionNum(LitNumerique& arg1, Complexe& arg2) =0;
    virtual Litterale* actionNum(Complexe& arg1, LitNumerique& arg2) =0;
    virtual Litterale* actionNum(Complexe& arg1, Complexe& arg2) =0;

};


class OpPlus : public OpSymbole{
public:
    OpPlus() : OpSymbole("+"){}
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
    Litterale* actionNum(LitNumerique& arg1, Complexe& arg2);
    Litterale* actionNum(Complexe& arg1, LitNumerique& arg2);
    Litterale* actionNum(Complexe& arg1, Complexe& arg2);

};

class OpMoins : public OpSymbole{
public:
    OpMoins() : OpSymbole("-"){}
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
    Litterale* actionNum(LitNumerique& arg1, Complexe& arg2);
    Litterale* actionNum(Complexe& arg1, LitNumerique& arg2);
    Litterale* actionNum(Complexe& arg1, Complexe& arg2);
};

class OpDiv : public OpSymbole{
public:
    OpDiv() : OpSymbole("/"){}
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Complexe* arg1, Litterale* arg2);
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
    Litterale* actionNum(LitNumerique& arg1, Complexe& arg2);
    Litterale* actionNum(Complexe& arg1, LitNumerique& arg2);
    Litterale* actionNum(Complexe& arg1, Complexe& arg2);
};

class OpMul : public OpSymbole{
public:
    OpMul() : OpSymbole("*"){}
    Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Complexe* arg1, Litterale* arg2);
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
    Litterale* actionNum(LitNumerique& arg1, Complexe& arg2);
    Litterale* actionNum(Complexe& arg1, LitNumerique& arg2);
    Litterale* actionNum(Complexe& arg1, Complexe& arg2);
};

#endif // OPERATEURCLASSIQUE

