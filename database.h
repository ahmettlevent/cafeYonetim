#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <string>
#include <QtSql>

class CafeDatabase
{
private:
    QSqlDatabase database;

public:
    bool isConnected = 0;

    CafeDatabase();
    ~CafeDatabase();
    void connectDB();
    void setDatabase(QSqlDatabase cafeDB){this->database = cafeDB;};
    QStringList getTableList(){return this->database.tables();};

};

#endif // DATABASE_H
