#ifndef COMMDialog_H
#define COMMDialog_H

// #include "receiverthread.h"

#include <QDialog>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

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
    const QSerialPort* getSerial() const;

private slots:
    void onConnectButtonClicked();
    void updateSerialPorts();

signals:
    void updateSerial(QSerialPort *serial);

private:
    int m_transactionCount = 0;
    QComboBox *m_serialPortComboBox = nullptr;
    QList<QSerialPortInfo> m_serialPortList;
    QSerialPort* m_serial;
    QTimer *m_scanTimer;
    QPushButton *m_connectButton = nullptr;
    QLabel *m_serialPortLabel = nullptr;
    QLabel *m_trafficLabel = nullptr;
    QLabel *m_statusLabel = nullptr;






    // ReceiverThread m_thread;
};

#endif // COMMDialog_H
