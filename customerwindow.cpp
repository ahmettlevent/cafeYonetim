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
    initBasket();
    setCurrentOrders();

    initUserInformations();
};

void CustomerWindow::initBasket(){
    this->orderID = database.createNewOrder(this->userID).toInt();
};

void CustomerWindow::initUserInformations(){
    QStringList customerInformation = database.getUserInformation(this->userID,this->userType);
    ui->label_3->setText(customerInformation.at(0));
    ui->label_4->setText(customerInformation.at(1));
    ui->label_6->setText(customerInformation.at(2));
    ui->label_13->setText(customerInformation.at(3));

    ui->label_11->setText(QString::number(this->orderID));
};

void CustomerWindow::setCurrentOrders(){

    QVector<QStringList> allUserOrders = database.getCustomerOrders(this->userID);
    clearLayout(ui->verticalLayout_4);
    for (int i=0 ; i < allUserOrders.size() ; i++){
        createOrderLayout( allUserOrders[i][1], database.getOrderTotalPrice(allUserOrders[i][1].toInt()), allUserOrders[i][0], allUserOrders[i][2]);
    };


    QVector<QStringList> allFoods = database.getAllFoods();
    clearLayout(ui->verticalLayout_6);
    for (int i=0 ; i < allFoods.size() ; i++){
        createMenuLayout( allFoods[i][0], allFoods[i][1], allFoods[i][2]);
    }

    QVector<QStringList> allUserOldOrders = database.getCustomerOldOrders(this->userID);
    clearLayout(ui->verticalLayout_13);
    for (int i=0 ; i < allUserOldOrders.size() ; i++){
        createOldOrdersLayout( allUserOldOrders[i][1], database.getOrderTotalPrice(allUserOldOrders[i][1].toInt()), allUserOldOrders[i][0], allUserOldOrders[i][2]);
    };

    QVector<QStringList> allBasketFoods = database.getAllFoodsFromBasket(this->orderID);
    clearLayout(ui->verticalLayout_11);
    for (int i=0 ; i < allBasketFoods.size() ; i++){
        createBasketLayout(allBasketFoods[i][0], allBasketFoods[i][1], allBasketFoods[i][2]);
    }

    QString toplamSepetTutari = "Toplam Sepet Tutari : "+ database.getOrderTotalPrice(this->orderID) + "TL";
    ui->label_12->setText(toplamSepetTutari);
};

void CustomerWindow::createOrderLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

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
    QString seperator_str = "" ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelToplamTutar = new QLabel(toplamTutar_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisTarihi_str);
    QLabel* labelKuryeAdi = new QLabel(kuryeAdi_str);
    QLabel* seperator = new QLabel(seperator_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelToplamTutar);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);
    vBoxOrderDetails->addWidget(seperator);

    vBoxOrderButtons->addWidget(btnSiparisIptal);
    vBoxOrderButtons->addWidget(btnSiparisListesi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_4->addLayout(hBoxNewOrder);
};

void CustomerWindow::createOldOrdersLayout(QString siparisNumarasi,QString toplamTutar,QString siparisTarihi,QString kuryeAdi){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

    QString siparisTarihi_str = "Siparis Tarihi : " + siparisTarihi;
    QString siparisNumarasi_str = "Siparis Numarasi : "+ siparisNumarasi;
    QString kuryeAdi_str = "Kurye Adi : "+kuryeAdi ;
    QString toplamTutar_str = "Toplam Siparis Tutari : "+ toplamTutar + "TL";
    QString seperator_str = "" ;


    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelToplamTutar = new QLabel(toplamTutar_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisTarihi_str);
    QLabel* labelKuryeAdi = new QLabel(kuryeAdi_str);
    QLabel* seperator = new QLabel(seperator_str);

    vBoxOrderDetails->addWidget(seperator);
    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelToplamTutar);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelKuryeAdi);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_13->addLayout(hBoxNewOrder);
};


void CustomerWindow::createMenuLayout(QString yemekID,QString yemekAdi,QString yemekFiyati){
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;

    QPushButton* btnSepeteEkle = new QPushButton("Sepete Ekle");
    btnSepeteEkle->setProperty("foodID",yemekID);

    connect(btnSepeteEkle, &QPushButton::clicked, this,[this, btnSepeteEkle]{buttonAddToBasket(btnSepeteEkle);});

    QString yemekAdi_str = "Urun Adi : " + yemekAdi;
    QString yemekFiyati_str = "Urun Fiyati : "+ yemekFiyati;
    QString seperator_str = "" ;

    QLabel* labelYemekAdi = new QLabel(yemekAdi_str);
    QLabel* labelYemekFiyati = new QLabel(yemekFiyati_str);
    QLabel* seperator = new QLabel(seperator_str);


    vBoxOrderDetails->addWidget(labelYemekAdi);
    vBoxOrderDetails->addWidget(labelYemekFiyati);
    vBoxOrderDetails->addWidget(btnSepeteEkle);
    vBoxOrderDetails->addWidget(seperator);

    ui->verticalLayout_6->addLayout(vBoxOrderDetails);
};

void CustomerWindow::createBasketLayout(QString yemekID, QString yemekAdi,QString yemekFiyati){
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;


    QPushButton* btnSepettenCikar = new QPushButton("Cikar");
    btnSepettenCikar->setProperty("itemID",yemekID);

    connect(btnSepettenCikar, &QPushButton::clicked, this,[this, btnSepettenCikar]{buttonRemoveFromBasket(btnSepettenCikar);});

    QString yemekAdi_str = "Urun : " + yemekAdi;
    QString yemekFiyati_str = "Fiyati : "+ yemekFiyati +"₺";
    QString seperator_str = "" ;

    QLabel* labelYemekAdi = new QLabel(yemekAdi_str);
    QLabel* labelYemekFiyati = new QLabel(yemekFiyati_str);
    QLabel* seperator = new QLabel(seperator_str);

    vBoxOrderDetails->addWidget(labelYemekAdi);
    vBoxOrderDetails->addWidget(labelYemekFiyati);
    vBoxOrderDetails->addWidget(btnSepettenCikar);
    vBoxOrderDetails->addWidget(seperator);

    ui->verticalLayout_11->addLayout(vBoxOrderDetails);
};


void CustomerWindow::buttonOrderDetail(QPushButton *button){

    OrderList *orderlist = new OrderList();
    orderlist->initForm(button->property("id").toInt());
    orderlist->show();
};

void CustomerWindow::buttonOrderCancel(QPushButton *button){
    database.setOrderCancel(button->property("id").toInt(),this->userID);
    setCurrentOrders();

};

void CustomerWindow::buttonAddToBasket(QPushButton *button){
    database.addToBasket(button->property("foodID").toInt(),this->orderID);
    setCurrentOrders();
    initUserInformations();
};

void CustomerWindow::buttonRemoveFromBasket(QPushButton *button){
    database.removeFromBasket(button->property("itemID").toInt(),this->orderID);
    setCurrentOrders();
};


void CustomerWindow::clearLayout( QLayout* layout )
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

void CustomerWindow::on_pushButton_clicked()
{
    database.setOrderConfirm(this->orderID);
    initBasket();
    setCurrentOrders();
}

