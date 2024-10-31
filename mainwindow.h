#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include <QStackedWidget>
#include <QToolBar>
#include <flightdata.h>
#include <flightgraphs.h>
#include <serialconnection.h>
#include "commdialog.h"
#include "logwindow.h"
#include "telemetrymodel.h"
#include "GroundStationComms.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateClock();
    void showCOMConnection();
    // void showSuccessfulMemAlloc();
    // void showUnsuccessfulMemAlloc();

signals:
    void telemetryDataReceived(const QByteArray &data);
    void change();

private:
    // graphics
    QStackedWidget *stackedWidget;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QLabel *clock;

    // pages
    FlightData *flightData;
    FlightGraphs *flightGraphs;
    SerialConnection *serialConnection;


    LogWindow *logWindow;
    CommDialog *commDialog;
    QTimer *timer;
    QSerialPort *serial;
    QFile *telemetryFile;
    QTextStream *stream;
    TelemetryModel *telemetryModel;

    GroundCommsManager comms;

    void initWindow();
    void initTelemetryFile();

    void simulateTelemetryData();
    void generateSimulatedData();

private slots:
    void onDataReceived();
    void onUpdateSerial(QSerialPort* newSerial);
    // void on_upload_telem_clicked();
    // void on_launch_button_released();
    // void on_connect_action_triggered();
    // void on_log_action_triggered();
    void on_actionFlight_Logs_triggered();
    void on_action3D_Graph_triggered();

};
#endif // MAINWINDOW_H
