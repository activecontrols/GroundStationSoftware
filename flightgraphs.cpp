#include "flightgraphs.h"
#include "ui_flightgraphs.h"

#include "myq3dscatter.h"
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QtCharts/QLineSeries>
#include <QBrush>

FlightGraphs::FlightGraphs(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightGraphs)
{
    ui->setupUi(this);

    MyQ3DScatter scatter;

    if (!scatter.initialize()) {
        QMessageBox::warning(nullptr, "MyQ3DScatter", "Couldn't initialize the OpenGL context.");
    }
    ui->gridLayout->removeWidget(ui->placeholder);
    ui->gridLayout->addWidget(scatter.scatterWidget(), 0, 0, 2, 2);

    if (!initialize2DGraphs()) {
        QMessageBox::warning(nullptr, "2D Graphs", "Couldn't properly initalize.");
    }


}

FlightGraphs::~FlightGraphs()
{
    delete ui;
}

bool FlightGraphs::initialize2DGraphs() {
    QLineSeries *line_series_1 = new QLineSeries();
    QLineSeries *line_series_2 = new QLineSeries();
    QLineSeries *line_series_3 = new QLineSeries();
    QLineSeries *line_series_4 = new QLineSeries();
    QLineSeries *line_series_5 = new QLineSeries();
    
    QChart *data_1 = new QChart();
    QChart *data_2 = new QChart();
    QChart *data_3 = new QChart();
    QChart *data_4 = new QChart();
    QChart *data_5 = new QChart();
    
    data_1->legend()->hide();
    data_1->addSeries(line_series_1);
    data_1->createDefaultAxes();
    data_1->axes(Qt::Horizontal).back()->setRange(0, 10);
    data_1->axes(Qt::Vertical).back()->setRange(-10, 10);
    data_1->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    data_1->axes(Qt::Vertical).back()->setTitleText("Throttle");
    
    data_2->legend()->hide();
    data_2->addSeries(line_series_2);
    data_2->createDefaultAxes();
    data_2->axes(Qt::Horizontal).back()->setRange(0, 10);
    data_2->axes(Qt::Vertical).back()->setRange(-10, 10);
    data_2->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    data_2->axes(Qt::Vertical).back()->setTitleText("Altitude");
    
    data_3->legend()->hide();
    data_3->addSeries(line_series_3);
    data_3->createDefaultAxes();
    data_3->axes(Qt::Horizontal).back()->setRange(0, 10);
    data_3->axes(Qt::Vertical).back()->setRange(-10, 10);
    data_3->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    data_3->axes(Qt::Vertical).back()->setTitleText("How High I am");
    
    data_4->legend()->hide();
    data_4->addSeries(line_series_4);
    data_4->createDefaultAxes();
    data_4->axes(Qt::Horizontal).back()->setRange(0, 10);
    data_4->axes(Qt::Vertical).back()->setRange(-10, 10);
    data_4->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    data_4->axes(Qt::Vertical).back()->setTitleText("How High I am");
    
    data_5->legend()->hide();
    data_5->addSeries(line_series_5);
    data_5->createDefaultAxes();
    data_5->axes(Qt::Horizontal).back()->setRange(0, 10);
    data_5->axes(Qt::Vertical).back()->setRange(-10, 10);
    data_5->axes(Qt::Horizontal).back()->setTitleText("Time (sec)");
    data_5->axes(Qt::Vertical).back()->setTitleText("How High I am");
    
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
    data_4->setAnimationOptions(QChart::AllAnimations);
    data_5->setAnimationOptions(QChart::AllAnimations);
    ui->graph_1->setChart(data_1);
    ui->graph_2->setChart(data_2);
    ui->graph_3->setChart(data_3);
    ui->graph_4->setChart(data_4);
    ui->graph_5->setChart(data_5);

    return true;
}
