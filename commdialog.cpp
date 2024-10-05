#include "commdialog.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSerialPortInfo>

CommDialog::CommDialog(QWidget *parent) :
    QDialog(parent),
    m_serialPortLabel(new QLabel(tr("Serial port:"))),
    m_serialPortComboBox(new QComboBox),
    m_trafficLabel(new QLabel(tr("No traffic."))),
    m_statusLabel(new QLabel(tr("Status: Not running."))),
    m_runButton(new QPushButton(tr("Start")))
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
        m_serialPortComboBox->addItem(info.portName());

    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(m_serialPortLabel, 0, 0);
    mainLayout->addWidget(m_serialPortComboBox, 0, 1);
    mainLayout->addWidget(m_runButton, 0, 2, 2, 1);
    mainLayout->addWidget(m_trafficLabel, 3, 0, 1, 4);
    mainLayout->addWidget(m_statusLabel, 4, 0, 1, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("COM Port Connection"));
    m_serialPortComboBox->setFocus();

    // connect(m_runButton, &QPushButton::clicked, this, &CommDialog::startReceiver);
    // connect(&m_thread, &ReceiverThread::request, this,&CommDialog::showRequest);
    // connect(&m_thread, &ReceiverThread::error, this, &CommDialog::processError);
    // connect(&m_thread, &ReceiverThread::timeout, this, &CommDialog::processTimeout);

    connect(m_serialPortComboBox, &QComboBox::currentIndexChanged, this, &CommDialog::activateRunButton);
}

// void CommDialog::startReceiver()
// {
//     m_runButton->setEnabled(false);
//     m_statusLabel->setText(tr("Status: Running, connected to port %1.")
//                                .arg(m_serialPortComboBox->currentText()));
//     // m_thread.startReceiver(m_serialPortComboBox->currentText());
// }

// void CommDialog::showRequest(const QString &s)
// {
//     m_trafficLabel->setText(tr("Traffic, transaction #%1:"
//                                "\n\r-request: %2"
//                                "\n\r-response: %3")
//                                 .arg(++m_transactionCount)
//                                 .arg(s)
//                                 .arg(m_responseLineEdit->text()));
// }

// void CommDialog::processError(const QString &s)
// {
//     activateRunButton();
//     m_statusLabel->setText(tr("Status: Not running, %1.").arg(s));
//     m_trafficLabel->setText(tr("No traffic."));
// }

// void CommDialog::processTimeout(const QString &s)
// {
//     m_statusLabel->setText(tr("Status: Running, %1.").arg(s));
//     m_trafficLabel->setText(tr("No traffic."));
// }

void CommDialog::activateRunButton()
{
    m_runButton->setEnabled(true);
}
