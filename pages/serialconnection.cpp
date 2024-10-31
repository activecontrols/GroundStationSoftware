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

    // graphicsView = new QGraphicsView();
    // graphicsView->setMinimumSize(1000, 775);
    // scene = new QGraphicsScene();
    // graphicsView->setScene(scene);

    // layout = new QVBoxLayout();
    // layout->addWidget(graphicsView);
    // layout->addWidget(m_connectButton);
    // layout->addWidget(m_comboBox);
    // setLayout(layout);
    // setStyleSheet("background-color: white;");
}

SerialConnection::~SerialConnection()
{
    delete scene;
    delete layout;
    delete graphicsView;
}


void SerialConnection::onConnectButtonClicked()
{

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


