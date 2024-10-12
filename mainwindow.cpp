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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWindow();
    // initSerialPort();
    // initTelemetryFile();

    stackedWidget->setCurrentIndex(0);

    logWindow = new LogWindow(this);
    commDialog = new CommDialog(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000);

    connect(telemetryModel, &TelemetryModel::addTelemetryData, flightData, &FlightData::updateTelemetryDisplay);

    simulateTelemetryData();

    // QObject::connect(this, &MainWindow::change, ui->flightGraphs->scatter, &MyQ3DScatter::receiveChange);
}

MainWindow::~MainWindow()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete telemetryModel;
    delete serial;
}

// For when data is received from the serial port
void MainWindow::onDataReceived()
{
    QByteArray data = serial->readAll();
    QString telemetryStr = QString::fromUtf8(data);
    QStringList telemetryList = telemetryStr.split(",");
    if (telemetryList.size() != 14) {
        return;
    }

    emit telemetryDataReceived(data);
}

void MainWindow::initWindow()
{
    menuBar = new QMenuBar();
    QMenu *fileMenu = menuBar->addMenu("File");
    QAction *exportDataAction = fileMenu->addAction("Export Data");
    QMenu *visualMenu = menuBar->addMenu("Visual");
    QAction *twoDGraphAction = visualMenu->addAction("2D Graph");
    QAction *threeDGraphAction = visualMenu->addAction("3D Graph");

    setMenuBar(menuBar);

    // connect(exportDataAction, &QAction::triggered, this, &MainWindow::on_actionConnect_triggered);
    // connect(twoDGraphAction, &QAction::triggered, this, &MainWindow::on_actionFlight_Logs_triggered);
    // connect(threeDGraphAction, &QAction::triggered, this, &MainWindow::on_action3D_Graph_triggered);

    toolBar = addToolBar("Navigation");

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

    connect(flightDataAction, &QAction::triggered, this, [=]() { stackedWidget->setCurrentIndex(0); });
    connect(flightGraphsAction, &QAction::triggered, this, [=]() { stackedWidget->setCurrentIndex(1); });

    flightData = new FlightData();
    flightGraphs = new FlightGraphs();

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(flightData);
    stackedWidget->addWidget(flightGraphs);
    setCentralWidget(stackedWidget);
}

void MainWindow::initSerialPort()
{
    // Set the serial port name and parameters (modify COM port as needed)
    serial->setPortName("COM1");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Open the serial port
    if (serial->open(QIODevice::ReadOnly)) {
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::onDataReceived);
        qDebug() << "Serial port opened successfully!";
    } else {
        qDebug() << "Failed to open serial port: " << serial->errorString();
    }
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
    QTimer *simulateTimer = new QTimer(this);
    connect(simulateTimer, &QTimer::timeout, this, &MainWindow::generateSimulatedData);
    timer->start(5000);
}

void MainWindow::generateSimulatedData()
{
    // Simulate telemetry data
    QRandomGenerator *generator = QRandomGenerator::global();
    TelemetryData testTelemetryData;
    testTelemetryData.setBattery(generator->bounded(0, 100));
    testTelemetryData.setTemperature(generator->bounded(-20, 50));
    testTelemetryData.setXPos(generator->generateDouble() * 100);
    testTelemetryData.setYPos(generator->generateDouble() * 100);
    testTelemetryData.setZPos(generator->generateDouble() * 100);
    testTelemetryData.setXVel(generator->generateDouble() * 100);
    testTelemetryData.setYVel(generator->generateDouble() * 100);
    testTelemetryData.setZVel(generator->generateDouble() * 100);
    testTelemetryData.setXAcc(generator->generateDouble() * 100);
    testTelemetryData.setYAcc(generator->generateDouble() * 100);
    testTelemetryData.setZAcc(generator->generateDouble() * 100);
    testTelemetryData.setAirspeed(generator->generateDouble() * 100);
    float variance[3] = {static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100)};
    testTelemetryData.setVelVariance(variance);
    testTelemetryData.setPosVariance(variance);
    float altitude[4] = {static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100), static_cast<float>(generator->generateDouble() * 100)};
    testTelemetryData.setAltitude(altitude);
    testTelemetryData.setRoll(generator->generateDouble() * 100);
    testTelemetryData.setPitch(generator->generateDouble() * 100);
    testTelemetryData.setYaw(generator->generateDouble() * 100);
    telemetryModel->addTelemetryData(testTelemetryData);
}

void MainWindow::updateClock()
{
    clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}

// void MainWindow::showCOMConnected()
// {
//     ui->connection_label->setStyleSheet("color: green");
//     logWindow->addCOMConnected();
// }

// void MainWindow::showSuccessfulMemAlloc()
// {
//     QMessageBox::information(this, "Successful Memory Allocation", "Success");
//     ui->statusbar->showMessage("Successful Memory Allocation", 5000);
//     logWindow->addSuccessfulMemAlloc();
// }

// void MainWindow::showUnsuccessfulMemAlloc()
// {
//     QMessageBox::warning(this, "Unsuccessful Memory Allocation", "Fail");
//     ui->statusbar->showMessage("Unsuccessful Memory Allocation", 5000);
//     logWindow->addUnsuccessfulMemAlloc();
// }

// void MainWindow::on_upload_telem_clicked()
// {
//     // Upload telemetry, and then receive message back to see what we write
//     if (1) {
//         showSuccessfulMemAlloc();
//     } else {
//         // showUnsuccessfulMemAlloc();
//     }
// }

void MainWindow::showCOMConnection()
{
    if (true) {
        QMessageBox::information(this, "Connection Successful", "Serial port connected");
        logWindow->addCOMConnected();
        // QIcon connected = new QIcon();
        // ui->actionConnect->setIcon();
    }
    else {
        QMessageBox::information(this, "Connection Not Successful", "Error. Failed to connect to serial port.");
    }
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
