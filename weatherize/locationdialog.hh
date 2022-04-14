#ifndef LOCATIONDIALOG_HH
#define LOCATIONDIALOG_HH

#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QVBoxLayout>
#include <algorithm>
#include <vector>
#include "data.hh"



namespace Ui {
class LocationDialog;
}

class LocationDialog : public QWidget
{
    Q_OBJECT

public:
    explicit LocationDialog(QWidget *parent = nullptr);
    ~LocationDialog();

    void on_doneButton_clicked();

    void dataFromMainwindow(Data* data);

signals:
    void dialogClosed();

private slots:

    void on_locationBtn_pressed();

private:
    std::vector<std::string> locations = {"Pirkkala", "Turku", "Helsinki", "Vantaa", "Oulu"};
    Ui::LocationDialog *ui;
    Data* data;
};

#endif // LOCATIONDIALOG_HH
