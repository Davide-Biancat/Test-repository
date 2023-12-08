#include "arduinoreader.h"
#include <iostream>
#include <sys/time.h>

using namespace std;

long elapsed_ms(struct timeval start, struct timeval end)
{
  return static_cast<long> ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

ArduinoReader::ArduinoReader(QString serial_name)//Passo il nome della porta sulla quale c'è arduino
{
    //qDebug() << "ARDUINOREADER: Constructor called";
    arduino_port_name = serial_name;
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
    arduino->setBaudRate(SERIAL_BAUD_RATE);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    //qDebug() << "ARDUINOREADER: serial connection setup done";

    QThread::msleep(2000);//Wait 2 sec
    QObject::connect(arduino,SIGNAL(readyRead()),this, SLOT(serialRead()));

    arduino->clear();
    arduino->write("i");
    arduino->flush();
    qDebug()<<"requested first frame";
}

void ArduinoReader::serialRead()
{  
    if(arduino->bytesAvailable() >= MESSAGE_LENGHT)
    {
        i = 0;

        GD_t = (uint16_t)((arduino->read(1)[0] & 0xff) | ((arduino->read(1)[0] & 0xff)<<8));
        for(k = 0; k < 3; k++)
          gyroRate[k] = (int16_t)((arduino->read(1)[0] & 0xff) | (arduino->read(1)[0] & 0xff)<<8);
        for(k = 0; k < 3; k++)
          accel[k] = (int16_t)((arduino->read(1)[0] & 0xff) | (arduino->read(1)[0] & 0xff)<<8);
        for(k = 0; k < 3; k++)
          magn[k] = (float)((arduino->read(1)[0] & 0xff) | (arduino->read(1)[0] & 0xff)<<8 | (arduino->read(1)[0] & 0xff)<<16 | (arduino->read(1)[0] & 0xff)<<24);

        for(k = 0; k < 3; k++)
          accelAngs[k] = (float)((arduino->read(1)[0] & 0xff) | (arduino->read(1)[0] & 0xff)<<8 | (arduino->read(1)[0] & 0xff)<<16 | (arduino->read(1)[0] & 0xff)<<24);
        for(k = 0; k < 3; k++)
          filteredAngs[k] = (float)((arduino->read(1)[0] & 0xff) | (arduino->read(1)[0] & 0xff)<<8 | (arduino->read(1)[0] & 0xff)<<16 | (arduino->read(1)[0] & 0xff)<<24);

        if(arduino->read(1)[0] == '\n'&& !firstIteration)
        {
            emit gotNewVals(GD_t, gyroRate, accel, accelAngs, magn);
            emit updateGUI(filteredAngs);
        }
        else if(firstIteration)
        {
            emit initFilter(accel, magn);
            firstIteration = false;
        }
        /*qDebug()<<"GD_t: "<<(int)GD_t<<"\tgyro:\t"<<gyroRate[0]<<"\t"<<gyroRate[1]<<"\t"<<gyroRate[2]<<
                  "\taccel: "<<accel[0]<<"\t"<<accel[1]<<"\t"<<accel[2]<<
                  "\tmagn: "<<magn[0]<<"\t"<<magn[1]<<"\t"<<magn[2];*/
        arduino->clear();
        arduino->write("i");
    }
    QThread::msleep(5);

}
