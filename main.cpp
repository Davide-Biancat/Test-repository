#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

#define ARDUINO_VENDOR_ID  1027 //1659 //9025
#define ARDUINO_PRODUCT_ID 24597 //8963 //67

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    qRegisterMetaType<QVector< QString > >("QVector<QString>");
    //static const qint16 arduino_uno_vendor_id = 1027;//1659;//9025;
    //static const qint16 arduino_uno_product_id = 24597;//8963;//67;


    //======================Cerco Arduino================================

    bool arduino_available = false;
    QString arduino_port_name = "";

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

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier() && serialPortInfo.vendorIdentifier() == ARDUINO_VENDOR_ID && serialPortInfo.productIdentifier() == ARDUINO_PRODUCT_ID)
        {
            arduino_port_name = serialPortInfo.portName();
            arduino_available = true;//Trovato arduino
        }
    }

    if(arduino_available)
    {
        qDebug() << "Found an arduino";
        ArduinoReader *arduinoReader = new ArduinoReader(arduino_port_name); //istanzio un thread ArduinoReader
        qDebug() << "MAIN: Attempting to connect signal & slots";

        QObject::connect(arduinoReader,SIGNAL(gotNewVals(const QVector<QString> &)),&w, SLOT(updateWindowData(const QVector<QString> &)));

        QThread *qThread1 = new QThread;
        arduinoReader->moveToThread(qThread1);
        QObject::connect(qThread1,SIGNAL(started()),arduinoReader,SLOT(connectToArduino()));
        QObject::connect(qThread1, SIGNAL(finished()), qThread1, SLOT(deleteLater()));


        qThread1->start();
        qDebug() << "MAIN: Done connecting signal & slots, ArduinoReader started on a new thread";

        w.show();
    }
    else
    {
        //give error message if not avaibale
        qDebug () << "Port error, couldn't find an arduino";
        //w.deleteLater();
    }

return a.exec();
}
