#ifndef OPRATORFACTORY_H
#define OPRATORFACTORY_H

#include "operator.h"

#include <QMap>
#include <QString>

using namespace std;

class OperateurFactory {
public:
    virtual ~OperateurFactory();
    virtual Operateur* getOperateur() =0;
    static QMap<QString, OperateurFactory*> getFactoriesMap();
};

class OpExpFactory : public OperateurFactory {
public:
    OpExpFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpExp(); }
};

class OpLnFactory : public OperateurFactory {
public:
    OpLnFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpLn(); }
};
/*
class OpNumFactory : public OperateurFactory {
public:
    OpNumFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpNum(); }
};

class OpDenFactory : public OperateurFactory {
public:
    OpDenFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDen(); }
};

class OpReFactory : public OperateurFactory {
public:
    OpReFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpRe(); }
};

class OpImFactory : public OperateurFactory {
public:
    OpImFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpIm(); }
};

class OpArgFactory : public OperateurFactory {
public:
    OpArgFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpArg(); }
};

class OpNormFactory : public OperateurFactory {
public:
    OpNormFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpNorm(); }
};

class OpNotFactory : public OperateurFactory {
public:
    OpNotFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpNot(); }
};

class OpEvalFactory : public OperateurFactory {
public:
    OpEvalFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpEval(); }
};
*/
class OpNegFactory : public OperateurFactory {
public:
    OpNegFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpNeg(); }
};

class OpSinFactory : public OperateurFactory {
public:
    OpSinFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpSin(); }
};/*

class OpCosFactory : public OperateurFactory {
public:
    OpCosFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpCos(); }
};

class OpTanFactory : public OperateurFactory {
public:
    OpTanFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpTan(); }
};

class OpArcsinFactory : public OperateurFactory {
public:
    OpArcsinFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpArcsin(); }
};

class OpArccosFactory : public OperateurFactory {
public:
    OpArccosFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpArccos(); }
};

class OpArctanFactory : public OperateurFactory {
public:
    OpArctanFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpArctan(); }
};

class OpSqrtFactory : public OperateurFactory {
public:
    OpSqrtFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpSqrt(); }
};

class OpDupFactory : public OperateurFactory {
public:
    OpDupFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDup(); }
};

class OpDropFactory : public OperateurFactory {
public:
    OpDropFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDrop(); }
};

class OpEditFactory : public OperateurFactory {
public:
    OpEditFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpEdit(); }
};
*/
class OpInfegFactory : public OperateurFactory {
public:
    OpInfegFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpExp(); }
};

class OpSupegFactory : public OperateurFactory {
public:
    OpSupegFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpSupeg(); }
};

class OpInfFactory : public OperateurFactory {
public:
    OpInfFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpInf(); }
};

class OpSupFactory : public OperateurFactory {
public:
    OpSupFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpSup(); }
};

class OpAndFactory : public OperateurFactory {
public:
    OpAndFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpAnd(); }
};

class OpOrFactory : public OperateurFactory {
public:
    OpOrFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpOr(); }
};

class OpPlusFactory : public OperateurFactory {
public:
    OpPlusFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpPlus(); }
};

class OpMoinsFactory : public OperateurFactory {
public:
    OpMoinsFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpMoins(); }
};

class OpMulFactory : public OperateurFactory {
public:
    OpMulFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpMul(); }
};

class OpDivFactory : public OperateurFactory {
public:
    OpDivFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDiv(); }
};
/*
class OpDiventFactory : public OperateurFactory {
public:
    OpDiventFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDivent(); }
};

class OpPowFactory : public OperateurFactory {
public:
    OpPowFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpPow(); }
};

class OpModFactory : public OperateurFactory {
public:
    OpModFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpMod(); }
};

class OpDolFactory : public OperateurFactory {
public:
    OpDolFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDol(); }
};
*/
class OpEgFactory : public OperateurFactory {
public:
    OpEgFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpEg(); }
};

class OpDifFactory : public OperateurFactory {
public:
    OpDifFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpDiff(); }
};/*

class OpSwapFactory : public OperateurFactory {
public:
    OpSwapFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpEg(); }
};

class OpIftFactory : public OperateurFactory {
public:
    OpIftFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpIft(); }
};

class OpIfteFactory : public OperateurFactory {
public:
    OpIfteFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpIfte(); }
};

class OpWhileFactory : public OperateurFactory {
public:
    OpWhileFactory() : OperateurFactory() {}
    Operateur* getOperateur() { return new OpWhile(); }
};*/

#endif // OPRATORFACTORY_H

