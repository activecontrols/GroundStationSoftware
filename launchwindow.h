#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QtCharts>
#include <QtCharts/QLineSeries>

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
    double update_time = 0.5; // in seconds

    int x_range_1 = 10;
    int y_range_1 = 50;
    int x_range_2 = 10;
    int y_range_2 = 50;
    int x_range_3 = 10;
    int y_range_3 = 50;

private:
    Ui::LaunchWindow *ui;
    QTimer *timer;
    QChart *data_1;
    QChart *data_2;
    QChart *data_3;

    QLineSeries *line_series_1;
    QLineSeries *line_series_2;
    QLineSeries *line_series_3;

    void updateClock();
    void updateGraph();
};

#endif // LAUNCHWINDOW_H
