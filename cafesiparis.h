#ifndef CAFESIPARIS_H
#define CAFESIPARIS_H

#include <QMainWindow>
#include <database.h>
#include <customerwindow.h>

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

public:
    CafeSiparis(QWidget *parent = nullptr);
    ~CafeSiparis();

private:
    void databaseConnection();
    void userAuthenticator();
    void switchToCustomerWindow(int userID);

private slots:
    void on_pushButton_clicked();

private:
    CustomerWindow *customerWindow;
    Ui::CafeSiparis *ui;
};
#endif // CAFESIPARIS_H
