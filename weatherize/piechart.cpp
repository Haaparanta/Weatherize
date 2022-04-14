#include "piechart.hh"

PieChart::PieChart()
{

}

PieChart::~PieChart()
{
    delete series;
    delete chart;
}

void PieChart::setPie(double nuclearValue, double hydroValue, double windValue)
{
    double rest = 1 - nuclearValue - hydroValue - windValue;

    chart->removeAllSeries();
    series = new QPieSeries;

    series->append("Nuclear", nuclearValue);
    series->append("Hydro", hydroValue);
    series->append("Wind", windValue);
    series->append("Others", rest);

    chart->addSeries(series);
}

QChart *PieChart::returnChart()
{
    return chart;
}
