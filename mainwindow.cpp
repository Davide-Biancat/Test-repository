#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

/*#include <QSerialPortInfo>
#include <arduinoreader.h>
#include <math.h>
#include <qmath.h>*/


#define PI 3.14159265

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) //Cercare arduino, lanciare un thread ArduinoReader, ricevere da ArduinoReader informazioni per aggionare l' UI
{

    ui->setupUi(this);

    unitsOnScreen = 10;
    unitLenghtInms = 1000; //1 uniti = 1000 milliseconds
    //notPos = QVector<double> (9,0);
    raw_readings = QVector<double> (9,0);
    raw_accAngs = QVector<double> (3,0);
    //offsets = QVector<double> (9,0);
    LBS = QVector<double> (3,0);
    currGraph = 0;
    filters = QVector<Worker> (3);
    for(int i = 0; i < 3; i++)
        filters[i].setAccGain(0.02);

    LBS[0] = 230; //Accelerometer LBS
    LBS[1] = 14.375;//Gyroscope 14.375
    LBS[2] = 230;//Magnetometer
    //offsets[2] = 192;
    //offsets[4] = 20;

    QObject::connect(this, SIGNAL(xRotationChanged(int)), ui->openGLWidget, SLOT(setXRotation(int)));
    QObject::connect(this, SIGNAL(yRotationChanged(int)), ui->openGLWidget, SLOT(setYRotation(int)));
    QObject::connect(this, SIGNAL(zRotationChanged(int)), ui->openGLWidget, SLOT(setZRotation(int)));


    ui->accX_label->setStyleSheet("QLabel { color : blue; }");
    ui->gyroX_label->setStyleSheet("QLabel{ color : blue; }");
    ui->magX_label->setStyleSheet("QLabel { color : blue; }");

    ui->accY_label->setStyleSheet("QLabel { color : green; }");
    ui->gyroY_label->setStyleSheet("QLabel{ color : green; }");
    ui->magY_label->setStyleSheet("QLabel { color : green; }");

    ui->accZ_label->setStyleSheet("QLabel { color : red; }");
    ui->gyroZ_label->setStyleSheet("QLabel{ color : red; }");
    ui->magZ_label->setStyleSheet("QLabel{ color : red; }");

    ui->accX_label->setText("");
    ui->accY_label->setText("");
    ui->accZ_label->setText("");
    ui->gyroX_label->setText("");
    ui->gyroY_label->setText("");
    ui->gyroZ_label->setText("");
    ui->magX_label->setText("");
    ui->magY_label->setText("");
    ui->magZ_label->setText("");

//======================plotWidget 1 Setup==================================

    //X line
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setPen(QPen(QColor(0,0,255)));

    //Y line
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(1)->setPen(QPen(Qt::green));

    //Z line
    ui->plotWidget->addGraph();
    ui->plotWidget->graph(2)->setPen(QPen(Qt::red));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plotWidget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget->yAxis2, SLOT(setRange(QCPRange)));



//======================plotWidget 2 Setup==================================
    //X line
    ui->plotWidget_2->addGraph();
    ui->plotWidget_2->graph(0)->setPen(QPen(Qt::blue));

    //Y line
    ui->plotWidget_2->addGraph();
    ui->plotWidget_2->graph(1)->setPen(QPen(Qt::green));

    //Z line
    ui->plotWidget_2->addGraph();
    ui->plotWidget_2->graph(2)->setPen(QPen(Qt::red));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plotWidget_2->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_2->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget_2->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_2->yAxis2, SLOT(setRange(QCPRange)));

    lastUpdateTime = timeAtStart = QDateTime::currentDateTime().toMSecsSinceEpoch();

}



