#ifndef STORAGE
#define STORAGE

#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "litterale.h"
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

class DbManager {
    QSqlDatabase db;
    DbManager(const QString& path);
    ~DbManager();
    static DbManager* instance;
public:
    static DbManager* getInstance();
    bool addVariable(const QString& name, const QString& value);
    bool addProgramme(const QString& name, const QString& value);
    bool addPile(const QString& value);
    bool removePile(const QString& value);
};

class StockVariable {
    friend class QComputer;
    StockVariable();
    ~StockVariable(){}

    QMap<QString, Nombres*> listeVar;
    unsigned int nbVarToAffiche;
    unsigned int nb;
    static StockVariable* instance;
public:
    static StockVariable* getInstance();
    void addVariable(const QString s, Nombres* n);
    void removeVariable(QString s);
    Litterale* fabriqLitterale(const QString& v);
    Litterale* isRationnelle(const QString& v);
    //Adapteur d'objet
    unsigned int getNbItemsToAffiche(){ return nbVarToAffiche;}
    bool contains(const QString& s) { return listeVar.contains(s);}
    Nombres* at(const QString& key) {return listeVar[key];}

};
/*
class StockProgramme {
    friend class QComputer;
    StockVariable();
    ~StockVariable(){}

    QMap<QString, LitProgramme*> listeProg;
    unsigned int nbVarToAffiche;
    unsigned int nb;
    static StockProgramme* instance;
public:
    static StockProgramme* getInstance();
    void addProgramme(const QString s, Nombres* n);
    void removeProgramme(QString s);
    //Adapteur d'objet
    unsigned int getNbItemsToAffiche(){ return nbVarToAffiche;}
    bool contains(const QString& s) { return listeProg.contains(s);}
    LitProgramme* at(const QString& key) {return listeProg[key];}

};
*/


#endif // STORAGE

