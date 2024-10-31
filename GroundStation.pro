QT    += core gui serialport datavisualization charts multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += pages\
               graphs\
               widgets\

SOURCES += \
    axesinputhandler.cpp \
    camera.cpp \
    commdialog.cpp \
    pages/serialconnection.cpp \
    widgets/controlsystemstatewidget.cpp \
    graphs/linegraph.cpp \
    graphs/myq3dscatter.cpp \
    logwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    pages/flightdata.cpp \
    pages/flightgraphs.cpp \
    scatterdatamodifier.cpp \
    telemetrydata.cpp \
    telemetrymodel.cpp

HEADERS += \
    axesinputhandler.h \
    camera.h \
    commdialog.h \
    pages/serialconnection.h \
    widgets/controlsystemstatewidget.h \
    graphs/linegraph.h \
    graphs/myq3dscatter.h \
    logwindow.h \
    mainwindow.h \
    pages/flightdata.h \
    pages/flightgraphs.h \
    scatterdatamodifier.h \
    telemetrydata.h \
    telemetrymodel.h


FORMS += \
    controlsystemstatewidget.ui \
    flightdata.ui \
    flightgraphs.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    README.md \
    .gitignore

