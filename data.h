#ifndef DATA_H
#define DATA_H

#include <QObject>

class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    
    void setBattery(uint8_t battery);
    void setXPos(float x_pos);
    void setYPos(float y_pos);
    void setZPos(float z_pos);
    void setXVel(float x_vel);
    void setYVel(float y_vel);
    void setZVel(float z_vel);
    void setXAcc(float x_acc);
    void setYAcc(float y_acc);
    void setZAcc(float z_acc);
private:
    uint8_t battery;
    float x_pos;
    float y_pos;
    float z_pos;
    float x_vel;
    float y_vel;
    float z_vel;
    float x_acc;
    float y_acc;
    float z_acc;

    float altitude;
    float temperature;
    float pressure;


signals:
};

#endif // DATA_H
