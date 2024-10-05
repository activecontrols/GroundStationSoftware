#include "telemetrydata.h"

Data::Data(QObject *parent)
    : QObject{parent}
{
    battery = 0;
    x_pos = 0;
    y_pos = 0;
    z_pos = 0;
    x_vel = 0;
    y_vel = 0;
    z_vel = 0;
    x_acc = 0;
    y_acc = 0;
    z_acc = 0;
    altitude = 0;
    temperature = 0;
    pressure = 0;
}

void Data::setBattery(uint8_t battery)
{
    this->battery = battery;
}
void Data::setXPos(float x_pos)
{
    this->x_pos = x_pos;
}
void Data::setYPos(float y_pos)
{
    this->y_pos = y_pos;
}
void Data::setZPos(float z_pos)
{
    this->z_pos = z_pos;
}
void Data::setXVel(float x_vel)
{
    this->x_vel = x_vel;
}
void Data::setYVel(float y_vel)
{
    this->y_vel = y_vel;
}
void Data::setZVel(float z_vel)
{
    this->z_vel = z_vel;
}
void Data::setXAcc(float x_acc)
{
    this->x_acc = x_acc;
}
void Data::setYAcc(float y_acc)
{
    this->y_acc = y_acc;
}
void Data::setZAcc(float z_acc)
{
    this->z_acc = z_acc;
}
