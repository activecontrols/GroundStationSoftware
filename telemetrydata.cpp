#include "telemetrydata.h"

TelemetryData::TelemetryData()
{
    battery = 0;
    temperature = 0;
    x_pos = 0;
    y_pos = 0;
    z_pos = 0;
    x_vel = 0;
    y_vel = 0;
    z_vel = 0;
    x_acc = 0;
    y_acc = 0;
    z_acc = 0;
    airspeed = -1;
    for (int i = 0; i < 3; i++)
    {
        vel_variance[i] = 0;
    }
    for (int i = 0; i < 3; i++)
    {
        pos_variance[i] = 0;
    }
    for (int i = 0; i < 4; i++)
    {
        altitude[i] = 0;
    }
    roll_rate = 0;
    pitch_rate = 0;
    yaw_rate = 0;
}
void TelemetryData::parseValues(const QStringList &values)
{
    int i = 0; // So that you can change order easily without changing indexes
    battery = values[i++].toInt();
    temperature = values[i++].toInt();

    x_pos = values[i++].toFloat();
    y_pos = values[i++].toFloat();
    z_pos = values[i++].toFloat();
    x_vel = values[i++].toFloat();
    y_vel = values[i++].toFloat();
    z_vel = values[i++].toFloat();
    x_acc = values[i++].toFloat();
    y_acc = values[i++].toFloat();
    z_acc = values[i++].toFloat();
    airspeed = values[i++].toFloat();

    for (int j = 0; j < 3; j++)
    {
        vel_variance[j] = values[i++].toFloat();
    }
    for (int j = 0; j < 3; j++)
    {
        pos_variance[j] = values[i++].toFloat();
    }
    for (int j = 0; j < 4; j++)
    {
        altitude[j] = values[i++].toFloat();
    }
    roll_rate = values[i++].toFloat();
    pitch_rate = values[i++].toFloat();
    yaw_rate = values[i++].toFloat();
}

// void TelemetryData::setBattery(uint8_t battery)
// {
//     this->battery = battery;
// }
// void TelemetryData::setXPos(float x_pos)
// {
//     this->x_pos = x_pos;
// }
// void TelemetryData::setYPos(float y_pos)
// {
//     this->y_pos = y_pos;
// }
// void TelemetryData::setZPos(float z_pos)
// {
//     this->z_pos = z_pos;
// }
// void TelemetryData::setXVel(float x_vel)
// {
//     this->x_vel = x_vel;
// }
// void TelemetryData::setYVel(float y_vel)
// {
//     this->y_vel = y_vel;
// }
// void TelemetryData::setZVel(float z_vel)
// {
//     this->z_vel = z_vel;
// }
// void TelemetryData::setXAcc(float x_acc)
// {
//     this->x_acc = x_acc;
// }
// void TelemetryData::setYAcc(float y_acc)
// {
//     this->y_acc = y_acc;
// }
// void TelemetryData::setZAcc(float z_acc)
// {
//     this->z_acc = z_acc;
// }
