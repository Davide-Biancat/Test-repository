#include "sensorsimulator.h"
#include <QDebug>

SensorSimulator::SensorSimulator()
{

}

void SensorSimulator::getNextRotation(float rotatedVector[3], int16_t raw_gyro_rates[3])
{
    totalAxisRotation += 1.0f/Hz; //(in °)  on 100Hz -> 1 adding degree per second
    rotatiaons[currAxis].rotate3DVector(rotatedVector);
    memset((void*)raw_gyro_rates,0,sizeof(raw_gyro_rates[0])*3); //6B
    raw_gyro_rates[currAxis] = (int16_t)((1.0f/Hz)*14.375f);
    if(totalAxisRotation >= 360)//Done rotating on this axis
    {
        currAxis = (currAxis == 2)?0:currAxis+1;
        totalAxisRotation = 0;
    }
    qDebug()<<"total axis rotation:"<<totalAxisRotation;
    //currRotation.rotate3DVector(rotatedVector);
    //currRotation.toEulerianAngle(euler);
}

void SensorSimulator::matrixCrossProduct3X3(float *a, float *b, float *out)
{

}

void SensorSimulator::matrixVector3DCrossProduct(float *m, float *v, float *out)
{

}
