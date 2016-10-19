#include "worker.h"
#include "libs/Eigen/Dense"
#include <QVector>
#include <QDebug>
#include <iostream>

//using namespace Eigen;

Worker::Worker()
{
    compAngle = 0;
    gK = 0.98;
    aK = 0.02;

    A.setIdentity(3,3);
    P.setIdentity(3,3);
    K.setIdentity(3,3);
    H.setIdentity(3,3);
    C.setIdentity(3,3);
    I.setIdentity(3,3);

    Q(0) = 0.38;
    Q(1) = 0;
    Q(2) = 0;

    for(int i = 0; i < 3; i++)
    {
        x(i) = 0;
    }

}

Worker::Worker(const Worker &w)
{
    compAngle = w.compAngle;
    gK = w.gK;
    aK = w.aK;
}

double Worker::getCurrAngle()
{
    return compAngle;
}

void Worker::setGyroGain(double gain)
{
    if(gain > 1)
    {
        qDebug() << "setGyroGain: Illegal gain(bigger than 1)";
        return;
    }
    if(gain < 0)
    {
        qDebug() << "setGyroGain: Illegal gain(smaller than 0";
        return;
    }
    gK = gain;
    aK = 1 - gain;
}

void Worker::setAccGain(double gain)
{
    if(gain > 1)
    {
        qDebug() << "setAccGain: Illegal gain(bigger than 1)";
        return;
    }
    if(gain < 0)
    {
        qDebug() << "setAccGain: Illegal gain(smaller than 0";
        return;
    }
    aK = gain;
    gK = 1 - gain;
}

void Worker::estimateNewPos(const double acc,int dtInms)
{
    z(2) = acc;
    z(1) += acc*dtInms;
    z(0) += z(1)*dtInms;
    predictEstimate(dtInms);
    update();
}

void Worker::predictEstimate(double dtInms)
{

    A(0,1)=A(1,2)=dtInms;
    A(0,2)=(dtInms*dtInms)/2;
    x=A*xPrev;

    P = A*PPrev*A.transpose() + Q;

}

void Worker::update()
{
    K = P*H.transpose()*((H*P*H.transpose() + R).inverse());
    x = x + K*(C*z-H*x);
    P = (I-K*H)*P;
    xPrev = x;
    PPrev = P;
}

double Worker::complemetaryFilter(double gyroData,double dTs, double accData)
{
    //qDebug() << "GyroData: " << gyroData << " AccData: " << accData;
    return compAngle = gK * (compAngle + gyroData * dTs) + aK * accData;
}

