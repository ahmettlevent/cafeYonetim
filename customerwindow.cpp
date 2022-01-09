#include "customerwindow.h"
#include "ui_customerwindow.h"

CustomerWindow::CustomerWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::CustomerWindow)
{
    ui->setupUi(this);
    CustomerWindow::databaseConnection();
}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}


void CustomerWindow::databaseConnection(){
     database.connectDefaultDB();

};


void CustomerWindow::setUserID(int userID){
    this->userID = userID;
    if (database.isConnected){
        ui->label->setText(QString::number(this->userID));
    }else{
        ui->label->setText("Baglanti Basarisiz");
    }
};
