#include "flightgraphs.h"
#include "ui_flightgraphs.h"
#include "graphs/myq3dscatter.h"

#include <QMessageBox>
#include <QPlainTextEdit>
#include <QtCharts/QLineSeries>
#include <QBrush>
#include <QtCharts>
#include <QVector3D>
#include <QTimer>

FlightGraphs::FlightGraphs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightGraphs)
    , scatter(new MyQ3DScatter())
{
    ui->setupUi(this);

    ui->gridLayout->removeWidget(ui->placeholder);
    ui->gridLayout->addWidget(scatter, 0, 0, 3, 2);

    if (!initialize2DGraphs()) {
        QMessageBox::warning(nullptr, "2D Graphs", "Couldn't properly initalize.");
    }
}

FlightGraphs::~FlightGraphs()
{
    delete ui;
}

bool FlightGraphs::initialize2DGraphs() {
    xVelGraph = new LineGraph();
    yVelGraph = new LineGraph();
    zVelGraph = new LineGraph();

    xVelGraph->label("X velocity", "m/s");
    yVelGraph->label("Y velocity", "m/s");
    zVelGraph->label("Z velocity", "m/s");

    ui->xVelChart->setChart(xVelGraph->getChart());
    ui->yVelChart->setChart(yVelGraph->getChart());
    ui->zVelChart->setChart(zVelGraph->getChart());


    /*
    altChart->setChart(altGraph->getChart());
    throttleChart->setChart(throttleGraph->getChart());
    pitchChart->setChart(pitchGraph->getChart());
    rollChart->setChart(rollGraph->getChart());
    yawChart->setChart(yawGraph->getChart());

    ui->graph_3->setChart(data_3);
    ui->graph_5->setChart(data_5);

    QVBoxLayout *vLayout = new QVBoxLayout();

    vLayout->addWidget(altChart);
    vLayout->addWidget(throttleChart);
    vLayout->addWidget(pitchChart);
    vLayout->addWidget(rollChart);
    vLayout->addWidget(yawChart);

    QWidget *container = new QWidget;
    container->setLayout(vLayout);
    */
    // ui->graphs->setWidget(container);

    return true;
}

void FlightGraphs::updateGraphs(const TelemetryData &data) {
    scatter->updateGraph(QVector3D(data.getXPos(), data.getYPos(), data.getZPos()));
    xVelGraph->updateGraph(QPointF(data.getTimestamp(), data.getXVel()));
    yVelGraph->updateGraph(QPointF(data.getTimestamp(), data.getYVel()));
    zVelGraph->updateGraph(QPointF(data.getTimestamp(), data.getZVel()));
}
