#ifndef CONTROLSYSTEMSTATEWIDGET_H
#define CONTROLSYSTEMSTATEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QSpacerItem>
#include <telemetrydata.h>

namespace Ui {
class ControlSystemStateWidget;
}

class ControlSystemStateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlSystemStateWidget(QWidget *parent = nullptr);
    ~ControlSystemStateWidget();

    void updateData(const TelemetryData &data);
signals:

private:
    Ui::ControlSystemStateWidget *ui;
};

#endif // CONTROLSYSTEMSTATEWIDGET_H
