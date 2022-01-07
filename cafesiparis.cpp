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

    if (database.isConnected){
        ui->label_3->setText("Veritabani Baglantisi Basarili");
    }else{
        ui->label_3->setText("Veritabani Baglantisi Basarisiz");
    }
};

void CafeSiparis::add_listWidget1(){

    ui->label_3->setText("Item Eklenıyor");
    ui->listWidget->addItems(database.getTableList());

    ui->label_3->setText("Item Eklendi");
};

void CafeSiparis::on_pushButton_clicked()
{
    CafeSiparis::add_listWidget1();
};

