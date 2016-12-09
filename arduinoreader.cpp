#include "arduinoreader.h"
#include <iostream>
#include <sys/time.h>

#define MESSAGE_LENGHT 24 //Message lenght from arduino in bytes

using namespace std;

long elapsed_ms(struct timeval start, struct timeval end)
{
  return static_cast<long> ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

ArduinoReader::ArduinoReader(QString serial_name)//Passo il nome della porta sulla quale c'è arduino
{
    //qDebug() << "ARDUINOREADER: Constructor called";
    arduino_port_name = serial_name;
    sensorData = QVector<QString>(9,"");
    //buffer.resize(MESSAGE_LENGHT);
    synched = false;
    i=0;
}

ArduinoReader::~ArduinoReader()
{
    if(arduino!=NULL)
        if(arduino->isOpen())
            arduino->close();
}

void ArduinoReader::connectToArduino() //Setup
{
    //qDebug() << "ARDUINOREADER: setting up serial connection";
    arduino = new QSerialPort;
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud57600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    //qDebug() << "ARDUINOREADER: serial connection setup done";

    //qDebug() << "ARDUINOREADER: Signals & slots connetcted";

    QThread::msleep(2000);//Wait 2 sec
    //qDebug() << "ARDUINOREADER: Synchyng up";

    //buffer = arduino->readAll(); //Clear buffer
    //qDebug() <<"ARDUINOREADER: Requesting synch token!";
    arduino->write("#o0#ob#oe0");//Disable continuos output stream, output in bynary mode, disable error message output
    arduino->clear();
    arduino->write("#f");
    QObject::connect(arduino,SIGNAL(readyRead()),this, SLOT(serialRead()));
}

void ArduinoReader::serialRead()
{
    if(arduino->bytesAvailable() >= qint64(MESSAGE_LENGHT))
    {
        buffer = arduino->readAll();

        float t[MESSAGE_LENGHT/4];
        char *returnFloat = (char*) & t;
        for(i = 0; i < MESSAGE_LENGHT; i++) //C++ Float has the same endianess of C, java not though
            returnFloat[i] = (char)buffer[i];

        emit gotNewVals(t);
        qDebug() << "buffer size: "<<buffer.size();
        qDebug() <<"Floats: "<<t[0]<<'\t'<<t[1]<<'\t'<<t[2]<<'\t'<<t[3]<<'\t'<<t[4]<<'\t'<<t[5];
        arduino->clear();
        arduino->write("#f");

    }

}
