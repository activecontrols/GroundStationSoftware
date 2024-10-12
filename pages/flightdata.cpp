#include "flightdata.h"
#include "ui_flightdata.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

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
    QPixmap logo_image{":/assets/PSP-AC-1Color-white.png"};
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(logo_image.scaled(w, h, Qt::KeepAspectRatio));

    QPixmap checkmark{":/assets/checkmark.png"};
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

void FlightData::updateChecks(qreal battery) {
    if (battery < 0) {
        qDebug() << "Battery dead";
        // ui->mark_1->setPixmap(checkmark);
    }
    else {
        // ui->mark_1->setPixmap();
    }
}

void FlightData::uploadTelem(qreal k_val, qreal p_val, qreal n_val, qreal m_val, qreal N_val) {
    ui->k_data->setText(QString::number(k_val));
    ui->p_data->setText(QString::number(p_val));
    ui->n_data->setText(QString::number(n_val));
    ui->m_data->setText(QString::number(m_val));
    ui->N_data->setText(QString::number(N_val));
}

void FlightData::on_uploadButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Upload Telemetry", QDir::homePath());
    QFile file(file_name);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Not readable", "File couldn't be read");
    }

    QTextStream in(&file);
    QString text = in.readAll();

    // Read in telemetry to change values on screen as well as send to teensy

    // qreal k_val = text.toDouble();
    // qreal p_val = text.toDouble();
    // qreal n_val = text.toDouble();
    // qreal m_val = text.toDouble();
    // qreal N_val = text.toDouble();
    // uploadTelem(k_val, p_val, n_val, m_val, N_val);
}

void FlightData::updateTelemetryDisplay(TelemetryData &data)
{
    qDebug() << "Updating telemetry display";
    ui->batt->setText(QString::number(data.getBattery()));
    ui->temp->setText(QString::number(data.getTemperature()));
    ui->x_pos->setText(QString::number(data.getXPos()));
    ui->y_pos->setText(QString::number(data.getYPos()));
    ui->z_pos->setText(QString::number(data.getZPos()));
    ui->x_vel->setText(QString::number(data.getXVel()));
    ui->y_vel->setText(QString::number(data.getYVel()));
    ui->z_vel->setText(QString::number(data.getZVel()));
    ui->x_acc->setText(QString::number(data.getXAcc()));
    ui->y_acc->setText(QString::number(data.getYAcc()));
    ui->z_acc->setText(QString::number(data.getZAcc()));
    ui->pos_var_1->setText(QString::number(data.getPosVariance(0)));
    ui->pos_var_2->setText(QString::number(data.getPosVariance(1)));
    ui->pos_var_3->setText(QString::number(data.getPosVariance(2)));
    ui->vel_var_1->setText(QString::number(data.getVelVariance(0)));
    ui->vel_var_2->setText(QString::number(data.getVelVariance(1)));
    ui->vel_var_3->setText(QString::number(data.getVelVariance(2)));
    ui->alt_1->setText(QString::number(data.getAltitude(0)));
    ui->airspeed->setText(QString::number(data.getAirspeed()));
    ui->roll->setText(QString::number(data.getRoll()));
    ui->pitch->setText(QString::number(data.getPitch()));
    ui->yaw->setText(QString::number(data.getYaw()));
}
