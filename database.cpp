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


int CafeDatabase::checkUser(QString email,QString password){
    QSqlQuery query(database);

    query.prepare("SELECT id FROM public.user where email = '"+email+"' and password = '"+password+"';");
    query.exec();

    if (query.first())
    {
      return query.value( 0 ).toInt();
    }else{
      return 0;
    };

};








