#include "commdialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSerialPortInfo>

CommDialog::CommDialog(QWidget *parent) :
    QDialog(parent),
    m_serialPortComboBox(new QComboBox),
    m_serial{ new QSerialPort(this) },
    m_scanTimer{ new QTimer(this) },
    m_connectButton{ new QPushButton("Connect", this) },
    m_serialPortLabel(new QLabel(tr("Serial port:"))),
    m_trafficLabel(new QLabel(tr("No traffic."))),
    m_statusLabel(new QLabel(tr("Status: Not running.")))
{
    updateSerialPorts();

    m_scanTimer->setInterval(5000);
    m_scanTimer->start();

    connect(m_scanTimer, &QTimer::timeout,
            this, &CommDialog::updateSerialPorts);

    connect(m_connectButton, &QPushButton::clicked,
            this, &CommDialog::onConnectButtonClicked);

    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(m_serialPortLabel, 0, 0);
    mainLayout->addWidget(m_serialPortComboBox, 0, 1);
    mainLayout->addWidget(m_connectButton, 0, 2, 2, 1);
    mainLayout->addWidget(m_trafficLabel, 3, 0, 1, 4);
    mainLayout->addWidget(m_statusLabel, 4, 0, 1, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("COM Port Connection"));
    m_serialPortComboBox->setFocus();
}


void CommDialog::onConnectButtonClicked()
{
    m_connectButton->setEnabled(false);
    QString serialLoc  =  m_serialPortComboBox->currentData().toString();

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
    }
    m_connectButton->setEnabled(true);
    emit updateSerial(m_serial);
}

void CommDialog::updateSerialPorts()
{
    m_serialPortList = QSerialPortInfo::availablePorts();

    m_serialPortComboBox->clear();
    for (QSerialPortInfo& port : m_serialPortList) {
        m_serialPortComboBox->addItem(port.portName(), port.systemLocation());
    }
}

const QSerialPort* CommDialog::getSerial() const
{
    return m_serial;
}
