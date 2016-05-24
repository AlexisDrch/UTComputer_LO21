#ifndef LITTERALE_H
#define LITTERALE_H
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
    protected :
        bool neg;
        friend class LitteraleManager;
    public :
        Litterale(const QString& na = ""):Operande(na),neg(false){}
        virtual ~Litterale();
        virtual QString toString() const = 0;
        //A voir si utile ou pas lors de la création de variable + type utile ou pas ?
        void setName(const QString& na) { name = na;}
        void setNeg(bool s) { neg = s;}
        bool getNeg() const {return neg;}
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
               const QString& getValueProg() const {return stringValue;}
        };

        class LitNumerique;

    //2) Litterale expression // GERER LES PRIORIOTE !!!///
        class LitExpression :public Litterale{
            //on considerera qu'une expression n'est en réalité qu'une liste d'opérande
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
        };
            //On choisira ici de rester conforme à l'énoncé en séparant les LitNumerique des complexes.

            //4.1) Litterale numérique
            class LitNumerique : public Nombres{
            protected:
                // par défaut sera initialisé à false
            public :
                LitNumerique(const QString& na=""):Nombres(na){}
                virtual ~LitNumerique();
                virtual QString toString() const = 0;
                Litterale* returnType();
                virtual float getValue()const = 0;
            };

            //4.1.1) Littérale entière
                class Entier : public LitNumerique {
                    unsigned int value;
                public:
                    //Remarque n'accepte pas les negatif : unsigned : operator NEG se charge de ça
                    Entier(unsigned int va, const QString& na =""): LitNumerique(na), value(va){}
                    QString toString() const ;
                    float getValue()const ;
                    unsigned int getValueEnt() const {return value;}
                    void setValue(unsigned int v) {value = v; }
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
                    float getValue()const;
                    unsigned int getValueRat() const {return numerateur.getValue();} //todo

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
                    float getValue()const;
                    float toFloatPositif() const;

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



#endif // LITTERALE_H
