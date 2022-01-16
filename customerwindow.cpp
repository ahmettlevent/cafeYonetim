#include "customerwindow.h"
#include "ui_customerwindow.h"

CustomerWindow::CustomerWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::CustomerWindow)
{
    ui->setupUi(this);
    databaseConnection();
};

CustomerWindow::~CustomerWindow()
{
    delete ui;
};

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

    for (int i=0 ; i < allUserOrders.size() ; i++){
        createOrderLayout( allUserOrders[i][1], database.getOrderTotalPrice(allUserOrders[i][1].toInt()), allUserOrders[i][0], allUserOrders[i][2]);
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

    QString siparisTarihi_str = "Siparis Tarihi : " + siparisTarihi;
    QString siparisNumarasi_str = "Siparis Numarasi : "+ siparisNumarasi;
    QString kuryeAdi_str = "Kurye Adi : "+kuryeAdi ;
    QString toplamTutar_str = "Toplam Siparis Tutari : "+ toplamTutar + "TL";

    labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    labelToplamTutar = new QLabel(toplamTutar_str);
    labelSiparisTarihi = new QLabel(siparisTarihi_str);
    labelKuryeAdi = new QLabel(kuryeAdi_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelToplamTutar);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    vBoxOrderButtons->addWidget(btnSiparisIptal);
    vBoxOrderButtons->addWidget(btnSiparisListesi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->widget->setLayout(hBoxNewOrder);
};


void CustomerWindow::buttonOrderDetail(QPushButton *button){
    qDebug() << button->property("id");
    QVector<QStringList> info_of_couriers_live_order = database.getCouriersLiveOrder(4,5);

    for (int i = 0; i < info_of_couriers_live_order.size(); ++i){
        qDebug() << info_of_couriers_live_order[0][0];
    };
};
void CustomerWindow::buttonOrderCancel(QPushButton *button){
    database.setOrderCancel(button->property("id").toInt(),this->userID);

    delete button->parentWidget();

    setCurrentOrders();

};



