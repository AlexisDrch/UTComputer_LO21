#include "litterale.h"

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
        LitExpression::LitExpression(const QString& str, const QString& na):Litterale(na){
            //remplir le vector de littérale
            //Analyser les espaces dans l'expression str puis:
            stringValue = str;
        }

        QString LitExpression::toString()const{
                    return stringValue;
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


        //I.3) Litterale atome
        QString LitAtome::toString() const {
            return value;
        }

        //II.4) Litterale Nombres

        Litterale* Nombres::returnType(){
            Entier* newe3 = dynamic_cast<Entier*>(this); if (newe3 != nullptr){return (new Entier(*newe3));}
            Reelle* newe4 = dynamic_cast<Reelle*>(this); if (newe4 != nullptr){return (new Reelle(*newe4));}
            Rationelle* newe5 = dynamic_cast<Rationelle*>(this);if (newe5 != nullptr){return (new Rationelle(*newe5)) ;}
        }

        //I.5) Litterale numerique
        LitNumerique::~LitNumerique(){

        }

            //I.5.1) Entier
            QString Entier::toString() const {
                QString val = QString::number(value);
                if (neg) {
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
            }

            float Entier::getValue()const {
                return getValueEnt();
            }

            //I.5.2) Rationelle
            int pgcd(int a, int b) { return b ?  pgcd(b,a%b) : a; }

            Litterale* Rationelle::simplification(){
                int n = numerateur.getValue(), d = denominateur.getValue();
                int r = pgcd(n, d);
                numerateur.setValue(n/r);
                denominateur.setValue(d/r);
                if (denominateur.getValue() != 1) {
                    return new Rationelle(numerateur.getValueEnt(),denominateur.getValueEnt(),numerateur.getValueEnt() + "/" + denominateur.getValueEnt());
                } else {
                    return new Entier(numerateur.getValue());
                }
            }
            float Rationelle::getValue()const {
                return getValueRat();
            }

            QString Rationelle::toString() const {
                return (numerateur.toString() + "/" + denominateur.toString());
            }

            //I.5.3) Reelle
            float Reelle::toFloatPositif() const {
                QString val = QString::number(pEntiere) + ".";
                if(mantisse<10000 && mantisse>=1000) val.append("0"+QString::number(mantisse)); //Un 0 après la virgule
                else if(mantisse<1000 && mantisse>=100) val.append("00"+QString::number(mantisse)); //Deux 0 après la virgule
                else if(mantisse<100 && mantisse>=10) val.append("000"+QString::number(mantisse)); //Trois 0 après la virgule
                else if(mantisse<10 && mantisse>=1) val.append("0000"+QString::number(mantisse)); //Quatre 0 après la virgule
                else val.append(QString::number(mantisse));
                return val.toFloat();
            }
            QString Reelle::toString() const {
                QString val = QString::number(pEntiere) + ".";
                if(mantisse<10000 && mantisse>=1000) val.append("0"+QString::number(mantisse)); //Un 0 après la virgule
                else if(mantisse<1000 && mantisse>=100) val.append("00"+QString::number(mantisse)); //Deux 0 après la virgule
                else if(mantisse<100 && mantisse>=10) val.append("000"+QString::number(mantisse)); //Trois 0 après la virgule
                else if(mantisse<10 && mantisse>=1) val.append("0000"+QString::number(mantisse)); //Quatre 0 après la virgule
                else val.append(QString::number(mantisse));
                if (neg) {
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
            }
            float Reelle::getValue()const {
                return toFloatPositif();
            }
            LitNumerique* Reelle::simplification(){
                if(mantisse == 0) return (new Entier(pEntiere));
                else return (new Reelle(getValue()));
            }

