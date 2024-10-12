#ifndef DATA_H
#define DATA_H

#include <QObject>

class TelemetryData
{
public:
    TelemetryData();

    uint8_t getBattery();
    int16_t getTemperature();
    float getXPos();
    float getYPos();
    float getZPos();
    float getXVel();
    float getYVel();
    float getZVel();
    float getXAcc();
    float getYAcc();
    float getZAcc();
    float getAirspeed();
    float getVelVariance(int index);
    float getPosVariance(int index);
    float getAltitude(int index);
    float getRoll();
    float getPitch();
    float getYaw();

    void setBattery(uint8_t battery);
    void setTemperature(int16_t temperature);
    void setXPos(float x_pos);
    void setYPos(float y_pos);
    void setZPos(float z_pos);
    void setXVel(float x_vel);
    void setYVel(float y_vel);
    void setZVel(float z_vel);
    void setXAcc(float x_acc);
    void setYAcc(float y_acc);
    void setZAcc(float z_acc);
    void setAirspeed(float airspeed);
    void setVelVariance(float variance[3]);
    void setPosVariance(float variance[3]);
    void setAltitude(float altitude[4]);
    void setRoll(float roll);
    void setPitch(float pitch);
    void setYaw(float yaw);

    void parseValues(const QStringList &values);
private:
    uint8_t battery;
    int16_t temperature; // Temperature in Celsius

    // Control System State
    float x_pos; // X position in body frame in m
    float y_pos; // Y position in body frame in m
    float z_pos; // Z position in body frame in m
    float x_vel; // X velocity in body frame in m/s
    float y_vel; // Y velocity in body frame in m/s
    float z_vel; // Z velocity in body frame in m/s
    float x_acc; // X acceleration in body frame in m/s^2
    float y_acc; // Y acceleration in body frame in m/s^2
    float z_acc; // Z acceleration in body frame in m/s^2

    float airspeed; // Airspeed in m/s, set to -1 if unknown
    float vel_variance[3]; // Variance of body velocity estimate
    float pos_variance[3]; // Variance in local position

    float altitude[4]; // Altitude represented as Quaternion

    float roll; // Angular rate in roll axis
    float pitch; // Angular rate in pitch axis
    float yaw; // Angular rate in yaw axis


signals:
};

#endif // DATA_H