void MainWindow::updateWindowData(const QVector<QString> &v)
{

    //qDebug() << "MAINWINDOW: updateGraph";
    ui->accX_label->setText("raw_accelX = " + v[0]);
    ui->accY_label->setText("raw_accelY = " + v[1]);
    ui->accZ_label->setText("raw_accelZ = " + v[2]);
    ui->gyroX_label->setText("raw_gyroX = " + v[3]);
    ui->gyroY_label->setText("raw_gyroY = " + v[4]);
    ui->gyroZ_label->setText("raw_gyroZ = " + v[5]);
    ui->magX_label->setText("raw_magX = " + v[6]);
    ui->magY_label->setText("raw_magY = " + v[7]);
    ui->magZ_label->setText("raw_magZ = " + v[8]);

    for(int i = 0; i < 9; i++)
        raw_readings[i] = v[i].toDouble()/LBS[i<4?0:(i<7?1:2)];

//----------------------------- plot 1 ------------------------------------------
    //qDebug() << "MAINWINDOW: updateGraph 2";
    // add data to lines:
    double key = (QDateTime::currentDateTime().toMSecsSinceEpoch() - timeAtStart)/unitLenghtInms;
    ui->plotWidget->graph(0)->addData(key, raw_readings[currGraph]);
    ui->plotWidget->graph(1)->addData(key, raw_readings[currGraph+1]);
    ui->plotWidget->graph(2)->addData(key, raw_readings[currGraph+2]);

    // remove data of lines that's outside visible range:
    ui->plotWidget->graph(0)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget->graph(1)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget->graph(2)->removeDataBefore(key-unitsOnScreen);

    // rescale value (vertical) axis to fit the current data:

    ui->plotWidget->graph(0)->rescaleValueAxis();
    ui->plotWidget->graph(1)->rescaleValueAxis(true);
    ui->plotWidget->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data:
    ui->plotWidget->xAxis->setRange(key,unitsOnScreen,Qt::AlignRight);

    ui->plotWidget->replot();
//----------------------------- plot 2 -----------------------------------------



    raw_accAngs[0] = std::atan(raw_readings[0]/std::sqrt(raw_readings[1]*raw_readings[1]+raw_readings[2]*raw_readings[2]))*180/PI;
    raw_accAngs[1] = std::atan(raw_readings[1]/std::sqrt(raw_readings[0]*raw_readings[0]+raw_readings[2]*raw_readings[2]))*180/PI;
    raw_accAngs[2] = std::atan(raw_readings[2]/std::sqrt(raw_readings[1]*raw_readings[1]+raw_readings[0]*raw_readings[0]))*180/PI;

    /*
    [0] += temp[0]*cos(notPos[3]) + temp[1]*sin(notPos[4]) - temp[2]*sin(notPos[5]);
    [1] += temp[1]*cos(notPos[4]) - temp[0]*sin(notPos[3]) + temp[2]*sin(notPos[5]);
    [2] += temp[2]*cos(notPos[5]) - temp[1]*sin(notPos[4]) + temp[0]*sin(notPos[3]);
    */

    double dt = QDateTime::currentDateTime().toMSecsSinceEpoch() - lastUpdateTime;
    lastUpdateTime  = QDateTime::currentDateTime().toMSecsSinceEpoch();

    filters[0].complemetaryFilter(raw_readings[0],dt,raw_accAngs[0]);
    filters[1].complemetaryFilter(raw_readings[1],dt,raw_accAngs[1]);
    filters[2].complemetaryFilter(raw_readings[2],dt,raw_accAngs[2]);

    emit xRotationChanged(filters[0].getCurrAngle());
    emit yRotationChanged(filters[1].getCurrAngle());
    emit zRotationChanged(filters[2].getCurrAngle());

    ui->plotWidget_2->graph(0)->addData(key,filters[0].getCurrAngle());
    ui->plotWidget_2->graph(1)->addData(key,filters[1].getCurrAngle());
    ui->plotWidget_2->graph(2)->addData(key,filters[2].getCurrAngle());

    qDebug() <<"dt: " << dt << "filter[0]: " << filters[0].getCurrAngle() << "filter[1]: " << filters[1].getCurrAngle() << "filter[2]: " << filters[2].getCurrAngle();

    // remove data of lines that's outside visible range:
    ui->plotWidget_2->graph(0)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_2->graph(1)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_2->graph(2)->removeDataBefore(key-unitsOnScreen);

    // rescale value (vertical) axis to fit the current data:

    ui->plotWidget_2->graph(0)->rescaleValueAxis();
    ui->plotWidget_2->graph(1)->rescaleValueAxis(true);
    ui->plotWidget_2->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plotWidget_2->xAxis->setRange(key,unitsOnScreen,Qt::AlignRight);

    ui->plotWidget_2->replot();
}

void MainWindow::on_pushButton_clicked()
{
    unitLenghtInms = ui->textEdit->toPlainText().toFloat();
    unitsOnScreen = ui->textEdit_2->toPlainText().toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_changeGraph_clicked()
{
    switch (currGraph)
    {
        case 0: currGraph +=3;
                ui->changeGraph->setText("Gyroscope");
                break;

        case 3: currGraph +=3;
                ui->changeGraph->setText("Magnetometer");
                break;

        case 6: currGraph = 0;
                ui->changeGraph->setText("Accelerometer");
                break;
    }
    ui->plotWidget->graph(0)->clearData();
    ui->plotWidget->graph(1)->clearData();
    ui->plotWidget->graph(2)->clearData();
}

