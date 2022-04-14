#include "database.hh"

DataBase::DataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("MyDatabase"); // Saves file named MyDatabase
    db.open();
    query = QSqlQuery(db);
    makeDb();
}

QSqlQuery DataBase::returnQuery()
{
    return query;
}

void DataBase::makeDb()
{
    query.exec("create table weather " // creates sql table
               "(time date primary key,"
               "temp INT,"
               "windspeed INT,"
               "cloud INT,"
               "predictTemp INT,"
               "predictWindSpeed INT)"
               );
    query.exec("create table electricity " // creates sql table
               "(time date primary key,"
               "electricity_con INT,"
               "electricity_con_fore INT,"
               "tentative_pro INT,"
               "electricity_pro INT,"
               "wind_fore INT,"
               "nuclear_pro INT,"
               "hydro_pro INT)"
               );

    qDebug() << "tables:" << db.tables();
}
