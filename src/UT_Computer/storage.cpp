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


StockVariable::StockVariable() : nb(0) {
    DbManager* db = DbManager::getInstance();
    QSqlQuery query;
    if(query.exec("SELECT * FROM variable")){
        while(query.next()){
            QString q = query.value(1).toString();
            Litterale* l = fabriqLitterale(q);
            Nombres* n = dynamic_cast<Nombres*>(l); // aucun risque car les variables stockées sont forcément des nombres
            listeVar[query.value(0).toString()] = n;
        }
    }
    int i;
    i++;
}

Litterale* StockVariable::fabriqLitterale(const QString& v) {
    bool ok=false;

    if(v.contains("$")) {
        QString part1 = v.mid(0,v.indexOf("$"));
        Litterale* l1 = fabriqLitterale(part1);
        LitNumerique* ln1 = dynamic_cast<LitNumerique*>(l1); // aucun risque car le complexe stocké est valide

        QString part2 = v.mid(v.indexOf("$")+1,v.size());
        Litterale* l2 = fabriqLitterale(part2);
        LitNumerique* ln2 = dynamic_cast<LitNumerique*>(l2); // aucun risque car le complexe stocké est valide

        return new Complexe(ln1,ln2);
    }

    if(v.at(0).isNumber()){
       unsigned int val = v.toLongLong(&ok); if(ok){return (new Entier(val));}
       float val2 = v.toFloat(&ok) ; if(ok){
           Reelle r(val2);
           Litterale* res = r.simplification();
           return res;
       }
       Litterale* l = isRationnelle(v); if ( l != nullptr) return l; else delete l;
    }
    return nullptr;
}

Litterale* StockVariable::isRationnelle(const QString& v){

    bool rationnel = true, premiere_partie = true, seconde_partie = true;
    int i=0, temp, num, den;
    while (premiere_partie && i<v.size()-1) {
        if (!v.at(i).isNumber())
            premiere_partie = false;
        i++;
    }
    if (i==1 || v.at(i-1) != '/')
        rationnel = false;
    temp = i;
    num = v.left(i-1).toInt();
    while (rationnel && seconde_partie && i<v.size()) {
        if (!v.at(i).isNumber())
            seconde_partie = false;
        i++;
    }
    if (i+1 == v.size())
        rationnel = false;
    den = v.right(v.size()-(temp)).toInt();

    if (rationnel) {
        Rationnelle* r = new Rationnelle(num,den,num + "/" + den);
        Litterale *l = r->simplification();
        delete r;
        return l;
    }
    else return (nullptr);

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
        value = n1->toString();
    }

    Reelle* n2 = dynamic_cast<Reelle*>(n);
    if (n2 != nullptr) {
        listeVar[s] = n2;
        value = n2->toString();
    }

    Rationnelle* n3 = dynamic_cast<Rationnelle*>(n);
    if (n3 != nullptr) {
        listeVar[s] = n3;
        value = n3->toString();
    }

    Complexe* n4 = dynamic_cast<Complexe*>(n);
    if (n4 != nullptr) {
        listeVar[s] = n4;
        value = n4->toString();
    }

    DbManager* db = DbManager::getInstance();
    db->addVariable(s,value);

    nb++;
}

void StockVariable::removeVariable(QString s) {
    listeVar.erase(listeVar.find(s));
    nb--;
}
