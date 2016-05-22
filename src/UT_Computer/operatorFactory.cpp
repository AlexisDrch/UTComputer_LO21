#include "OperatorFactory.h"

OperateurFactory::~OperateurFactory(){

}


QMap<QString,OperateurFactory*> OperateurFactory::getFactoriesMap() {
    QMap<QString, OperateurFactory*> factories;


    factories["+"] = new OpPlusFactory();
    factories["-"] = new OpMoinsFactory();/*
    factories["*"] = new OpMulFactory();
    factories["/"] = new OpDivFactory();
   /* factories["DIV"] = new OpDiventFactory();
    factories["POW"] = new OpPowFactory(); */
    factories["NEG"] = new OpNegFactory();
    factories["SIN"] = new OpSinFactory();/*
    factories["COS"] = new OpCosFactory();
    factories["TAN"] = new OpTanFactory();
    factories["ARCSIN"] = new OpArcsinFactory();
    factories["ARCCOS"] = new OpArccosFactory();
    factories["ARCTAN"] = new OpArctanFactory();
    factories["SQRT"] = new OpSqrtFactory();
  */factories["EXP"] = new OpExpFactory();
    factories["LN"] = new OpLnFactory();/*
    factories["NUM"] = new OpNumFactory();
    factories["DEN"] = new OpDenFactory();
    factories["$"] = new OpDolFactory();
    factories["RE"] = new OpNumFactory();
    factories["IM"] = new OpImFactory();
    factories["ARG"] = new OpArgFactory();
    factories["NORM"] = new OpNormFactory();
    factories["="] = new OpEgFactory();
   // factories["!="] = new OpDifFactory();
    factories["=<"] = new OpInfegFactory();
    factories[">="] = new OpSupegFactory();
    factories["<"] = new OpInfFactory();
    factories[">"] = new OpSupFactory();
    factories["AND"] = new OpAndFactory();
    factories["OR"] = new OpOrFactory();
    factories["NOT"] = new OpNotFactory();
    factories["EVAL"] = new OpEvalFactory();
    factories["DUP"] = new OpDupFactory();
    factories["DROP"] = new OpDropFactory();
    factories["SWAP"] = new OpSwapFactory();
    /*factories["IFT"] = new OpIftFactory();
    factories["IFTE"] = new OpIfteFactory();
    factories["WHILE"] = new OpWhileFactory();*/
    /*factories["EDIT"] = new OpEditFactory();*/

    return factories;
}
