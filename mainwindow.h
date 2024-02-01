#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "launchwindow.h"
#include "commdialog.h"

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

    void startClock();
    void showCOMConnected();
    void showSuccessfulMemAlloc();
    void showUnsuccessfulMemAlloc();

private:
    Ui::MainWindow *ui;
    LaunchWindow *lw;
    CommDialog *cd;

private slots:
    void on_upload_telem_clicked();
    void on_launch_button_released();
    void on_connect_action_triggered();
};
#endif // MAINWINDOW_H
