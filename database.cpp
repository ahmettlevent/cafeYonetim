    #include "database.h"

CafeDatabase::CafeDatabase()
{
    CafeDatabase::connectDB();
}

void CafeDatabase::connectDB(){
    QSqlDatabase cafeDB = QSqlDatabase::addDatabase("QPSQL");
    cafeDB.setHostName("localhost");
    cafeDB.setPort(5432);
    cafeDB.setUserName("cafeAdmin");
    cafeDB.setPassword("123456");
    cafeDB.setDatabaseName("cafeDB");

    CafeDatabase::isConnected = cafeDB.open();
};

