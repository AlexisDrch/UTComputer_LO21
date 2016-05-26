#ifndef OPERATEURCLASSIQUE
#define OPERATEURCLASSIQUE

#include "operator.h"



/* ****** BINAIRE ******* */


class OpClassique : public OpBinaire {
public:
    OpClassique(const QString& na) : OpBinaire(na) {}

};


class OpSymbole : public OpClassique{
public:
    OpSymbole(const QString& na) : OpClassique(na) {}
};

class OpCaractere : public OpClassique{
public:
    OpCaractere(const QString& na) : OpClassique(na) {}

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
};

class OpDiv : public OpSymbole{
public:
    OpDiv() : OpSymbole("/"){}
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
};

class OpMul : public OpSymbole{
public:
    OpMul() : OpSymbole("*"){}
    Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
    Litterale* fonctionNum2(Rationnelle* arg1, Litterale* arg2);
    Litterale* actionNum(Entier& arg1, Entier& arg2);
    Litterale* actionNum(Entier& arg1, Reelle& arg2);
    Litterale* actionNum(Entier& arg1, Rationnelle& arg2);
    Litterale* actionNum(Reelle& arg1, Reelle& arg2);
    Litterale* actionNum(Reelle& arg1, Entier& arg2);
    Litterale* actionNum(Reelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Rationnelle& arg2);
    Litterale* actionNum(Rationnelle& arg1, Entier& arg2);
    Litterale* actionNum(Rationnelle& arg1, Reelle& arg2);
};



/*class OpDol : public OpSymbole{
public:
    OpDol() : OpSymbole("$"){}
    Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
};
*/

#endif // OPERATEURCLASSIQUE

