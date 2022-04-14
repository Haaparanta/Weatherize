#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <charttool.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDateTime>
#include <string>
#include <data.hh>
#include <counter.h>
#include <calculations.hh>
#include <locationdialog.hh>
#include <piechart.hh>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

const QString tempName = "Temperature";
const QString windName = "Windspeed";
const QString electrConName = "Electricity consumption";
const QString cloudName = "Cloudiness";
const QString tentProName = "Tentative production";
const QString nucProName = "Nuclear power production";
const QString hydroProName = "Hydropower production";
const QString windForeName = "Windspeed forecast";
const QString elecProName = "Electricity production";


struct Schedule
{
  QDateTime startTime;
  QDateTime endTime;
};

const QDateTime null;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Called in main.cpp and updates API for the first time and creates
    //tables with database
    void loadCharts();

private slots:

    //setProgress is responsible of progress bar working correctly
    //progress bar tells when charts can be showed
    void setProgress(int value);

    //takes screenshot of the window and saves it as .png format
    void on_screenshot_clicked();

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_Temp_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_Wind_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_Electricity_toggled(bool checked);

    void on_minDateTime_dateTimeChanged(const QDateTime &dateTime);

    void on_maxDateTime_dateTimeChanged(const QDateTime &dateTime);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_Cloud_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_TentativePro_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_NuclearPro_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_Hydro_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_WindFore_toggled(bool checked);

    /*radiobutton in mainwindow. when checked SQL query will get
    wanted data from database and make process them into data that charttool
    functions can work on.*/
    void on_ElectricityPro_toggled(bool checked);

    //Updates charts using updateDateTime and getWeeklyData functions.
    void on_getData_clicked();

    //opens dialog/widget where location can be changed
    void on_SelectLocation_clicked();

    void on_request_clicked();

private:
    //Updates and sets date time
    void updateDateTime();

    //Gets weekly data and updates API using updateAPI in data.cpp
    void getWeeklyData();

    QDateTime current;
    QDateTime tomorrow;
    QDateTime weekBack;
    QDateTime minDateTime;
    QDateTime maxDateTime;

    Schedule* timeSchedule = new Schedule;

    Ui::MainWindow *ui;

    ChartTool* tempChart = nullptr;
    ChartTool* elecChart;
    ChartTool* windChart = nullptr;
    ChartTool* cloudChart;
    ChartTool* tempForeChart;
    ChartTool* tentativeProChart;
    ChartTool* windForeChart;
    ChartTool* hydroChart;
    ChartTool* nuclearChart;
    ChartTool* electricityProChart;

    PieChart* pie = new PieChart();

    //QtChart needs data in this format so it can be used in charts
    std::vector<std::pair<qreal,QDateTime>> weatherV;
    std::vector<std::pair<qreal,QDateTime>> powerV;
    std::vector<std::pair<qreal,QDateTime>> windV;
    std::vector<std::pair<qreal,QDateTime>> cloudV;
    std::vector<std::pair<qreal,QDateTime>> tempForeV;
    std::vector<std::pair<qreal,QDateTime>> tentativeProV;
    std::vector<std::pair<qreal,QDateTime>> nuclearProV;
    std::vector<std::pair<qreal,QDateTime>> hydroV;
    std::vector<std::pair<qreal,QDateTime>> windForeV;
    std::vector<std::pair<qreal,QDateTime>> electricityProV;

    Data* data;

    QSqlQuery query;

    std::shared_ptr<Calculations> calculator_;

    LocationDialog *locationDialog = new LocationDialog;

    int Progress;
    Counter* counter;
};
#endif // MAINWINDOW_H
