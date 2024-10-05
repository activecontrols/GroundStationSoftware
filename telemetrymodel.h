#ifndef TELEMETRYMODEL_H
#define TELEMETRYMODEL_H

#include <QObject>

class TelemetryModel : public QObject
{
    Q_OBJECT
public:
    explicit TelemetryModel(QObject *parent = nullptr);

signals:
};

#endif // TELEMETRYMODEL_H
