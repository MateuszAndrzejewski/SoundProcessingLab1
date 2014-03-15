#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QtMultimedia/QSound>
#include <QString>

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

void MainWindow::on_pushButton_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0),
                                                    tr("Sound files (*.wav);;All files (*.*)"));
}

void MainWindow::on_pushButton_2_clicked()
{
    QSound::play(fileName);
}
