#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "worker.h"

/*#include <QSerialPortInfo>
#include <arduinoreader.h>
#include <math.h>
#include <qmath.h>*/


//#define PI 3.14159265

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) //Cercare arduino, lanciare un thread ArduinoReader, ricevere da ArduinoReader informazioni per aggionare l' UI
{
    gyroAngs[0] = 0;
    gyroAngs[1] = 0;
    gyroAngs[2] = 0;

    ui->setupUi(this);

    unitsOnScreen = 10;
    unitLenghtInms = 1000; //1 uniti = 1000 milliseconds

    QObject::connect(this, SIGNAL(xRotationChanged(int)), ui->openGLWidget, SLOT(setXRotation(int)));
    QObject::connect(this, SIGNAL(yRotationChanged(int)), ui->openGLWidget, SLOT(setYRotation(int)));
    QObject::connect(this, SIGNAL(zRotationChanged(int)), ui->openGLWidget, SLOT(setZRotation(int)));


    ui->accX_label->setStyleSheet("QLabel { color : rgb(0,0,255); }"); // accel = red, kalman = purple, gyro = blue
    ui->kalmanX_label->setStyleSheet("QLabel{ color : rgb(0,128,0); }");
    ui->gyroX_label->setStyleSheet("QLabel { color : rgb(255,0,0); }");

    ui->accY_label->setStyleSheet("QLabel { color : rgb(0,150,255); }");
    ui->kalmanY_label->setStyleSheet("QLabel{ color : rgb(64,192,0); }");
    ui->gyroY_label->setStyleSheet("QLabel { color : rgb(255,128,0); }");

    ui->accZ_label->setStyleSheet("QLabel { color : rgb(0,240,255); }");
    ui->kalmanZ_label->setStyleSheet("QLabel{ color : rgb(128,255,0); }");
    ui->gyroZ_label->setStyleSheet("QLabel { color : rgb(255,200,0); }");

    ui->accX_label->setText("");
    ui->kalmanX_label->setText("");
    ui->gyroX_label->setText("");
    ui->accY_label->setText("");
    ui->kalmanY_label->setText("");
    ui->gyroY_label->setText("");
    ui->accZ_label->setText("");
    ui->kalmanZ_label->setText("");
    ui->gyroZ_label->setText("");

//======================plotWidget_X Setup==================================

    //X line
    ui->plotWidget_X->addGraph();
    ui->plotWidget_X->graph(0)->setPen(QPen(QColor(255,0,0)));

    //Y line
    ui->plotWidget_X->addGraph();
    ui->plotWidget_X->graph(1)->setPen(QPen(QColor(255,128,0)));

    //Z line
    ui->plotWidget_X->addGraph();
    ui->plotWidget_X->graph(2)->setPen(QPen(QColor(255,200,0)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plotWidget_X->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_X->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget_X->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_X->yAxis2, SLOT(setRange(QCPRange)));

//======================plotWidget_Y Setup==================================

    //X line
    ui->plotWidget_Y->addGraph();
    ui->plotWidget_Y->graph(0)->setPen(QPen(QColor(0,128,0)));

    //Y line
    ui->plotWidget_Y->addGraph();
    ui->plotWidget_Y->graph(1)->setPen(QPen(QColor(64,192,0)));

    //Z line
    ui->plotWidget_Y->addGraph();
    ui->plotWidget_Y->graph(2)->setPen(QPen(QColor(128,255,0)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plotWidget_Y->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_Y->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget_Y->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_Y->yAxis2, SLOT(setRange(QCPRange)));




//======================plotWidget_Z Setup==================================
    //X line
    ui->plotWidget_Z->addGraph();
    ui->plotWidget_Z->graph(0)->setPen(QPen(QColor(0,0,255)));

    //Y line
    ui->plotWidget_Z->addGraph();
    ui->plotWidget_Z->graph(1)->setPen(QPen(QColor(0,150,255)));

    //Z line
    ui->plotWidget_Z->addGraph();
    ui->plotWidget_Z->graph(2)->setPen(QPen(QColor(0,240,255)));


    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->plotWidget_Z->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_Z->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->plotWidget_Z->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plotWidget_Z->yAxis2, SLOT(setRange(QCPRange)));

    lastUpdateTime = timeAtStart = QDateTime::currentDateTime().toMSecsSinceEpoch();

}

void MainWindow::setGyroAngles(float x, float y, float z)
{
    gyroAngs[0] = x;
    gyroAngs[1] = y;
    gyroAngs[2] = z;
}

void MainWindow::updateWindowData(uint16_t GD_t, int16_t* gyroRates, float* accelAngs, float* filteredAngs)
{
    double key = (QDateTime::currentDateTime().toMSecsSinceEpoch() - timeAtStart)/unitLenghtInms;
    float kalmanAngs[3];

    for(uint8_t i = 0; i < 3; i++)
    {
        gyroAngs[i] += (float)gyroRates[i]/14.375f/Hz; //~10ms integration time (+- 16us)

        kalmanAngs[i] = filteredAngs[i]/PI*180.0;
    }

    ui->accX_label->setText(std::to_string(accelAngs[0]).c_str());
    ui->kalmanX_label->setText(std::to_string(kalmanAngs[0]).c_str());
    ui->gyroX_label->setText(std::to_string(gyroAngs[0]).c_str());
    ui->accY_label->setText(std::to_string(accelAngs[1]).c_str());
    ui->kalmanY_label->setText(std::to_string(kalmanAngs[1]).c_str());
    ui->gyroY_label->setText(std::to_string(gyroAngs[1]).c_str());
    ui->accZ_label->setText(std::to_string(accelAngs[2]).c_str());
    ui->kalmanZ_label->setText(std::to_string(kalmanAngs[2]).c_str());
    ui->gyroZ_label->setText(std::to_string(gyroAngs[2]).c_str());


//----------------------------- plot 1 ------------------------------------------

    // add data to lines:

    ui->plotWidget_X->graph(0)->addData(key, gyroAngs[0]);
    ui->plotWidget_X->graph(1)->addData(key, gyroAngs[1]);
    ui->plotWidget_X->graph(2)->addData(key, gyroAngs[2]);

    // remove data of lines that's outside visible range:
    ui->plotWidget_X->graph(0)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_X->graph(1)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_X->graph(2)->removeDataBefore(key-unitsOnScreen);

    // rescale value (vertical) axis to fit the current data:

    ui->plotWidget_X->graph(0)->rescaleValueAxis();
    ui->plotWidget_X->graph(1)->rescaleValueAxis(true);
    ui->plotWidget_X->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data:
    ui->plotWidget_X->xAxis->setRange(key,unitsOnScreen,Qt::AlignRight);

    ui->plotWidget_X->replot();

//----------------------------- plot 2 -----------------------------------------

    // add data to lines:
    ui->plotWidget_Y->graph(0)->addData(key, kalmanAngs[0]);
    ui->plotWidget_Y->graph(1)->addData(key, kalmanAngs[1]);
    ui->plotWidget_Y->graph(2)->addData(key, kalmanAngs[2]);

    // remove data of lines that's outside visible range:
    ui->plotWidget_Y->graph(0)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_Y->graph(1)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_Y->graph(2)->removeDataBefore(key-unitsOnScreen);

    // rescale value (vertical) axis to fit the current data:

    ui->plotWidget_Y->graph(0)->rescaleValueAxis();
    ui->plotWidget_Y->graph(1)->rescaleValueAxis(true);
    ui->plotWidget_Y->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data:
    ui->plotWidget_Y->xAxis->setRange(key,unitsOnScreen,Qt::AlignRight);

    ui->plotWidget_Y->replot();

//----------------------------- plot 3 -----------------------------------------

    // add data to lines:
    ui->plotWidget_Z->graph(0)->addData(key, accelAngs[0]);
    ui->plotWidget_Z->graph(1)->addData(key, accelAngs[1]);
    ui->plotWidget_Z->graph(2)->addData(key, accelAngs[2]);

    // remove data of lines that's outside visible range:
    ui->plotWidget_Z->graph(0)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_Z->graph(1)->removeDataBefore(key-unitsOnScreen);
    ui->plotWidget_Z->graph(2)->removeDataBefore(key-unitsOnScreen);

    // rescale value (vertical) axis to fit the current data:

    ui->plotWidget_Z->graph(0)->rescaleValueAxis();
    ui->plotWidget_Z->graph(1)->rescaleValueAxis(true);
    ui->plotWidget_Z->graph(2)->rescaleValueAxis(true);

    // make key axis range scroll with the data:
    ui->plotWidget_Z->xAxis->setRange(key,unitsOnScreen,Qt::AlignRight);

    ui->plotWidget_Z->replot();


    //qDebug()<<"euler2"<<kalmanAngs[0]<<"\t"<<kalmanAngs[1]<<"\t"<<kalmanAngs[2];
    emit xRotationChanged(/*kalmanAngs[0]*/((kalmanAngs[1] >= 0)?((int)(kalmanAngs[1]*16 + 0.5)):((int)(kalmanAngs[1]*16 - 0.5))));
    emit yRotationChanged(/*kalmanAngs[1]*/((kalmanAngs[0] >= 0)?((int)(kalmanAngs[0]*16 + 0.5)):((int)(kalmanAngs[0]*16 - 0.5))));
    emit zRotationChanged(/*kalmanAngs[2]*/((kalmanAngs[2] >= 0)?((int)(kalmanAngs[2]*16 + 0.5)):((int)(kalmanAngs[2]*16 - 0.5))));


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

