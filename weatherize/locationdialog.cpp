#include "locationdialog.hh"
#include "ui_locationdialog.h"

LocationDialog::LocationDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    connect(ui->doneButton,&QPushButton::clicked,this,&LocationDialog::on_doneButton_clicked);
    QWidget *content = new QWidget();
    content->setLayout(new QVBoxLayout);

    std::sort(locations.begin(),locations.end());

    for(auto &a: locations)
    {
        QPushButton *newBtn = new QPushButton(QString::fromStdString(a));
        connect(newBtn, SIGNAL(clicked()), this, SLOT(on_locationBtn_pressed()));
        content->layout()->addWidget(newBtn);
    }
    ui->scrollArea->setWidget(content);
}

LocationDialog::~LocationDialog()
{
    delete ui;
}


void LocationDialog::on_doneButton_clicked()
{
    qDebug() << "done";
    emit dialogClosed();
    LocationDialog::close();
}

void LocationDialog::dataFromMainwindow(Data *mainwindowData)
{
    data = mainwindowData;
}

void LocationDialog::on_locationBtn_pressed()
{
    QPushButton *senderBtn = qobject_cast<QPushButton*>(QObject::sender());
    QString name = senderBtn->text();
    senderBtn->setDisabled(true);
    for(auto &a: ui->scrollArea->widget()->children())
    {
        QPushButton *btn = qobject_cast<QPushButton*>(a);
        if(btn != senderBtn && btn != NULL) btn->setDisabled(false);
    }
    qDebug() << "change location to" << name;
    data->setPlace(name);
}
