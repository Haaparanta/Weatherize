#ifndef DATABASE_HH
#define DATABASE_HH

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>


class DataBase
{
public:
    DataBase();
    void makeDb();
    QSqlQuery returnQuery();
private:
    QSqlDatabase db;
    QSqlQuery query;

};

#endif // DATABASE_HH
