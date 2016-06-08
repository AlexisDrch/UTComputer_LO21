#include "storage.h"

DbManager* DbManager::instance=0;
StockVariable* StockVariable::instance=0;

DbManager::DbManager(const QString &path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/Irvin/src/UT_Computer/calculette.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";
    }

    if (db.tables().empty()) {
        QSqlQuery query;
        query.prepare("CREATE TABLE variable(name varchar(50), value varchar(50))");
        if(query.exec()) {
               qDebug() << "ok1";
           } else {
                qDebug() << "adVariable error:  "
                         << query.lastError();
           }
        query.prepare("CREATE TABLE programme(name varchar(50), value varchar(50))");
        if(query.exec()) {
               qDebug() << "success";
           } else {
                qDebug() << "adVariable error:  "
                         << query.lastError();
           }
    }
        qDebug() << "non nul";

    qDebug() << db.tables();
}

DbManager* DbManager::getInstance() {
    if (!instance)
        instance = new DbManager("calculette.db");
    return instance;
}

bool DbManager::addVariable(const QString& name, const QString& value){
    bool success = false;
    QSqlQuery query;
    query.prepare("INSERT INTO variable (name,value) VALUES (:name,:value)");
    query.bindValue(":name", name);
    query.bindValue(":value", value);
    if(query.exec()) {
           success = true;
           qDebug() << success;
       } else {
            qDebug() << "adVariable error:  "
                     << query.lastError();
       }

       return success;
}


StockVariable* StockVariable::getInstance() {
    if (!instance)
        instance = new StockVariable();
    return instance;
}

void StockVariable::addVariable(const QString s, Nombres* n) {
    QString value;
    Entier* n1 = dynamic_cast<Entier*>(n);
    if (n1 != nullptr) {
        listeVar[s] = n1;
        value.setNum(n1->getValue());
    }

    Reelle* n2 = dynamic_cast<Reelle*>(n);
    if (n2 != nullptr) {
        listeVar[s] = n2;
        value.setNum(n2->getValue());
    }

    Rationnelle* n3 = dynamic_cast<Rationnelle*>(n);
    if (n3 != nullptr) {
        listeVar[s] = n3;
        value.setNum(n3->getValue());
    }

    DbManager* db = DbManager::getInstance();
    db->addVariable(s,value);

    nb++;
}

void StockVariable::removeVariable(QString s) {
    listeVar.erase(listeVar.find(s));
    nb--;
}
