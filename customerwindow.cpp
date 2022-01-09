#include "customerwindow.h"
#include "ui_customerwindow.h"

CustomerWindow::CustomerWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::CustomerWindow)
{
    ui->setupUi(this);

    databaseConnection();
}

CustomerWindow::~CustomerWindow()
{
    delete ui;
}



void CustomerWindow::databaseConnection(){
     database.connectDefaultDB();

};


void CustomerWindow::initUser(int userID){
    this->userID = userID;
    initUserInformations();
};

void CustomerWindow::initUserInformations(){
    QStringList customerInformation = database.getUserInformation(this->userID,this->userType);
    ui->label_3->setText(customerInformation.at(0));
    ui->label_4->setText(customerInformation.at(1));
    ui->label_6->setText(customerInformation.at(2));
};
