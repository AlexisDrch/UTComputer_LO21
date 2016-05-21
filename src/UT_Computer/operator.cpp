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
        Litterale* LitNumerique::operatorNeg() {
            neg = !neg;
            return this;
        }
        Litterale* LitNumerique::operatorExp(){
            return this;
        }
        Litterale* LitNumerique::operatorLn(){
            return this;
        }

            //I.4.1) Entier
            Litterale* Entier::operatorExp(){
                if (neg) throw ComputerException("Operation impossible sur litterale negative");;
                value = exp(value);
                return this;
            }
            Litterale* Entier::operatorLn(){
                if (neg) throw ComputerException("Operation impossible sur litterale negative");;
                value = log(value);
                return this;
            }

            QString Entier::toString() const {
                QString val = QString::number(value);
                if (neg) {
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
            }

            //I.4.2) Rationelle
            Litterale* Rationelle::operatorExp(){
                //value = exp(value);
                return this;
            }

            QString Rationelle::toString() const {
                return (numerateur.toString() + "/" + denominateur.toString());
            }

            //I.4.3) Reelle
            Litterale* Reelle::operatorExp(){
                if (neg) throw ComputerException("Operation impossible sur litterale negative");;
                value = exp(value);
                pEntiere = floor(value); mantisse = (value-pEntiere)*1000000 ;
                return this;
            }
            Litterale* Reelle::operatorLn(){
                if (neg) throw ComputerException("Operation impossible sur litterale negative");;
                value = log(value);
                pEntiere = floor(value); mantisse = (value-pEntiere)*1000000 ;
                return this;
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

        Litterale* OpUnaire::executer(){

            LitNumerique* arg1 = dynamic_cast<LitNumerique*>(tab.front());

            if(arg1 != nullptr){
                return fonctionNum(*arg1);
            }
            else {
                throw "error : operateur non valide sur ce litterale";
                //LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.front());
                //if(arg1 != nullptr){
                //return fonction2(*arg1);*/
            }
        }

            //NEG
            Litterale* OpNeg::fonctionNum(LitNumerique &arg1) const{
                return arg1.operatorNeg();
            }
             //EXP
            Litterale* OpExp::fonctionNum(LitNumerique &arg1) const{
                return arg1.operatorExp();
            }
            //LN
            Litterale* OpLn::fonctionNum(LitNumerique &arg1) const{
                return arg1.operatorLn();
            }


        //II.2) Operateur Binaire
        OpBinaire::~OpBinaire(){

        }

        Litterale* OpBinaire::executer(){
            return (new Entier(3));

        }


unsigned int OpUnaire::addArg(Litterale& e){
    if (tab.size() <=2){
    tab.push_back(&e);
    }
    else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
}


unsigned int OpBinaire::addArg(Litterale& e){
    if (tab.size() <=2){
    tab.push_back(&e);
    }
    else throw "Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire";
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

