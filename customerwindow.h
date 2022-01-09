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

public:
    explicit CustomerWindow(QWidget *parent = nullptr);
    ~CustomerWindow();

    void setUserID(int userID);
private:
    void databaseConnection();

private:
    Ui::CustomerWindow *ui;
};

#endif // CUSTOMERWINDOW_H
