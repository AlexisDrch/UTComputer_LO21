#ifndef OPRATORFACTORY_H
#define OPRATORFACTORY_H


#include "operator.h"

#include <map>
#include <QString>

using namespace std;

class OperatorFactory {
public:
    virtual ~OperatorFactory();
    virtual Operator* getOperator() =0;
    static map<QString, OperatorFactory*> getFactoriesMap();
};


class OpExpFactory : public OperatorFactory {
public:
    OpExpFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpExp(); }
};

class OpLnFactory : public OperatorFactory {
public:
    OpLnFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpLn(); }
};

class OpNumFactory : public OperatorFactory {
public:
    OpNumFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpNum(); }
};

class OpDenFactory : public OperatorFactory {
public:
    OpDenFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDen(); }
};

class OpReFactory : public OperatorFactory {
public:
    OpReFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpRe(); }
};

class OpImFactory : public OperatorFactory {
public:
    OpImFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpIm(); }
};

class OpArgFactory : public OperatorFactory {
public:
    OpArgFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpArg(); }
};

class OpNormFactory : public OperatorFactory {
public:
    OpNormFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpNorm(); }
};

class OpNotFactory : public OperatorFactory {
public:
    OpNotFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpNot(); }
};

class OpEvalFactory : public OperatorFactory {
public:
    OpEvalFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpEval(); }
};

class OpNegFactory : public OperatorFactory {
public:
    OpNegFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpNeg(); }
};

class OpSinFactory : public OperatorFactory {
public:
    OpSinFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpSin(); }
};

class OpCosFactory : public OperatorFactory {
public:
    OpCosFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpCos(); }
};

class OpTanFactory : public OperatorFactory {
public:
    OpTanFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpTan(); }
};

class OpArcsinFactory : public OperatorFactory {
public:
    OpArcsinFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpArcsin(); }
};

class OpArccosFactory : public OperatorFactory {
public:
    OpArccosFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpArccos(); }
};

class OpArctanFactory : public OperatorFactory {
public:
    OpArctanFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpArctan(); }
};

class OpSqrtFactory : public OperatorFactory {
public:
    OpSqrtFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpSqrt(); }
};

class OpDupFactory : public OperatorFactory {
public:
    OpDupFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDup(); }
};

class OpDropFactory : public OperatorFactory {
public:
    OpDropFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDrop(); }
};

class OpEditFactory : public OperatorFactory {
public:
    OpEditFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpEdit(); }
};

class OpInfegFactory : public OperatorFactory {
public:
    OpExpFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpExp(); }
};

class OpSupegFactory : public OperatorFactory {
public:
    OpSupegFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpSupeg(); }
};

class OpInfFactory : public OperatorFactory {
public:
    OpInfFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpInf(); }
};

class OpSupFactory : public OperatorFactory {
public:
    OpSupFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpSup(); }
};

class OpAndFactory : public OperatorFactory {
public:
    OpEAndFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpAnd(); }
};

class OpOrFactory : public OperatorFactory {
public:
    OpOrFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpOr(); }
};

class OpPlusFactory : public OperatorFactory {
public:
    OpPlusFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpPlus(); }
};

class OpMoinsFactory : public OperatorFactory {
public:
    OpMoinsFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpMoins(); }
};

class OpMulFactory : public OperatorFactory {
public:
    OpMulFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpMul(); }
};

class OpDivFactory : public OperatorFactory {
public:
    OpDivFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDiv(); }
};

class OpDiventFactory : public OperatorFactory {
public:
    OpDiventFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDivent(); }
};

class OpPowFactory : public OperatorFactory {
public:
    OpPowFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpPow(); }
};

class OpModFactory : public OperatorFactory {
public:
    OpModFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpMod(); }
};

class OpDolFactory : public OperatorFactory {
public:
    OpDolFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDol(); }
};

class OpEgFactory : public OperatorFactory {
public:
    OpEgFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpEg(); }
};

class OpDifFactory : public OperatorFactory {
public:
    OpDifFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpDif(); }
};

class OpSwapFactory : public OperatorFactory {
public:
    OpSwapFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpEg(); }
};

class OpIftFactory : public OperatorFactory {
public:
    OpIftFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpIft(); }
};

class OpIfteFactory : public OperatorFactory {
public:
    OpIfteFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpIfte(); }
};

class OpWhileFactory : public OperatorFactory {
public:
    OpWhileFactory() : OperatorFactory() {}
    Operator* getOperator() { return new OpWhile(); }
};

#endif // OPRATORFACTORY_H

