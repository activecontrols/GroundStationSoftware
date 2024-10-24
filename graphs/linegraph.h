#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QObject>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

class LineGraph : public QObject
{
    Q_OBJECT
public:
    explicit LineGraph(QObject *parent = nullptr);

    void label(QString title, QString yAxisLabel);
    QChart *getChart() { return chart; }

public slots:
    void updateGraph(QPointF data);


private:
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;

    qreal minY = -10.0f;
    qreal maxY = 10.0f;

    float sampleRange = 100.0f;
    bool autoScroll = true;


signals:
};

#endif // LINEGRAPH_H
