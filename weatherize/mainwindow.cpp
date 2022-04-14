#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Temp->setAutoExclusive(false);
    ui->Wind->setAutoExclusive(false);
    ui->Electricity->setAutoExclusive(false);
    ui->Cloud->setAutoExclusive(false);
    ui->TentativePro->setAutoExclusive(false);
    ui->NuclearPro->setAutoExclusive(false);
    ui->Hydro->setAutoExclusive(false);
    ui->WindFore->setAutoExclusive(false);
    ui->ElectricityPro->setAutoExclusive(false);

    data = new Data();
    counter = data->returnCounter();
    connect(counter, &Counter::valueChanged, this, &MainWindow::setProgress);
    ui->progressBar->setMinimum(0);

    ui->chartView->setRubberBand(QChartView::HorizontalRubberBand);
    ui->chartView2->setRubberBand(QChartView::HorizontalRubberBand);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
    delete timeSchedule;
    delete pie;
}

void MainWindow::loadCharts()
{
    updateDateTime();
    ui->label->setText("");

    ui->minDateTime->setDateTime(QDateTime::currentDateTime());//weekBack);
    ui->maxDateTime->setDateTime(tomorrow);

    data->updateAPI(weekBack, current, current, tomorrow);
    query = data->returnQuery();
    calculator_ = std::make_shared<Calculations>(query);
}

void MainWindow::setProgress(int value)
{
    if (value) {
        Progress += 1;
    } else {
        Progress = 0;
    }
    ui->progressBar->setMaximum(counter->returnMax());
    ui->progressBar->setValue(Progress);
    if (Progress == counter->returnMax()) {
        data->deleteStuff();
        getWeeklyData();
        ui->Temp->setChecked(false);
        ui->Temp->setChecked(true);

        ui->Wind->setChecked(false);
        ui->Wind->setChecked(true);
    }

}

void MainWindow::updateDateTime()
{
    current = QDateTime::currentDateTimeUtc();
    tomorrow = current.addDays(1);
    weekBack = current.addDays(-3);

    //ui->minDateTime->setMinimumDateTime(weekBack);
    ui->minDateTime->setMaximumDateTime(tomorrow);
    //ui->maxDateTime->setMinimumDateTime(weekBack);
    ui->maxDateTime->setMaximumDateTime(tomorrow);
}

void MainWindow::on_screenshot_clicked()
{
    QPixmap p = ui->chartView->grab();
    p.save(current.toString(Qt::ISODate) + "1.png", "PNG");
    p = ui->chartView2->grab();
    p.save(current.toString(Qt::ISODate) + "2.png", "PNG");
}

