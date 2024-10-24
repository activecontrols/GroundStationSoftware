#include "telemetrymodel.h"
#include <QVector3D>

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
    return 26; // Number of telemetry data fields
}

QVariant TelemetryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const TelemetryData &data = telemetryDataList[index.row()];

    return QVariant();

    switch (index.column()) {
    case 0: return data.getBattery();          // Column 0: Battery
    case 1: return data.getTemperature();          // Column 1: Temperature
    case 2: return data.getTimestamp();   // Column 2: Timestamp
    case 3: return data.getXPos();          // Column 3: X Position
    case 4: return data.getYPos();          // Column 4: Y Position
    case 5: return data.getZPos();          // Column 5: Z Position
    case 6: return data.getXVel();          // Column 6: X Velocity
    case 7: return data.getYVel();          // Column 7: Y Velocity
    case 8: return data.getZVel();          // Column 8: Z Velocity
    case 9: return data.getXAcc();          // Column 9: X Acceleration
    case 10: return data.getYAcc();         // Column 10: Y Acceleration
    case 11: return data.getZAcc();         // Column 11: Z Acceleration
    case 12: return data.getAirspeed();     // Column 12: Airspeed
    case 13: return data.getVelVariance(0); // Column 13: Velocity Variance X
    case 14: return data.getVelVariance(1); // Column 14: Velocity Variance Y
    case 15: return data.getVelVariance(2); // Column 15: Velocity Variance Z
    case 16: return data.getPosVariance(0); // Column 16: Position Variance X
    case 17: return data.getPosVariance(1); // Column 17: Position Variance Y
    case 18: return data.getPosVariance(2); // Column 18: Position Variance Z
    case 19: return data.getAttitude(0);    // Column 19: Attitude W
    case 20: return data.getAttitude(1);    // Column 20: Attitude X
    case 21: return data.getAttitude(2);    // Column 21: Attitude Y
    case 22: return data.getAttitude(3);    // Column 22: Attitude Z
    case 23: return data.getRoll();          // Column 23: Roll
    case 24: return data.getPitch();         // Column 24: Pitch
    case 25: return data.getYaw();           // Column 25: Yaw
    default: return QVariant();
    }
}

QVariant TelemetryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Battery";          // Column 0: Battery
        case 1: return "Temperature";          // Column 1: Temperature
        case 2: return "Timestamp";   // Column 2: Timestamp
        case 3: return "X Position";          // Column 3: X Position
        case 4: return "Y Position";          // Column 4: Y Position
        case 5: return "Z Position";          // Column 5: Z Position
        case 6: return "X Velocity";          // Column 6: X Velocity
        case 7: return "Y Velocity";          // Column 7: Y Velocity
        case 8: return "Z Velocity";          // Column 8: Z Velocity
        case 9: return "X Acceleration";          // Column 9: X Acceleration
        case 10: return "Y Acceleration";         // Column 10: Y Acceleration
        case 11: return "Z Acceleration";         // Column 11: Z Acceleration
        case 12: return "Airspeed";     // Column 12: Airspeed
        case 13: return "Velocity Variance X"; // Column 13: Velocity Variance X
        case 14: return "Velocity Variance Y"; // Column 14: Velocity Variance Y
        case 15: return "Velocity Variance Z"; // Column 15: Velocity Variance Z
        case 16: return "Position Variance X"; // Column 16: Position Variance X
        case 17: return "Position Variance Y"; // Column 17: Position Variance Y
        case 18: return "Position Variance Z"; // Column 18: Position Variance Z
        case 19: return "Attitude W";    // Column 19: Attitude W
        case 20: return "Attitude X";    // Column 20: Attitude X
        case 21: return "Attitude Y";    // Column 21: Attitude Y
        case 22: return "Attitude Z";    // Column 22: Attitude Z
        case 23: return "Roll";          // Column 23: Roll
        case 24: return "Pitch";         // Column 24: Pitch
        case 25: return "Yaw";           // Column 25: Yaw
        default: return QVariant();
        }
    }
    return QVariant();
}

QVector<QVector3D> TelemetryModel::get3DScatterPoints() const
{
    QVector<QVector3D> points;

    for (const TelemetryData &data : telemetryDataList) {
        points.append(QVector3D(data.getXPos(), data.getYPos(), data.getZPos()));
    }

    return points;
}

void TelemetryModel::addTelemetryData(const TelemetryData &data)
{
    beginInsertRows(QModelIndex(), telemetryDataList.size(), telemetryDataList.size());
    telemetryDataList.append(data);  // Add data to the list
    endInsertRows();

    emit telemetryDataAdded(data);
}
