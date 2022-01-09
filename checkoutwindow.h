#ifndef CHECKOUTWINDOW_H
#define CHECKOUTWINDOW_H

#include <QMainWindow>
#include <database.h>

namespace Ui {
class CheckoutWindow;
}

class CheckoutWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;

public:
    explicit CheckoutWindow(QWidget *parent = nullptr);
    ~CheckoutWindow();
    void initUser(int userID);
private:
    void databaseConnection();

private:
    Ui::CheckoutWindow *ui;
};

#endif // CHECKOUTWINDOW_H
