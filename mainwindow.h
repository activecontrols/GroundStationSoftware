#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "commdialog.h"
#include "QTimer"
#include "logwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void updateClock();
    // void showCOMConnected();
    // void showSuccessfulMemAlloc();
    // void showUnsuccessfulMemAlloc();

private:
    Ui::MainWindow *ui;
    LogWindow *logWindow;
    CommDialog *commDialog;
    QTimer *timer;

private slots:
    // void on_upload_telem_clicked();
    // void on_launch_button_released();
    // void on_connect_action_triggered();
    // void on_log_action_triggered();
    void on_actionFlight_Graphs_triggered();
    void on_actionFlight_Data_triggered();
    void on_actionConnect_triggered();
    void on_actionFlight_Logs_triggered();
};
#endif // MAINWINDOW_H
