#include "data.hh"

Data::Data()
{
    DataBase* db = new DataBase;
    query = db->returnQuery();
}

Data::~Data()
{
    delete db;
    delete counter;
    delete temp;
    delete wind;
    delete cloud;
    delete foreTemp;
    delete foreWind;
    delete elecCon;
    delete elecConFore;
    delete tentativePro;
    delete electricityPro;
    delete windFore;
    delete hydroPro;
}

QSqlQuery Data::returnQuery()
{
    return query;
}

Counter *Data::returnCounter()
{
    return counter;
}

void Data::updateAPI(QDateTime pastMin, QDateTime pastMax, QDateTime futureMin, QDateTime futureMax)
{
    counter->setValue(false);
    QString past;
    QString future;
    if (pastMin != pastMax) {
        if (futureMin == futureMax) {
            counter->setMax(7);
        }
        past = "starttime="+pastMin.toString(Qt::ISODate)+"&endtime="+pastMax.toString(Qt::ISODate);

        temp->fetchData(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place="+Place+"&"+past+"&timestep=30&parameters=t2m")
                       , false, {"BsWfs:Time", "BsWfs:ParameterValue"}, {"time", "temp"}, query, counter);

        wind->fetchData(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place="+Place+"&"+past+"&timestep=30&parameters=ws_10min")
                       , false, {"BsWfs:Time", "BsWfs:ParameterValue"}, {"time", "windspeed"}, query, counter);

        cloud->fetchData(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple&place="+Place+"&"+past+"&timestep=30&parameters=n_man")
                       , false, {"BsWfs:Time", "BsWfs:ParameterValue"}, {"time", "cloud"}, query, counter);

        elecCon->fetchData(QUrl("https://api.fingrid.fi/v1/variable/124/events/xml?start_time="+pastMin.toString(Qt::ISODate)+"&end_time=" + pastMax.toString(Qt::ISODate))
                       , true, {"start_time", "value"}, {"time", "electricity_con"}, query, counter);

        electricityPro->fetchData(QUrl("https://api.fingrid.fi/v1/variable/74/events/xml?start_time="+pastMin.toString(Qt::ISODate)+"&end_time=" + pastMax.toString(Qt::ISODate))
                                  , true, {"start_time", "value"}, {"time", "electricity_pro"}, query, counter);

        nuclearPro->fetchData(QUrl("https://api.fingrid.fi/v1/variable/188/events/xml?start_time="+pastMin.toString(Qt::ISODate)+"&end_time=" + pastMax.toString(Qt::ISODate))
                              , true, {"start_time", "value"}, {"time", "nuclear_pro"}, query, counter);

        hydroPro->fetchData(QUrl("https://api.fingrid.fi/v1/variable/191/events/xml?start_time="+pastMin.toString(Qt::ISODate)+"&end_time=" + pastMax.toString(Qt::ISODate))
                            , true, {"start_time", "value"}, {"time", "hydro_pro"}, query, counter);
    }
    if (futureMin != futureMax) {
        if (pastMin == pastMax) {
            counter->setMax(5);
        }
        future = "starttime="+futureMin.toString(Qt::ISODate)+"&endtime="+futureMax.toString(Qt::ISODate);

        foreTemp->fetchData(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::forecast::hirlam::surface::point::simple&&place="+Place+"&"+future+"&timestep=30&parameters=temperature")
                       , false, {"BsWfs:Time", "BsWfs:ParameterValue"}, {"time", "predictTemp"}, query, counter);

        foreWind->fetchData(QUrl("https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::forecast::hirlam::surface::point::simple&&place="+Place+"&"+future+"&timestep=30&parameters=windspeedms")
                       , false, {"BsWfs:Time", "BsWfs:ParameterValue"}, {"time", "predictWindSpeed"}, query, counter);

        elecConFore->fetchData(QUrl("https://api.fingrid.fi/v1/variable/166/events/xml?start_time="+futureMin.toString(Qt::ISODate)+"&end_time=" + futureMax.toString(Qt::ISODate))
                       , true, {"start_time", "value"}, {"time", "electricity_con_fore"}, query, counter);

        tentativePro->fetchData(QUrl("https://api.fingrid.fi/v1/variable/242/events/xml?start_time="+futureMin.toString(Qt::ISODate)+"&end_time=" + futureMax.toString(Qt::ISODate))
                                , true, {"start_time", "value"}, {"time", "tentative_pro"}, query, counter);

        windFore->fetchData(QUrl("https://api.fingrid.fi/v1/variable/245/events/xml?start_time="+futureMin.toString(Qt::ISODate)+"&end_time=" + futureMax.toString(Qt::ISODate))
                            , true, {"start_time", "value"}, {"time", "wind_fore"}, query, counter);
    }
    if (pastMin != pastMax) {
        if (futureMin != futureMax) {
            counter->setMax(12);
        }
    }
}

void Data::deleteStuff()
{
    delete temp;
    delete wind;
    delete cloud;
    delete foreTemp;
    delete foreWind;
    delete elecCon;
    delete elecConFore;
    delete tentativePro;
    delete electricityPro;
    delete windFore;
    delete nuclearPro;
    delete hydroPro;
    temp = new API();
    wind = new API();
    cloud = new API();
    foreTemp = new API();
    foreWind = new API();
    elecCon = new API();
    elecConFore = new API();
    tentativePro = new API();
    electricityPro = new API();
    windFore = new API();
    nuclearPro = new API();
    hydroPro = new API();
}

void Data::setPlace(QString place)
{
    Place = place;
}

DataBase *Data::getDataBase()
{
    return db;
}

