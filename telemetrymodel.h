#ifndef TELEMETRYMODEL_H
#define TELEMETRYMODEL_H

#include <QAbstractTableModel>
#include "telemetrydata.h"

class TelemetryModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TelemetryModel(QObject *parent = nullptr);

    // Required overrides for QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addTelemetryData(const TelemetryData &data) {
        emit telemetryDataAdded(data);
    }
signals:
    void telemetryDataAdded(const TelemetryData &data);

private:
    QList<TelemetryData> telemetryDataList;  // List to hold telemetry data
};

#endif // TELEMETRYMODEL_H
