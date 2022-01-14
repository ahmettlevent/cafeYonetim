#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <string>
#include <QtSql>
#include <QVector>
using namespace std;

class CafeDatabase
{
private:
    QSqlDatabase database;

public:
    bool isConnected = 0;

    CafeDatabase();
    ~CafeDatabase();

    void connectDB(string hostName,int port,string userName,string password,string databaseName);
    void connectDefaultDB();
    void setDatabase(QSqlDatabase cafeDB);

    int checkUser(QString email,QString password,int userType);

    QStringList getUserInformation(int userID,int userType);
    QVector<QStringList> getUserOrders(int userID);

    QString getOrderTotalPrice(int orderID);

};

#endif // DATABASE_H
