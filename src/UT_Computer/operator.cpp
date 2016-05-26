#include "operator.h"


    //II]Operateur
    Operateur::~Operateur(){
     //ici on supprime les litteraux sauf le premier (car c'est devenu le resultat de l'operation et est en pile)
        for(unsigned int i =1; i <taille; i++){
            delete tab.operator [](i);
        }
    }
    void Operateur::addArg(Pile *pile){pile->setMessage("Operateur abstrait");}

        //II.1) Operateur Unaire
        OpUnaire::~OpUnaire(){

        }
        void OpUnaire::addArg(Pile* pile){
            if (tab.size() <=1){
            tab.push_back(&pile->top());
            }
            else throw ComputerException("Error : Tentative d'ajout de plus de 1 argument à un opérateur unaire");
        }
        Litterale* OpUnaire::executer(){

            Nombres* arg1 = dynamic_cast<Nombres*>(tab.front());

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
        Litterale* OpUnaire::fonctionNum(Nombres *arg1) {
            Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return actionNum(*conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return actionNum(*conv1);
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return actionNum(*conv2);
        }

            //NEG
            Litterale* OpNeg::fonctionNum(Nombres* arg1){
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
            Litterale* OpNeg::actionNum(Rationnelle& arg1){
                arg1.setNeg(!arg1.getNeg());
                return arg1.returnType();
            }

             //EXP
            Litterale* OpExp::actionNum(Entier& arg1){
                float f = exp(arg1.getValue());
                return (new Reelle(f));
            }
            Litterale* OpExp::actionNum(Reelle& arg1){
                float f = arg1.getValue();
                f = exp(f);
                return (new Reelle(f));
            }
            Litterale* OpExp::actionNum(Rationnelle& arg1){
                float f = exp(arg1.getValue());
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
                float f = arg1.getValue();
                f = log(f);
                return (new Reelle(f));
            }
            Litterale* OpLn::actionNum(Rationnelle &arg1) {
                if (arg1.getNeg()) throw ComputerException("Operation impossible sur litterale negative");;
                float f = arg1.getValue();
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
            Litterale* OpSin::actionNum(Rationnelle &arg1){
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

            //1.2 OpLogique unaire
            OpLogiqueUnaire::~OpLogiqueUnaire(){}

            Litterale* OpLogiqueUnaire::fonctionNum(Nombres *arg1){
                LitNumerique* conv1 = dynamic_cast<LitNumerique*>(arg1);
                if (conv1 != nullptr) return actionLogiNumerique(conv1);
                else throw ComputerException("Operation impossible sur ces littéraux");
            }

            Litterale* OpLogiqueUnaire::actionNum(Entier& arg1){ throw ("Error ");} //A ameliorer ?? Creation d'une sous classe pour distinguer NON logique de Logique plutot que d'avoir tout en classe OpBinaire...Unaire
            Litterale* OpLogiqueUnaire::actionNum(Reelle& arg1){ throw ("Error ");}
            Litterale* OpLogiqueUnaire::actionNum(Rationnelle& arg1){ throw ("Error ");}

            //OpNot
            Litterale* OpNot::actionLogiNumerique(LitNumerique* arg1)  {
                Entier* conv = dynamic_cast<Entier*>(arg1);
                if(conv!=nullptr) if(conv->getValue() == 0) return (new Entier(1));
                return (new Entier(0));
            }



        //II.2) Operateur Binaire
        OpBinaire::~OpBinaire(){

        }

        void OpBinaire::addArg(Pile* pile){
            if (tab.size() <=2){
            tab.push_back(&pile->top());
            }
            else throw ComputerException("Error : Tentative d'ajout de plus de 2 arguments à un opérateur binaire");
        }

        Litterale* OpBinaire::executer(){

            Nombres* arg1 = dynamic_cast<Nombres*>(tab.operator [](1));
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
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return fonctionNum2(conv2, arg2);
        }
        Litterale* OpBinaire::fonctionNum2(Entier* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
        }
        Litterale* OpBinaire::fonctionNum2(Reelle* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
        }
        Litterale* OpBinaire::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
            Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) return actionNum(*arg1, *conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) return actionNum(*arg1, *conv1);
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) return actionNum(*arg1, *conv2);
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
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue();}
                else y = arg1.getValue() + arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Entier& arg1, Rationnelle& arg2){
                int num,den;
                bool neg;
                den = arg2.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=arg2.getNum() + arg1.getValue()*den; neg = true;}
                else if (arg1.getNeg()) {num=arg2.getNum() - arg1.getValue()*den;}
                else if (arg2.getNeg()) {num=-arg2.getNum() + arg1.getValue()*den;}
                else num=arg2.getNum() + arg1.getValue()*den;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }

            Litterale* OpPlus::actionNum(Reelle& arg1, Reelle &arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
                else y = arg1.getValue() + arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Reelle& arg1, Entier& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue();  }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
                else y = arg1.getValue() + arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Reelle& arg1, Rationnelle& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
                else y = arg1.getValue() + arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }

            Litterale* OpPlus::actionNum(Rationnelle& arg1, Rationnelle& arg2){
                int num,den;
                bool neg = false;
                den = arg1.getDen() * arg2.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen(); neg = true;}
                else if (arg1.getNeg()) {num=-arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
                else if (arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();}
                else num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Rationnelle& arg1, Entier& arg2){
                int num,den;
                bool neg;
                den = arg1.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=arg1.getNum() + (int)arg2.getValue()*den; neg = true;}
                else if (arg1.getNeg()) {num=-arg1.getNum() + (int)arg2.getValue()*den;}
                else if (arg2.getNeg()) {num=arg1.getNum() - (int)arg2.getValue()*den;}
                else num=arg1.getNum() + (int)arg2.getValue()*den;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpPlus::actionNum(Rationnelle& arg1, Reelle& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = arg1.getValue()+arg2.getValue(); neg = true; }
                else if(arg1.getNeg()) { y = -arg1.getValue() + arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() - arg2.getValue(); }
                else y = arg1.getValue() + arg2.getValue();
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
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.getValue(); }
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
                else y = arg1.getValue() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Entier& arg1, Rationnelle& arg2){
                int num,den;
                bool neg;
                den = arg2.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=arg2.getNum() - arg1.getValue()*den;}
                else if (arg1.getNeg()) {num=-arg2.getNum() - arg1.getValue()*den;}
                else if (arg2.getNeg()) {num=arg2.getNum() + arg1.getValue()*den;}
                else num=-arg2.getNum() + (int)arg1.getValue()*den;
                int temp1 = -arg2.getNum();
                int temp2 = arg1.getValue();
                int temp3 = temp2*den;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Reelle& arg1, Reelle &arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue() + arg2.getValue();}
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
                else y = arg1.getValue() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Reelle& arg1, Entier& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue();}
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue();}
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
                else y = arg1.getValue() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Reelle& arg1, Rationnelle& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue(); }
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
                else y = arg1.getValue() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }

            Litterale* OpMoins::actionNum(Rationnelle& arg1, Rationnelle& arg2){
                int num,den;
                bool neg = false;
                den = arg1.getDen() * arg2.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=-arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
                else if (arg1.getNeg()) {num=-arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();}
                else if (arg2.getNeg()) {num=arg1.getNum()*arg2.getDen() + arg2.getNum()*arg1.getDen();}
                else num=arg1.getNum()*arg2.getDen() - arg2.getNum()*arg1.getDen();;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Rationnelle& arg1, Entier& arg2){
                int num,den;
                bool neg;
                den = arg1.getDen();
                if(arg1.getNeg() && arg2.getNeg()) {num=-arg1.getNum() + (int)arg2.getValue()*den;}
                else if (arg1.getNeg()) {num=-arg1.getNum() - (int)arg2.getValue()*den;}
                else if (arg2.getNeg()) {num=arg1.getNum() + (int)arg2.getValue()*den;}
                else num=arg1.getNum() - (int)arg2.getValue()*den;
                if(num<0) {num=-num; neg = true;}
                Rationnelle* temp = new Rationnelle(num,den);
                Litterale* res = temp->simplification(); if (neg) res->setNeg(true); return res;
            }
            Litterale* OpMoins::actionNum(Rationnelle& arg1, Reelle& arg2){
                float y; bool neg =false;
                if(arg1.getNeg() && arg2.getNeg()){ y = -arg1.getValue()+arg2.getValue(); }
                else if(arg1.getNeg()) { y = -arg1.getValue() - arg2.getValue(); }
                else if(arg2.getNeg()) { y = arg1.getValue() + arg2.getValue(); }
                else y = arg1.getValue() - arg2.getValue();
                if(y<0) {y=-y; neg = true;}
                Reelle* res = new Reelle(y); if (neg) res->setNeg(true); return res;
            }
            //OpDiv
            Litterale* OpDiv::fonctionNum(Nombres* arg1, Litterale* arg2){
                LitNumerique* conv = dynamic_cast<LitNumerique*>(arg2);
                if (conv!= nullptr) if(conv->getValue() ==0) throw ComputerException("Error : div par 0 impossible");
                OpBinaire::fonctionNum(arg1, arg2);//sinon on reappelle la division classique.
            }

            Litterale* OpDiv::fonctionNum2(Entier* arg1, Litterale *arg2) {
                Litterale *res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res;}
                else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
                return res;
            }
            Litterale* OpDiv::fonctionNum2(Reelle* arg1, Litterale *arg2) {
                Litterale* res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res; }
                else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
                return res;
            }
            Litterale* OpDiv::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
                Litterale* res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res; }
                else if(arg1->getNeg() || arg2->getNeg()) { res->setNeg(true); }
                return res;
            }

            Litterale* OpDiv::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
                return (new Reelle(arg1.getValue()/(float)arg2.getValue()));
            }
            Litterale* OpDiv::actionNum(Entier& arg1, Reelle& arg2){
                return (new Reelle(arg1.getValue()/arg2.getValue()));
            }
            Litterale* OpDiv::actionNum(Entier& arg1, Rationnelle& arg2){
                Rationnelle* r = new Rationnelle(arg1.getValue()*arg2.getDen(),arg2.getNum());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpDiv::actionNum(Reelle& arg1, Reelle &arg2){
                return (new Reelle(arg1.getValue()/arg2.getValue()));
            }
            Litterale* OpDiv::actionNum(Reelle& arg1, Entier& arg2){
                return (new Reelle(arg1.getValue()/arg2.getValue()));
            }
            Litterale* OpDiv::actionNum(Reelle& arg1, Rationnelle& arg2){
                return (new Reelle(arg1.getValue()/arg2.getValue()));
            }

            Litterale* OpDiv::actionNum(Rationnelle& arg1, Rationnelle& arg2){
                Rationnelle* r = new Rationnelle(arg1.getNum()*arg2.getDen(),arg1.getDen()*arg2.getNum());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpDiv::actionNum(Rationnelle& arg1, Entier& arg2){
                Rationnelle* r = new Rationnelle(arg2.getValue()*arg1.getDen(),arg1.getNum());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpDiv::actionNum(Rationnelle& arg1, Reelle& arg2){
                return (new Reelle(arg1.getValue()/arg2.getValue()));
            }

            //OpMul
            Litterale* OpMul::fonctionNum2(Entier* arg1, Litterale *arg2) {
                Litterale *res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr)  res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res;}
                else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
                return res;
            }
            Litterale* OpMul::fonctionNum2(Reelle* arg1, Litterale *arg2) {
                Litterale* res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res; }
                else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
                return res;
            }
            Litterale* OpMul::fonctionNum2(Rationnelle* arg1, Litterale *arg2) {
                Litterale* res;
                Entier* conv = dynamic_cast<Entier*>(arg2); if(conv != nullptr) res = actionNum(*arg1, *conv);
                Reelle* conv1 = dynamic_cast<Reelle*>(arg2); if(conv1 != nullptr) res = actionNum(*arg1, *conv1);
                Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg2); if(conv2 != nullptr) res = actionNum(*arg1, *conv2);
                if(arg1->getNeg() && arg2->getNeg()){ return res; }
                else if(arg1->getNeg() || arg1->getNeg()) { res->setNeg(true); }
                return res;
            }

            Litterale* OpMul::actionNum(Entier& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
                return (new Entier(arg1.getValue()*(float)arg2.getValue()));
            }
            Litterale* OpMul::actionNum(Entier& arg1, Reelle& arg2){
                return (new Reelle(arg1.getValue()*arg2.getValue()));
            }
            Litterale* OpMul::actionNum(Entier& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
                Rationnelle* r = new Rationnelle(arg1.getValue()*arg2.getNum(),arg2.getDen());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpMul::actionNum(Reelle& arg1, Reelle &arg2){
                return (new Reelle(arg1.getValue()*arg2.getValue()));
            }
            Litterale* OpMul::actionNum(Reelle& arg1, Entier& arg2){
                return (new Reelle(arg1.getValue()*arg2.getValue()));
            }
            Litterale* OpMul::actionNum(Reelle& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
                return (new Reelle(arg1.getValue()*arg2.getValue()));
            }

            Litterale* OpMul::actionNum(Rationnelle& arg1, Rationnelle& arg2){ // Reelle ou Rationnelle return ?
                Rationnelle* r = new Rationnelle(arg1.getNum()*arg2.getNum(),arg1.getDen()*arg2.getDen());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpMul::actionNum(Rationnelle& arg1, Entier& arg2){ // Reelle ou Rationnelle return ?
                Rationnelle* r = new Rationnelle(arg2.getValue()*arg1.getNum(),arg1.getDen());
                Litterale* res = r->simplification();
                return res;
            }
            Litterale* OpMul::actionNum(Rationnelle& arg1, Reelle& arg2){ // Reelle ou Rationnelle return ?
                return (new Reelle(arg1.getValue()*arg2.getValue()));
            }
            //OpLogiqueBinaire
            OpLogiqueBinaire::~OpLogiqueBinaire(){}

            Litterale* OpLogiqueBinaire::fonctionNum(Nombres* arg1, Litterale* arg2){
                LitNumerique* conv1 = dynamic_cast<LitNumerique*>(arg1);
                LitNumerique* conv2 = dynamic_cast<LitNumerique*>(arg2);
                if (conv1 != nullptr  && conv2 != nullptr) return actionLogiNumerique(conv1, conv2);
                else throw ComputerException("Operation < impossible sur ces littéraux");
            }

            Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Entier& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Reelle& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Entier& arg1, Rationnelle& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Reelle& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Entier& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Reelle& arg1, Rationnelle& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Rationnelle& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Entier& arg2){ throw ("Error ");}
            Litterale* OpLogiqueBinaire::actionNum(Rationnelle& arg1, Reelle& arg2){ throw ("Error ");}


            //OpInf
            Litterale* OpInf::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2)  { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue()< arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpSup
            Litterale* OpSup::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue()> arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpEg
            Litterale* OpEg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue() == arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpDif
            Litterale* OpDiff::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue() != arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpInfeg
            Litterale* OpInfeg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue()<= arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpSupeg
            Litterale* OpSupeg::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue()>= arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpAnd
            Litterale* OpAnd::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue() && arg2->getValue())? (new Entier(1)) :new Entier(0));
            }
            //OpOr
            Litterale* OpOr::actionLogiNumerique(LitNumerique *arg1, LitNumerique *arg2) { // faire avec Litterale génerale (complexe ? )
                 return ((arg1->getValue() || arg2->getValue())? (new Entier(1)) :new Entier(0));
            }


            //II.3) Operateur Pile
            OpPile::~OpPile(){}


            void OpPile::addArg(Pile *pile){
                litAff=pile;
            }
            Litterale* OpPile::executer(){
                try{
                    executerPile();
                    return (new Entier(1));
                }
                catch(ComputerException ex){
                    litAff->setMessage(ex.getInfo());
                    return (new Entier(0));
                }
            }

                //3.1 Operateur Pile Unaire
                OpPileUnaire::~OpPileUnaire(){

                }
                void OpPileUnaire::executerPile(){
                    /*INUTILE ?
                   LitNumerique* arg1 = dynamic_cast<LitNumerique*>(&litAff->top());

                    if(arg1 != nullptr){
                        fonctionNum(arg1);
                    }
                    else {
                        throw "error : operateur non valide sur ce litterale";
                        //LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.front());
                        //if(arg1 != nullptr){
                        //return fonction2(*arg1);
                    }*/
                }
                /*INUTILE ?
                void OpPileUnaire::fonctionNum(LitNumerique *arg1) {
                    Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return actionNum(*conv);
                    Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return actionNum(*conv1);
                }*/

                //DUP
                void OpDup::executerPile(){
                    litAff->push(litAff->top());
                }
                /*INUTILE ?
                void OpDup::actionNum(Entier &arg1){
                    //return (new Entier(arg1));
                }
                void OpDup::actionNum(Reelle &arg1){
                    //return (new Reelle(arg1));
                }*/
                //DROP
                void OpDrop::executerPile(){
                    litAff->pop();
                }
                //CLEAR
                void OpClear::executerPile(){
                    while(!(litAff->estVide())){
                        litAff->pop();
                    }
                }
                //SWAP
                void OpSwap::executerPile(){
                    Litterale* arg1 = &litAff->top();litAff->pop();
                    Litterale* arg2 = &litAff->top(); litAff->pop();
                    litAff->push(*arg1); litAff->push(*arg2);
                }










