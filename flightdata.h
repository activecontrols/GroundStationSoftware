#ifndef FLIGHTDATA_H
#define FLIGHTDATA_H

#include <QWidget>

namespace Ui {
class FlightData;
}

class FlightData : public QWidget
{
    Q_OBJECT

public:
    explicit FlightData(QWidget *parent = nullptr);
    ~FlightData();

private slots:
    void on_launchButton_clicked();

private:
    Ui::FlightData *ui;
    bool initialize();
};

#endif // FLIGHTDATA_H
