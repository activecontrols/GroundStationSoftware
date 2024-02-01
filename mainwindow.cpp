#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixMap>
#include <QTime>
#include <QString>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap logo_image{":/imgs/PSP-AC-1Color-white.png"};
    int w = ui->logo->width();
    int h = ui->logo->height();
    ui->logo->setPixmap(logo_image.scaled(w, h, Qt::KeepAspectRatioByExpanding));

    QPixmap checkmark{":/imgs/checkmark.png"};

    int w2 = ui->mark_1->width();
    int h2 = ui->mark_1->height();
    ui->mark_1->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_2->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_3->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_4->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));
    ui->mark_5->setPixmap(checkmark.scaled(w2, h2, Qt::KeepAspectRatio));

    ui->statusbar->addPermanentWidget(ui->connection_label);
    ui->statusbar->addPermanentWidget(ui->clock);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::startClock);
    timer->start(1000);

    ui->connection_label->setStyleSheet("color: red");

    // connect(ui->connect_action, SIGNAL(), , SLOT());
    // connect(ui->disconnect_action, SIGNAL(), , SLOT());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startClock()
{
    ui->clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}

void MainWindow::showCOMConnected()
{
    ui->connection_label->setStyleSheet("color: green");
}

void MainWindow::showSuccessfulMemAlloc()
{
    QMessageBox::information(this, "Successful Memory Allocation", "Success");
    ui->statusbar->showMessage("Successful Memory Allocation", 5000);
}

void MainWindow::showUnsuccessfulMemAlloc()
{
    QMessageBox::warning(this, "Unsuccessful Memory Allocation", "Fail");
    ui->statusbar->showMessage("Unsuccessful Memory Allocation", 1000);
}

void MainWindow::on_upload_telem_clicked()
{
    showCOMConnected();
    showSuccessfulMemAlloc();
    // showUnsuccessfulMemAlloc();

}

void MainWindow::on_launch_button_released()
{
    lw = new LaunchWindow(this);
    lw->show();
}


void MainWindow::on_connect_action_triggered()
{
    cd = new CommDialog(this);
    cd->show();
}

