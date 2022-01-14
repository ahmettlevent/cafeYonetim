#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>
#include <database.h>

#include <QPushButton>
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
    int userID;
    int userType = 0;

public:
    explicit CustomerWindow(QWidget *parent = nullptr);
    ~CustomerWindow();
    void initUser(int userID);

private:
    QLabel* labelSiparisNumarasi;
    QLabel* labelToplamTutar;
    QLabel* labelSiparisTarihi;
    QLabel* labelKuryeAdi;
    QHBoxLayout* hBoxNewOrder;
    QVBoxLayout* vBoxOrderDetails;
    QVBoxLayout* vBoxOrderButtons;

    QGroupBox* hGroup;

private:
    void databaseConnection();
    void initUserInformations();

    void setCurrentOrders();
    void createOrderLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi);

public slots:
    void buttonOrderDetail(QPushButton *button);
    void buttonOrderCancel(QPushButton *button);

private:
    Ui::CustomerWindow *ui;
};

#endif // CUSTOMERWINDOW_H
