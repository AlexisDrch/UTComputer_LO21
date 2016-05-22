#ifndef OPERATOR_H
#define OPERATOR_H

#include <Qvector>
#include <QString>
#include <math.h>
#include <sstream>
#include <string>


class ComputerException {
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};

//I] Operande : classe de base.
    class Operande {
    protected :
        QString name;
    public:
        Operande(const QString& na): name(na){}
        virtual ~Operande();
        virtual QString toString() const = 0;
    };

//II] Littérale
    //return QString::number(value); --> recup un string depuis un nombre
    class Litterale : public Operande {
        //unsigned int type;
        friend class LitteraleManager;
    public :
        Litterale(const QString& na = ""):Operande(na){}
        virtual ~Litterale();
        virtual QString toString() const = 0;
        //A voir si utile ou pas lors de la création de variable + type utile ou pas ?
        void setName(const QString& na) { name = na;}
        //void getType() const {return type;}

            //Opunaire

    };

    //1) Litterale programme
        class LitProgramme : public Litterale{
           QString stringValue;
           QVector<QString> tab;
           unsigned int taille;
           public :
               LitProgramme(const QString& str,const QString na = "");
               unsigned int getTaille(){return taille;}
               QString getelem(){return tab.front();}
               QString toString() const;
               const QString& getValue() const {return stringValue;}
        };

        class LitNumerique;

    //2) Litterale expression // GERER LES PRIORIOTE !!!///
        class LitExpression :public Litterale{
            //on considerera qu'une expression n'est en réalité qu'une liste d'opérande
            bool neg;
            QVector<const Operande*> value;
            QString stringValue;    //RETIRER LES ESPACES DANS LE CONSTRUCTOR
        public :
            //a redefinir dans le .cpp pour push dans le value.
            LitExpression(const QString& str, const QString& na = "");
            Litterale* getValue() const;
            QString toString()const;
            void  verifNeg() const;
            //Operateur unaire
            QString operatorUnaire(const QString& str);
            Litterale* operatorExp();
            Litterale* operatorNeg();
            Litterale* operatorSin();
            Litterale* operatorCos();
            Litterale* operatorTan();
            Litterale* operatorArcsin();
            Litterale* operatorArccos();
            Litterale* operatorArctan();
            Litterale* operatorSqrt();
            Litterale* operatorLn();
            Litterale* operatorNum();
            Litterale* operatorDen();
            Litterale* operatorRe();
            Litterale* operatorArg();
            Litterale* operatorNorm();
            //Operateur binaire Exp - Exp
                //Que sur des littérales entière ? (cf enoncé 1.4.1)
            QString operatorBinaire(const QString& str, const QString& str2);
            Litterale* operatorDiv(const LitExpression& lit);
            Litterale* operatorMod(const LitExpression& lit);
            Litterale* operatorPow(const LitExpression& lit);
                //Op symbole
                QString operatorSymbole(const QString& str, const QString& str2);
                Litterale* operator+(const LitExpression& lit);
                Litterale* operator-(const LitExpression& lit);
                Litterale* operator*(const LitExpression& lit);
                Litterale* operator/(const LitExpression& lit);
                Litterale* operator$(const LitExpression& lit);

                //Litterale* operator$(const LitExpression& lit);
            //Operateur binaire Exp - Lit(a appeler dans sens inverse si besoin depuis le lit)
            LitExpression* litToExp(const LitNumerique& lit);
            Litterale* operatorDiv(const LitNumerique& lit);
            Litterale* operatorMod(const LitNumerique& lit);
            Litterale* operatorPow(const LitNumerique& lit);
                //Op symbole
                Litterale* operator+(const LitNumerique& lit);
                Litterale* operator-(const LitNumerique& lit);
                Litterale* operator*(const LitNumerique& lit);
                Litterale* operator/(const LitNumerique& lit);
                Litterale* operator$(const LitNumerique& lit);

        };

    //3) Litterale atome
        class LitAtome : public Litterale {
            const QString value;
        public:
            LitAtome(const QString& va, const QString& na = ""):Litterale(na),value(va){}
            const QString& getValue() const {return value;}
            QString toString() const;
        };

    //4) Nombres
        class Nombres : public Litterale{
        public :
            Nombres(const QString& na=""):Litterale(na){}
            virtual ~Nombres(){}
            virtual QString toString() const =0;

            //Opearteur Binaire
            //virtual Litterale* operator+(const Nombres& n) = 0;
        };
            //On choisira ici de rester conforme à l'énoncé en séparant les LitNumerique des complexes.

            //4.1) Litterale numérique
            class LitNumerique : public Nombres{
            protected:
                bool neg; // par défaut sera initialisé à false
            public :
                LitNumerique(const QString& na=""):Nombres(na),neg(false){}
                virtual ~LitNumerique();
                virtual QString toString() const = 0;
                void setNeg(bool s) { neg = s;}
                bool getNeg() const {return neg;}
                Litterale* returnType();

                //Operateur unaire
                /*Litterale* operatorNeg();
                virtual Litterale* operatorExp();
               /* virtual Litterale* operatorLn();
                virtual Litterale* operatorSin();
                //Operateur binaire*/
            };

            //4.1.1) Littérale entière
                class Entier : public LitNumerique {
                    unsigned int value;
                public:
                    //Remarque n'accepte pas les negatif : unsigned : operator NEG se charge de ça
                    Entier(unsigned int va, const QString& na =""): LitNumerique(na), value(va){}
                    QString toString() const ;
                    unsigned int getValue() const {return value;}
                    void setValue(unsigned int v) {value = v; }

                    //Operateur
                    Litterale* operatorExp();
                    Litterale* operatorLn();
                    Litterale* operatorSin();
                    //Operateur binaire
                    Litterale* operator+(const Nombres& n);
                };

            //4.1.2) Littérale rationelle
                class Rationelle : public LitNumerique{
                    Entier numerateur;
                    Entier denominateur;
                public:
                    //Denominateur diff de 0 sinon throw et diff de 1 sinon appelle simplification ?
                    Rationelle(Entier num, Entier den, const QString& na =""): LitNumerique(na), numerateur(num),denominateur(den){}
                    QString toString() const;
                    Litterale* simplification();

                    //Operateur
                    Litterale* operator+(const Nombres& n);
                    // TODO
               };

            //4.1.3) Littérale réelle
                class Reelle: public LitNumerique{
                    unsigned int pEntiere;
                    unsigned int mantisse;
                public:
                    //mantisse != 0 OR pEntiere != 0
                    Reelle(float val, const QString& na=""):LitNumerique(na), pEntiere(floor(val)), mantisse((val-pEntiere)*100000){}
                    LitNumerique* simplification();
                    QString toString() const;
                    float toFloatPositif() const;

                    //Operateur
                    Litterale* operatorExp();
                    Litterale* operatorLn();
                    Litterale* operatorSin();
                    //Operateur binaire
                    Litterale* operator+(const Nombres& n);
                };

        //4.2) Complexe
            class Complexe {
                LitNumerique* pRe;
                LitNumerique* pIm;
            public:
                Complexe(LitNumerique* re, LitNumerique* im): pRe(re), pIm(im){}
                QString toString() const;
                LitNumerique& getpRe() const;
                LitNumerique& getpIm() const;

            };




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
            Litterale*fonction(const Litterale& arg1, const Litterale& arg2);
            Litterale* actionNum(Entier& arg1, Entier& arg2);
            Litterale* actionNum(Entier& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Reelle& arg2);
            Litterale* actionNum(Reelle& arg1, Entier& arg2);
        };
        /*
        class OpDiv : public OpBinaire{
        public:
            OpDiv() : OpBinaire("/"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

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
