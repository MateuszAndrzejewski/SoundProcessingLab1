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
#include <QThread>
#include <vector>

#include "wavfile.h"
#include "gnuplot_i.hpp"

//#define GNUPLOT "C:/gnuplot/bin"
#define GNUPLOT "D:/Narzedzia/gnuplot/bin"


QString fileName;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //set gnuplot location
    Gnuplot::set_GNUPlotPath(GNUPLOT);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector <unsigned int> MainWindow::readWavData()
{
    QVector <unsigned int> output;

    QFile wavFile(fileName);
    if (!wavFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open WAV file...";
        output.clear();
        return output;
    }

    int offset = 40;
    QByteArray buffer = wavFile.readAll(); //get all bytes in the .wav file
    QDataStream stream(buffer.mid(offset, 4)); //get the size of the data chunk
    stream.device()->reset();
    unsigned int size = 0;
    stream >> size; //convert 4 byte size of the data chunk to int

    QByteArray data = buffer.mid(offset + 4, size); //get the chunk with sound data
    for(int i = 0; i < data.size(); i = i + 4) { //loop getting sample data
        QDataStream ministream(data.mid(i, 4));
        unsigned int newDataByte;
        ministream >> newDataByte;
        output.append(newDataByte);
    }

    qDebug() << "Completed getting .wav data.";
    return output;
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

    QVector <unsigned int> data = readWavData();
    std::vector <double> x;
    std::vector <double> y;
    for(unsigned int i = 0; i < data.size(); i++) {
        y.push_back((double) data.toStdVector().at(i));
        x.push_back((double)i);
    }

    Gnuplot g1("lines");
    g1.set_title("Plot");
    g1.set_style("lines").plot_x(y, "Waveform");;

    QThread::sleep(5);
}
