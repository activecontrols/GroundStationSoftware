#include "myq3dscatter.h"

#include <Q3DTheme>
#include <iostream>
const int lowerNumberOfItems = 50;

MyQ3DScatter::MyQ3DScatter(QWidget *parent)
    : Q3DScatter(),
    m_itemCount(lowerNumberOfItems)
{
    setResizeMode(QQuickWidget::SizeRootObjectToView);
    QScatterDataProxy *proxy = new QScatterDataProxy;
    scat_series = new QScatter3DSeries(proxy);
    scat_array = new QScatterDataArray;
    *scat_array << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
    scat_series->dataProxy()->addItems(*scat_array);
    addSeries(scat_series);

    ptrToDataArray = &scat_array->first();

    Q3DTheme *theme = new Q3DTheme(Q3DTheme::ThemeArmyBlue);
    setActiveTheme(theme);
}

int MyQ3DScatter::getItemCount() {
    return m_itemCount;
}

void MyQ3DScatter::addData(qreal x, qreal y, qreal z) {
    axisX()->setTitle("X");
    axisY()->setTitle("Y");
    axisZ()->setTitle("Z");

    scat_array->resize(m_itemCount);
    ptrToDataArray->setPosition(QVector3D(x, y, z));
    seriesList().at(0)->dataProxy()->resetArray(scat_array);
    ptrToDataArray++;
    std::cout << "New point" << std::endl;
}
