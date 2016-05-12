#include "operator.h"


unsigned int OpUnaire::addArg(const Litterale& e){
    if (tab->size() <=2){
    tab->push_back(e);
    }
    else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
}


unsigned int OpBinaire::addArg(const Litterale& e){
    if (tab->size() <=2){
    tab->push_back(e);
    }
    else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
}



//Littérale expression
    //Constructeur de la classe

    LitExpression::LitExpression(const QString& str, const QString& na = ""):Litterale(na){
        //remplir le vector de littérale
        //Analyser les espaces dans l'expression str puis:
        stringValue(str);
    }

    //Méthode de la classe
        //Op unaire
        QString LitExpression::operatorUnaire(const QString &str){
            return (str+"("+toString+")");
        }

        Litterale* LitExpression::operatorExp(){
           return (new LitExpression(operatorUnaire("EXP")));
        }
        Litterale* LitExpression::operatorNeg(){
           return (new LitExpression(operatorUnaire("NEG")));
        }
        Litterale* LitExpression::operatorSin(){
           return (new LitExpression(operatorUnaire("Sin")));
        }
        Litterale* LitExpression::operatorCos(){
           return (new LitExpression(operatorUnaire("COS")));
        }
        Litterale* LitExpression::operatorTan(){
           return (new LitExpression(operatorUnaire("TAN")));
        }
        Litterale* LitExpression::operatorArcsin(){
           return (new LitExpression(operatorUnaire("ARCSIN")));
        }
        Litterale* LitExpression::operatorArccos(){
           return (new LitExpression(operatorUnaire("ARCCOS")));
        }
        Litterale* LitExpression::operatorArctan(){
           return (new LitExpression(operatorUnaire("ARCTAN")));
        }
        Litterale* LitExpression::operatorSqrt(){
           return (new LitExpression(operatorUnaire("SQRT")));
        }
        Litterale* LitExpression::operatorLn(){
           return (new LitExpression(operatorUnaire("LN")));
        }
        Litterale* LitExpression::operatorNum(){
           return (new LitExpression(operatorUnaire("NUM")));
        }
        Litterale* LitExpression::operatorDen(){
           return (new LitExpression(operatorUnaire("DEN")));
        }
        Litterale* LitExpression::operatorRe(){
           return (new LitExpression(operatorUnaire("RE")));
        }
        Litterale* LitExpression::operatorArg(){
           return (new LitExpression(operatorUnaire("ARG")));
        }
        Litterale* LitExpression::operatorNorm(){
           return (new LitExpression(operatorUnaire("NORM")));
        }

        //Op Binaire EXP - EXP
        QString LitExpression::operatorBinaire(const QString &str, const QString &str2){
            return (str+"("+toString()+","+str2+")");
        }
        Litterale* LitExpression::operatorDiv(const LitExpression& lit){
           return (new LitExpression(operatorBinaire("DIV", lit.toString())));
        }
        Litterale* LitExpression::operatorMod(const LitExpression& lit){
           return (new LitExpression(operatorBinaire("MOD", lit.toString())));
        }
        Litterale* LitExpression::operatorPow(const LitExpression& lit){
           return (new LitExpression(operatorBinaire("POW", lit.toString())));
        }
            //Op symbole
            QString LitExpression::operatorSymbole(const QString& symb, const QString &lit){
                return (toString()+" "+ symb +" "+ lit);
            }
            Litterale* operator+(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("+",lit.toString())));
            }

            Litterale* operator*(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("*",lit.toString())));
            }
            Litterale* operator-(const LitExpression& lit){
                return(new LitExpression(operatorSymbole('-',lit.toString())));
            }
            Litterale* operator/(const LitExpression& lit){
                return(new LitExpression(operatorSymbole('/',lit.toString())));
            }
            Litterale* operator$(const LitExpression& lit){
                return(new LitExpression(operatorSymbole('$',lit.toString())));
            }
        //Op Binaire Exp - Lit
        LitExpression* litToExp(const LitNumerique& lit){
            QString str = "'" + lit.toString() + "'";
            return (new LitExpression(str));
        }

        Litterale* operatorDiv(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("DIV",litEx->toString())));
        }
        Litterale* operatorMod(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("MOD",litEx->toString())));
        }
        Litterale* operatorPow(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("POW",litEx->toString())));
        }
            //Op symbole

            Litterale* operator+(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("+",litEx->toString())));
            }
            Litterale* operator-(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("-",litEx->toString())));
            }
            Litterale* operator/(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("/",litEx->toString())));
            }
            Litterale* operator*(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("*",litEx->toString())));
            }
            Litterale* operator$(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("$",litEx->toString())));
            }

