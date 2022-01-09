#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include <QMainWindow>
#include <database.h>

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
    void databaseConnection();

    void initUserInformations();

private:
    Ui::CustomerWindow *ui;
};

#endif // CUSTOMERWINDOW_H
