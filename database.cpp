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
}

void CafeDatabase::connectDefaultDB(){
     QSqlDatabase cafeDB = QSqlDatabase::database();
     CafeDatabase::isConnected = cafeDB.open();
     setDatabase(cafeDB);
}
void CafeDatabase::setDatabase(QSqlDatabase cafeDB){
    this->database = cafeDB;
}

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
}
QStringList CafeDatabase::getUserInformation(int userID,int userType){
    QSqlQuery query(database);

    QString dbUserType;

    switch(userType) {
      case 0:
            dbUserType = "customers";
            query.prepare("SELECT firstname,lastname,email,address FROM public."+dbUserType+" where id = '"+QString::number(userID)+"';");
        break;
      case 1:
            dbUserType = "couriers";
            query.prepare("SELECT firstname,lastname,email FROM public."+dbUserType+" where id = '"+QString::number(userID)+"';");
        break;
      case 2:
            dbUserType = "chefs";
            query.prepare("SELECT firstname,lastname,email FROM public."+dbUserType+" where id = '"+QString::number(userID)+"';");
        break;
      case 3:
            dbUserType = "checkouts";
            query.prepare("SELECT checkout_name,email,id FROM public."+dbUserType+" where id = '"+QString::number(userID)+"';");
        break;
    }


    query.exec();

    if (query.first())
    {
      QStringList userInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString(),query.value( 3 ).toString()};
      return userInformation;
    }else{
      QStringList userInformation = {"Ad Bulunamadi","Soyad Bulunamadi","Mail Bulunamadı","Adres Bulunamadı"};
      return userInformation;
    };

};

// Customer Functions

QVector<QStringList> CafeDatabase::getCustomerOrders(int userID){
    QSqlQuery query(database);
    QVector<QStringList> allUserOrders;

    query.prepare("SELECT public.order.order_date, public.order.id, public.couriers.firstname FROM public.customers,public.couriers,public.order where ( public.customers.id = "+QString::number(userID)+" and public.couriers.id = public.order.courier_id and public.customers.id = public.order.customer_id and public.order.order_status != 5 and public.order.order_status != 6  );");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allUserOrders.append(userOrderInformation);
    };
    return allUserOrders;
}

QVector<QStringList> CafeDatabase::getCustomerOldOrders(int userID){
    QSqlQuery query(database);
    QVector<QStringList> allUserOrders;

    query.prepare("SELECT public.order.order_date, public.order.id, public.couriers.firstname FROM public.customers,public.couriers,public.order where ( public.customers.id = "+QString::number(userID)+" and public.couriers.id = public.order.courier_id and public.customers.id = public.order.customer_id and public.order.order_status = 5);");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allUserOrders.append(userOrderInformation);
    };
    return allUserOrders;
}

QVector<QStringList> CafeDatabase::getAllFoods(){
    QSqlQuery query(database);
    QVector<QStringList> allUserOrders;

    query.prepare("select id,food_name,food_price from food ORDER BY (food_type,id) desc;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allUserOrders.append(userOrderInformation);
    };
    return allUserOrders;
}

QVector<QStringList> CafeDatabase::getAllFoodsFromBasket(int orderID){
    QSqlQuery query(database);
    QVector<QStringList> allUserOrders;

    query.prepare("select public.item.id,public.food.food_name,public.food.food_price from public.food,public.item where public.item.food_id = public.food.id and public.item.order_id = "+QString::number(orderID)+" ;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allUserOrders.append(userOrderInformation);
    };
    return allUserOrders;
}

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
}

int CafeDatabase::setOrderCancel(int orderID,int customerID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET order_status = '5' FROM  public.customers WHERE public.order.customer_id = "+ QString::number(customerID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND (public.order.order_status = '0' or public.order.order_status = '1' or public.order.order_status = '2');");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}

QString CafeDatabase::createNewOrder(int userID){
    QSqlQuery query(database);
    query.prepare("INSERT INTO public.order ( checkout_id, courier_id, customer_id, order_date, chef_id, payment_status,order_status) VALUES ( ( select checkouts.id from checkouts order by random() limit 1 ), ( select couriers.id from couriers order by random() limit 1 ), "+ QString::number(userID)+ ", ( select CURRENT_DATE ), ( select chefs.id from chefs order by random() limit 1 ), 0,6) returning id;");

    query.exec();
    if (query.first())
    {
      return query.value( 0 ).toString();
    }else{
      return 0;
   };
}

int CafeDatabase::addToBasket(int foodID, int orderID){
    QSqlQuery query(database);
    query.prepare("INSERT INTO public.item( order_id, food_id) VALUES ("+ QString::number(orderID)+ ", "+ QString::number(foodID)+ ");");

    query.exec();
    if (query.first())
    {
      return 1;
    }else{
      return 0;
    };
}

int CafeDatabase::removeFromBasket(int itemID, int orderID){
    QSqlQuery query(database);
    query.prepare("DELETE FROM public.item WHERE item.id = "+ QString::number(itemID)+ " and item.order_id = "+ QString::number(orderID)+ " ;");

    query.exec();
    if (query.first())
    {
      return 1;
    }else{
      return 0;
    };
}

