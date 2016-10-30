#ifndef ARDUINOREADER_H
#define ARDUINOREADER_H

#include <QtSerialPort>
#include <QByteArray>
#include <cstdint>

class ArduinoReader : public QObject
{
    Q_OBJECT
public:
    ArduinoReader(QString arduino_port_name);
    ~ArduinoReader();

signals:
    void gotNewVals(const QVector<QString>&);

private:

    QString arduino_port_name;
    QSerialPort *arduino;
    QByteArray buffer;
    QVector<QString> sensorData;
    QList<QString> xyz;

private slots:
    void serialRead();
    void connectToArduino();

protected:
    void removeNonNumberLeftChars(QString &s);
    int i;

};

#endif // ARDUINOREADER_H
