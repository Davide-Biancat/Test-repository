#include "arduinoreader.h"
#include <iostream>
#include <sys/time.h>

#define MESSAGE_LENGHT 12 //Message lenght from arduino in bytes

using namespace std;

long elapsed_ms(struct timeval start, struct timeval end)
{
  return static_cast<long> ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}
/*
bool _checkToken(QSerialPort *s,const string&token)
{
    qDebug() <<s->read(1);
    if(s->peek(1).toStdString()[0] == '#')
    {
        for(int i = 0; i < token.size(); i++)
        {
            if(s->read(1).toStdString()[0] != token[i])return false;
        }
        return true;
    }
    return false;
}

bool _syncrhonize(QSerialPort *serial, int connectionTimeoutMS)
{
    timeval t0;
    timeval t1,t2;

    gettimeofday(&t0,NULL);

    serial->write("#s00");

    gettimeofday(&t1,NULL);
    while(true)
    {
        if(_checkToken(serial,string("#SYNCH00\r\n")))
            return true;
        gettimeofday(&t2,NULL);
        if(elapsed_ms(t1,t2) > 200)// >200ms
        {
            serial->write("#s00");
            t1 = t2;//Leggermente sbagliato, meglio: gettimeofday(t1,NULL);
        }
        if(elapsed_ms(t0,t2) > connectionTimeoutMS)
            return false;
    }


}*/

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
    //qDebug() <<"ARDUINOREADER: Requested synch token!";
}
/*
void ArduinoReader::requestSynToken(char *token)
{

}

void ArduinoReader::removeNonNumberLeftChars(QString &s) //BAD function
{
    int l = s.size() - 1;
    for(int i = 0; i < l &&( s[i] <= 48 || s[i] >= 57 ); i++)
    {
        s[i] = ' ';
    }
}*/

void ArduinoReader::serialRead()
{
   /* if(!synched)
    {
        qDebug() << "Waiting sync";
        arduino->clear();
        //arduino->write("#s00");//Request synch token
        synched = _syncrhonize(arduino,5000);
    }
    else
    {*/
        if(arduino->bytesAvailable() >= qint64(MESSAGE_LENGHT))
        {
            buffer = arduino->readAll();

            float t[3];
            char *returnFloat = (char*) & t;
            for(i = 0; i < MESSAGE_LENGHT; i++) //C++ Float has the same endianess of C, java not though
                returnFloat[i] = (char)buffer[i];

            qDebug() << "buffer size: "<<buffer.size();
            qDebug() <<"Floats: "<<t[0]<<'\t'<<t[1]<<'\t'<<t[2];
            arduino->clear();
            arduino->write("#f");

        }
    /*    else
        {
            synched = false;
        }
    }*/
}
