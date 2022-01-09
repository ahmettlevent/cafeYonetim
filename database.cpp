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
