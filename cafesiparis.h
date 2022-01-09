#ifndef CAFESIPARIS_H
#define CAFESIPARIS_H

#include <QMainWindow>
#include <database.h>

#include <customerwindow.h>
#include <chefwindow.h>
#include <courierwindow.h>
#include <checkoutwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class CafeSiparis; }
QT_END_NAMESPACE

class CafeSiparis : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
private:
    string hostName = "localhost";
    int port = 5432;
    string userName = "cafeAdmin";
    string password ="123456";
    string databaseName = "cafeDB";
    QStringList userTypes = { "Musteri", "Kurye", "Sef", "Kasa" };
    int currentUserType = 0; // 0->Musteri 1->Kurye 2->Sef 3->Kasa

public:
    CafeSiparis(QWidget *parent = nullptr);
    ~CafeSiparis();

private:
    void initComboBox();

    void databaseConnection();
    void userAuthenticator();
    void switchToSpecificWindow(int userID,int userType);

private slots:
    void on_pushButton_clicked();

private:
    CustomerWindow *customerWindow;
    ChefWindow *chefWindow;
    CourierWindow *courierWindow;
    CheckoutWindow *checkoutWindow;

    Ui::CafeSiparis *ui;
};
#endif // CAFESIPARIS_H
