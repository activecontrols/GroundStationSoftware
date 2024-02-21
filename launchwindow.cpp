#include "launchwindow.h"
#include "ui_launchwindow.h"

#include <QGridLayout>
#include <QTime>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <iostream>
#include <stdlib.h>
#include <QVector>

QVector<QPointF> test_vector;

LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);

    srand(1234);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LaunchWindow::updateClock);
    connect(timer, &QTimer::timeout, this, &LaunchWindow::updateGraph);
    timer->start(update_time * 1000);

    line_series_1 = new QLineSeries();
    line_series_2 = new QLineSeries();
    line_series_3 = new QLineSeries();

    data_1 = new QChart();
    data_1->legend()->hide();
    data_1->addSeries(line_series_1);
    data_1->createDefaultAxes();
    data_1->axes(Qt::Horizontal).back()->setRange(0, x_range_1);
    data_1->axes(Qt::Vertical).back()->setRange(0, y_range_1);
    data_1->axes(Qt::Horizontal).back()->setTitleText("Seconds");
    data_1->axes(Qt::Vertical).back()->setTitleText("Axis y");

    data_2 = new QChart();
    data_2->legend()->hide();
    data_2->addSeries(line_series_2);
    data_2->createDefaultAxes();
    data_2->axes(Qt::Horizontal).back()->setRange(0, x_range_2);
    data_2->axes(Qt::Vertical).back()->setRange(0, y_range_2);
    data_2->axes(Qt::Horizontal).back()->setTitleText("Seconds");
    data_2->axes(Qt::Vertical).back()->setTitleText("Axis y");

    data_3 = new QChart();
    data_3->legend()->hide();
    data_3->addSeries(line_series_3);
    data_3->createDefaultAxes();
    data_3->axes(Qt::Horizontal).back()->setRange(0, x_range_3);
    data_3->axes(Qt::Vertical).back()->setRange(0, y_range_3);
    data_3->axes(Qt::Horizontal).back()->setTitleText("Seconds");
    data_3->axes(Qt::Vertical).back()->setTitleText("Axis y");

    QFont font;
    font.setPixelSize(18);
    data_1->setTitleFont(font);
    data_1->setTitleBrush(QBrush(Qt::black));
    data_1->setTitle("Data");

    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    line_series_1->setPen(pen);

    data_1->setAnimationOptions(QChart::AllAnimations);
    data_2->setAnimationOptions(QChart::AllAnimations);
    data_3->setAnimationOptions(QChart::AllAnimations);

    ui->graph_1->setChart(data_1);
    ui->graph_2->setChart(data_2);
    ui->graph_3->setChart(data_3);

    test_vector.append(QPointF(0, 16));
    test_vector.append(QPointF(1, 25));
    test_vector.append(QPointF(2, 24));
    test_vector.append(QPointF(3, 19));
    test_vector.append(QPointF(4, 33));
    test_vector.append(QPointF(5, 25));
    test_vector.append(QPointF(6, 34));
    test_vector.append(QPointF(7, 29));
    test_vector.append(QPointF(8, 40));
    test_vector.append(QPointF(9, 32));
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}


void LaunchWindow::updateClock()
{
    ui->clock->setText(QTime::currentTime().toString("h:mm:ss ap"));
}

void LaunchWindow::updateGraph()
{
    QPointF point_1 = QPointF(time_d, pow(time_d, 2) + sqrt(time_d));
    QPointF point_2;
    QPointF point_3 = QPointF(time_d, (rand() % 5) + 3);

    *line_series_1 << point_1;
    if (time_d <= 9) {
        point_2 = test_vector[(int) time_d];
        *line_series_2 << point_2;
    }
    *line_series_3 << point_3;

    if (x_range_1 <= point_1.x() + 2) {
        x_range_1 += 10;
        data_3->axes(Qt::Horizontal).back()->setRange(0, x_range_1);
    } else if (y_range_1 <= point_1.y() + 10) {
        y_range_1 *= 2;
        data_3->axes(Qt::Vertical).back()->setRange(0, y_range_1);
    } else if ((x_range_3 <= point_3.x() + 2) || (y_range_3 <= point_3.y() + 10)) {
        x_range_3 += 10;
        // y_range_3 *= 2;
    }

    time_d += update_time;
    std::cout << time_d;
}
