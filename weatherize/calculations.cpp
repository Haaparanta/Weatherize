#include "calculations.hh"

Calculations::Calculations(QSqlQuery query)
{
    query_ = query;
}

std::vector<double> Calculations::calcPercentages(QDateTime minDate, QDateTime current,
                                                  QDateTime maxDate)
{

    QString min = minDate.toString(Qt::ISODate);
    QString cur = current.toString(Qt::ISODate);
    QString max = maxDate.toString(Qt::ISODate);

    query_.exec("SELECT AVG(nuclear_pro), AVG(hydro_pro), AVG(electricity_pro) FROM "
                 "electricity WHERE time > '" + min + "' AND time < '" + cur + "';");
    query_.first();
    double totalValue = query_.value(2).toDouble();
    double nuclearValue = query_.value(0).toDouble() / totalValue;
    double hydroValue = query_.value(1).toDouble() / totalValue;

    query_.exec("SELECT AVG(wind_fore), AVG(tentative_pro) FROM "
                "electricity WHERE time > '" + cur + "' AND time < '" + max + "';");
    query_.first();
    double totalValueFuture = query_.value(1).toDouble();
    double windValue = query_.value(0).toDouble() / totalValueFuture;

    query_.exec("SELECT AVG(temp) FROM weather WHERE time > '" + min + "' AND time < '" + cur + "';");
    query_.first();
    double avgTemp = query_.value(0).toDouble();


    helper(minDate, current);
    double avgTempMax = max_ / count_;
    double avgTempMin = min_ / count_;
    return {nuclearValue, hydroValue, windValue, avgTemp, avgTempMax, avgTempMin};
}

void Calculations::helper(QDateTime minDate, QDateTime current)
{
    QDateTime dayTime = minDate.addDays(1);
    QString min = minDate.toString(Qt::ISODate);
    QString cur = current.toString(Qt::ISODate);
    QString day = dayTime.toString(Qt::ISODate);
    ++count_;
    if (dayTime >= current) {
        query_.exec("SELECT MAX(temp) FROM weather WHERE time > '" + min + "' AND time < '" + cur + "';");
        query_.first();
        double max = query_.value(0).toDouble();
        max_ += max;

        query_.exec("SELECT MIN(temp) FROM weather WHERE time > '" + min + "' AND time < '" + cur + "';");
        query_.first();
        double min = query_.value(0).toDouble();
        min_ += min;
    } else {
        query_.exec("SELECT MAX(temp) FROM weather WHERE time > '" + min + "' AND time < '" + day + "';");
        query_.first();
        double max = query_.value(0).toDouble();
        max_ += max;

        query_.exec("SELECT MIN(temp) FROM weather WHERE time > '" + min + "' AND time < '" + day + "';");
        query_.first();
        double min = query_.value(0).toDouble();
        min_ += min;

        helper(dayTime, current);
    }

}

