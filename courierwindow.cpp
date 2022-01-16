#include "courierwindow.h"
#include "ui_courierwindow.h"

CourierWindow::CourierWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CourierWindow)
{
    ui->setupUi(this);
    databaseConnection();
}

CourierWindow::~CourierWindow()
{
    delete ui;
}


void CourierWindow::databaseConnection(){
     database.connectDefaultDB();

};



void CourierWindow::initUser(int userID){
    this->userID = userID;
};
