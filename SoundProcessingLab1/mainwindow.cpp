#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QtMultimedia/QSound>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QtEndian>
#include <QDataStream>
#include <QByteArray>
#include <QtMultimedia/QAudioFormat>

QString fileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::readWavData(signed short *ramBuffer)
{
    QFile wavFile(fileName);
    if (!wavFile.open(QFile::ReadOnly)) {
        qDebug() << "Failed to open WAV file...";
        return -1; // Done
    }

}

void MainWindow::on_openFile_pushButton_clicked()
{
    if(fileName.length() == 0)
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                "C:/Users/Mateusz/Documents/Szkola/Sound Processing/Lab1/artificial/med",
                                                //QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                tr("Sound files (*.wav);;All files (*.*)"));
    else
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                fileName,
                                                tr("Sound files (*.wav);;All files (*.*)"));
}

void MainWindow::on_playFile_pushButton_clicked()
{
    QSound::play(fileName);
}

void MainWindow::on_psa_pushButton_clicked()
{
    if(fileName.length() == 0) {
        QMessageBox::warning(this, "Warning", "No .wav file selected.", QMessageBox::Ok);
        return;
    }
    signed short *buffer = new signed short [100000];
    readWavData(buffer);
}
