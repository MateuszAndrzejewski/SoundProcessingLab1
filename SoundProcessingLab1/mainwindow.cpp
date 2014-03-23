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

    // Read in the whole thing
    QByteArray wavFileContent = wavFile.readAll();
    qDebug() << "The size of the WAV file is: " << wavFileContent.size();


    // Define the header components
    char fileType[4];
    qint32 fileSize;
    char waveName[4];
    char fmtName[3];
    qint32 fmtLength;
    short fmtType;
    short numberOfChannels;
    qint32 sampleRate;
    qint32 sampleRateXBitsPerSampleXChanngelsDivEight;
    short bitsPerSampleXChannelsDivEightPointOne;
    short bitsPerSample;
    char dataHeader[4];
    qint32 dataSize;

    // Create a data stream to analyze the data
    QDataStream analyzeHeaderDS(&wavFileContent,QIODevice::ReadOnly);
    analyzeHeaderDS.setByteOrder(QDataStream::LittleEndian);

    // Now pop off the appropriate data into each header field defined above
    analyzeHeaderDS.readRawData(fileType,4); // "RIFF"
    analyzeHeaderDS >> fileSize; // File Size
    analyzeHeaderDS.readRawData(waveName,4); // "WAVE"
    analyzeHeaderDS.readRawData(fmtName,3); // "fmt"
    analyzeHeaderDS >> fmtLength; // Format length
    analyzeHeaderDS >> fmtType; // Format type
    analyzeHeaderDS >> numberOfChannels; // Number of channels
    analyzeHeaderDS >> sampleRate; // Sample rate
    analyzeHeaderDS >> sampleRateXBitsPerSampleXChanngelsDivEight; // (Sample Rate * BitsPerSample * Channels) / 8
    analyzeHeaderDS >> bitsPerSampleXChannelsDivEightPointOne; // (BitsPerSample * Channels) / 8.1
    analyzeHeaderDS >> bitsPerSample; // Bits per sample
    analyzeHeaderDS.readRawData(dataHeader,4); // "data" header
    analyzeHeaderDS >> dataSize; // Data Size

    qint32 grzybek[100000];
    for(int i = 0; i < dataSize; i++)
    {analyzeHeaderDS >> grzybek[i];

    }
    // Print the header
    qDebug() << "WAV File Header read:";
    qDebug() << "File Type: " << QString::fromUtf8(fileType);
    qDebug() << "File Size: " << fileSize;
    qDebug() << "WAV Marker: " << QString::fromUtf8(waveName);
    qDebug() << "Format Name: " << QString::fromUtf8(fmtName);
    qDebug() << "Format Length: " << fmtLength;
    qDebug() << "Format Type: " << fmtType;
    qDebug() << "Number of Channels: " << numberOfChannels;
    qDebug() << "Sample Rate: " << sampleRate;
    qDebug() << "Sample Rate * Bits/Sample * Channels / 8: " << sampleRateXBitsPerSampleXChanngelsDivEight;
    qDebug() << "Bits per Sample * Channels / 8.1: " << bitsPerSampleXChannelsDivEightPointOne;
    qDebug() << "Bits per Sample: " << bitsPerSample;
    qDebug() << "Data Header: " << QString::fromUtf8(dataHeader);
    qDebug() << "Data Size: " << dataSize;
    for(int i = 0; i < dataSize; i++)
    {
        qDebug() << grzybek[i];
    }
    // Now pull out the data
    return analyzeHeaderDS.readRawData((char*)ramBuffer,(int)dataSize);
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
