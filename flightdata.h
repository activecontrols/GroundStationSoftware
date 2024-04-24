#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <QWidget>
#include "camera.h"

namespace Ui {
class FlightData;
}

class FlightData : public QWidget
{
    Q_OBJECT

public:
    explicit FlightData(QWidget *parent = nullptr);
    ~FlightData();

    void updateChecks(qreal);
    void updateData(qreal alt, qreal amb_press, qreal batt, qreal climb,
                    qreal current, qreal imu, qreal pitch, qreal roll,
                    qreal yaw, qreal lat, qreal longit);

signals:
    void transmitCamera();

private slots:
    void on_launchButton_clicked();
    void uploadTelem();

    // void receiveCamera();

private:
    Ui::FlightData *ui;
    Camera camera;
    bool initialize();
};

#endif // FLIGHTDATA_H
