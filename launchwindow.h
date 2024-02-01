#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QMainWindow>

namespace Ui {
class LaunchWindow;
}

class LaunchWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LaunchWindow(QWidget *parent = nullptr);
    ~LaunchWindow();

private:
    Ui::LaunchWindow *ui;
};

#endif // LAUNCHWINDOW_H
