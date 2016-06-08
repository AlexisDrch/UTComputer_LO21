#ifndef STORAGE
#define STORAGE

#include <QMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "litterale.h"
#include <QVariant>
#include <QDebug>
#include <QSqlError>


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
    StockVariable() : nb(0){}
    ~StockVariable(){}

    QMap<QString, Nombres*> listeVar;
    int nb;
    static StockVariable* instance;
public:
    static StockVariable* getInstance();
    void addVariable(const QString s, Nombres* n);
    void removeVariable(QString s);
};



#endif // STORAGE

