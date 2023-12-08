#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

#define ARDUINO_VENDOR_ID  5824 //<-Teensy 3.6//1027 //1659 //9025
#define ARDUINO_PRODUCT_ID 1155 //<-Teensy 3.6//24597 //8963 //67

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    qRegisterMetaType<QVector< QString > >("QVector<QString>");
    qRegisterMetaType<int16_t>("int16_t");
    qRegisterMetaType<int16_t>("uint16_t");


    //======================Cerco Arduino================================

    bool arduino_available = false;
    QString arduino_port_name = "";
    while(!arduino_available)
    {
        qDebug() << "Number of available ports: "<< QSerialPortInfo::availablePorts().length();
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
        {
            qDebug() <<"Port name: " << serialPortInfo.portName();
            qDebug() << " -Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
            if(serialPortInfo.hasVendorIdentifier())
            qDebug() << " -Vendor ID: "<< serialPortInfo.vendorIdentifier();
            qDebug() << " -Has product ID: " << serialPortInfo.hasProductIdentifier();
            if(serialPortInfo.hasProductIdentifier())
            qDebug() << " -Product ID: "<< serialPortInfo.productIdentifier();
         }
        foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())//Cerco arduino
        {
            if(/*serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier() && */
                 serialPortInfo.vendorIdentifier() == ARDUINO_VENDOR_ID && serialPortInfo.productIdentifier() == ARDUINO_PRODUCT_ID)//Trovato arduino
            {
                arduino_port_name = serialPortInfo.portName();
                arduino_available = true;
            }
        }
        if(arduino_available)
        {
            qDebug() << "Found an arduino";
            ArduinoReader* arduinoReader = new ArduinoReader(arduino_port_name);
            Worker* worker = new Worker();

            qDebug() << "MAIN: Attempting to connect signal & slots";

            QObject::connect(arduinoReader,SIGNAL(initFilter(int16_t*,float*)),worker,SLOT(initFilter(int16_t*,float*)));
            QObject::connect(arduinoReader,SIGNAL(gotNewVals(uint16_t, int16_t*, int16_t*, float*, float*)),worker, SLOT(work(uint16_t, int16_t*, int16_t*, float*, float*)));
            QObject::connect(worker,SIGNAL(newData(uint16_t, int16_t*, float*, float*)),&window, SLOT(updateWindowData(uint16_t, int16_t*, float*, float*)));

            QThread* arduinoReaderThread = new QThread;
            QThread* workerThread = new QThread;



            worker->moveToThread(workerThread);
            arduinoReader->moveToThread(arduinoReaderThread); //Sposto l' ArduinoReader su un'altro thread

            //QObject::connect(workerThread,SIGNAL(started()),workerThread,SLOT(connectToArduino()));
            QObject::connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
            QObject::connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

            QObject::connect(arduinoReaderThread,SIGNAL(started()),arduinoReader,SLOT(connectToArduino()));
            QObject::connect(arduinoReaderThread, SIGNAL(finished()), arduinoReaderThread, SLOT(deleteLater()));


            workerThread->start();
            arduinoReaderThread->start();
            qDebug() << "MAIN: Done connecting signal & slots, ArduinoReader moved on a new thread";

            window.show();
        }
        else
        {
            //give error message if not avaibale
            qDebug () << "Port error, couldn't find an arduino";
            //w.deleteLater();
        }
        QThread::msleep(1000);
    }

return a.exec();
}
