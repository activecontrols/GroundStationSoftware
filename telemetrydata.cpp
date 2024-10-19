#include "telemetrydata.h"

TelemetryData::TelemetryData()
{
    battery = 0;
    temperature = 0;
    timestamp = 0;
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
        attitude[i] = 0;
    }
    roll = 0;
    pitch = 0;
    yaw = 0;
}
void TelemetryData::parseValues(const QStringList &values)
{
    int i = 0; // So that you can change order easily without changing indexes
    battery = values[i++].toInt();
    temperature = values[i++].toInt();
    timestamp = values[i++].toULongLong();

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
        attitude[j] = values[i++].toFloat();
    }
    roll = values[i++].toFloat();
    pitch = values[i++].toFloat();
    yaw = values[i++].toFloat();
}

uint8_t TelemetryData::getBattery() const
{
    return battery;
}

int16_t TelemetryData::getTemperature() const
{
    return temperature;
}

uint64_t TelemetryData::getTimestamp() const
{
    return timestamp;
}

float TelemetryData::getXPos() const
{
    return x_pos;
}

float TelemetryData::getYPos() const
{
    return y_pos;
}

float TelemetryData::getZPos() const
{
    return z_pos;
}

float TelemetryData::getXVel() const
{
    return x_vel;
}

float TelemetryData::getYVel() const
{
    return y_vel;
}

float TelemetryData::getZVel() const
{
    return z_vel;
}

float TelemetryData::getXAcc() const
{
    return x_acc;
}

float TelemetryData::getYAcc() const
{
    return y_acc;
}

float TelemetryData::getZAcc() const
{
    return z_acc;
}

float TelemetryData::getAirspeed() const
{
    return airspeed;
}

float TelemetryData::getVelVariance(int index) const
{
    return vel_variance[index];
}

float TelemetryData::getPosVariance(int index) const
{
    return pos_variance[index];
}

float TelemetryData::getAttitude(int index) const
{
    return attitude[index];
}

float TelemetryData::getRoll() const
{
    return roll;
}

float TelemetryData::getPitch() const
{
    return pitch;
}

float TelemetryData::getYaw() const
{
    return yaw;
}

void TelemetryData::setBattery(uint8_t battery)
{
    this->battery = battery;
}

void TelemetryData::setTemperature(int16_t temperature)
{
    this->temperature = temperature;
}

void TelemetryData::setTimestamp(uint64_t timestamp)
{
    this->timestamp = timestamp;
}

void TelemetryData::setXPos(float x_pos)
{
    this->x_pos = x_pos;
}
void TelemetryData::setYPos(float y_pos)
{
    this->y_pos = y_pos;
}
void TelemetryData::setZPos(float z_pos)
{
    this->z_pos = z_pos;
}
void TelemetryData::setXVel(float x_vel)
{
    this->x_vel = x_vel;
}
void TelemetryData::setYVel(float y_vel)
{
    this->y_vel = y_vel;
}
void TelemetryData::setZVel(float z_vel)
{
    this->z_vel = z_vel;
}
void TelemetryData::setXAcc(float x_acc)
{
    this->x_acc = x_acc;
}
void TelemetryData::setYAcc(float y_acc)
{
    this->y_acc = y_acc;
}
void TelemetryData::setZAcc(float z_acc)
{
    this->z_acc = z_acc;
}

void TelemetryData::setAirspeed(float airspeed)
{
    this->airspeed = airspeed;
}

void TelemetryData::setVelVariance(float variance[3])
{
    for (int i = 0; i < 3; i++)
    {
        vel_variance[i] = variance[i];
    }
}

void TelemetryData::setPosVariance(float variance[3])
{
    for (int i = 0; i < 3; i++)
    {
        pos_variance[i] = variance[i];
    }
}

void TelemetryData::setAttitude(float attitude[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->attitude[i] = attitude[i];
    }
}

void TelemetryData::setRoll(float roll)
{
    this->roll = roll;
}

void TelemetryData::setPitch(float pitch)
{
    this->pitch = pitch;
}

void TelemetryData::setYaw(float yaw)
{
    this->yaw = yaw;
}
