#include "launchwindow.h"
#include "ui_launchwindow.h"

#include <QGridLayout>
#include <QTime>
#include <QDateTime>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QVector3D>
#include <iostream>

LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LaunchWindow::updateClock);
    connect(timer, &QTimer::timeout, this, &LaunchWindow::updateGraph);
    timer->start(update_time * 1000);

    line_series_1 = new QLineSeries();

    data_1 = new QChart();
    data_1->legend()->hide();
    data_1->addSeries(line_series_1);
    data_1->createDefaultAxes();
    data_1->axes(Qt::Horizontal).back()->setRange(0, x_range_1);
    data_1->axes(Qt::Vertical).back()->setRange(0, y_range_1);
    data_1->axes(Qt::Horizontal).back()->setTitleText("Seconds");
    data_1->axes(Qt::Vertical).back()->setTitleText("Axis y");

    QFont font;
    font.setPixelSize(18);
    data_1->setTitleFont(font);
    data_1->setTitleBrush(QBrush(Qt::black));
    data_1->setTitle("Data");

    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    line_series_1->setPen(pen);

    data_1->setAnimationOptions(QChart::AllAnimations);
    ui->graph_1->setChart(data_1);

    ui->scatter_1->show();
}

LaunchWindow::~LaunchWindow()
{

    ui->scatter_1->update();
    delete ui;
}

void LaunchWindow::updateClock()
{
    ui->clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}

void LaunchWindow::updateGraph()
{
    // Update the first graph
    QPointF point_1 = QPointF(time_d, pow(time_d, 2) + sqrt(time_d));

    *line_series_1 << point_1;

    if (x_range_1 <= point_1.x() + 2) {
        x_range_1 += 10;
        data_1->axes(Qt::Horizontal).back()->setRange(0, x_range_1);
    } else if (y_range_1 <= point_1.y() + 10) {
        y_range_1 *= 2;
        data_1->axes(Qt::Vertical).back()->setRange(0, y_range_1);
    }

    // Update the second graph
    ui->scatter_1->addData(time_d, time_d, time_d);

    time_d += update_time;
}
