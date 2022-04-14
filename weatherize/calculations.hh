#ifndef CALCULATIONS_HH
#define CALCULATIONS_HH

#include <QDebug>
#include <QSqlQuery>
#include <QDateTime>
#include <vector>

class Calculations
{
public:
    Calculations(QSqlQuery query);

    //Calculates energyform, average temperature,
    //average max and min temperature
    std::vector<double> calcPercentages(QDateTime minDate, QDateTime current, QDateTime maxDate);

    //Recursive function that helps calcPercentages to work correctly
    void helper(QDateTime minDate, QDateTime current);

private:
    QSqlQuery query_;
    double max_ = 0;
    double min_ = 0;
    int count_ = 0;
};

#endif // CALCULATIONS_HH
