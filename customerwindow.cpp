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
    setCurrentOrders();
};

void CustomerWindow::initUserInformations(){
    QStringList customerInformation = database.getUserInformation(this->userID,this->userType);
    ui->label_3->setText(customerInformation.at(0));
    ui->label_4->setText(customerInformation.at(1));
    ui->label_6->setText(customerInformation.at(2));
};

void CustomerWindow::setCurrentOrders(){
    QVector<QStringList> allUserOrders = database.getUserOrders(this->userID);

    for (int i = 0; i < allUserOrders.size(); ++i) {
        QString siparisTarihi = "Siparis Tarihi : " + allUserOrders[i][0];
        QString siparisNumarasi = "Siparis Numarasi : "+ allUserOrders[i][1];
        QString kuryeAdi = "Kurye Adi : "+ allUserOrders[i][2];
        QString toplamTutar = "Toplam Siparis Tutari : "+ database.getOrderTotalPrice(allUserOrders[i][1].toInt()) + "TL";

        createOrderLayout( siparisNumarasi, toplamTutar, siparisTarihi, kuryeAdi);
    };
};

void CustomerWindow::createOrderLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi){
    hBoxNewOrder = new QHBoxLayout;
    vBoxOrderDetails = new QVBoxLayout;
    vBoxOrderButtons = new QVBoxLayout;
    hGroup = new QGroupBox("Siparis Ozeti");

    QPushButton* btnSiparisIptal = new QPushButton("Siparis Iptal");
    btnSiparisIptal->setProperty("id",siparisNumarasi);

    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",siparisNumarasi);

    connect(btnSiparisIptal, &QPushButton::clicked, this,[this, btnSiparisIptal]{buttonOrderCancel(btnSiparisIptal);});
    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});

    labelSiparisNumarasi = new QLabel(siparisNumarasi);
    labelToplamTutar = new QLabel(toplamTutar);
    labelSiparisTarihi = new QLabel(siparisTarihi);
    labelKuryeAdi = new QLabel(kuryeAdi);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelToplamTutar);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    vBoxOrderButtons->addWidget(btnSiparisIptal);
    vBoxOrderButtons->addWidget(btnSiparisListesi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_4->addLayout(hBoxNewOrder,1);
};


void CustomerWindow::buttonOrderDetail(QPushButton *button){
    qDebug() << button->property("id");;
};
void CustomerWindow::buttonOrderCancel(QPushButton *button){
    qDebug() << button->property("id");;
};














