#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <libs/QCustomPlot/qcustomplot.h>
#include "arduinoreader.h"
#include "worker.h"

#include <QMainWindow>
#include <QSerialPortInfo>
#include <math.h>
#include <qmath.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addDataToGraph(double key,double value);

public slots:
    void updateWindowData(const QVector<QString>&);

private slots:

    void on_pushButton_clicked();

    void on_changeGraph_clicked();

private:
    Ui::MainWindow *ui;

    double timeAtStart,unitLenghtInms,lastUpdateTime;
    QVector<double> notPos;
    QVector<double> raw_accAngs;
    QVector<double> raw_readings;
    QVector<double> offsets;
    QVector<double> LBS;
    int unitsOnScreen,currGraph;
    QVector<Worker> filters;

signals:
    xRotationChanged(int);
    yRotationChanged(int);
    zRotationChanged(int);
};

#endif // MAINWINDOW_H
