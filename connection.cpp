#include "connection.h"

Connection::Connection()
{
    connect(m_serial, &QSerialPort::readyRead, this, [&](){ emit readyRead(); });
    connect(m_socket, &QSerialPort::readyRead, this, [&](){ emit readyRead(); });
}

void Connection::initSerial(QSerialPort* serial)
{
    m_serial = serial;
}

void Connection::initSocket(QUdpSocket* udpfd)
{
    m_socket = udpfd;
}

void Connection::write(const char* data)
{
    if (m_socket->isOpen())
        m_socket->write(data);
    else if (m_socket != nullptr)
        m_socket->write(data);
}

QByteArray Connection::readAll()
{
    QByteArray data;
    if (m_serial != nullptr)
    {
        data = m_serial->readAll();
    } else if (m_socket != nullptr) {

        data.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(data.data(), data.size());
    }
    return data;
 }

