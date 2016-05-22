#include "operator.h"

//Operande
Operande::~Operande(){

}
    //I]Litteral
    Litterale::~Litterale(){

    }

        //I.1) Litterale programme
        LitProgramme::LitProgramme(const QString& str, const QString na): Litterale(na), stringValue(str) {
            //décomposition + insertion de chaque element du programme
            QString::const_iterator it = str.begin(); QString::const_iterator it2 = str.end(); it2--;
            while (it != it2){
                if ( (*it == ' ') || (*it == '[') || (*it == '\0') ) { it ++; }
                else {
                    QString sPart;
                    unsigned int i =0;
                    while (*it != ' '){

                        sPart.push_back(*it); it++; i++;
                    }
                    tab.push_back(sPart); taille++;
                }
            }
        }

        QString LitProgramme::toString() const {
            return stringValue;
        }
        //I.2) Litterale expression
        QString LitExpression::toString()const{
                    return stringValue;
        }

        //I.3) Litterale atome
        QString LitAtome::toString() const {
            return value;
        }

        //I.4) Litterale numerique
        LitNumerique::~LitNumerique(){

        }
        Litterale* LitNumerique::returnType(){
            Entier* newe3 = dynamic_cast<Entier*>(this); if (newe3 != nullptr){return (new Entier(*newe3));}
            Reelle* newe4 = dynamic_cast<Reelle*>(this); if (newe4 != nullptr){return (new Reelle(*newe4));}
            Rationelle* newe5 = dynamic_cast<Rationelle*>(this);if (newe5 != nullptr){return (new Rationelle(*newe5)) ;}
        }

            //I.4.1) Entier

            Litterale* Entier::operatorSin(){
                double x = (double) value;
                x = sin(x);
                if (x<0){
                    x =-x;
                    neg  = !neg;
                }
                Reelle* res = new Reelle(x);
                if (neg) res->setNeg(!res->getNeg());
                return(res);
            }

            QString Entier::toString() const {
                QString val = QString::number(value);
                if (neg) {
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
            }

            //I.4.2) Rationelle
			
			int pgcd(int a, int b) { return b ?  pgcd(b,a%b) : a; }

            Litterale* Rationelle::simplification(){
                int n = numerateur.getValue(), d = denominateur.getValue();
                int r = pgcd(n, d);
                numerateur.setValue(n/r);
                denominateur.setValue(d/r);
                if (denominateur.getValue() != 1) {
                    return new Rationelle(numerateur.getValue(),denominateur.getValue(),numerateur.getValue() + "/" + denominateur.getValue());
                } else {
                    return new Entier(numerateur.getValue());
                }
            }
            /*Litterale* Rationelle::operatorExp(){
                //value = exp(value);
                return this;
            }*/

            QString Rationelle::toString() const {
                return (numerateur.toString() + "/" + denominateur.toString());
            }

            //I.4.3) Reelle
            float Reelle::toFloatPositif() const {
                QString val = QString::number(pEntiere) + "." + QString::number(mantisse);
                return val.toFloat();
            }
            QString Reelle::toString() const {
                QString val = QString::number(pEntiere) + "." + QString::number(mantisse);
                if (neg) {
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
            }


    //II]Operateur
    Operateur::~Operateur(){
     //ici on supprime les litteraux sauf le premier (car c'est devenu le resultat de l'operation et est en pile)
    for(unsigned int i =1; i <taille; i++){
        delete tab.operator [](i);
    }
    }
        //II.1) Operateur Unaire
        OpUnaire::~OpUnaire(){

        }
        unsigned int OpUnaire::addArg(Litterale& e){
            if (tab.size() <=2){
            tab.push_back(&e);
            }
            else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
        }
        Litterale* OpUnaire::executer(){

            LitNumerique* arg1 = dynamic_cast<LitNumerique*>(tab.front());

            if(arg1 != nullptr){
                Litterale* res = fonctionNum(arg1);
                delete arg1;
                return res;
            }
            else {
                throw "error : operateur non valide sur ce litterale";
                //LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.front());
                //if(arg1 != nullptr){
                //return fonction2(*arg1);*/
            }
        }
        Litterale* OpUnaire::fonctionNum(LitNumerique *arg1) {
            Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return actionNum(*conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return actionNum(*conv1);
        }

            //NEG
            Litterale* OpNeg::fonctionNum(LitNumerique* arg1){
                arg1->setNeg(!arg1->getNeg());
                return arg1->returnType();
            }
            Litterale* OpNeg::actionNum(Entier& arg1){
                arg1.setNeg(!arg1.getNeg());
                return arg1.returnType();
            }
            Litterale* OpNeg::actionNum(Reelle& arg1){
                arg1.setNeg(!arg1.getNeg());
                return arg1.returnType();
            }

             //EXP
            Litterale* OpExp::actionNum(Entier& arg1){
                if (arg1.getNeg()) throw ComputerException("Operation impossible sur litterale negative");
                float f = exp(arg1.getValue());
                return (new Reelle(f));
            }
            Litterale* OpExp::actionNum(Reelle& arg1){
                if (arg1.getNeg()) throw ComputerException("Operation impossible sur litterale negative");;
                float f = arg1.toFloatPositif();
                f = exp(f);
                return (new Reelle(f));
            }
            //LN
            Litterale* OpLn::actionNum(Entier &arg1) {
                if (arg1.getNeg()) throw ComputerException("Operation impossible sur litterale negative");;
                float f = log(arg1.getValue());
                return (new Reelle(f));

            }
            Litterale* OpLn::actionNum(Reelle &arg1) {
                if (arg1.getNeg()) throw ComputerException("Operation impossible sur litterale negative");;
                float f = arg1.toFloatPositif();
                f = log(f);
                return (new Reelle(f));

            }
            //SIN
            Litterale* OpSin::actionNum(Entier &arg1){
                double x = (double) arg1.getValue();
                x = sin(x);
                if (x<0){
                    x =-x;
                    arg1.setNeg(!arg1.getNeg());
                }
                Reelle* res = new Reelle(x);
                if (arg1.getNeg()) res->setNeg(!res->getNeg());
                return(res);
            }
            Litterale* OpSin::actionNum(Reelle &arg1){
                double x = (double) arg1.toFloatPositif();
                x = sin(x);
                if (x<0){
                    x =-x;
                    arg1.setNeg(!arg1.getNeg());
                }
                Reelle* res = new Reelle(x);
                if (arg1.getNeg()) res->setNeg(!res->getNeg());
                return(res);
            }


        //II.2) Operateur Binaire
        OpBinaire::~OpBinaire(){

        }

        unsigned int OpBinaire::addArg(Litterale& e){
            if (tab.size() <=2){
            tab.push_back(&e);
            }
            else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
        }

        Litterale* OpBinaire::executer(){

            LitNumerique* arg1 = dynamic_cast<LitNumerique*>(tab.operator [](1));
            Litterale* arg2 = tab.operator [](0);

            if(arg1 != nullptr){
                Litterale* res = fonctionNum(arg1,arg2);
                delete arg2;
                return res;
            }
            else {
                throw "error : operateur non valide sur ce litterale";
                //LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.front());
                //if(arg1 != nullptr){
                //return fonction2(*arg1);*/
            }
        }
        Litterale* OpBinaire::fonctionNum(Nombres* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return fonctionNum2(conv, arg2);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return fonctionNum2(conv1, arg2);
        }
        Litterale* OpBinaire::fonctionNum2(Entier* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
        }
        Litterale* OpBinaire::fonctionNum2(Reelle* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
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
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.toFloatPositif(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.toFloatPositif(); }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.toFloatPositif();}
                else y = arg1.getValue() + arg2.toFloatPositif();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Reelle& arg1, Reelle &arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.toFloatPositif()+arg2.toFloatPositif(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.toFloatPositif() + arg2.toFloatPositif(); }
                else if(arg2.getNeg()) { y = arg1.toFloatPositif() - arg2.toFloatPositif(); }
                else y = arg1.toFloatPositif() + arg2.toFloatPositif();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Reelle& arg1, Entier& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.toFloatPositif()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.toFloatPositif() + arg2.getValue();  }
                else if(arg2.getNeg()) { y = arg1.toFloatPositif() - arg2.getValue(); }
                else y = arg1.toFloatPositif() + arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
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
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.toFloatPositif(); }
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.toFloatPositif(); }
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.toFloatPositif(); }
                else y = arg1.getValue() - arg2.toFloatPositif();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Reelle& arg1, Reelle &arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.toFloatPositif() + arg2.toFloatPositif(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.toFloatPositif() + arg2.toFloatPositif(); }
                else if(arg2.getNeg()) { y = arg1.toFloatPositif() - arg2.toFloatPositif(); }
                else y = arg1.toFloatPositif() - arg2.toFloatPositif();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Reelle& arg1, Entier& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.toFloatPositif()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.toFloatPositif() + arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.toFloatPositif() - arg2.getValue(); }
                else y = arg1.toFloatPositif() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }




