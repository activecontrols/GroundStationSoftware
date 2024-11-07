#include "mainwindow.h"
#include "pages/flightdata.h"

#include <QDateTime>
#include <QTime>
#include <QString>
#include <QMessageBox>
#include <QStackedWidget>
#include <QDebug>
#include <QSerialPort>

#include <QRandomGenerator>

// Delete this when serial port is working
QTimer *simulateTimer;
uint64_t first = QDateTime::currentMSecsSinceEpoch();
TelemetryData previousData;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    logWindow(new LogWindow(this)),
    commDialog(new CommDialog(this)),
    telemetryModel(new TelemetryModel(this))
{
    initWindow();
    stackedWidget->setCurrentIndex(0);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000);

    connect(telemetryModel, &TelemetryModel::telemetryDataAdded, flightData, &FlightData::updateTelemetryDisplay);
    connect(telemetryModel, &TelemetryModel::telemetryDataAdded, flightGraphs, &FlightGraphs::updateGraphs);
    connect(commDialog, &CommDialog::updateSerial, this, &MainWindow::onUpdateSerial);

}

MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete stackedWidget;
    delete timer;
    delete simulateTimer;
    delete telemetryModel;
    delete serial;
}

// For when data is received from the serial port
void MainWindow::onDataReceived()
{
    QByteArray data = serial->readAll();
    comms.spin(data);
}

void MainWindow::onUpdateSerial(QSerialPort* newSerial)
{
    serial = newSerial;
    if (serial->isOpen())
    {
        QMessageBox::information(this, "Connection Successful", "Serial port connected");
        logWindow->addCOMConnected();
        comms.init(serial, -1, telemetryModel);
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::onDataReceived);
    }
    else
        QMessageBox::information(this, "Connection Cut", "Serial port disconnected");
}

