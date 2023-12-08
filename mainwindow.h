#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <libs/QCustomPlot/qcustomplot.h>
#include "arduinoreader.h"
#include "worker.h"

#include <QMainWindow>
#include <QSerialPortInfo>
#include <math.h>
#include <qmath.h>
#include <cstring>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateWindowData(uint16_t, int16_t*, float*, float*);//
    void setGyroAngles(float x, float y, float z);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    double timeAtStart,unitLenghtInms,lastUpdateTime;
    float gyroAngs[3];

    int unitsOnScreen;

signals:
    xRotationChanged(int);
    yRotationChanged(int);
    zRotationChanged(int);
};

#endif // MAINWINDOW_H
