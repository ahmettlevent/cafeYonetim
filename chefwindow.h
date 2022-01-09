#ifndef CHEFWINDOW_H
#define CHEFWINDOW_H

#include <QMainWindow>
#include <database.h>

namespace Ui {
class ChefWindow;
}

class ChefWindow : public QMainWindow
{
    Q_OBJECT
    CafeDatabase database;
    int userID;

public:
    explicit ChefWindow(QWidget *parent = nullptr);
    ~ChefWindow();
    void initUser(int userID);
private:
    void databaseConnection();

private:
    Ui::ChefWindow *ui;
};

#endif // CHEFWINDOW_H
