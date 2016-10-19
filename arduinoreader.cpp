#include "arduinoreader.h"
#include <iostream>

ArduinoReader::ArduinoReader(QString serial_name)//Passo il nome della porta sulla quale c'è arduino
{
    qDebug() << "ARDUINOREADER: Constructor called";
    arduino_port_name = serial_name;
    sensorData = QVector<QString>(9,"");
    i=0;
}

ArduinoReader::~ArduinoReader()
{
    if(arduino!=NULL)
        if(arduino->isOpen())
            arduino->close();
}

void ArduinoReader::connectToArduino()
{
    qDebug() << "ARDUINOREADER: My thread got started, setting up serial connection";
    arduino = new QSerialPort;
    arduino->setPortName(arduino_port_name);
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud57600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "ARDUINOREADER: My thread got started, serial connection setup done";

    qDebug() << "ARDUINOREADER: Signals & slots connetcted";
    arduino->write("#o1");//Enable output stream
    arduino->write("#ob 4");//1: accelerometer, 2:magnetometer, 3:gyroscope ,4: $ax,ay,az,gx,gy,gz,mx,my,mz
    qDebug() << "ARDUINOREADER: Sent serial commands, listenig serial";
    QThread::msleep(1000);//Wait 1 sec
    buffer = arduino->readAll();

    arduino->flush();
    QObject::connect(arduino,SIGNAL(readyRead()),this, SLOT(serialRead()));
}

void ArduinoReader::removeNonNumberLeftChars(QString &s) //BAD function
{
    int l = s.size() - 1;
    for(int i = 0; i < l &&( s[i] <= 48 || s[i] >= 57 ); i++)
    {
        s[i] = ' ';
    }
}

void ArduinoReader::serialRead()
{
    if(arduino->canReadLine())
    {
        buffer = arduino->readLine();

        xyz = buffer.split(',');
        //qDebug() <<"xyz size:"<< xyz.size();
        int k = (xyz.size()>9)?9:xyz.size();
        //if(xyz.size() == 9)
        //{
            for(i = 0; i < k && k == 9; i++)
                sensorData[i] = xyz[i];
            sensorData[0][1] = ' ';
            //qDebug() << "buffer:" << buffer;
            //qDebug() << "x: " << sensorData[0];
            //removeNonNumberLeftChars(sensorData[0]);
            emit gotNewVals(sensorData);
        //}
        buffer = "";
    }
}
