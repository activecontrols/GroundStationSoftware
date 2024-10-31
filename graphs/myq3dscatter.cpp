#include "myq3dscatter.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qcommandlinkbutton.h>
#include <QMessageBox>

using namespace Qt::StringLiterals;

MyQ3DScatter::MyQ3DScatter(QWidget *parent) :
    QWidget(parent),
    scatterGraph(new Q3DScatter),
    inputHandler(new AxesInputHandler(scatterGraph))
{
    if (!initialize()) {
        QMessageBox::warning(nullptr, "MyQ3DScatter", "Couldn't initialize the OpenGL context.");
    }

    scatterGraph->activeTheme()->setType(Q3DTheme::ThemeStoneMoss);
    scatterGraph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftHigh);
    scatterGraph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    scatterGraph->scene()->activeCamera()->setZoomLevel(100.f);

    auto *proxy = new QScatterDataProxy;
    auto *series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat(u"@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"_s);
    series->setMeshSmooth(false);
    series->setBaseColor(QRgb(0xC29700));
    series->setMesh(QAbstract3DSeries::MeshSphere);
    series->setItemSize(0.1);
    scatterGraph->addSeries(series);
    scatterGraph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

    scatterGraph->axisX()->setTitle("X (meters)");
    scatterGraph->axisY()->setTitle("Y (meters)");
    scatterGraph->axisZ()->setTitle("Z (meters)");

    // Give ownership of the handler to the graph and make it the active handler
    scatterGraph->setActiveInputHandler(inputHandler);

    // Give our axes to the input handler
    inputHandler->setAxes(scatterGraph->axisX(), scatterGraph->axisZ(), scatterGraph->axisY());
}

MyQ3DScatter::~MyQ3DScatter() = default;

bool MyQ3DScatter::initialize()
{
    if (!scatterGraph->hasContext())
        return false;

    auto *vLayout = new QVBoxLayout(this);
    QWidget *container = QWidget::createWindowContainer(scatterGraph, this);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);
    vLayout->addWidget(container, 1);

    QSlider *timeSlider = new QSlider(Qt::Orientation::Horizontal);
    timeSlider->setSliderDown(false);
    timeSlider->setTickInterval(5);
    timeSlider->setTickPosition(QSlider::TicksAbove);

    vLayout->addWidget(timeSlider);

    // static auto *modifier = new ScatterDataModifier(m_scatterGraph, this);

    // QObject::connect(timeSlider, &QSlider::valueChanged, modifier, &ScatterDataModifier::toggleTimeStamp);

    // QObject::connect(cameraButton, &QCommandLinkButton::clicked, modifier,
    //                  &ScatterDataModifier::changePresetCamera);
    // QObject::connect(itemCountButton, &QCommandLinkButton::clicked, modifier,
    //                  &ScatterDataModifier::toggleItemCount);

    // QObject::connect(this, &MyQ3DScatter::updateGraph, modifier, &ScatterDataModifier::addData);

    return true;
}

void MyQ3DScatter::updateGraph(QVector3D data)
{
    // qDebug() << "Update graph";
    scatterGraph->seriesList().at(0)->dataProxy()->addItem(data);
}

void MyQ3DScatter::toggleTimeRange()
{
    qDebug() << "Toggle time range";
    // scatterGraph->seriesList().at(0)->dataProxy()->removeItem(0);
}
