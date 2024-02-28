#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtCharts>
#include <QtCharts/QLineSeries>
#include <QtGraphs>
#include<QtGraphs/QScatter3DSeries>

namespace Ui {
class LaunchWindow;
}

class LaunchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();
    double time_d = 0;
    double update_time = 1; // in seconds

    int x_range_1 = 10;
    int y_range_1 = 50;
private:
    Ui::LaunchWindow *ui;
    QTimer *timer;
    QChart *data_1;

    QLineSeries *line_series_1;

    void updateClock();
    void updateGraph();
};

#endif // LAUNCHWINDOW_H
