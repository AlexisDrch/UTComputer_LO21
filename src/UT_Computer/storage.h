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
};

class StockVariable {
    StockVariable();
    ~StockVariable(){}

    QMap<QString, Nombres*> listeVar;
    int nb;
    static StockVariable* instance;
public:
    static StockVariable* getInstance();
    void addVariable(const QString s, Nombres* n);
    void removeVariable(QString s);
    Litterale* fabriqLitterale(const QString& v);
    Litterale* isRationnelle(const QString& v);
};



#endif // STORAGE

