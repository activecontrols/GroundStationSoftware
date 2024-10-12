#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <QWidget>
#include "camera.h"
#include <telemetrydata.h>

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
    void updateTelemetryDisplay(const TelemetryData &data);

signals:
    void transmitCamera();

private slots:
    void on_launchButton_clicked();
    void uploadTelem(qreal k_val, qreal p_val, qreal n_val, qreal m_val, qreal N_val);

    // void receiveCamera();

    void on_uploadButton_clicked();

private:
    Ui::FlightData *ui;
    Camera camera;
    bool initialize();
};

#endif // FLIGHTDATA_H
