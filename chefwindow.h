#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <orderlist.h>

#include <QPushButton>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVector>

namespace Ui {
class ChefWindow;
}

class ChefWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;
    int userType = 2;

public:
    explicit ChefWindow(QWidget *parent = nullptr);
    ~ChefWindow();
    void initUser(int userID);
private:
    void databaseConnection();
    void initUserInformations();

    void setCurrentOrders();
    void createWaitingOrdersLayout(QString siparisID,QString courierName,QString checkoutName);
    void createCurrentOrdersLayout(QString siparisID,QString courierName,QString checkoutName);
    void createOldOrdersLayout(QString siparisID,QString courierName,QString checkoutName);
    void clearLayout(QLayout* layout);

public slots:
    void buttonOrderAccept(QPushButton *button);
    void buttonOrderDecline(QPushButton *button);
    void buttonOrderDetail(QPushButton *button);
    void buttonOrderReady(QPushButton *button);


private:
    Ui::ChefWindow *ui;
};

#endif // CHEFWINDOW_H
