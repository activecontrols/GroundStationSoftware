#ifndef FLIGHTGRAPHS_H
#define FLIGHTGRAPHS_H

#include <QWidget>

namespace Ui {
class FlightGraphs;
}

class FlightGraphs : public QWidget
{
    Q_OBJECT

public:
    explicit FlightGraphs(QWidget *parent = nullptr);
    ~FlightGraphs();

    bool initialize2DGraphs();

private:
    Ui::FlightGraphs *ui;
};

#endif // FLIGHTGRAPHS_H
