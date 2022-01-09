#include "checkoutwindow.h"
#include "ui_checkoutwindow.h"

CheckoutWindow::CheckoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckoutWindow)
{
    ui->setupUi(this);

    databaseConnection();
}

CheckoutWindow::~CheckoutWindow()
{
    delete ui;
}

void CheckoutWindow::databaseConnection(){
     database.connectDefaultDB();
};


void CheckoutWindow::initUser(int userID){
    this->userID = userID;
};
