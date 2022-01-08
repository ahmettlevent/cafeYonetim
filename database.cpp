#include "database.h"

CafeDatabase::CafeDatabase()
{
    CafeDatabase::connectDB();
}

CafeDatabase::~CafeDatabase()
{
    database.removeDatabase("cafeDB");
}

void CafeDatabase::connectDB(){
    QSqlDatabase cafeDB = QSqlDatabase::addDatabase("QPSQL");
    cafeDB.setHostName("localhost");
    cafeDB.setPort(5432);
    cafeDB.setUserName("cafeAdmin");
    cafeDB.setPassword("123456");
    cafeDB.setDatabaseName("cafeDB");

    CafeDatabase::isConnected = cafeDB.open();
    setDatabase(cafeDB);
};

