#ifndef OPERATOR_H
#define OPERATOR_H
#include <vector>
#include <QString>


//I] Operande : classe de base.
    class Operande {
    protected :
        QString name;
    public:
        Operande(const QString& na): name(na){}
        virtual ~Operande();
        virtual const QString toString() const = 0;
    };

//II] Littérale
    class Litterale : public Operande {
        //unsigned int type;
        friend class LitteraleManager;
    public :
        Litterale(const QString& na):Operande(na){}
        virtual ~Litterale();
        virtual const QString toString() const = 0;
        //A voir si utile ou pas lors de la création de variable + type utile ou pas ?
        void setName(const QString& na) { name = na;}
        //void getType() const {return type;}
    };

    //1) Litterale programme
        class LitProgramme : public Litterale{
            const QString value;
        public :
            LitProgramme(const QString& va, const QString na = ""):Litterale(na), value(va){}
            // A revoir .. pb de type de retour
            const QString toString() const {return name;}
            const QString& getValue() const {return value;}
        };

    //2) Litterale expression // GERER LES PRIORIOTE !!!///
        class LitExpression :public Litterale{
            //on considerera qu'une expression n'est en réalité qu'une liste d'opérande
            bool neg;
            QVector<Operande*> value;
            QString stringValue;    //RETIRER LES ESPACES DANS LE CONSTRUCTOR
        public :
            //a redefinir dans le .cpp pour push dans le value.
            LitExpression(const QString& str, const QString& na = "");
            Litterale* getValue() const;
            const QString toString()const;
            //Operateur unaire
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
                Litterale* operator*(const LitExpression& lit);
                Litterale* operator/(const LitExpression& lit);
                Litterale* operator$(const LitExpression& lit);
            //Operateur binaire Exp - Lit(a appeler dans sens inverse si besoin depuis le lit)
            QString litToExp(const LitNumerique& lit);
            Litterale* operatorDiv(const LitNumerique& lit);
            Litterale* operatorMod(const LitNumerique& lit);
            Litterale* operatorPow(const LitNumerique& lit);
                //Op symbole
                Litterale* operator+(const LitNumerique& lit);
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
            const QString toString() const;
        };

    //4) Nombres
        class Nombres : public Litterale{
        public :
            Nombres(const QString& na=""):Litterale(na){}
            virtual ~Nombres(){}
            virtual const QString toString() const =0;
            virtual Litterale* operatorExp();
        };
            //On choisira ici de rester conforme à l'énoncé en séparant les LitNumerique des complexes.

            //4.1) Litterale numérique
            class LitNumerique : public Nombres{
                int neg; // par défaut sera initialisé à 1
            public :
                LitNumerique(const QString& na=""):Nombres(na),neg(1){}
                virtual ~LitNumerique();
                virtual const QString toString() const = 0;
            };

            //4.1.1) Littérale entière
                class Entier : public LitNumerique {
                    unsigned int value;
                public:
                    //Remarque n'accepte pas les negatif : unsigned : operator NEG se charge de ça
                    Entier(unsigned int va, const QString& na =""): LitNumerique(na), value(va){}
                    const QString toString() const;
                };

            //4.1.2) Littérale rationelle
                class Rationelle : public LitNumerique{
                    Entier numerateur;
                    Entier denominateur;
                public:
                    //Denominateur diff de 0 sinon throw et diff de 1 sinon appelle simplification ?
                    Rationelle(Entier num, Entier den, const QString& na =""): LitNumerique(na), numerateur(num),denominateur(den){}
                    const QString toString() const;
                    LitNumerique* simplification();
               };

            //4.1.3) Littérale réelle
                class Reelle: public LitNumerique{
                    unsigned int mantisse;
                    unsigned int pEntiere;
                public:
                    //mantisse != 0 OR pEntiere != 0
                    Reelle(unsigned int ent, unsigned int man): pEntiere(ent), mantisse(man){}
                    LitNumerique* simplification();
                    const QString toString() const;
                };

        //4.2) Complexe
            class Complexe {
                LitNumerique* pRe;
                LitNumerique* pIm;
            public:
                Complexe(LitNumerique* re, LitNumerique* im): pRe(re), pIm(im){}
                const QString toString() const;
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
        virtual unsigned int addArg() = 0;
        unsigned int getTaille() const;
        const QString toString() const { return name;}

    };

    //1) Operateur Unaire
        class OpUnaire : public Operateur {

        public :
            OpUnaire(const QString& na): Operateur(na,1) {}
            virtual ~OpUnaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual Litterale* fonction(const Litterale& arg1) const =0;
            unsigned int addArg(const Litterale& e);
        };

        class OpExp : public OpUnaire {
        public:
            OpExp(): OpUnaire("EXP"){}
            Litterale*   fonction(const Litterale& arg1) const;
        };

        class OpLn : public OpUnaire {
        public:
            OpLn(): OpUnaire("LN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpNum : public OpUnaire {
        public:
            OpNum(): OpUnaire("NUM"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpDen : public OpUnaire {
        public:
            OpDen(): OpUnaire("DEN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpRe : public OpUnaire {
        public:
            OpRe(): OpUnaire("RE"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpIm : public OpUnaire {
        public:
            OpIm(): OpUnaire("IM"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpArg : public OpUnaire {
        public:
            OpArg(): OpUnaire("ARG"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpNorm : public OpUnaire {
        public:
            OpNorm(): OpUnaire("NORM"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpNot : public OpUnaire {
        public:
            OpNot(): OpUnaire("NOT"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpEval : public OpUnaire {
        public:
            OpEval(): OpUnaire("EVAL"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpNeg : public OpUnaire {
        public:
            OpNeg(): OpUnaire("NEG"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpSin : public OpUnaire {
        public:
            OpSin(): OpUnaire("SIN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpCos : public OpUnaire {
        public:
            OpCos(): OpUnaire("COS"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpTan: public OpUnaire {
        public:
            OpTan(): OpUnaire("TAN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpArcsin : public OpUnaire {
        public:
            OpArcsin(): OpUnaire("ARCSIN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpArccos : public OpUnaire {
        public:
            OpArccos(): OpUnaire("ARCCOS"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpArctan : public OpUnaire {
        public:
            OpArctan(): OpUnaire("ARCTAN"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpSqrt: public OpUnaire {
        public:
            OpSqrt(): OpUnaire("SQRT"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpDup : public OpUnaire {
        public:
            OpDup(): OpUnaire("DUP"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpDrop : public OpUnaire {
        public:
            OpDrop(): OpUnaire("DROP"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

        class OpEdit : public OpUnaire {
        public:
            OpEdit(): OpUnaire("EDIT"){}
            Litterale* fonction(const Litterale& arg1) const;
        };

    //2) Operateur Binaire
        class OpBinaire : public Operateur {

        public :
            OpBinaire(const QString& na): Operateur(na,2) {}
            virtual ~OpBinaire();
            //Executer :squelette pour classe fille : template methode
            Litterale* executer();
            virtual Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const =0;
            unsigned int addArg(const Litterale& e);

        };

        //ATTENTION : APPLIQUABLE SEULEMENT SUR LTTERALE NUMERIQUE ET EXPRESSION : FAUT IL LE PRECISER EN RESTREIGNANT LE TYPE DE PARAMETRE
        class OpInf : public OpBinaire{
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

        class OpPlus : public OpBinaire{
        public:
            OpPlus() : OpBinaire("+"){}
            Litterale* fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

        class OpMoins : public OpBinaire{
        public:
            OpMoins() : OpBinaire("-"){}
            Litterale*fonction(const Litterale& arg1, const Litterale& arg2) const;
        };

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








    #endif // PERATOR_H
