#ifndef FLIGHTGRAPHS_H
#define FLIGHTGRAPHS_H

#include "graphs/linegraph.h"
#include "graphs/myq3dscatter.h"
#include "telemetrydata.h"

#include <QWidget>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QChartView>
#include <QTimer>

namespace Ui {
class FlightGraphs;
}

class FlightGraphs : public QWidget
{
    Q_OBJECT

public:
    explicit FlightGraphs(QWidget *parent = nullptr);
    ~FlightGraphs();

    LineGraph *xVelGraph;
    LineGraph *yVelGraph;
    LineGraph *zVelGraph;

    QChartView *xVelChart;
    QChartView *yVelChart;
    QChartView *zVelChart;


    bool initialize2DGraphs();
    void updateGraphs(const TelemetryData &data);

private:
    Ui::FlightGraphs *ui;
    MyQ3DScatter *scatter;
};

#endif // FLIGHTGRAPHS_H
