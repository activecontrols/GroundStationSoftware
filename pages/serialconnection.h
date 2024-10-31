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


private slots:
    void onConnectButtonClicked();

private:
    QSerialPort* m_serial;
    QList<QSerialPortInfo> m_serialPortList;
    QTimer* m_scanTimer;
    QPushButton* m_connectButton;
    QComboBox* m_comboBox;

    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QVBoxLayout *layout;

    void updateSerialPorts();
};

#endif // SERIALCONNECTION_H
