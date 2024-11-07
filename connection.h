#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QUdpSocket>

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection();
    QByteArray readAll();
    QByteArray writeAll(const QByteArray& data);
    void init(QSerialPort* serial, QUdpSocket* udpfd);
signals:
    void readyRead();

private:
    QSerialPort* m_serial = nullptr;
    QUdpSocket* m_socket = nullptr;
};

#endif // CONNECTION_H
