#ifndef OPERATEURLOGIQUE
#define OPERATEURLOGIQUE

#include "operator.h"


//ATTENTION : APPLIQUABLE SEULEMENT SUR LTTERALE NUMERIQUE ET EXPRESSION : FAUT IL LE PRECISER EN RESTREIGNANT LE TYPE DE PARAMETRE
class OpLogiqueBinaire : public OpBinaire{
public :
    OpLogiqueBinaire(const QString &na):OpBinaire(na){}
    virtual ~OpLogiqueBinaire();
    Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
    Litterale* fonctionExpression(LitExpression *arg1, Litterale *arg2); // TODO
    virtual Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2) =0;
    //virtual //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2) const =0;
    //actionLogiqueComplexe ? Expression ?
};

class OpInf : public OpLogiqueBinaire{
public:
    OpInf() : OpLogiqueBinaire("<"){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2);
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2)  ;
};

class OpSup : public OpLogiqueBinaire{
public:
    OpSup() : OpLogiqueBinaire(">"){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2);
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2)  ;
};

class OpSupeg : public OpLogiqueBinaire{
public:
    OpSupeg() : OpLogiqueBinaire(">="){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2);
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2) ;
};

class OpInfeg : public OpLogiqueBinaire{
public:
    OpInfeg() : OpLogiqueBinaire("=<"){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2);
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2) ;
};

class OpEg: public OpLogiqueBinaire{
public:
    OpEg() : OpLogiqueBinaire("="){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2) ;
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2)  ;
};

class OpDiff : public OpLogiqueBinaire{
public:
    OpDiff() : OpLogiqueBinaire("!="){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2) ;
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2) ;
};

class OpAnd : public OpLogiqueBinaire{
public:
    OpAnd() : OpLogiqueBinaire("AND"){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2) ;
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2)  ;
};

class OpOr : public OpLogiqueBinaire{
public:
    OpOr() : OpLogiqueBinaire("OR"){}
    Litterale* actionLogiNumerique(LitNumerique* arg1, LitNumerique* arg2) ;
    //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2)  ;
};

#endif // OPERATEURLOGIQUE

