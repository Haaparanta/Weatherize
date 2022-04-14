#ifndef DATA_HH
#define DATA_HH

#include <database.hh>
#include <api.hh>
#include <counter.h>

#include <QSqlQuery>

#include <QDateTime>

#include <QTimer>

class Data : public QObject
{

    Q_OBJECT

public:
    Data();

    ~Data();

    QSqlQuery returnQuery();

    Counter* returnCounter();

    //Fetches data from Fingrid and FMI using API functions
    void updateAPI(QDateTime pastMin, QDateTime pastMax, QDateTime futureMin, QDateTime futureMax);

    //Deletes all APIs and then give birth to new ones with same names :)
    //This is to make QNetworkAccessManager work correctly
    void deleteStuff();

    void setPlace(QString place);
    DataBase *getDataBase();

private:

    QSqlQuery query;

    DataBase* db;

    Counter* counter = new Counter();

    QString Place = "Pirkkala";

    API* temp = new API();
    API* wind = new API();
    API* cloud = new API();
    API* foreTemp = new API();
    API* foreWind = new API();
    API* elecCon = new API();
    API* elecConFore = new API();
    API* tentativePro = new API();
    API* electricityPro = new API();
    API* windFore = new API();
    API* nuclearPro = new API();
    API* hydroPro = new API();

};

#endif // DATA_HH
