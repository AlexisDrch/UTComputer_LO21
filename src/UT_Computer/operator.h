#ifndef OPERATOR_H
#define OPERATOR_H

#include "pile.h"
#include "storage.h"

class OpDol;

//III] Opérateur /////FAIRE OPERATEUR DE PILE + DE BOUCLE////
    class Operateur : public Operande {

    protected :
        //tab contient les littéraux sur lequel sera appliqué la fontion définie dans la classe fille (template method).
        QVector<Litterale*> tab;
        unsigned int taille;

    public :
        Operateur(const QString& na, unsigned int t): Operande(na), taille(t) {}
        virtual ~Operateur();
        virtual Litterale* executer() = 0;
        virtual void addArg(Pile* pile);
        virtual void addArg(Litterale* arg1);
        unsigned int getTaille() const {return taille;}
        void setTaille(unsigned int t) { taille = t; }
        QString toString() const { return name;}

    };

    //1) Operateur Unaire
        class OpUnaire : public Operateur {

        public :
            OpUnaire(const QString& na): Operateur(na,1) {}
            virtual ~OpUnaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();

            virtual Litterale* fonctionNum(Nombres* arg1) ; // definie action commune a tout LitNumerique puis appelle la bonne surcharge
            virtual Litterale* fonctionExpression(LitExpression* arg1);
            virtual Litterale* actionNum(Entier& arg1)  =0;
            virtual Litterale* actionNum(Reelle& arg1)  =0;
            virtual Litterale* actionNum(Rationnelle& arg1)  =0;
            virtual Litterale* actionNum(Complexe& arg1)  =0;
            void addArg(Pile* pile);
            void addArg(Litterale* arg1);
        };

        //1.1 logique unaire
        class OpLogiqueUnaire : public OpUnaire{
        public :
            OpLogiqueUnaire(const QString &na):OpUnaire(na){}
            virtual ~OpLogiqueUnaire();
            Litterale* fonctionNum(Nombres* arg1);
            virtual Litterale* actionLogiNumerique(LitNumerique* arg1)  =0;
            //virtual //Litterale* actionLogiLitterale(Litterale* arg1, Litterale* arg2) const =0;
            //actionLogiqueComplexe ? Expression ?
            Litterale* actionNum(Reelle& arg1);
            Litterale* actionNum(Entier& arg1);
            Litterale* actionNum(Rationnelle& arg1);
            Litterale* actionNum(Complexe& arg1);

        };

        class OpNot : public OpLogiqueUnaire {
        public:
            OpNot(): OpLogiqueUnaire("NOT"){}
            Litterale* actionLogiNumerique(LitNumerique* arg1) ;
        };


        class OpExp : public OpUnaire {
        public:
            OpExp(): OpUnaire("EXP"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
            Litterale* actionNum(Rationnelle &arg1) ;
            Litterale* actionNum(Complexe &arg1) ;

        };
        class OpLn : public OpUnaire {
        public:
            OpLn(): OpUnaire("LN"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
            Litterale* actionNum(Rationnelle &arg1) ;
            Litterale* actionNum(Complexe &arg1) ;
        };
        /*
        class OpNum : public OpUnaire {
        public:
            OpNum(): OpUnaire("NUM"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpDen : public OpUnaire {
        public:
            OpDen(): OpUnaire("DEN"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpRe : public OpUnaire {
        public:
            OpRe(): OpUnaire("RE"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpIm : public OpUnaire {
        public:
            OpIm(): OpUnaire("IM"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpArg : public OpUnaire {
        public:
            OpArg(): OpUnaire("ARG"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpNorm : public OpUnaire {
        public:
            OpNorm(): OpUnaire("NORM"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };
        */
        class OpEval : public OpUnaire {
        public:
            OpEval(): OpUnaire("EVAL"){}
            Litterale* fonctionExpression(LitExpression* arg1);
            Litterale* Evaluation(QVector<Operande*>& vec);
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
            Litterale* actionNum(Rationnelle &arg1) ;
            Litterale* actionNum(Complexe &arg1) ;
        };


        class OpNeg : public OpUnaire {
        public:
            OpNeg(): OpUnaire("NEG"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
            Litterale* actionNum(Rationnelle &arg1) ;
            Litterale* actionNum(Complexe &arg1) ;
        };

        class OpSin : public OpUnaire {
        public:
            OpSin(): OpUnaire("SIN"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
            Litterale* actionNum(Rationnelle &arg1) ;
            Litterale* actionNum(Complexe &arg1) ;

        };/*

        class OpCos : public OpUnaire {
        public:
            OpCos(): OpUnaire("COS"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpTan: public OpUnaire {
        public:
            OpTan(): OpUnaire("TAN"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpArcsin : public OpUnaire {
        public:
            OpArcsin(): OpUnaire("ARCSIN"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpArccos : public OpUnaire {
        public:
            OpArccos(): OpUnaire("ARCCOS"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpArctan : public OpUnaire {
        public:
            OpArctan(): OpUnaire("ARCTAN"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpSqrt: public OpUnaire {
        public:
            OpSqrt(): OpUnaire("SQRT"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };
        */


    //2) Operateur Binaire
        class OpBinaire : public Operateur {

        public :
            OpBinaire(const QString& na): Operateur(na,2) {}
            virtual ~OpBinaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2)=0;
            virtual Litterale* fonctionExpression(LitExpression* arg1, Litterale* arg2) =0;
            void addArg(Pile* pile);
            void addArg(Litterale* arg);

        };




        //II] 3 Operateur de pile
        class OpPile: public Operateur{
        protected:
            Pile* litAff;
        public:
            OpPile(const QString& na,  unsigned int size):Operateur(na,size){}
            virtual ~OpPile();
            void  addArg(Pile *pile);
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual void executerPile() =0 ;
            void setPile(Pile* p1) {litAff = p1;}

        };

        class OpPileUnaire: public OpPile {
        public:
            OpPileUnaire(const QString& na): OpPile(na,1) {}
            virtual ~OpPileUnaire();
            //Executer :squelette pour classe fille : template methode
            virtual void executerPile();
        };

        class OpDup : public OpPileUnaire {
        public:
            OpDup(): OpPileUnaire("DUP"){}
            void executerPile();
            void fonctionNum(Litterale* arg1); //TODO: a definir en virtuelle pure dans la classe OPUNAIRE/OPBINAIRE

        };

        class OpDrop : public OpPileUnaire {
        public:
            OpDrop(): OpPileUnaire("DROP"){}
            void executerPile();
        };

        class OpClear : public OpPileUnaire {
        public:
            OpClear(): OpPileUnaire("CLEAR"){}
            void executerPile();
        };

        class OpSwap : public OpPileUnaire {
        public:
            OpSwap(): OpPileUnaire("SWAP"){}
            void executerPile();
        };
        /*
        class OpEdit : public OpPileUnaire {
        public:
            OpEdit(): OpPileUnaire("EDIT"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };
        */





#endif // OPERATOR_H
