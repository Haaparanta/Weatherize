#include "charttool.h"

ChartTool::ChartTool()
{
    chart_ = new QChart;

    series_ = new QLineSeries();
    series2_ = new QLineSeries();

    axisX_ = new QDateTimeAxis;
    axisX_->setTickCount(10);
    axisX_->setFormat("dd:MM hh:mm");
    axisX_->setTitleText("Date");
    axisX_->setLabelsAngle(45);
    chart_->addAxis(axisX_, Qt::AlignBottom);
    series_->attachAxis(axisX_);
    series2_->attachAxis(axisX_);

    axisX_->setMin(QDateTime::currentDateTime());
    axisX_->setMax(QDateTime::currentDateTime());


    axisY_ = new QValueAxis;
    axisY2_ = new QValueAxis;

    chart_->addAxis(axisY_, Qt::AlignLeft);
    series_->attachAxis(axisY_);

    axisY_->setMin(0);
    axisY_->setMax(0);
}

void ChartTool::addData(std::vector<std::pair<qreal, QDateTime>> v, QString datatype)
{
    series_ = new QLineSeries;
    series_->setName(datatype);
    for(auto &a: v)
    {
        series_->append(a.second.toMSecsSinceEpoch(), a.first);
        series_->setName(datatype);

        adjustYaxis(a.first, axisY_);
        adjustXaxis(a.second);

    }
    chart_->addSeries(series_);
}

void ChartTool::addSecondData(std::vector<std::pair<qreal, QDateTime> > v, QString datatype)
{
    series2_ = new QLineSeries;
    series2_->setName(datatype);
    for(auto &a: v)
    {
        series2_->append(a.second.toMSecsSinceEpoch(), a.first);
        adjustYaxis(a.first, axisY2_);
    }

    chart_->addSeries(series2_);


    chart_->addAxis(axisY2_, Qt::AlignRight);

    series2_->attachAxis(axisX_);

    series2_->attachAxis(axisY2_);
}

void ChartTool::setChartType(QString title, QString datatype)
{
    chart_->setTitle(title);
    axisY_->setTitleText(datatype);
}

void ChartTool::setSecondType(QString datatype)
{
    axisY2_->setTitleText(datatype);
}

void ChartTool::removeData(QString datatype)
{
    for(auto &a: chart_->series())
    {
        if(a->name() == datatype)
        {
            //for(auto &b: a->attachedAxes()) chart_->removeAxis(b);
            chart_->removeSeries(a);
        }

    }
}

void ChartTool::setMinMax(QDateTime min, QDateTime max)
{
    axisX_->setMin(min);
    axisX_->setMax(max);
}

QChart *ChartTool::getChart()
{
    return chart_;
}

void ChartTool::adjustXaxis(QDateTime time)
{
    if(time < axisX_->min()) axisX_->setMin(time);
    if(time > axisX_->max()) axisX_->setMax(time);
}

void ChartTool::adjustYaxis(qreal x, QValueAxis *axis)
{
    if(x < axis->min()) axis->setMin((x + x/5));
    if(x > axis->max()) axis->setMax(x + x/5);
}
