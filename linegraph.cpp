#include "linegraph.h"

#include <QtCharts>
#include <QtCharts/QLineSeries>

LineGraph::LineGraph(QObject *parent)
    : QObject{parent}
{
    chart = new QChart();
    series = new QLineSeries();
    list = new QList<QPointF>();
}

void LineGraph::initialize(QString title, QString yAxis) {
    chart->setTheme(QChart::ChartTheme(QChart::ChartThemeDark));

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).back()->setRange(0, 10);
    chart->axes(Qt::Vertical).back()->setRange(-10, 10);
    chart->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    chart->axes(Qt::Vertical).back()->setTitleText(yAxis);

    QFont font = QFont("8514oem");
    font.setPixelSize(8);
    chart->setTitleFont(font);
    // chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(title);

    QPen pen(QRgb(0xDAAA00));
    pen.setWidth(2);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::SeriesAnimations);
}

void LineGraph::addData(qreal time, qreal value) {
    QPointF dataPoint = QPointF(time, value);
    *list << dataPoint;
    *series << dataPoint;
    if (autoScroll && time > 10.0f) {
        chart->axes(Qt::Horizontal).back()->setRange(time - 10.0f, time);
    }
}
