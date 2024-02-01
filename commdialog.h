#ifndef COMMDialog_H
#define COMMDialog_H

// #include "receiverthread.h"

#include <QDialog>

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

private slots:
    // void startReceiver();
    // void showRequest(const QString &s);
    // void processError(const QString &s);
    // void processTimeout(const QString &s);
    void activateRunButton();

private:
    int m_transactionCount = 0;
    QLabel *m_serialPortLabel = nullptr;
    QComboBox *m_serialPortComboBox = nullptr;
    QLabel *m_trafficLabel = nullptr;
    QLabel *m_statusLabel = nullptr;
    QPushButton *m_runButton = nullptr;

    // ReceiverThread m_thread;
};

#endif // COMMDialog_H
