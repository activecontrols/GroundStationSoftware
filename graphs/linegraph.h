#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QObject>
#include <QtCharts/QLineSeries>

class LineGraph : public QObject
{
    Q_OBJECT
public:
    explicit LineGraph(QObject *parent = nullptr);

    void initialize(QString, QString);
    QChart *getChart() { return chart; }

    void addData(qreal, qreal);
private:
    QLineSeries *series;
    QChart *chart;
    QList<QPointF> *list;
    bool autoScroll = true;


signals:
};

#endif // LINEGRAPH_H
