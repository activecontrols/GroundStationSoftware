#ifndef MYQ3DSCATTER_H
#define MYQ3DSCATTER_H

#include <QtCore/qobject.h>
#include <QtDataVisualization/q3dscatter.h>

#include "axesinputhandler.h"
#include "qwidget.h"

class MyQ3DScatter : public QWidget
{
    Q_OBJECT
public:
    explicit MyQ3DScatter(QWidget *parent = nullptr);
    ~MyQ3DScatter();

public slots:
    void updateGraph(QVector3D data);

private:
    Q3DScatter *scatterGraph = nullptr;
    AxesInputHandler *inputHandler = nullptr;

    bool initialize();
    void toggleTimeRange();
};

#endif
