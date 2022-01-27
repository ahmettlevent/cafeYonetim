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

    // Customer Query's
    QVector<QStringList> getCustomerOrders(int userID);
    QString getOrderTotalPrice(int orderID);
    QVector<QStringList> getAllFoods();
    QVector<QStringList> getAllFoodsFromBasket(int orderID);

    QVector<QStringList> getCustomerOldOrders(int userID);
    QString createNewOrder(int userID);
    int setOrderCancel(int orderID,int customerID);
    int addToBasket(int foodID, int orderID);
    int removeFromBasket(int foodID, int orderID);
    int setOrderConfirm(int orderID);

    // Chef Query's
    QVector<QStringList> getChefWaitingOrders(int chefID);
    QVector<QStringList> getChefCurrentOrders(int chefID);
    QVector<QStringList> getChefOldOrders(int chefID);

    int setChefReadyOrder(int orderID,int chefID);
    int setChefAcceptOrder(int orderID,int chefID);
    int setChefDeclineOrder(int orderID,int chefID);

   // Checkouts Query's
    QVector<QStringList> getCheckoutAcceptedPayments(int checkoutID);
    QVector<QStringList> getCheckoutWaitingPayment(int checkoutID);

    int setOrderPaymentSuccessful(int orderID,int checkoutID);
    int setOrderPaymentUnsuccessful(int orderID,int checkoutID);


};

#endif // DATABASE_H
