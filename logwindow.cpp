#include "logwindow.h"

#include <QGridLayout>
#include <QScrollBar>
#include <QTextStream>
#include <QFont>
#include <QDebug>

LogWindow::LogWindow(QWidget *parent)
    : QDialog(parent),
    m_logFile(new QFile("Saved Messages")),
    m_logMessages(new QPlainTextEdit(tr("Log Messages")))
{
    setStyleSheet("QPlainTextEdit {font: 10pt 'Times'}");
    auto mainLayout = new QGridLayout;
    m_logMessages->setReadOnly(true);
    mainLayout->addWidget(m_logMessages);
    setLayout(mainLayout);
    setBaseSize(QSize(100, 100));

    setWindowTitle(tr("Comm Messages"));

    // connect();
}

void LogWindow::addCOMConnected()
{
    addLog("COM connected");
}

void LogWindow::addCOMDisconnected()
{
    addLog("COM disconnected");
}

void LogWindow::addSuccessfulMemAlloc() {
    addLog("Successful Memory Allocation");
}

void LogWindow::addUnsuccessfulMemAlloc() {
    addLog("Unsuccessful Memory Allocation");
}

void LogWindow::addLog(const QString& text)
{
    m_logFile->open(QIODevice::WriteOnly);
    if (!m_logFile->isOpen()) {
        qDebug() << "Could not load file";
        return;
    }
    QTextStream stream(m_logFile);
    stream << text;
    m_logMessages->appendPlainText(text); // Adds the message to the widget
    m_logMessages->verticalScrollBar()->setValue(m_logMessages->verticalScrollBar()->maximum());
    m_logFile->close();
    // optional if you want to see the changes
    // after appendPlainText() immediately
    // useful if you use this->appendMessage() in a loop
    // QDialog::processEvents();
}
