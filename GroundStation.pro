QT    += core gui serialport datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    axesinputhandler.cpp \
    commdialog.cpp \
    customformatter.cpp \
    flightdata.cpp \
    flightgraphs.cpp \
    logwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    myq3dscatter.cpp \
    scatterdatamodifier.cpp

HEADERS += \
    axesinputhandler.h \
    commdialog.h \
    customformatter.h \
    flightdata.h \
    flightgraphs.h \
    logwindow.h \
    mainwindow.h \
    myq3dscatter.h \
    scatterdatamodifier.h

FORMS += \
    flightdata.ui \
    flightgraphs.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    README.md
