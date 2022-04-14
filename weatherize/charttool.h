#ifndef CHARTTOOL_H
#define CHARTTOOL_H

#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <vector>
#include <QDebug>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>

using namespace QtCharts;

class ChartTool
{
public:
    //creates all of the private values
    ChartTool();

    //takes std::vector<std::pair<qreal, QDateTime>> and adds
    //the data into chart_.
    void addData(std::vector<std::pair<qreal, QDateTime>> v, QString datatype);

    //Same as addData but for multiple charts in same graph.
    void addSecondData(std::vector<std::pair<qreal,QDateTime>> v, QString datatype);
    void setChartType(QString title, QString datatype);
    void setSecondType(QString datatype);
    void removeData(QString datatype);
    void setMinMax(QDateTime min, QDateTime max);
    QChart *getChart();

private:
    void adjustXaxis(QDateTime time);
    void adjustYaxis(qreal x, QValueAxis *axis);

    QLineSeries *series_;
    QLineSeries *series2_;

    QChart *chart_;

    QDateTimeAxis *axisX_;
    QValueAxis *axisY_;

    QValueAxis *axisY2_;

    std::vector<QValueAxis*> yAxes;

};

#endif // CHARTTOOL_H
