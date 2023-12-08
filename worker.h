#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>

#include "sensorsimulator.h"
#include "quaternion.h"
#include "math_helper.h"
//#include "libs/Eigen/Dense"

//using namespace std;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker();
    //Worker(const Worker &w);

    //TODO: add yaw correction using magnetometer
    void update(uint16_t GD_t, int16_t* newGyro, int16_t* newAccel, float* newMagn);


public slots:

    //Set starting angle;
    void initFilter(int16_t* accel, float *magn);
    //Basically update the filter and pass the results to the GUI
    void work(uint16_t dtus, int16_t* gyro, int16_t* accel, float* accelAngles, float* magn); //dtus isn't being properly read :(

private:
    int16_t dtus;
    double accel[3];
    double gyroRates[3];
    double newMagn[3];
    float temp[3] ={0,0,1};
    float Gravity[3] = {0,0,256.0f};

    Quaternion q;
    Quaternion qw;
    Quaternion qacc;
    Quaternion qmag;
    Quaternion dqacc;
    Quaternion dqmag;
    Quaternion qI;
    Quaternion Dqw;

    SensorSimulator fakeSensors;
    float matOmega[4][4] ;
    float tau;
    float alfa;

    Quaternion proportional_LERP(float alpha,Quaternion &q1, Quaternion &q2);
    Quaternion proportional_SLERP(float alpha, Quaternion &q1, Quaternion &q2);


signals:
    void newData(uint16_t, int16_t* , float*, float*);
};




#endif // WORKER_H