int CafeDatabase::setOrderConfirm(int orderID){
    QSqlQuery query(database);
    query.prepare("UPDATE public.order SET order_status = '0' FROM  public.chefs WHERE public.order.id = "+ QString::number(orderID)+ "  AND  public.order.order_status = '6';");

    query.exec();
    if (query.first())
    {
      return 1;
    }else{
      return 0;
    };
}

// Chef Functions

QVector<QStringList> CafeDatabase::getChefWaitingOrders(int chefID){
    QSqlQuery query(database);
    QVector<QStringList> allActiveOrders;

    query.prepare("SELECT DISTINCT ON (public.order.id) public.order.id, couriers.firstname, checkouts.checkout_name  FROM public.chefs, public.order,public.checkouts,public.couriers where "+ QString::number(chefID)+ " = public.order.chef_id and public.order.order_status = 0  and public.order.payment_status = '1'  and public.order.checkout_id = checkouts.id and public.order.courier_id = couriers.id;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allActiveOrders.append(userOrderInformation);
    };
    return allActiveOrders;
}

QVector<QStringList> CafeDatabase::getChefCurrentOrders(int chefID){
    QSqlQuery query(database);
    QVector<QStringList> allActiveOrders;

    query.prepare("SELECT DISTINCT ON (public.order.id) public.order.id, couriers.firstname, checkouts.checkout_name  FROM public.chefs, public.order,public.checkouts,public.couriers where "+ QString::number(chefID)+ " = public.order.chef_id and public.order.order_status = 1  and public.order.payment_status = '1'  and public.order.checkout_id = checkouts.id and public.order.courier_id = couriers.id;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allActiveOrders.append(userOrderInformation);
    };
    return allActiveOrders;
}

QVector<QStringList> CafeDatabase::getChefOldOrders(int chefID){
    QSqlQuery query(database);
    QVector<QStringList> allActiveOrders;

    query.prepare("SELECT DISTINCT ON (public.order.id) public.order.id, couriers.firstname, checkouts.checkout_name  FROM public.chefs, public.order,public.checkouts,public.couriers where "+ QString::number(chefID)+ " = public.order.chef_id and public.order.order_status != 1 and public.order.order_status != 0 and public.order.payment_status = '1'  and public.order.checkout_id = checkouts.id and public.order.courier_id = couriers.id;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString()};
        allActiveOrders.append(userOrderInformation);
    };
    return allActiveOrders;
}


int CafeDatabase::setChefAcceptOrder(int orderID,int chefID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET order_status = '1' FROM  public.chefs WHERE public.order.chef_id = "+ QString::number(chefID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = '0';");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}

int CafeDatabase::setChefDeclineOrder(int orderID,int chefID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET order_status = '5' FROM  public.chefs WHERE public.order.chef_id = "+ QString::number(chefID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = '0';");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}


int CafeDatabase::setChefReadyOrder(int orderID,int chefID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET order_status = '2' FROM  public.chefs WHERE public.order.chef_id = "+ QString::number(chefID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = '1';");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}


// Checkout Functions

QVector<QStringList> CafeDatabase::getCheckoutAcceptedPayments(int checkoutID){
    QSqlQuery query(database);
    QVector<QStringList> allActiveOrders;

    query.prepare("SELECT DISTINCT ON (public.order.id) public.order.id, public.order.order_date, public.customers.firstname, public.customers.email FROM public.order,public.checkouts,public.customers where public.order.checkout_id = "+QString::number(checkoutID)+" and public.order.customer_id = public.customers.id and public.order.payment_status = 1 ;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString(),query.value( 3 ).toString(),query.value( 4 ).toString()};
        allActiveOrders.append(userOrderInformation);
    };
    return allActiveOrders;
}


QVector<QStringList> CafeDatabase::getCheckoutWaitingPayment(int checkoutID){
    QSqlQuery query(database);
    QVector<QStringList> allActiveOrders;

    query.prepare("SELECT DISTINCT ON (public.order.id) public.order.id, public.order.order_date, public.customers.firstname, public.customers.email FROM public.order,public.checkouts,public.customers where public.order.checkout_id = "+QString::number(checkoutID)+" and public.order.customer_id = public.customers.id and public.order.payment_status = '0' and public.order.order_status = 0;");
    query.exec();

    while( query.next() )
    {
        QStringList userOrderInformation = {query.value( 0 ).toString(),query.value( 1 ).toString(),query.value( 2 ).toString(),query.value( 3 ).toString(),query.value( 4 ).toString()};
        allActiveOrders.append(userOrderInformation);
    };
    return allActiveOrders;
}

int CafeDatabase::setOrderPaymentSuccessful(int orderID,int checkoutID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET payment_status = 1 FROM  checkouts WHERE public.order.checkout_id = "+ QString::number(checkoutID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = 0;");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}

int CafeDatabase::setOrderPaymentUnsuccessful(int orderID,int checkoutID){
    QSqlQuery query(database);

    query.prepare("UPDATE public.order SET payment_status = -1 FROM  public.order, WHERE public.order.checkout_id = "+ QString::number(checkoutID)+ "  AND public.order.id = "+ QString::number(orderID)+ "  AND public.order.order_status = 0;");
    query.exec();

    while( query.next() )
    {
        return query.value( 0 ).toInt();
    };
    return 0;
}


