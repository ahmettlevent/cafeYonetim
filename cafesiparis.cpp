#include "cafesiparis.h"
#include "ui_cafesiparis.h"


CafeSiparis::CafeSiparis(QWidget *parent): QMainWindow(parent),ui(new Ui::CafeSiparis)
{
    ui->setupUi(this);
    CafeSiparis::databaseConnection();
}

CafeSiparis::~CafeSiparis()
{
    delete ui;
}

void CafeSiparis::databaseConnection(){
    database.connectDB(this->hostName,this->port,this->userName,this->password,this->databaseName);
    if (database.isConnected){
        ui->label_4->setText("Baglanti Basarili");
    }else{
        ui->label_4->setText("Baglanti Basarisiz");
    }
};

void CafeSiparis::on_pushButton_clicked()
{
    QString email,password;
    email = ui->lineEdit->text();
    password = ui->lineEdit_2->text();

    int userCheckResult = database.checkUser(email,password);

    ui->label_4->setText("Bilgiler Kontrol Ediliyor");
    if (userCheckResult > 0) {
        ui->label_4->setText("Bilgiler Dogrulandi"+userCheckResult);
        CafeSiparis::switchToCustomerWindow(userCheckResult);
    };
    if (userCheckResult == -1) {

        ui->label_4->setText("Bilgiler Dogrulandi -1");
    };

    if (userCheckResult == -2) {
        ui->label_4->setText("Bilgiler Dogrulandi -2");
    };
};


void CafeSiparis::switchToCustomerWindow(int userID)
{
    customerWindow = new CustomerWindow();
    customerWindow->setUserID(userID);
    customerWindow->show();

};
