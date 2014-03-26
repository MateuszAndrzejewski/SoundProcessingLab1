#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define GNUPLOT "D:/Narzedzia/gnuplot/bin"
//#define GNUPLOT "C:/gnuplot/bin"

#include <QMainWindow>
#include <QVector>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector <unsigned int>  readWavData();

    QString fileName;
    QVector <unsigned int> samples;
    std::vector <double> x;
    std::vector <double> y;
    
private slots:
    void on_openFile_pushButton_clicked();
    void on_playFile_pushButton_clicked();

    void on_psa_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
