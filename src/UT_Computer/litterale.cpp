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
        LitExpression::LitExpression(const QString& str,  const QString& na):Litterale(na){

            stringValue = str;
        }
        /*
         Algo recursif :
            fonction EVAL(LitteraleExpression* litExp) :
            if (op) {
                op->addArg(Litterale* res1 = EVAL(EXP1));
                if(Op.size>1){
                    op->addArg(Litterale* res2 = EVAL(EXP2));
                }
                return op->exectuer
            }
            else return fabriqueLitterale(LitExp->toString());
         */

        QString LitExpression::toString()const{
                    return stringValue;
        }


        //I.3) Litterale atome
        QString LitAtome::toString() const {
            return value;
        }

        //II.4) Litterale Nombres

        Litterale* Nombres::returnType(){
            Entier* newe3 = dynamic_cast<Entier*>(this); if (newe3 != nullptr){return (new Entier(*newe3));}
            Reelle* newe4 = dynamic_cast<Reelle*>(this); if (newe4 != nullptr){return (new Reelle(*newe4));}
            Rationnelle* newe5 = dynamic_cast<Rationnelle*>(this);if (newe5 != nullptr){return (new Rationnelle(*newe5)) ;}
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

            //I.5.2) Rationnelle
            int pgcd(int a, int b) { return b ?  pgcd(b,a%b) : a; }

            Litterale* Rationnelle::simplification(){
                int n = numerateur.getValue(), d = denominateur.getValue();
                int r = pgcd(n, d);
                numerateur.setValue(n/r);
                denominateur.setValue(d/r);
                if (denominateur.getValue() != 1) {
                    return new Rationnelle(numerateur.getValueEnt(),denominateur.getValueEnt(),numerateur.getValueEnt() + "/" + denominateur.getValueEnt());
                } else {
                    return new Entier(numerateur.getValue());
                }
            }
            float Rationnelle::getValue()const {
                return numerateur.getValue()/denominateur.getValue();
            }

            QString Rationnelle::toString() const {
                QString val = (numerateur.toString() + "/" + denominateur.toString());
                if (neg){
                    QString val2 = "- "; val2.append(val); return val2;
                }
                return val;
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

        //I.6) Complexe
            Complexe::~Complexe() {
                //delete pRe, pIm;
            }

        QString Complexe::toString() const {
            return pRe->toString() + "$" + pIm->toString();
        }

        Litterale* Complexe::simplification() {
            if (pIm->getValue() == 0) {
                Entier* conv = dynamic_cast<Entier*>(pRe);
                if (conv != nullptr)
                    return conv;
                Reelle* conv2 = dynamic_cast<Reelle*>(pRe);
                if (conv2 != nullptr)
                    return conv2;
                Rationnelle* conv3 = dynamic_cast<Rationnelle*>(pRe);
                if (conv3 != nullptr)
                    return conv3;
            }
            Entier* conv = dynamic_cast<Entier*>(pRe);
            if (conv != nullptr){
                Entier* pr = new Entier(conv->getValue());
                Complexe* res = new Complexe(pr,pIm);
                return res;
            }
            Reelle* conv2 = dynamic_cast<Reelle*>(pRe);
            if (conv2 != nullptr){
                Reelle* pr = new Reelle(conv2->getValue());
                Complexe* res = new Complexe(pr,pIm);
                return res;
            }
            Rationnelle* conv3 = dynamic_cast<Rationnelle*>(pRe);
            if (conv3 != nullptr){
                Rationnelle* pr = new Rationnelle(conv3->getNum(),conv3->getDen());
                Complexe* res = new Complexe(pr,pIm);
                return res;
            }
        }

