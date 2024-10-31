#include "flightdata.h"
#include <QGraphicsProxyWidget>

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>

FlightData::FlightData(QWidget *parent)
    : QWidget(parent)
{
    // QPixmap logo_image{":/assets/PSP-AC-1Color-white.png"};
    // int w = logo->width();
    // int h = logo->height();
    // ui->logo->setPixmap(logo_image.scaled(w, h, Qt::KeepAspectRatio));
    // initialize();

    graphicsView = new QGraphicsView();
    graphicsView->setMinimumSize(1000, 775);
    scene = new QGraphicsScene();
    graphicsView->setScene(scene);

    // Create the QVideoWidget for displaying the live camera feed
    videoWidget = new QVideoWidget();
    // Set Video Widget to be the size of the parent
    videoWidget->setMinimumSize(graphicsView->width(), graphicsView->height());

    // Create the camera and the medi   a capture session
    // camera = new QCamera(this);
    // captureSession = new QMediaCaptureSession(this);

    // Set up the capture session to use the camera and the video sink
    // captureSession->setCamera(camera);
    // captureSession->setVideoOutput(videoWidget);

    // Start the camera (important for live feed)
    // camera->start();

    // Add the QVideoWidget to the scene
    QGraphicsProxyWidget *videoProxy = scene->addWidget(videoWidget);
    videoProxy->setPos(0, 0);

    controlSystemStateWidget = new ControlSystemStateWidget();
    controlSystemStateWidget->setAttribute(Qt::WA_StyledBackground, true);
    QGraphicsProxyWidget *controlSystemStateProxy = scene->addWidget(controlSystemStateWidget);
    controlSystemStateProxy->setPos(graphicsView->width() - controlSystemStateWidget->width() - 10, 0);

    QPushButton *toggleButton = new QPushButton("Hide");
    toggleButton->setStyleSheet("font: 12pt 'Bahnschrift'; color: rgb(218, 170, 0); background-color:black");
    QGraphicsProxyWidget *toggleButtonProxy = scene->addWidget(toggleButton);
    toggleButtonProxy->setPos(graphicsView->width() - toggleButton->width() - 10, 0);

    connect(toggleButton, &QPushButton::clicked, [this, toggleButton]() {
        if (controlSystemStateWidget->isVisible()) {
            controlSystemStateWidget->hide();
            toggleButton->setText("Show");
        } else {
            controlSystemStateWidget->show();
            toggleButton->setText("Hide");
        }
    });

    // Set up the layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(graphicsView);
    setLayout(layout);
    setStyleSheet("background-color: black;");
}

void FlightData::on_launchButton_clicked()
{
    // LAUNCH
    qDebug() << "To Infinity and Beyond";
}

void FlightData::updateChecks(qreal battery) {
    if (battery < 0) {
        qDebug() << "Battery dead";
        // ui->mark_1->setPixmap(checkmark);
    }
    else {
        // ui->mark_1->setPixmap();
    }
}

void FlightData::uploadTelem(qreal k_val, qreal p_val, qreal n_val, qreal m_val, qreal N_val) {
    // ui->k_data->setText(QString::number(k_val));
    // ui->p_data->setText(QString::number(p_val));
    // ui->n_data->setText(QString::number(n_val));
    // ui->m_data->setText(QString::number(m_val));
    // ui->N_data->setText(QString::number(N_val));
}

void FlightData::on_uploadButton_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Upload Telemetry", QDir::homePath());
    QFile file(file_name);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Not readable", "File couldn't be read");
    }

    QTextStream in(&file);
    QString text = in.readAll();

    // Read in telemetry to change values on screen as well as send to teensy

    // qreal k_val = text.toDouble();
    // qreal p_val = text.toDouble();
    // qreal n_val = text.toDouble();
    // qreal m_val = text.toDouble();
    // qreal N_val = text.toDouble();
    // uploadTelem(k_val, p_val, n_val, m_val, N_val);
}

void FlightData::updateTelemetryDisplay(const TelemetryData &data)
{
    // qDebug() << "Updating telemetry display";
    controlSystemStateWidget->updateData(data);
}
