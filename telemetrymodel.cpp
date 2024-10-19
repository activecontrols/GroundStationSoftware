#include "telemetrymodel.h"

#include <QObject>

TelemetryModel::TelemetryModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int TelemetryModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return telemetryDataList.size();  // Number of telemetry data points
}

int TelemetryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 15; // Number of telemetry data fields
}

QVariant TelemetryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const TelemetryData &data = telemetryDataList[index.row()];

    return QVariant();

    // switch (index.column()) {
    // case 0: return data.getAltitude();          // Column 0: Altitude
    // case 1: return data.getVelocity();          // Column 1: Velocity
    // case 2: return data.getIMUAcceleration();   // Column 2: IMU Acceleration
    // default: return QVariant();
    // }
}

QVariant TelemetryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return QString("Altitude (m)");
        case 1: return QString("Velocity (m/s)");
        case 2: return QString("IMU Acceleration (m/s²)");
        default: return QVariant();
        }
    }
    return QVariant();
}

void TelemetryModel::addTelemetryData(const TelemetryData &data)
{
    beginInsertRows(QModelIndex(), telemetryDataList.size(), telemetryDataList.size());
    telemetryDataList.append(data);  // Add data to the list
    endInsertRows();

    emit telemetryDataAdded(data);
}
