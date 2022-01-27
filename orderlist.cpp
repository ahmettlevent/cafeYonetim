#include "orderlist.h"
#include "ui_orderlist.h"

OrderList::OrderList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrderList)
{
    ui->setupUi(this);
    databaseConnection();

}

OrderList::~OrderList()
{
    delete ui;
}


void OrderList::databaseConnection(){
     database.connectDefaultDB();
};

void OrderList::initForm(int orderID){
    this->orderID = orderID;
    initOrders();

};

void OrderList::initOrders(){
    QVector<QStringList> allOrderFoods = database.getAllFoodsFromBasket(this->orderID);
    clearLayout(ui->verticalLayout_3);
    for (int i=0 ; i < allOrderFoods.size() ; i++){
        createOrderListLayout( allOrderFoods[i][1], allOrderFoods[i][2]);
    }

};


void OrderList::createOrderListLayout(QString yemekAdi,QString yemekFiyati){
    QVBoxLayout* vBoxOrderDetails = new QVBoxLayout;

    QString yemekAdi_str = "Urun : " + yemekAdi;
    QString yemekFiyati_str = "Fiyati : "+ yemekFiyati +"₺";
    QString seperator_str = "" ;

    QLabel* labelYemekAdi = new QLabel(yemekAdi_str);
    QLabel* labelYemekFiyati = new QLabel(yemekFiyati_str);
    QLabel* seperator = new QLabel(seperator_str);

    vBoxOrderDetails->addWidget(labelYemekAdi);
    vBoxOrderDetails->addWidget(labelYemekFiyati);
    vBoxOrderDetails->addWidget(seperator);

    ui->verticalLayout_3->addLayout(vBoxOrderDetails);
};


void OrderList::clearLayout( QLayout* layout )
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
