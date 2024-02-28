#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
#include <QFile>
#include <QPlainTextEdit>

namespace Ui {
class LogWindow;
}

class LogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogWindow(QWidget *parent = nullptr);
public slots:
    void addLog(const QString &s);
    void addCOMConnected();
    void addSuccessfulMemAlloc();
    void addUnsuccessfulMemAlloc();
private:
    QFile *m_logFile = nullptr;
    QPlainTextEdit *m_logMessages = nullptr;

};

#endif // LOGWINDOW_H
