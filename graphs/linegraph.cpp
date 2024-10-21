#include "linegraph.h"

#include <QtCharts>
#include <QtCharts/QLineSeries>

LineGraph::LineGraph(QObject *parent)
    : QObject{parent},
      chart{new QChart()},
      series{new QLineSeries()},
      axisX{new QValueAxis()},
      axisY{new QValueAxis()},
      minY{-10.0f},
      maxY{10.0f},
      sampleRange{10.0f},
      autoScroll{true}
{
    chart->setTheme(QChart::ChartTheme(QChart::ChartThemeDark));
    chart->legend()->hide();

    chart->addSeries(series);
    axisX->setRange(0, 10);
    axisY->setRange(minY, minY);


    QFont font = QFont("Bahnschrift");
    font.setPixelSize(8);
    chart->setTitleFont(font);
    // chart->setTitleBrush(QBrush(Qt::black));

    QPen pen(QRgb(0xDAAA00));
    pen.setWidth(2);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void LineGraph::label(QString title, QString yAxisLabel)
{
    chart->setTitle(title);
    axisX->setTitleText("Time (sec)");
    axisY->setTitleText(yAxisLabel);
}

void LineGraph::updateGraph(QPointF data) {
    series->append(data);
    if (data.y() > maxY) {
        maxY = data.y();
    }
    if (data.y() < minY) {
        minY = data.y();
    }
    if (autoScroll && data.x() > sampleRange) {
        axisX->setRange(data.x() - sampleRange, data.x());
    }

    axisY->setRange(minY, maxY);
}
