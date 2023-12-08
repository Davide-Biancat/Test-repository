#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include "quaternion.h"
#include <QObject>

#define Hz 10.0f

class SensorSimulator
{
public:
    SensorSimulator();
    void getNextRotation(float rotatedVector[3], int16_t raw_gyro_rates[3]); //ypr in radians

private:

    Quaternion currRotation;
    float rotatedZ[3] = {0,0,1};
    float totalAxisRotation = 0;
    const float X[3] = {1,0,0};
    const float Y[3] = {0,1,0};
    const float Z[3] = {0,0,1};
    Quaternion rotatiaons[3] = {Quaternion(1.0f/180.0f*PI/Hz,X),Quaternion(1.0f/180.0f*PI/Hz,Y),Quaternion(1.0f/180.0f*PI/Hz,Z)}; //100Hz -> 1 degree per second
    uint8_t currAxis = 0; //0 = X, 1 = Y, 2 = Z

    void matrixCrossProduct3X3(float* a, float* b, float* out);
    void matrixVector3DCrossProduct(float* m, float *v, float *out);


    /*
     *        1    0      0
     * Rx =   0   cosθ  -sinθ
     *        0   sinθ   cosθ
     *
     *       cosθ   0    sinθ
     * Ry =   0     1     0
     *      -sinθ   0    cosθ
     *
     *       cosθ  -sinθ  0
     * Rz =  sinθ   cosθ  0
     *        0      0    1
     */

    //float magn[3];
};

#endif // SENSORSIMULATOR_H
