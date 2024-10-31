#ifndef SERIALCONNECTION_H
#define SERIALCONNECTION_H

#include <QWidget>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QComboBox>

class SerialConnection : public QWidget
{
    Q_OBJECT
public:
    explicit SerialConnection(QWidget *parent = nullptr);
    ~SerialConnection();
    const QSerialPort* getSerial() const;

signals:
    void updateSerial(QSerialPort* newSerial);

private slots:
    void onConnectButtonClicked();
    void updateSerialPorts();

private:
    QSerialPort* m_serial;
    QList<QSerialPortInfo> m_serialPortList;
    QTimer* m_scanTimer;
    QPushButton* m_connectButton;
    QComboBox* m_comboBox;

    QVBoxLayout *layout;


};

#endif // SERIALCONNECTION_H
