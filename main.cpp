#include "mainwindow.h"

#include <QApplication>
#include <QtWidgets/qmessagebox.h>

using namespace Qt::StringLiterals;

int main(int argc, char **argv)
{
    qputenv("QSG_RHI_BACKEND", "opengl");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
