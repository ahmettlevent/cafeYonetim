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

    QVector<QStringList> getCouriersLiveOrder(int orderID, int couriersID);
    QString getOrderTotalPrice(int orderID);
    int setOrderCancel(int orderID,int customerID);
    int set_order_2_to_3(int orderID,int couriersID);


};

#endif // DATABASE_H