//Littérale expression
    //Constructeur de la classe

    LitExpression::LitExpression(const QString& str, const QString& na):Litterale(na){
        //remplir le vector de littérale
        //Analyser les espaces dans l'expression str puis:
        stringValue = str;
    }

    //Méthode de la classe
        //Op unaire
        QString LitExpression::operatorUnaire(const QString &str){
            return (str+"("+toString()+")");
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
            Litterale* LitExpression::operator+(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("+",lit.toString())));
            }
            Litterale* LitExpression::operator*(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("*",lit.toString())));
            }
            Litterale* LitExpression::operator-(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("-",lit.toString())));
            }
            Litterale* LitExpression::operator/(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("/",lit.toString())));
            }
            Litterale* LitExpression::operator$(const LitExpression& lit){
                return (new LitExpression(operatorSymbole("$",lit.toString())));
            }
        //Op Binaire Exp - Lit
        LitExpression* LitExpression::litToExp(const LitNumerique& lit){
            QString str = "'" + lit.toString() + "'";
            return (new LitExpression(str));
        }

        Litterale* LitExpression::operatorDiv(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("DIV",litEx->toString())));
        }
        Litterale* LitExpression::operatorMod(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("MOD",litEx->toString())));
        }
        Litterale* LitExpression::operatorPow(const LitNumerique& lit){
            LitExpression* litEx = litToExp(lit);
            return (new LitExpression(operatorBinaire("POW",litEx->toString())));
        }
            //Op symbole

            Litterale* LitExpression::operator+(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("+",litEx->toString())));
            }
            Litterale* LitExpression::operator-(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("-",litEx->toString())));
            }
            Litterale* LitExpression::operator/(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("/",litEx->toString())));
            }
            Litterale* LitExpression::operator*(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("*",litEx->toString())));
            }
            Litterale* LitExpression::operator$(const LitNumerique& lit){
                LitExpression* litEx = litToExp(lit);
                return (new LitExpression(operatorSymbole("$",litEx->toString())));
            }

