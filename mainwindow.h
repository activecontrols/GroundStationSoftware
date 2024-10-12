#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QSerialPort>
#include <QStackedWidget>
#include <QToolBar>
#include <flightdata.h>
#include <flightgraphs.h>
#include "commdialog.h"
#include "logwindow.h"
#include "telemetrymodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void telemetryDataReceived(const QByteArray &data);
    void change();

public slots:
    void initialize();
    void updateClock();
    void showCOMConnection();
    // void showSuccessfulMemAlloc();
    // void showUnsuccessfulMemAlloc();

private:
    QStackedWidget *stackedWidget;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    FlightData *flightData;
    FlightGraphs *flightGraphs;
    QLabel *clock;

    LogWindow *logWindow;
    CommDialog *commDialog;
    QTimer *timer;
    QSerialPort *serial;
    TelemetryModel *telemetryModel;


private slots:
    void onDataReceived();
    // void on_upload_telem_clicked();
    // void on_launch_button_released();
    // void on_connect_action_triggered();
    // void on_log_action_triggered();
    void on_actionConnect_triggered();
    void on_actionFlight_Logs_triggered();
    void on_action3D_Graph_triggered();
};
#endif // MAINWINDOW_H
