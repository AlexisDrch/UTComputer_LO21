#ifndef OPERATOR_H
#define OPERATOR_H

#include "litterale.h"

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
        virtual unsigned int addArg(Litterale& e) = 0;
        unsigned int getTaille() const {return taille;}
        QString toString() const { return name;}

    };

    //1) Operateur Unaire
        class OpUnaire : public Operateur {

        public :
            OpUnaire(const QString& na): Operateur(na,1) {}
            virtual ~OpUnaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual Litterale* fonctionNum(LitNumerique* arg1) ; // definie action commune a tout LitNumerique puis appelle la bonne surcharge
            virtual Litterale* actionNum(Entier& arg1)  =0;
            virtual Litterale* actionNum(Reelle& arg1)  =0;
            unsigned int addArg(Litterale& e);
        };

       class OpExp : public OpUnaire {
        public:
            OpExp(): OpUnaire("EXP"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;

        };
        class OpLn : public OpUnaire {
        public:
            OpLn(): OpUnaire("LN"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;
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

        class OpNot : public OpUnaire {
        public:
            OpNot(): OpUnaire("NOT"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpEval : public OpUnaire {
        public:
            OpEval(): OpUnaire("EVAL"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };
*/
        class OpNeg : public OpUnaire {
        public:
            OpNeg(): OpUnaire("NEG"){}
            Litterale* fonctionNum(LitNumerique *arg1) ;
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;

        };

        class OpSin : public OpUnaire {
        public:
            OpSin(): OpUnaire("SIN"){}
            Litterale* actionNum(Entier &arg1) ;
            Litterale* actionNum(Reelle &arg1) ;

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

        class OpDup : public OpUnaire {
        public:
            OpDup(): OpUnaire("DUP"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpDrop : public OpUnaire {
        public:
            OpDrop(): OpUnaire("DROP"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

        class OpEdit : public OpUnaire {
        public:
            OpEdit(): OpUnaire("EDIT"){}
            Litterale* fonctionNum(LitNumerique& arg1) const;
        };

    *///2) Operateur Binaire
        class OpBinaire : public Operateur {

        public :
            OpBinaire(const QString& na): Operateur(na,2) {}
            virtual ~OpBinaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual Litterale* fonctionNum(Nombres* arg1, Litterale* arg2);
            virtual Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
            virtual Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
            virtual Litterale* actionNum(Entier& arg1, Entier& arg2) =0;
            virtual Litterale* actionNum(Entier& arg1, Reelle& arg2) =0;
            virtual Litterale* actionNum(Reelle& arg1, Reelle& arg2) =0;
            virtual Litterale* actionNum(Reelle& arg1, Entier& arg2) =0;
            unsigned int addArg(Litterale& e);

        };

        //ATTENTION : APPLIQUABLE SEULEMENT SUR LTTERALE NUMERIQUE ET EXPRESSION : FAUT IL LE PRECISER EN RESTREIGNANT LE TYPE DE PARAMETRE
    /*    class OpInf : public OpBinaire{
        public:
            OpInf() : OpBinaire("<"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpSup : public OpBinaire{
        public:
            OpSup() : OpBinaire(">"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpSupeg : public OpBinaire{
        public:
            OpSupeg() : OpBinaire(">="){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpInfeg : public OpBinaire{
        public:
            OpInfeg() : OpBinaire("=<"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpEg: public OpBinaire{
        public:
            OpEg() : OpBinaire("="){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpDiff : public OpBinaire{
        public:
            OpDiff() : OpBinaire("!="){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

     */ class OpPlus : public OpBinaire{
        public:
            OpPlus() : OpBinaire("+"){}
            Litterale* actionNum(Entier& arg1, Entier& arg2);
            Litterale* actionNum(Entier& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Entier& arg2);

        };

        class OpMoins : public OpBinaire{
        public:
            OpMoins() : OpBinaire("-"){}
            Litterale* actionNum(Entier& arg1, Entier& arg2);
            Litterale* actionNum(Entier& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Entier& arg2);
        };

        class OpDiv : public OpBinaire{
        public:
            OpDiv() : OpBinaire("/"){}
            Litterale* fonctionNum2(Entier* arg1, Litterale* arg2);
            Litterale* fonctionNum2(Reelle* arg1, Litterale* arg2);
            Litterale* actionNum(Entier& arg1, Entier& arg2);
            Litterale* actionNum(Entier& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Entier& arg2);
        };
        /*
        class OpMul : public OpBinaire{
        public:
            OpMul() : OpBinaire("*"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpMod : public OpBinaire{
        public:
            OpMod() : OpBinaire("%"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpDol : public OpBinaire{
        public:
            OpDol() : OpBinaire("$"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpAnd : public OpBinaire{
        public:
            OpAnd() : OpBinaire("AND"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpOr : public OpBinaire{
        public:
            OpOr() : OpBinaire("OR"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

*/





#endif // OPERATOR_H
