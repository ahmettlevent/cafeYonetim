#include "cafesiparis.h"
#include "ui_cafesiparis.h"


CafeSiparis::CafeSiparis(QWidget *parent): QMainWindow(parent),ui(new Ui::CafeSiparis)
{
    ui->setupUi(this);
    CafeSiparis::databaseConnection();

    initComboBox();
}

CafeSiparis::~CafeSiparis()
{
    delete ui;
}

void CafeSiparis::databaseConnection(){
    database.connectDB(this->hostName,this->port,this->userName,this->password,this->databaseName);
    if (database.isConnected){
        ui->label_4->setText("Baglanti Basarili");}
    else{
        ui->label_4->setText("Baglanti Basarisiz");
    }
};

void CafeSiparis::initComboBox(){
    for (int i = 0 ;i<userTypes.size();++i){
      ui->comboBox->addItem(userTypes.at(i));
    };
};

void CafeSiparis::on_pushButton_clicked()
{
    QString email,password;
    int userType;

    email = ui->lineEdit->text();
    password = ui->lineEdit_2->text();
    userType = ui->comboBox->currentIndex();

    int userID = database.checkUser(email,password,userType);

    if (userID > 0) {
        ui->label_5->setText("Kimlik Dogrulandi");
        CafeSiparis::switchToSpecificWindow(userID,userType);
    }else{
        ui->label_5->setText("Bilgilerinizi Kontrol Edin");
    }
};

void CafeSiparis::switchToSpecificWindow(int userID,int userType)
{
    switch(userType) {
      case 0:
        customerWindow = new CustomerWindow();
        customerWindow->initUser(userID);
        customerWindow->show();
        break;
      case 1:
        courierWindow = new CourierWindow();
        courierWindow->initUser(userID);
        courierWindow->show();
        break;
      case 2:
        chefWindow = new ChefWindow();
        chefWindow->initUser(userID);
        chefWindow->show();
        break;
      case 3:
        checkoutWindow = new CheckoutWindow();
        checkoutWindow->initUser(userID);
        checkoutWindow->show();
        break;
    }

};















