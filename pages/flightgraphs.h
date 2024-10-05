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
    LineGraph *altGraph;
    LineGraph *throttleGraph;
    LineGraph *pitchGraph;
    LineGraph *rollGraph;
    LineGraph *yawGraph;

    QChartView *altChart;
    QChartView *throttleChart;
    QChartView *pitchChart;
    QChartView *rollChart;
    QChartView *yawChart;

    QTimer *temp_timer;

    void addData();

private slots:
    void updateGraphs();

private:
    Ui::FlightGraphs *ui;
};

#endif // FLIGHTGRAPHS_H
