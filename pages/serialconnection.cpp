#include "serialconnection.h"


SerialConnection::SerialConnection(QWidget *parent)
    : QWidget{parent},
    m_serial{ new QSerialPort(this) },
    m_scanTimer{ new QTimer(this) },
    m_connectButton{ new QPushButton("Connect", this) }
{
    this->setWindowTitle("Serial Connection");
    updateSerialPorts();

    m_scanTimer->setInterval(5000);
    m_scanTimer->start();

    connect(m_scanTimer, &QTimer::timeout,
            this, &SerialConnection::updateSerialPorts);

    connect(m_connectButton, &QPushButton::clicked,
            this, &SerialConnection::onConnectButtonClicked);

    connect(m_sendButton, &QPushButton::clicked,
            this, &SerialConnection::onSendButtonClicked);

    connect(m_serial, &QSerialPort::readyRead,
            this, &SerialConnection::serialReadyRead);

    graphicsView = new QGraphicsView();
    graphicsView->setMinimumSize(1000, 775);
    scene = new QGraphicsScene();
    graphicsView->setScene(scene);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(graphicsView);
    setLayout(layout);
    setStyleSheet("background-color: black;");
}

SerialConnection::~SerialConnection()
{

}


void SerialConnection::onConnectButtonClicked()
{

}

void SerialConnection::onSendButtonClicked()
{

}

void SerialConnection::serialReadyRead()
{

}


void SerialConnection::updateSerialPorts()
{

}

const QSerialPort* SerialConnection::getSerial() const
{
    return m_serial;
}


