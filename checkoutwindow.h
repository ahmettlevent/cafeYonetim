#ifndef CHECKOUTWINDOW_H
#define CHECKOUTWINDOW_H

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
class CheckoutWindow;
}

class CheckoutWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;
    int userType = 3;

public:
    explicit CheckoutWindow(QWidget *parent = nullptr);
    ~CheckoutWindow();
    void initUser(int userID);
private:
    void databaseConnection();
    void initUserInformations();

    void setCurrentOrders();
    void clearLayout(QLayout* layout);
    void createWaitingPaymentsLayout(QString orderID,QString orderDate,QString customerName,QString customerEmail,QString totalPrice);
    void createAcceptedPaymentsLayout(QString orderID,QString orderDate,QString customerName,QString customerEmail,QString totalPrice);

public slots:
    void buttonPaymentAccept(QPushButton *button);
    void buttonPaymentDecline(QPushButton *button);
    void buttonOrderDetail(QPushButton *button);


private:
    Ui::CheckoutWindow *ui;
};

#endif // CHECKOUTWINDOW_H
