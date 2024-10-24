#include "controlsystemstatewidget.h"
#include "ui_controlsystemstatewidget.h"

ControlSystemStateWidget::ControlSystemStateWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlSystemStateWidget)
{
    ui->setupUi(this);
}

ControlSystemStateWidget::~ControlSystemStateWidget()
{
    delete ui;
}

void ControlSystemStateWidget::updateData(const TelemetryData &data)
{
    int digits = 3;
    ui->batt->setText(QString::number(data.getBattery()));
    ui->temp->setText(QString::number(data.getTemperature()));
    // Make this display the UNIX Epoch time into the hours, minutes, seconds, and milliseconds
    ui->timestamp->setText(QString::number(data.getTimestamp()));
    ui->x_pos->setText(QString::number(data.getXPos(),'f',digits));
    ui->y_pos->setText(QString::number(data.getYPos(),'f',digits));
    ui->z_pos->setText(QString::number(data.getZPos(),'f',digits));
    ui->x_vel->setText(QString::number(data.getXVel(),'f',digits));
    ui->y_vel->setText(QString::number(data.getYVel(),'f',digits));
    ui->z_vel->setText(QString::number(data.getZVel(),'f',digits));
    ui->x_acc->setText(QString::number(data.getXAcc(),'f',digits));
    ui->y_acc->setText(QString::number(data.getYAcc(),'f',digits));
    ui->z_acc->setText(QString::number(data.getZAcc(),'f',digits));
    ui->pos_var_1->setText(QString::number(data.getPosVariance(0),'f',digits));
    ui->pos_var_2->setText(QString::number(data.getPosVariance(1),'f',digits));
    ui->pos_var_3->setText(QString::number(data.getPosVariance(2),'f',digits));
    ui->vel_var_1->setText(QString::number(data.getVelVariance(0),'f',digits));
    ui->vel_var_2->setText(QString::number(data.getVelVariance(1),'f',digits));
    ui->vel_var_3->setText(QString::number(data.getVelVariance(2),'f',digits));
    ui->att_1->setText(QString::number(data.getAttitude(0),'f',digits));
    ui->att_2->setText(QString::number(data.getAttitude(1),'f',digits));
    ui->att_3->setText(QString::number(data.getAttitude(2),'f',digits));
    ui->att_4->setText(QString::number(data.getAttitude(3),'f',digits));
    ui->airspeed->setText(QString::number(data.getAirspeed(),'f',digits));
    ui->roll->setText(QString::number(data.getRoll(),'f',digits));
    ui->pitch->setText(QString::number(data.getPitch(),'f',digits));
    ui->yaw->setText(QString::number(data.getYaw(),'f',digits));
}

