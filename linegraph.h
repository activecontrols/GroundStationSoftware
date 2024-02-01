#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QWidget>
#include <QChartView>

namespace Ui {
class LineGraph;
}

class LineGraph : public QChartView
{
    Q_OBJECT

public:
    explicit LineGraph(QWidget *parent = nullptr);
    ~LineGraph();

private:
    Ui::LineGraph *ui;
};

#endif // LINEGRAPH_H
