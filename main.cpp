#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets/qmessagebox.h>

using namespace Qt::StringLiterals;

int main(int argc, char **argv)
{
    qputenv("QSG_RHI_BACKEND", "opengl");
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(1000, 775);
    w.show();
    return a.exec();
}