void MainWindow::initWindow()
{
    menuBar = new QMenuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("Export Data");
    QMenu *visualMenu = menuBar->addMenu("Visual");
    visualMenu->addAction("2D Graph");
    visualMenu->addAction("3D Graph");

    setMenuBar(menuBar);

    // connect(exportDataAction, &QAction::triggered, this, &MainWindow::on_actionConnect_triggered);
    // connect(twoDGraphAction, &QAction::triggered, this, &MainWindow::on_actionFlight_Logs_triggered);
    // connect(threeDGraphAction, &QAction::triggered, this, &MainWindow::on_action3D_Graph_triggered);

    toolBar = new QToolBar();
    QToolButton *flightDataButton = new QToolButton(toolBar);
    QAction *flightDataAction = new QAction(QIcon(":/assets/flight_data.png"), "Flight Data", this);
    flightDataButton->setDefaultAction(flightDataAction);
    flightDataButton->setText("Flight Data");
    flightDataButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QToolButton *flightGraphsButton = new QToolButton(toolBar);
    QAction *flightGraphsAction = new QAction(QIcon(":/assets/flight_graph.png"), "Flight Graphs", this);
    flightGraphsButton->setDefaultAction(flightGraphsAction);
    flightGraphsButton->setText("Flight Graphs");
    flightGraphsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QToolButton *flightTestsButton = new QToolButton(toolBar);
    QAction *flightTestsAction = new QAction(QIcon(":/assets/flight_tests.png"), "Flight Test", this);
    flightTestsButton->setDefaultAction(flightTestsAction);
    flightTestsButton->setText("Flight Tests");
    flightTestsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QToolButton *flightLogsButton = new QToolButton(toolBar);
    QAction *flightLogsAction = new QAction(QIcon(":/assets/flight_logs.png"), "Flight Logs", this);
    flightLogsButton->setDefaultAction(flightLogsAction);
    flightLogsButton->setText("Flight Logs");
    flightLogsButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    clock = new QLabel(QTime::currentTime().toString("h:mm:ss ap"));
    clock->setStyleSheet("font-size: 20px; color: white;");

    QToolButton *connectButton = new QToolButton(toolBar);
    QAction *connectAction = new QAction(QIcon(":/assets/connect_icon.png"), "Connect", this);
    connectButton->setDefaultAction(connectAction);
    connectButton->setText("Connect");
    connectButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolBar->addWidget(flightDataButton);
    toolBar->addWidget(flightGraphsButton);
    toolBar->addWidget(flightTestsButton);
    toolBar->addWidget(flightLogsButton);
    toolBar->addWidget(spacer);
    toolBar->addWidget(clock);
    toolBar->addWidget(connectButton);

    toolBar->setFloatable(false);
    toolBar->setIconSize(QSize(60, 60));
    toolBar->setFixedHeight(93);
    toolBar->setStyleSheet("QToolBar{font:'Dubai';color:white;spacing:40px;}");

    addToolBar(toolBar);

    connect(flightDataAction, &QAction::triggered, this, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(flightGraphsAction, &QAction::triggered, this, [=]() { stackedWidget->setCurrentIndex(1); });
    // connect(flightTestsAction, &QAction::triggered, this, [=]() { stackedWidget->setCurrentIndex(2); });
    connect(connectAction, &QAction::triggered, this, [=]() { commDialog->show(); });

    flightData = new FlightData(this);
    flightGraphs = new FlightGraphs(this);

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(flightData);
    stackedWidget->addWidget(flightGraphs);

    setCentralWidget(stackedWidget);
}

void MainWindow::initTelemetryFile()
{
    // Open the file in append mode
    if (telemetryFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        stream = new QTextStream(telemetryFile);
        qDebug() << "Telemetry data file opened successfully!";
    } else {
        qDebug() << "Failed to open telemetry data file: " << telemetryFile->errorString();
    }
}

void MainWindow::simulateTelemetryData()
{
    simulateTimer = new QTimer(this);
    connect(simulateTimer, &QTimer::timeout, this, &MainWindow::generateSimulatedData);
    simulateTimer->start(100);
}

void MainWindow::generateSimulatedData()
{
    // Simulate telemetry data
    QRandomGenerator *generator = QRandomGenerator::global();
    TelemetryData testTelemetryData;
    testTelemetryData.setBattery(generator->bounded(0, 100));
    testTelemetryData.setTemperature(generator->bounded(-20, 50));
    testTelemetryData.setTimestamp((float) (QDateTime::currentMSecsSinceEpoch() - first)/1000.0);
    // Make all points relative to the previous point
    testTelemetryData.setXPos(previousData.getXPos() + (0.5 - generator->generateDouble()));
    testTelemetryData.setYPos(previousData.getYPos() + (0.5 - generator->generateDouble()));
    testTelemetryData.setZPos(previousData.getZPos() + (0.5 - generator->generateDouble()));
    testTelemetryData.setXVel(previousData.getXVel() + (0.5 - generator->generateDouble()));
    testTelemetryData.setYVel(previousData.getYVel() + (0.5 - generator->generateDouble()));
    testTelemetryData.setZVel(previousData.getZVel() + (0.5 - generator->generateDouble()));
    testTelemetryData.setXAcc(previousData.getXAcc() + (0.5 - generator->generateDouble()));
    testTelemetryData.setYAcc(previousData.getYAcc() + (0.5 - generator->generateDouble()));
    testTelemetryData.setZAcc(previousData.getZAcc() + (0.5 - generator->generateDouble()));
    testTelemetryData.setAirspeed(generator->generateDouble() * 100);
    float variance[3] = {static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100)};
    testTelemetryData.setVelVariance(variance);
    testTelemetryData.setPosVariance(variance);
    float altitude[4] = {static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100)};
    testTelemetryData.setAttitude(altitude);
    testTelemetryData.setRoll(generator->generateDouble() * 100);
    testTelemetryData.setPitch(generator->generateDouble() * 100);
    testTelemetryData.setYaw(generator->generateDouble() * 100);
    telemetryModel->addTelemetryData(testTelemetryData);
    previousData = testTelemetryData;
}

void MainWindow::updateClock()
{
    clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}

void MainWindow::on_actionFlight_Logs_triggered()
{
    logWindow->show();
}

void MainWindow::on_action3D_Graph_triggered()
{
    // qDebug() << "WORKS";
    // ui->flightGraphs->addData();
    emit change();
}
