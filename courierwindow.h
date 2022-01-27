#ifndef COURIERWINDOW_H
#define COURIERWINDOW_H

#include <QMainWindow>
#include <database.h>

#include <QPushButton>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QVector>

namespace Ui {
class CourierWindow;
}

class CourierWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;
    int userType = 1;

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
