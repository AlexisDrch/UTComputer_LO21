#include "operator.h"


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
            //OpDiv
            Litterale* OpDiv::fonctionNum2(Entier* arg1, Litterale *arg2) {
                Litterale *res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                if(arg1->getNeg() && arg2->getNeg()){ return res;}
                else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
                return res;
            }
            Litterale* OpDiv::fonctionNum2(Reelle* arg1, Litterale *arg2) {
                Litterale* res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                if(arg1->getNeg() && arg2->getNeg()){ return res; }
                else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
                return res;
            }

            Litterale* OpDiv::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationelle return ?
                return (new Reelle(arg1.getValue()/(float)arg2.getValue()));
            }
            Litterale* OpDiv::actionNum(Entier& arg1, Reelle& arg2){
                return (new Reelle(arg1.getValue()/arg2.toFloatPositif()));
            }
            Litterale* OpDiv::actionNum(Reelle& arg1, Reelle &arg2){
                return (new Reelle(arg1.toFloatPositif()/arg2.toFloatPositif()));
            }
            Litterale* OpDiv::actionNum(Reelle& arg1, Entier& arg2){
                return (new Reelle(arg1.toFloatPositif()/arg2.getValue()));
            }






