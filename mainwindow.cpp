#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    /* Google drive v3.5.9.tar.xz file */
//    QString fileId = "1CqiXkpQCgW5x2F0StN7yYqCtXt1dJYE-";
//    QUrl url("https://drive.google.com/uc?id=" + fileId);

    /* Demo 50mb .rar file */
//    QUrl url("https://sample-videos.com/zip/50mb.zip");

    // Demo 60mb pdf file
    QUrl url("https://collections.lib.utah.edu/file?id=423522");
    QNetworkRequest request(url);
    request.setTransferTimeout(100000);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(request);

    connect(reply, &QNetworkReply::downloadProgress, ui->progressBar, [=](qint64 bytesReceived, qint64 bytesTotal){
        ui->progressBar->setValue((bytesReceived * 100) / bytesTotal);
    });
    connect(reply, &QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal) {
        qDebug() << "Download progress: " << bytesReceived << "/" << bytesTotal;
    });


    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

//    QString downloadsPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "\\demo.xz";
    QString downloadsPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "\\demo.pdf";

    QFile file(downloadsPath);

    if (reply->error() == QNetworkReply::NoError) {
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
        }
        qDebug() << "File saved to " << file.fileName();
    } else {
        qDebug() << "Error: " << reply->errorString();
    }

    reply->deleteLater();
}
