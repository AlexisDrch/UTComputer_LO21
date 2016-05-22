#ifndef COMPUTER_H
#define COMPUTER_H


#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <operatorFactory.h>

using namespace std;



class LitteraleManager {
    Litterale** lits;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    LitteraleManager():lits(nullptr),nb(0),nbMax(0){}
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
    Litterale& addLitterale(const QString& str);
    Litterale& addLitterale(Litterale* res);
    Litterale* isRationelle(const QString& c);
    bool verifLitterale(const QString& c); // to implement
    Litterale* fabriqLitterale(const QString& v); // to implement
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


class Item {
    Litterale* lit;
public:
    Item():lit(nullptr){}
    void setLitterale(Litterale& e) { lit=&e; }
    void raz() { lit = 0; }
    Litterale& getLitterale() const;
};

class Pile : public QObject {
    Q_OBJECT

    Item* items;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(5){}
    ~Pile();
    void push(Litterale& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Litterale& top() const;
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }
    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }
    class iterator {
        Item* current;
        iterator(Item* u):current(u){}
        friend class Pile;
    public:
        iterator():current(nullptr){}
        Litterale& operator*() const { return current->getLitterale(); }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(items+nb-1); }
    iterator end() { return iterator(items-1); }

    class const_iterator {
        Item* current;
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const Litterale& operator*() const { return current->getLitterale(); }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(items+nb-1); }
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
};

class Controleur {
    LitteraleManager& litMng;
    Pile& litAff;
    QMap<QString, OperateurFactory*> factories;
public:
    Controleur(LitteraleManager& m, Pile& v):litMng(m), litAff(v){
        factories = OperateurFactory::getFactoriesMap();
    }
    Operateur* getOperateur(const QString& v);
    void commande(const QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);

#endif // COMPUTER_H
