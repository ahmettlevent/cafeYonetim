#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

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
class CustomerWindow;
}

class CustomerWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID,orderID;
    int userType = 0;

public:
    explicit CustomerWindow(QWidget *parent = nullptr);
    ~CustomerWindow();
    void initUser(int userID);
    void initBasket();

private:
    void databaseConnection();
    void initUserInformations();

    void setCurrentOrders();
    void createOrderLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi);
    void createOldOrdersLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi);
    void createMenuLayout(QString yemekID,QString yemekAdi,QString yemekFiyati);
    void createBasketLayout(QString yemekID,QString yemekAdi,QString yemekFiyati);
    void clearLayout(QLayout* layout);

public slots:
    void buttonOrderDetail(QPushButton *button);
    void buttonOrderCancel(QPushButton *button);
    void buttonAddToBasket(QPushButton *button);
    void buttonRemoveFromBasket(QPushButton *button);
private slots:
    void on_pushButton_clicked();

private:
    Ui::CustomerWindow *ui;
};

#endif // CUSTOMERWINDOW_H
