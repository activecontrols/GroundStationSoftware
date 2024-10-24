#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <QWidget>
#include <QCamera>
#include <QCameraDevice>
#include <QGraphicsView>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QVideoWidget>
// #include "camera.h"
#include <telemetrydata.h>
#include <controlsystemstatewidget.h>

class FlightData : public QWidget
{
    Q_OBJECT

public:
    explicit FlightData(QWidget *parent = nullptr);

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
    ControlSystemStateWidget *controlSystemStateWidget;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    // QCamera *camera;
    // QCameraDevice *cameraDevice;
    // QMediaDevices *mediaDevices;
    // QMediaCaptureSession *captureSession;
    QVideoWidget *videoWidget;
    // Camera camera;
    bool initialize();
};

#endif // FLIGHTDATA_H
