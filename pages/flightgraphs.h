#ifndef FLIGHTGRAPHS_H
#define FLIGHTGRAPHS_H

#include "graphs/linegraph.h"
#include "graphs/myq3dscatter.h"

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

    MyQ3DScatter *scatter;

    bool initialize2DGraphs();
    LineGraph *pitchGraph;
    LineGraph *rollGraph;
    LineGraph *yawGraph;

    QChartView *pitchChart;
    QChartView *rollChart;
    QChartView *yawChart;

    void addData();
    void updateGraphs();

private:
    Ui::FlightGraphs *ui;
};

#endif // FLIGHTGRAPHS_H
