#include "flightdata.h"
#include "ui_flightdata.h"

#include <QDebug>

FlightData::FlightData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightData)
{
    ui->setupUi(this);
    initialize();
}

FlightData::~FlightData()
{
    delete ui;
}


bool FlightData::initialize()
{
    QPixmap logo_image{":/imgs/PSP-AC-1Color-white.png"};
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(logo_image.scaled(w, h, Qt::KeepAspectRatio));

    QPixmap checkmark{":/imgs/checkmark.png"};
    int w2 = ui->mark_1->width();
    int h2 = ui->mark_1->height();
    ui->mark_1->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_2->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_3->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_4->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_5->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));

    return true;
}

void FlightData::on_launchButton_clicked()
{
    // LAUNCH
    qDebug() << "To Infinity and Beyond";
}

