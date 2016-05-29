#include "operator.h"


    //II]Operateur
    Operateur::~Operateur(){
     //ici on supprime les litteraux sauf le premier (car c'est devenu le resultat de l'operation et est en pile)
        for(unsigned int i =1; i <taille; i++){
            delete tab.operator [](i);
        }
    }
    void Operateur::addArg(Pile *pile){pile->setMessage("Operateur abstrait");}

    void Operateur::addArg(Litterale* arg1){throw ComputerException("Operateur abstrait : ERROR"); }

        //II.1) Operateur Unaire
        OpUnaire::~OpUnaire(){

        }
        void OpUnaire::addArg(Pile* pile){
            if (tab.size() <=1){
            tab.push_back(&pile->top());
            }
            else throw ComputerException("Error : Tentative d'ajout de plus de 1 argument à un opérateur unaire");
        }

        void OpUnaire::addArg(Litterale* arg1){
            if (tab.size() <=1){
            tab.push_back(arg1);
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
                LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.front());
                if(arg1 != nullptr){
                    Litterale* res = fonctionExpression(arg1);
                    delete arg1;
                    return res;
                }
                else throw "error : operateur non valide sur ce litterale";
            }
        }
        Litterale* OpUnaire::fonctionNum(Nombres *arg1) {
            Entier* conv = dynamic_cast<Entier*>(arg1); if(conv != nullptr) return actionNum(*conv);
            Reelle* conv1 = dynamic_cast<Reelle*>(arg1); if(conv1 != nullptr) return actionNum(*conv1);
            Rationnelle* conv2 = dynamic_cast<Rationnelle*>(arg1); if(conv2 != nullptr) return actionNum(*conv2);
        }
        Litterale* OpUnaire::fonctionExpression(LitExpression* arg1) {
            OpNeg* neg= dynamic_cast<OpNeg*>(this);
            if(neg != nullptr) {
                throw ComputerException("NEG n'est pas applicable sur une litterale expression");
            }
        return (new LitExpression(this->getName()+"("+arg1->toString()+")"));
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

            //EVAL
            Litterale* OpEval::fonctionExpression(LitExpression* arg1){
                QVector<Operande*>& vector = arg1->getVector();
                /*QString res;
                for(unsigned int i = 0 ; i<vector.size();i++){
                    res = res + vector.at(i)->toString();
                }
                    return (new LitExpression(res));*/
                return Evaluation(vector);
                }

            Litterale* OpEval::Evaluation(QVector<Operande*>& vec) {
                Operande* operande = vec.front();
                vec.pop_front();
                Litterale* litterale = dynamic_cast<Litterale*>(operande);
                if(litterale != nullptr) return litterale;

                Operateur* operateur = dynamic_cast<Operateur*>(operande);
                if (operateur!= nullptr) {
                    for(unsigned int i =0 ; i< operateur->getTaille(); i++){
                        operateur->addArg(Evaluation(vec));
                    }
                    return operateur->executer();
                }
            }
            Litterale* OpEval::actionNum(Entier &arg1) {
                return &arg1;
            }
            Litterale* OpEval::actionNum(Reelle &arg1) {
                return &arg1;
            }
            Litterale* OpEval::actionNum(Rationnelle &arg1){
                return &arg1;
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

        void OpBinaire::addArg(Litterale* arg){
            if (tab.size() <=2){
            tab.push_back(arg);
            }
            else throw ComputerException("Error : Tentative d'ajout de plus de 2 argument à un opérateur binaire");
        }

        Litterale* OpBinaire::executer(){
            Nombres* arg1 = dynamic_cast<Nombres*>(tab.operator [](1));
            Litterale* arg2 = dynamic_cast<Litterale*>(tab.operator [](0));

            if(arg1 != nullptr){
                Litterale* res = fonctionNum(arg1,arg2);
                delete arg2;
                return res;
            }
            else {
                LitExpression* arg1 = dynamic_cast<LitExpression*>(tab.operator [](1));
                if(arg1 != nullptr){
                    Litterale* res = fonctionExpression(arg1,arg2);
                    return res;
                }
                throw "error : operateur non valide sur ce litterale";
            }
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
                void OpPileUnaire::executerPile(){}

                //DUP
                void OpDup::executerPile(){
                    litAff->push(litAff->top());
                }
                //DROP
                void OpDrop::executerPile(){
                    litAff->pop();
                }
                //CLEAR
                void OpClear::executerPile(){
                    while(!(litAff->estVide())){
                        delete &litAff->top();
                        litAff->pop();
                    }
                }
                //SWAP
                void OpSwap::executerPile(){
                    Litterale* arg1 = &litAff->top();litAff->pop();
                    Litterale* arg2 = &litAff->top(); litAff->pop();
                    litAff->push(*arg1); litAff->push(*arg2);
                }










