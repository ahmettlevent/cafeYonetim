#include "checkoutwindow.h"
#include "ui_checkoutwindow.h"

CheckoutWindow::CheckoutWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckoutWindow)
{
    ui->setupUi(this);

    databaseConnection();
}

CheckoutWindow::~CheckoutWindow()
{
    delete ui;
}

void CheckoutWindow::databaseConnection(){
     database.connectDefaultDB();
};


void CheckoutWindow::initUser(int userID){
    this->userID = userID;
    initUserInformations();
    setCurrentOrders();
};


void CheckoutWindow::initUserInformations(){
    QStringList customerInformation = database.getUserInformation(this->userID,this->userType);
    ui->label_3->setText(customerInformation.at(0));
    ui->label_4->setText(customerInformation.at(1));
    ui->label_6->setText(customerInformation.at(2));

};
void CheckoutWindow::setCurrentOrders(){

    QVector<QStringList> allWaitingPayments = database.getCheckoutWaitingPayment(this->userID);
    clearLayout(ui->verticalLayout_4);
    for (int i=0 ; i < allWaitingPayments.size() ; i++){;
        createWaitingPaymentsLayout( allWaitingPayments[i][0], allWaitingPayments[i][1], allWaitingPayments[i][2],allWaitingPayments[i][3],database.getOrderTotalPrice(allWaitingPayments[i][0].toInt()));
    };

    clearLayout(ui->verticalLayout_5);

    QVector<QStringList> allAcceptedPayments = database.getCheckoutAcceptedPayments(this->userID);
    for (int i=0 ; i < allAcceptedPayments.size() ; i++){;
        createAcceptedPaymentsLayout( allAcceptedPayments[i][0], allAcceptedPayments[i][1], allAcceptedPayments[i][2],allAcceptedPayments[i][3],database.getOrderTotalPrice(allAcceptedPayments[i][0].toInt()));
    };

};


void CheckoutWindow::createWaitingPaymentsLayout(QString orderID,QString orderDate,QString customerName,QString customerEmail,QString totalPrice){
    QHBoxLayout* hBoxNewOrder = new QHBoxLayout;
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;
    QVBoxLayout* vBoxOrderButtons = new QVBoxLayout;

    QPushButton* btnSiparisKabul = new QPushButton("Odeme Onayla");
    btnSiparisKabul->setProperty("id",orderID);

    QPushButton* btnSiparisReddet= new QPushButton("Odeme Reddet");
    btnSiparisReddet->setProperty("id",orderID);

    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",orderID);


    connect(btnSiparisKabul, &QPushButton::clicked, this,[this, btnSiparisKabul]{buttonPaymentAccept(btnSiparisKabul);});
    connect(btnSiparisReddet, &QPushButton::clicked, this,[this, btnSiparisReddet]{buttonPaymentDecline(btnSiparisReddet);});
    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});


    QString siparisNumarasi_str = "Siparis ID : " + orderID;
    QString siparisTarihi_str = "Siparis Tarihi : " + orderDate;
    QString siparisMusteriAdi_str = "Musteri Adi : "+ customerName;
    QString siparisMusteriMail_str = "Musteri E-Mail : "+ customerEmail;
    QString siparisToplamFiyat_str = "Toplam Tutar : "+totalPrice ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelMusteriAdi = new QLabel(siparisMusteriAdi_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisTarihi_str);
    QLabel* labelMusteriMail = new QLabel(siparisMusteriMail_str);
    QLabel* labelToplamFiyat = new QLabel(siparisToplamFiyat_str);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelMusteriAdi);
    vBoxOrderDetails->addWidget(labelMusteriMail);
    vBoxOrderDetails->addWidget(labelToplamFiyat);

    vBoxOrderButtons->addWidget(btnSiparisKabul);
    vBoxOrderButtons->addWidget(btnSiparisListesi);
    vBoxOrderButtons->addWidget(btnSiparisReddet);

    QString splitter = " " ;
    QLabel* labelsplitter = new QLabel(splitter);
    vBoxOrderDetails->addWidget(labelsplitter);

    hBoxNewOrder->addLayout(vBoxOrderDetails,0);
    hBoxNewOrder->addLayout(vBoxOrderButtons,1);

    ui->verticalLayout_4->addLayout(hBoxNewOrder);
};

void CheckoutWindow::createAcceptedPaymentsLayout(QString orderID,QString orderDate,QString customerName,QString customerEmail,QString totalPrice){
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;

    QPushButton* btnSiparisKabul = new QPushButton("Odeme Onayla");
    btnSiparisKabul->setProperty("id",orderID);

    QPushButton* btnSiparisListesi = new QPushButton("Siparis Listesi");
    btnSiparisListesi->setProperty("id",orderID);

    connect(btnSiparisListesi, &QPushButton::clicked, this,[this, btnSiparisListesi]{buttonOrderDetail(btnSiparisListesi);});

    QString siparisNumarasi_str = "Siparis ID : " + orderID;
    QString siparisTarihi_str = "Siparis Tarihi : " + orderDate;
    QString siparisMusteriAdi_str = "Musteri Adi : "+ customerName;
    QString siparisMusteriMail_str = "Musteri E-Mail : "+ customerEmail;
    QString siparisToplamFiyat_str = "Toplam Tutar : "+totalPrice + "₺" ;
    QString splitter = " " ;

    QLabel* labelSiparisNumarasi = new QLabel(siparisNumarasi_str);
    QLabel* labelMusteriAdi = new QLabel(siparisMusteriAdi_str);
    QLabel* labelSiparisTarihi = new QLabel(siparisTarihi_str);
    QLabel* labelMusteriMail = new QLabel(siparisMusteriMail_str);
    QLabel* labelToplamFiyat = new QLabel(siparisToplamFiyat_str);
    QLabel* labelsplitter = new QLabel(splitter);

    vBoxOrderDetails->addWidget(labelSiparisNumarasi);
    vBoxOrderDetails->addWidget(labelSiparisTarihi);
    vBoxOrderDetails->addWidget(labelMusteriAdi);
    vBoxOrderDetails->addWidget(labelMusteriMail);
    vBoxOrderDetails->addWidget(labelToplamFiyat);
    vBoxOrderDetails->addWidget(btnSiparisListesi);
    vBoxOrderDetails->addWidget(labelsplitter);

    ui->verticalLayout_5->addLayout(vBoxOrderDetails);
};


void CheckoutWindow::buttonPaymentAccept(QPushButton *button){
    database.setOrderPaymentSuccessful(button->property("id").toInt(),this->userID);
    setCurrentOrders();
};


void CheckoutWindow::buttonOrderDetail(QPushButton *button){
    OrderList *orderlist = new OrderList();
    orderlist->initForm(button->property("id").toInt());
    orderlist->show();
};


void CheckoutWindow::buttonPaymentDecline(QPushButton *button){
    database.setOrderPaymentUnsuccessful(button->property("id").toInt(),this->userID);
    setCurrentOrders();

};


void CheckoutWindow::clearLayout( QLayout* layout )
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
