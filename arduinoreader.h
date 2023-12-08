#ifndef ARDUINOREADER_H
#define ARDUINOREADER_H

#include <QtSerialPort>
#include <QByteArray>
#include <cstdint>

#define MESSAGE_LENGHT 51 //2B GD_t, 6B gyro, 6B accel, 12B magnetometer, 12B accel ypr, 12B kalman ypr + 1 ending
#define SERIAL_BAUD_RATE 115200

class ArduinoReader : public QObject
{
    Q_OBJECT
public:
    ArduinoReader(QString arduino_port_name);
    ~ArduinoReader();

signals:
    void gotNewVals(uint16_t dtus, int16_t* gyroRates, int16_t* accel, float* accelAngles, float* magn); //Would be more consinstent to swap accelAngles with magn
    void updateGUI(float* rpy);
    void initFilter(int16_t* accel, float* magn);
private:

    QString arduino_port_name;
    QSerialPort *arduino;

    bool firstIteration = true;

    uint16_t GD_t = 0;
    int16_t gyroRate[3];
    int16_t accel[3];
    float magn[3];
    float accelAngs[3];
    float filteredAngs[3];

private slots:
    void serialRead();
    void connectToArduino();

protected:
    int i,k; //Used in serialRead

};

#endif // ARDUINOREADER_H
