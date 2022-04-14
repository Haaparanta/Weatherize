#ifndef PIECHART_HH
#define PIECHART_HH

#include <QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

class PieChart
{
public:
    PieChart();
    ~PieChart();
    void setPie(double nuclearValue, double hydroValue, double windValue);
    QChart* returnChart();
private:
    QPieSeries *series = new QPieSeries();
    QChart *chart = new QChart();
};

#endif // PIECHART_HH
