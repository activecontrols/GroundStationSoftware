#include "flightgraphs.h"
#include "ui_flightgraphs.h"
#include "myq3dscatter.h"

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
{
    ui->setupUi(this);

    scatter = new MyQ3DScatter();

    if (!scatter->initialize()) {
        QMessageBox::warning(nullptr, "MyQ3DScatter", "Couldn't initialize the OpenGL context.");
    }
    ui->gridLayout->removeWidget(ui->placeholder);
    ui->gridLayout->addWidget(scatter->scatterWidget(), 0, 0, 3, 2);

    if (!initialize2DGraphs()) {
        QMessageBox::warning(nullptr, "2D Graphs", "Couldn't properly initalize.");
    }

    temp_timer = new QTimer();
    connect(temp_timer, &QTimer::timeout, this, &FlightGraphs::updateGraphs);
    temp_timer->start(1000);
}

FlightGraphs::~FlightGraphs()
{
    delete ui;
}

bool FlightGraphs::initialize2DGraphs() {
    altGraph = new LineGraph();
    throttleGraph = new LineGraph();
    pitchGraph = new LineGraph();
    rollGraph = new LineGraph();
    yawGraph = new LineGraph();

    altChart = new QChartView();
    throttleChart = new QChartView();
    pitchChart = new QChartView();
    rollChart = new QChartView();
    yawChart = new QChartView();

    altGraph->initialize("Altitude", "meters ACL");
    throttleGraph->initialize("Throttle", "Percent");
    pitchGraph->initialize("Pitch", "meters");
    rollGraph->initialize("Roll", "meters");
    yawGraph->initialize("Yaw", "meters");

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

    ui->altChart->setChart(altGraph->getChart());
    ui->throttleChart->setChart(throttleGraph->getChart());
    ui->pitchChart->setChart(pitchGraph->getChart());
    ui->rollChart->setChart(rollGraph->getChart());
    ui->yawChart->setChart(yawGraph->getChart());

    return true;
}

void FlightGraphs::updateGraphs() {
    static int x = 0;
    if (x % 2) {
        altGraph->addData(x, 2);
    }
    else {
        altGraph->addData(x, -2);
    }
    x++;
}

void FlightGraphs::addData()
{
    scatter->addData();
}
