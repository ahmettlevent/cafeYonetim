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
    initUserInformations();
    setCurrentOrders();
};

void ChefWindow::initUserInformations(){
    QStringList customerInformation = database.getUserInformation(this->userID,this->userType);
    ui->label_3->setText(customerInformation.at(0));
    ui->label_4->setText(customerInformation.at(1));
    ui->label_6->setText(customerInformation.at(2));
};


void ChefWindow::setCurrentOrders(){
    QVector<QStringList> allChefOrders = database.getChefWaitingOrders(this->userID);
    clearLayout(ui->verticalLayout_4);
    for (int i=0 ; i < allChefOrders.size() ; i++){;
        createWaitingOrdersLayout( allChefOrders[i][0], allChefOrders[i][1], allChefOrders[i][2]);
    };


    QVector<QStringList> allChefCurrentOrders = database.getChefCurrentOrders(this->userID);
    clearLayout(ui->verticalLayout_5);
    for (int i=0 ; i < allChefCurrentOrders.size() ; i++){;
        createCurrentOrdersLayout( allChefCurrentOrders[i][0], allChefCurrentOrders[i][1], allChefCurrentOrders[i][2]);
    };


    QVector<QStringList> allChefOldOrders = database.getChefOldOrders(this->userID);
    clearLayout(ui->verticalLayout_6);
    for (int i=0 ; i < allChefOldOrders.size() ; i++){;
        createOldOrdersLayout( allChefOldOrders[i][0], allChefOldOrders[i][1], allChefOldOrders[i][2]);
    };

};

void ChefWindow::createWaitingOrdersLayout(QString siparisID,QString courierName,QString checkoutName){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

    QPushButton* btnSiparisKabul = new QPushButton("Siparisi Kabul Et");
    btnSiparisKabul->setProperty("id",siparisID);
    QPushButton* btnSiparisReddet= new QPushButton("Siparis Reddet");
    btnSiparisReddet->setProperty("id",siparisID);
    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",siparisID);
    connect(btnSiparisKabul, &QPushButton::clicked, this,[this, btnSiparisKabul]{buttonOrderAccept(btnSiparisKabul);});
    connect(btnSiparisReddet, &QPushButton::clicked, this,[this, btnSiparisReddet]{buttonOrderDecline(btnSiparisReddet);});
    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});


    QString siparisNumarasi_str = "Siparis ID : " + siparisID;
    QString siparisKuryeAdi_str = "Kurye Adi : "+ courierName;
    QString siparisKasaAdi_str = "Kasa Adi : "+checkoutName ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisKuryeAdi_str);
    QLabel* labelKuryeAdi = new QLabel(siparisKasaAdi_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    vBoxOrderButtons->addWidget(btnSiparisKabul);
    vBoxOrderButtons->addWidget(btnSiparisListesi);
    vBoxOrderButtons->addWidget(btnSiparisReddet);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_4->addLayout(hBoxNewOrder);
};

void ChefWindow::createCurrentOrdersLayout(QString siparisID,QString courierName,QString checkoutName){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

    QPushButton* btnSiparisHazir = new QPushButton("Siparis Hazir");
    btnSiparisHazir->setProperty("id",siparisID);
    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",siparisID);

    connect(btnSiparisHazir, &QPushButton::clicked, this,[this, btnSiparisHazir]{buttonOrderReady(btnSiparisHazir);});
    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});


    QString siparisNumarasi_str = "Siparis ID : " + siparisID;
    QString siparisKuryeAdi_str = "Kurye Adi : "+ courierName;
    QString siparisKasaAdi_str = "Kasa Adi : "+checkoutName ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisKuryeAdi_str);
    QLabel* labelKuryeAdi = new QLabel(siparisKasaAdi_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    vBoxOrderButtons->addWidget(btnSiparisHazir);
    vBoxOrderButtons->addWidget(btnSiparisListesi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_5->addLayout(hBoxNewOrder);
};

void ChefWindow::createOldOrdersLayout(QString siparisID,QString courierName,QString checkoutName){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",siparisID);

    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});


    QString siparisNumarasi_str = "Siparis ID : " + siparisID;
    QString siparisKuryeAdi_str = "Kurye Adi : "+ courierName;
    QString siparisKasaAdi_str = "Kasa Adi : "+checkoutName ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisKuryeAdi_str);
    QLabel* labelKuryeAdi = new QLabel(siparisKasaAdi_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    vBoxOrderButtons->addWidget(btnSiparisListesi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_6->addLayout(hBoxNewOrder);
};



void ChefWindow::buttonOrderAccept(QPushButton *button){
    database.setChefAcceptOrder(button->property("id").toInt(),this->userID);
    setCurrentOrders();
};


void ChefWindow::buttonOrderDetail(QPushButton *button){
    OrderList *orderlist = new OrderList();
    orderlist->initForm(button->property("id").toInt());
    orderlist->show();
};


void ChefWindow::buttonOrderDecline(QPushButton *button){
    database.setChefDeclineOrder(button->property("id").toInt(),this->userID);
    setCurrentOrders();
};

void ChefWindow::buttonOrderReady(QPushButton *button){
    database.setChefReadyOrder(button->property("id").toInt(),this->userID);
    setCurrentOrders();
};


void ChefWindow::clearLayout( QLayout* layout )
{
    QLayoutItem* child;
    while ( layout->count() != 0 ) {
        child = layout->takeAt ( 0 );
        if ( child->layout() != 0 ) {
            clearLayout ( child->layout() );
        } else if ( child->widget() != 0 ) {
            delete child->widget();
        }

        delete child;
    }
}
