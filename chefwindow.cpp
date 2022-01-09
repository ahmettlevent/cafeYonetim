#include "chefwindow.h"
#include "ui_chefwindow.h"

ChefWindow::ChefWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChefWindow)
{
    ui->setupUi(this);
    databaseConnection();
}

ChefWindow::~ChefWindow()
{
    delete ui;
}

void ChefWindow::databaseConnection(){
     database.connectDefaultDB();
};


void ChefWindow::initUser(int userID){
    this->userID = userID;
};
