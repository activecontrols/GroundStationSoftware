#include "connection.h"

Connection::Connection()
{
    connect(m_serial, &QSerialPort::readyRead, this, [&](){ emit readyRead(); });
    connect(m_socket, &QSerialPort::readyRead, this, [&](){ emit readyRead(); });
}

// initializing connection to either serial or socket
// prioritize serial, so if serial is connected, set pointer to udp socket to null
void Connection::init(QSerialPort* serial, QUdpSocket* socket)
{
    m_serial = serial;
    if (m_serial != nullptr && !m_serial->isOpen())
    {
        m_serial = nullptr;
        m_socket = socket;
    }
    else
        m_socket = nullptr;
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

