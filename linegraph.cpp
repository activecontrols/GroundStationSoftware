#include "linegraph.h"
#include "ui_linegraph.h"

#include <QtWidgets/QMainWindow>

// Widget used to display charts
#include <QtCharts/QChartView>

// Displays the color used to represent each
// QBarSet
#include <QtCharts/QLegend>

// Used to create a line chart
#include <QtCharts/QLineSeries>

// Used to change names on axis
#include <QtCharts/QCategoryAxis>

LineGraph::LineGraph(QWidget *parent)
    : QChartView(parent)
    , ui(new Ui::LineGraph)
{
    ui->setupUi(this);

    QLineSeries *series = new QLineSeries();
    series->append(0, 16);
    series->append(1, 25);
    series->append(2, 24);
    series->append(3, 19);
    series->append(4, 33);
    series->append(5, 25);
    series->append(6, 34);

    // Create chart, add data, hide legend, and add axis
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Customize the title font
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle("Gyroscopes");

    // Change the line color and weight
    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    // Change the x axis categories
    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("0",0);
    axisX->append("1",1);
    axisX->append("2",2);
    axisX->append("3",3);
    axisX->append("4",4);
    axisX->append("5",5);
    axisX->append("6",6);
    chart->setAxisX(axisX, series);

    setChart(chart);
}

LineGraph::~LineGraph()
{
    delete ui;
}
