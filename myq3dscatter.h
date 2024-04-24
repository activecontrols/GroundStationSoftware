#ifndef MYQ3DSCATTER_H
#define MYQ3DSCATTER_H

#include <QtCore/qobject.h>
#include <QtDataVisualization/q3dscatter.h>

class MyQ3DScatter : public QObject
{
    Q_OBJECT
public:
    MyQ3DScatter();
    ~MyQ3DScatter();

    bool initialize();
    void addData();
    QWidget *scatterWidget() { return m_scatterWidget; }


public slots:
    void receiveChange();

private:
    Q3DScatter *m_scatterGraph = nullptr;
    QWidget *m_container = nullptr;
    QWidget *m_scatterWidget = nullptr;
};

#endif
