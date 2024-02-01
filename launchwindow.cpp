#include "launchwindow.h"
#include "ui_launchwindow.h"

#include <QGridLayout>

LaunchWindow::LaunchWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LaunchWindow)
{
    ui->setupUi(this);
}

LaunchWindow::~LaunchWindow()
{
    delete ui;
}
