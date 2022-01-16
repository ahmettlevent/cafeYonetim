#include "database.h"


CafeDatabase::CafeDatabase(){}

CafeDatabase::~CafeDatabase()
{
    database.removeDatabase("cafeDB");
}

void CafeDatabase::connectDB(string hostName,int port,string userName,string password,string databaseName){
    QSqlDatabase cafeDB = QSqlDatabase::addDatabase("QPSQL");

    cafeDB.setHostName(QString::fromStdString(hostName));
    cafeDB.setPort(port);
    cafeDB.setUserName(QString::fromStdString(userName));
    cafeDB.setPassword(QString::fromStdString(password));
    cafeDB.setDatabaseName(QString::fromStdString(databaseName));

    CafeDatabase::isConnected = cafeDB.open();
    setDatabase(cafeDB);
};

void CafeDatabase::connectDefaultDB(){
     QSqlDatabase cafeDB = QSqlDatabase::database();
     CafeDatabase::isConnected = cafeDB.open();
     setDatabase(cafeDB);
};
void CafeDatabase::setDatabase(QSqlDatabase cafeDB){
    this->database = cafeDB;
};

// General Auth Functions
int CafeDatabase::checkUser(QString email,QString password,int userType){
    QSqlQuery query(database);

    switch(userType) {
      case 0:
        query.prepare("SELECT id FROM public.customers where email = '"+email+"' and password = '"+password+"';");
        break;
      case 1:
        query.prepare("SELECT id FROM public.couriers where email = '"+email+"' and password = '"+password+"';");
        break;
      case 2:
        query.prepare("SELECT id FROM public.chefs where email = '"+email+"' and password = '"+password+"';");
        break;
      case 3:
        query.prepare("SELECT id FROM public.checkouts where email = '"+email+"' and password = '"+password+"';");
        break;
    }
    query.exec();
    if (query.first())
    {
      return query.value( 0 ).toInt();
    }else{
      return 0;
    };
};
QStringList CafeDatabase::getUserInformation(int userID,int userType){
    QSqlQuery query(database);

    QString dbUserType;

    switch(userType) {
      case 0:
            dbUserType = "customers";
        break;
      case 1:
            dbUserType = "couriers";
        break;
      case 2:
            dbUserType = "chefs";
        break;
      case 3:
            dbUserType = "checkouts";
        break;
    }

    query.prepare("SELECT firstname,lastname,email FROM public."+dbUserType+" where id = '"+QString::number(userID)+"';");
    query.exec();

    if (query.first())
    {
      QStringList userInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
      return userInformation;
    }else{
      QStringList userInformation = {"Ad Bulunamadi","Soyad Bulunamadi","Mail Bulunamadı"};
      return userInformation;
    };

};

// Customer Functions

QVector<QStringList> CafeDatabase::getUserOrders(int userID){
    QSqlQuery query(database);
    QVector<QStringList> allUserOrders;

    query.prepare("SELECT public.order.order_date, public.order.id, public.couriers.firstname FROM public.customers,public.couriers,public.order where ( public.customers.id = "+QString::number(userID)+" and public.customers.id = public.order.customer_id and public.order.order_status != '5'   );");

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allUserOrders.append(userOrderInformation);
    };
    return allUserOrders;
};

QString CafeDatabase::getOrderTotalPrice(int orderID){
    QSqlQuery query(database);

    query.prepare("SELECT sum(public.food.food_price) FROM public.food,public.order,public.item where public.order.id = "+ QString::number(orderID)+ " and public.order.id = public.item.order_id and public.item.food_id = public.food.id;");
    query.exec();

    if( query.first() )
    {
        return query.value( 0 ).toString();
    }
    else{
        QString failText = "Hesaplanamadi";
        return failText;
    };
};



QVector<QStringList> CafeDatabase::getCouriersLiveOrder(int orderID, int couriersID){
    QSqlQuery query(database);
    QVector<QStringList> info_of_couriers_live_order;

    query.prepare("SELECT public.order.id as siparis_id,public.customers.address as siparis_adres, public.checkouts.checkout_name, public.food.food_name, public.chefs.firstname as hazirlayan_sef_adi FROM public.couriers, public.chefs,public.checkouts,public.order,public.item,public.food,public.customers WHERE customers.id = public.order.customer_id and public.order.order_status = 2 and  item.order_id = 4 and food.id = item.food_id and public.order.checkout_id = checkouts.id and public.order.courier_id = 5 and chefs.id = public.order.chef_id;");
    query.exec();

    while( query.next() )
    {
        QStringList couriersOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        info_of_couriers_live_order.append(couriersOrderInformation);
    };
    return info_of_couriers_live_order;
};

int CafeDatabase::setOrderCancel(int orderID,int customerID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET order_status = '5' FROM  public.customers WHERE public.order.customer_id = "+ QString::number(customerID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND (public.order.order_status = '0' or public.order.order_status = '1' or public.order.order_status = '2');");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
};


int CafeDatabase::set_order_2_to_3(int orderID, int couriersID){
    QSqlQuery query(database);
    query.prepare("UPDATE public.order SET order_status = '3' FROM  public.couriers WHERE public.order.courier_id = "+ QString::number(couriersID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = '2';");

    query.exec();
    if (query.first())
    {
      return 1;
    }else{
      return 0;
    };
};
