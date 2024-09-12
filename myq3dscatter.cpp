#include "myq3dscatter.h"
#include "scatterdatamodifier.h"

#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qcommandlinkbutton.h>

using namespace Qt::StringLiterals;

MyQ3DScatter::MyQ3DScatter()
{
    m_scatterGraph = new Q3DScatter();
}

MyQ3DScatter::~MyQ3DScatter() = default;

bool MyQ3DScatter::initialize()
{
    if (!m_scatterGraph->hasContext())
        return false;

    m_scatterWidget = new QWidget;
    auto *vLayout = new QVBoxLayout(m_scatterWidget);
    m_container = QWidget::createWindowContainer(m_scatterGraph, m_scatterWidget);
    m_container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_container->setFocusPolicy(Qt::StrongFocus);
    vLayout->addWidget(m_container, 1);

    QSlider *timeSlider = new QSlider(Qt::Orientation::Horizontal);
    timeSlider->setSliderDown(false);
    timeSlider->setTickInterval(5);
    timeSlider->setTickPosition(QSlider::TicksAbove);

    vLayout->addWidget(timeSlider);

    static auto *modifier = new ScatterDataModifier(m_scatterGraph, this);

    QObject::connect(timeSlider, &QSlider::valueChanged, modifier, &ScatterDataModifier::toggleTimeStamp);

    // QObject::connect(cameraButton, &QCommandLinkButton::clicked, modifier,
    //                  &ScatterDataModifier::changePresetCamera);
    // QObject::connect(itemCountButton, &QCommandLinkButton::clicked, modifier,
    //                  &ScatterDataModifier::toggleItemCount);

    QObject::connect(m_scatterGraph, &Q3DScatter::shadowQualityChanged, modifier,
                     &ScatterDataModifier::shadowQualityUpdatedByVisual);

    QObject::connect(this, &MyQ3DScatter::receiveChange, modifier, &ScatterDataModifier::addData);

    return true;
}

void MyQ3DScatter::addData()
{
    qDebug() << "Run";
    // m_scatterGraph->seriesList().at(0)->dataProxy()->addItem();
}

void MyQ3DScatter::receiveChange()
{
    qDebug() << "CHANGED";
}