void MainWindow::on_Temp_toggled(bool checked)
{
    if (!checked) {
        weatherV.clear();
        tempChart->removeData(tempName);
    } else {
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, temp, predictTemp FROM weather WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString temperature = query.value(1).toString();
            QString FutureTemp = query.value(2).toString();
            if(temperature != "") weatherV.push_back({temperature.toDouble(), time});
            else if (FutureTemp != "") weatherV.push_back({FutureTemp.toDouble(), time});

        }
        if(tempChart == nullptr) tempChart = new ChartTool();
        tempChart->setChartType("Temperature chart", "Temperature (C)");
        tempChart->setSecondType("Power consumption/production (MWh/h)");

        tempChart->addData(weatherV, tempName);

        ui->chartView->setRenderHint(QPainter::Antialiasing);

        ui->chartView->setChart(tempChart->getChart());

        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_Wind_toggled(bool checked)
{
    if (!checked) {
        windV.clear();
        windChart->removeData(windName);
    } else {
        qDebug() << "wind toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, windspeed, predictWindSpeed FROM weather WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString wind = query.value(1).toString();
            QString FutureWind = query.value(2).toString();
            if(wind != "") windV.push_back({wind.toDouble(), time});
            else if (FutureWind != "") windV.push_back({FutureWind.toDouble(), time});
        }
        if(windChart == nullptr) windChart = new ChartTool;
        windChart->setChartType("Wind chart", "Wind speed (m/s)");

        windChart->addData(windV, windName);

        ui->chartView2->setRenderHint(QPainter::Antialiasing);

        ui->chartView2->setChart(windChart->getChart());

        windChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_Electricity_toggled(bool checked)
{
    if(!checked) {
        powerV.clear();
        tempChart->removeData(electrConName);
    } else {
        ui->chartView2->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, electricity_con, electricity_con_fore FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        qDebug() << query.isActive();
        powerV.clear();
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString electricity_con = query.value(1).toString();
            QString electricity_con_fore = query.value(2).toString();

            if(electricity_con != "") powerV.push_back({electricity_con.toDouble(), time});
            if(electricity_con_fore != "") powerV.push_back({electricity_con_fore.toDouble(), time});
        }

        /*
        elecChart = new ChartTool();
        elecChart ->setChartType("Power consumption chart", "Power consumption (MWh/h)");
        elecChart ->addData(powerV, electrConName);
        */

        tempChart->addSecondData(powerV, electrConName);

        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_Cloud_toggled(bool checked)
{
    if (!checked) {
        cloudV.clear();
        windChart->removeData(cloudName);
    } else {
        qDebug() << "cloud toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, cloud FROM weather WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString cloud = query.value(1).toString();
            if(cloud != "") cloudV.push_back({cloud.toDouble(), time});
        }
        windChart->addSecondData(cloudV, cloudName);
        windChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_TentativePro_toggled(bool checked)
{
    if (!checked) {
        tentativeProV.clear();
        tempChart->removeData(tentProName);
    } else {
        qDebug() << "tentative_pro toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, tentative_pro FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString tentativePro = query.value(1).toString();
            if(tentativePro != "") tentativeProV.push_back({tentativePro.toDouble(), time});
        }
        tempChart->addSecondData(tentativeProV, tentProName);
        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_NuclearPro_toggled(bool checked)
{
    if (!checked) {
        nuclearProV.clear();
        tempChart->removeData(nucProName);
    } else {
        qDebug() << "nuclear_pro toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, nuclear_pro FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString nuclearPro = query.value(1).toString();
            if(nuclearPro != "") nuclearProV.push_back({nuclearPro.toDouble(), time});
        }
        tempChart->addSecondData(nuclearProV,nucProName);
        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_Hydro_toggled(bool checked)
{
    if (!checked) {
        hydroV.clear();
        tempChart->removeData(hydroProName);
    } else {
        qDebug() << "hydro toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, hydro_pro FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString hydro = query.value(1).toString();
            if(hydro != "") hydroV.push_back({hydro.toDouble(), time});
        }
        tempChart->addSecondData(hydroV, hydroProName);
        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_WindFore_toggled(bool checked)
{
    if (!checked) {
        windForeV.clear();
        tempChart->removeData(windForeName);
    } else {
        qDebug() << "wind_fore toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, wind_fore FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString windFore = query.value(1).toString();
            if(windFore != "") windForeV.push_back({windFore.toDouble(), time});
        }
        tempChart->addSecondData(windForeV, windForeName);
        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_ElectricityPro_toggled(bool checked)
{
    if (!checked) {
        electricityProV.clear();
        tempChart->removeData(elecProName);
    } else {
        qDebug() << "electricity_pro toggled";
        ui->chartView->show();
        QString min = minDateTime.toString(Qt::ISODate);
        QString max = maxDateTime.toString(Qt::ISODate);
        query.exec("SELECT time, electricity_pro FROM electricity WHERE time > '" + min + "' AND time < '" + max + "';");
        while(query.next()) {
            QDateTime time = query.value(0).toDateTime();
            QString electricityPro = query.value(1).toString();
            if(electricityPro != "") electricityProV.push_back({electricityPro.toDouble(), time});
        }
        tempChart->addSecondData(electricityProV,elecProName);
        tempChart->setMinMax(minDateTime, maxDateTime);
    }
}

void MainWindow::on_minDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    minDateTime = dateTime;
}

void MainWindow::on_maxDateTime_dateTimeChanged(const QDateTime &dateTime)
{
    maxDateTime = dateTime;
}


void MainWindow::on_getData_clicked()
{
    for(auto &a: ui->groupBox->children())
    {
        if(a->objectName() != "gridLayout")
        {
            QRadioButton *btn = qobject_cast<QRadioButton*>(a);
            btn->setChecked(false);
        }

    }
    tempChart = nullptr;
    windChart = nullptr;
    ui->Temp->setChecked(true);
    ui->Wind->setChecked(true);
    updateDateTime();
    timeSchedule->startTime = minDateTime;
    timeSchedule->endTime = maxDateTime;
    getWeeklyData();
}

void MainWindow::getWeeklyData()
{
    if (timeSchedule->startTime == null && timeSchedule->endTime == null) return;

    if (timeSchedule->endTime > current) {
        if (timeSchedule->startTime.toUTC() >= current) {
            data->updateAPI(current, current, timeSchedule->startTime.toUTC(), timeSchedule->endTime.toUTC());
            timeSchedule->startTime = null;
            timeSchedule->endTime = null;
        } else {
            data->updateAPI(current, current, current, timeSchedule->endTime.toUTC());
            timeSchedule->endTime = current;
        }
    } else {
        QDateTime week = timeSchedule->endTime.addDays(-7);
        if (timeSchedule->startTime >= week) {
            data->updateAPI(timeSchedule->startTime.toUTC(), timeSchedule->endTime.toUTC(), current.toUTC(), current.toUTC());
            timeSchedule->startTime = null;
            timeSchedule->endTime = null;
        } else {
            data->updateAPI(week.toUTC(), timeSchedule->endTime.toUTC(), current.toUTC(), current.toUTC());
            timeSchedule->endTime = week;
        }
    }
}


void MainWindow::on_SelectLocation_clicked()
{
    locationDialog->dataFromMainwindow(data);
    locationDialog->show();
    connect(locationDialog, SIGNAL(dialogClosed()), this, SLOT(on_getData_clicked()));
}

void MainWindow::on_request_clicked()
{
    std::vector<double> list = calculator_->calcPercentages(minDateTime, current, maxDateTime);
    pie->setPie(list.at(0), list.at(1), list.at(2));
    ui->chartView3->setChart(pie->returnChart());

    ui->lcdNumber1->display(list.at(3));
    ui->lcdNumber2->display(list.at(4));
    ui->lcdNumber3->display(list.at(5));
}
