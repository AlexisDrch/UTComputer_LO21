#ifndef COMPUTER_H
#define COMPUTER_H


#include <QDebug>
#include <QMediaPlayer>
#include <operatorFactory.h>

using namespace std;



class LitteraleManager {
    bool verif;
    Litterale** lits;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    LitteraleManager():lits(nullptr),nb(0),nbMax(0),verif(true){}
    ~LitteraleManager();
    LitteraleManager(const LitteraleManager& m);
    LitteraleManager& operator=(const LitteraleManager& m);

    struct Handler{
        LitteraleManager* instance;
        Handler():instance(nullptr){}
        // destructeur appel� � la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    bool getVerif(){return verif;}
    void setVerif(bool v) {verif =v;}
    Litterale* addLitterale(const QString& str);
    Litterale& addLitterale(Litterale* res);
    Litterale* isRationnelle(const QString& c);
    bool verifLitterale(QString& op, QString& nouvelle, QVector<Operande*>& vectorExp);
    QString verifExpressionValide(const QString& c, QVector<Operande*>& vect); // to implement
    Litterale* fabriqLitterale(const QString& v);
    void removeLitterale(Litterale& e);
    static LitteraleManager& getInstance();
    static void libererInstance();
    QString messageNouvelleCreation(Litterale& lit);
    class iterator {
        Litterale** current;
        iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:
        iterator():current(0){}
        Litterale& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(lits); }
    iterator end() { return iterator(lits+nb); }

    class const_iterator {
        Litterale** current;
        const_iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:
        const_iterator():current(0){}
        Litterale& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(lits); }
    const_iterator end() const { return const_iterator(lits+nb); }
};


class Controleur {
    QMediaPlayer* bip;
    LitteraleManager& litMng;
    Pile& litAff;
    QMap<QString, OperateurFactory*> factories;
public:
    Controleur(LitteraleManager& m, Pile& v):litMng(m), litAff(v){
        factories = OperateurFactory::getFactoriesMap();
        bip = new QMediaPlayer();
        bip->setMedia(QUrl("qrc:/sounds/beep-07.wav"));
    }
    Operateur* getOperateur(const QString& v);
    QString getFirst(QString& v);
    QString commande(QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);

#endif // COMPUTER_H
