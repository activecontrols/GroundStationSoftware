#include "flightdata.h"
#include "ui_flightdata.h"

#include <QDebug>

FlightData::FlightData(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightData)
{
    ui->setupUi(this);
    // setStyleSheet("font: 12pt '8514oem'\nbackground-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:0, stop:0.0913462"
    //               "rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));");
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
    checkmark = checkmark.scaled(w2, h2, Qt::KeepAspectRatio);

    ui->mark_1->setPixmap(checkmark);
    ui->mark_2->setPixmap(checkmark);
    ui->mark_3->setPixmap(checkmark);
    ui->mark_4->setPixmap(checkmark);

    return true;
}

void FlightData::on_launchButton_clicked()
{
    // LAUNCH
    qDebug() << "To Infinity and Beyond";
}

void FlightData::updateData(qreal alt, qreal amb_press, qreal batt, qreal climb,
                            qreal current, qreal imu, qreal pitch, qreal roll,
                            qreal yaw, qreal lat, qreal longit) {
    ui->alt_data->setText(QString::number(alt));
    ui->amb_press_data->setText(QString::number(amb_press));
    ui->batt_data->setText(QString::number(batt));
    ui->climb_data->setText(QString::number(climb));
    ui->current_data->setText(QString::number(current));
    ui->imu_temp_data->setText(QString::number(imu));
    ui->pitch_data->setText(QString::number(pitch));
    ui->roll_data->setText(QString::number(roll));
    ui->yaw_data->setText(QString::number(yaw));
    ui->lat_data->setText(QString::number(longit));
}

void FlightData::updateChecks(qreal battery) {
    if (battery < 0) {
        qDebug() << "Battery dead";
        // ui->mark_1->setPixmap(checkmark);
    }
    else {
        // ui->mark_1->setPixmap();
    }
}

void FlightData::uploadTelem() {

}
