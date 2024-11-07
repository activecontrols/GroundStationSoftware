#ifndef COMMDialog_H
#define COMMDialog_H

// #include "receiverthread.h"

#include <QDialog>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QUdpSocket>
#include <QLineEdit>

QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QPushButton;

QT_END_NAMESPACE

class CommDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CommDialog(QWidget *parent = nullptr);
    virtual ~CommDialog();
    const QSerialPort* getSerial() const;

private slots:
    void onConnectButtonClicked();
    void updateSerialPorts();

signals:
    void updateSerial(QSerialPort *serial, QUdpSocket* socket);

private:
    int m_transactionCount = 0;
    QComboBox *m_serialPortComboBox = nullptr;
    QList<QSerialPortInfo> m_serialPortList;
    QSerialPort* m_serial;
    QUdpSocket* m_socket;
    QTimer *m_scanTimer;
    QPushButton *m_connectButton = nullptr;
    QLineEdit* m_socketPortInput = nullptr;
    QLabel *m_serialPortLabel = nullptr;
    QLabel *m_udpPortLabel = nullptr;
    QLabel *m_trafficLabel = nullptr;
    QLabel *m_statusLabel = nullptr;






    // ReceiverThread m_thread;
};

#endif // COMMDialog_H
