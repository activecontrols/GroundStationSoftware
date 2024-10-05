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
    void uploadTelem(qreal k_val, qreal p_val, qreal n_val, qreal m_val, qreal N_val);

    // void receiveCamera();

    void on_uploadButton_clicked();
    void updateTelemetryDisplay(const QByteArray &data);

private:
    Ui::FlightData *ui;
    Camera camera;
    bool initialize();
};

#endif // FLIGHTDATA_H
