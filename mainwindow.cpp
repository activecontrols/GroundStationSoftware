#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QTime>
#include <QString>
#include <QMessageBox>
#include <QStackedWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    QWidget *spacerWidget = new QWidget(this);
    QWidget *spacerWidget2 = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    spacerWidget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->toolBar->insertWidget(ui->actionFlight_Data, spacerWidget);
    ui->toolBar->insertWidget(ui->actionConnect, new QLabel("                           "));
    ui->toolBar->insertWidget(ui->actionConnect, ui->clock);
    ui->toolBar->addWidget(spacerWidget2);
    spacerWidget->setVisible(true);
    spacerWidget2->setVisible(true);
    // ui->toolBar->setStyleSheet("QToolBar{spacing:0px;}");


    logWindow = new LogWindow(this);
    commDialog = new CommDialog(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000);

    QObject::connect(this, &MainWindow::change, ui->flightGraphs->scatter, &MyQ3DScatter::receiveChange);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    // auto *toolBar = new QToolBar();

    auto *flightData = new FlightData();
    auto *flightGraphs = new FlightGraphs();

    auto *stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(flightData);
    stackedWidget->addWidget(flightGraphs);
    setCentralWidget(stackedWidget);
}

void MainWindow::updateClock()
{
    ui->clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
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

void MainWindow::on_actionFlight_Data_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionFlight_Graphs_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_actionConnect_triggered()
{
    commDialog->show();
}

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
