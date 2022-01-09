#ifndef COURIERWINDOW_H
#define COURIERWINDOW_H

#include <QMainWindow>
#include <database.h>

namespace Ui {
class CourierWindow;
}

class CourierWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;

public:
    explicit CourierWindow(QWidget *parent = nullptr);
    ~CourierWindow();
    void initUser(int userID);
private:
    void databaseConnection();

private:
    Ui::CourierWindow *ui;
};

#endif // COURIERWINDOW_H
