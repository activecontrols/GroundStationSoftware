#include "serialconnection.h"


SerialConnection::SerialConnection(QWidget *parent)
    : QWidget{parent},
    m_serial{ new QSerialPort(this) },
    m_scanTimer{ new QTimer(this) },
    m_connectButton{ new QPushButton("Connect", this) },
    m_comboBox { new QComboBox(this) }
{
    this->setWindowTitle("Serial Connection");
    updateSerialPorts();

    m_scanTimer->setInterval(5000);
    m_scanTimer->start();

    connect(m_scanTimer, &QTimer::timeout,
            this, &SerialConnection::updateSerialPorts);

    connect(m_connectButton, &QPushButton::clicked,
            this, &SerialConnection::onConnectButtonClicked);

    layout = new QVBoxLayout();
    layout->addWidget(m_connectButton);
    layout->addWidget(m_comboBox);
    setLayout(layout);
    setStyleSheet("background-color: white;");
}

SerialConnection::~SerialConnection()
{
    delete layout;
}


void SerialConnection::onConnectButtonClicked()
{
    m_connectButton->setEnabled(false);
    QString serialLoc  =  m_comboBox->currentData().toString();

    if (m_serial->isOpen())
    {
        qDebug() << "Serial already connected, disconnecting!";
        m_serial->close();
    }
    else
    {
        m_serial->setPortName(serialLoc);
        m_serial->setBaudRate(QSerialPort::Baud115200);
        m_serial->setDataBits(QSerialPort::Data8);
        m_serial->setParity(QSerialPort::NoParity);
        m_serial->setStopBits(QSerialPort::OneStop);
        m_serial->setFlowControl(QSerialPort::NoFlowControl);
        if(m_serial->open(QIODevice::ReadWrite)) {
            qDebug() << "SERIAL: OK!";
        } else {
            qDebug() << "SERIAL: ERROR!";
        }
        m_connectButton->setEnabled(true);
    }
    emit updateSerial(m_serial);
}

void SerialConnection::updateSerialPorts()
{
    m_serialPortList = QSerialPortInfo::availablePorts();

    m_comboBox->clear();
    for (QSerialPortInfo& port : m_serialPortList) {
        m_comboBox->addItem(port.portName(), port.systemLocation());
    }
}

const QSerialPort* SerialConnection::getSerial() const
{
    return m_serial;
}


