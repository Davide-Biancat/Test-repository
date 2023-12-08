#include "worker.h"
#include "libs/Eigen/Dense"
#include <QVector>
#include <QDebug>
#include <iostream>
#include <cmath>

//using namespace Eigen;
#define G 256.0f
#define TO_DEG(x) (x * 180.0f/3.1415926535897932384626433832)
#define TO_RAD(x) (x * 3.1415926535897932384626433832/180.0f)

using namespace std;
float fastInvSqrt(float x);
float fsine(float a);

void normalizeVector3D(float *v)
{
    float norm = fastInvSqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= norm;
    v[1] *= norm;
    v[2] *= norm;
}

Worker::Worker()
{
    q = Quaternion(1.0f,0.0f,0.0f,0.0f);
    qw = Quaternion(1.0f,0.0f,0.0f,0.0f);
    dqacc = Quaternion(1.0f,0.0f,0.0f,0.0f);
    dqmag = Quaternion(1.0f,0.0f,0.0f,0.0f);
    qI = Quaternion(1.0f,0.0f,0.0f,0.0f);
    qacc = Quaternion();
    qmag = Quaternion();
}
/*
Worker::Worker(const Worker &w)
       :QObject()
{
    q = Quaternion(1.0f,0.0f,0.0f,0.0f,true);
    q = Quaternion(1.0f,0.0f,0.0f,0.0f,true);
    dqacc = Quaternion(1.0f,0.0f,0.0f,0.0f,true);
    dqmag = Quaternion(1.0f,0.0f,0.0f,0.0f,true);
    qI = Quaternion(1.0f,0.0f,0.0f,0.0f,true);
}*/

void Worker::initFilter(int16_t* raw_accel, float* magn)
{
    //TODO change qI to qmag when magnetometer is implemented

    accel[0] = raw_accel[0];
    accel[1] = raw_accel[1];
    accel[2] = raw_accel[2];
    //Normalizing accel's vector
    float accelInvNorm = fastInvSqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]);
    accel[0] *= accelInvNorm;
    accel[1] *= accelInvNorm;
    accel[2] *= accelInvNorm;
    //Initial gyro's rotation quaternion is set to the accelerometer and magnetometer rotation quaternions
    //q[t0] = qacc x qmag (qacc provides  pitch and roll, qmag provides yaw);
    qDebug()<<"q0: "<<q.q[0]<<"\t"<<q.q[1]<<"\t"<<q.q[2]<<"\t"<<q.q[3]<<"\t";
    if(accel[2]>=0) //if Az >= 0, Eq. 25 is used to get the accelerometer's quaternion
        q = Quaternion(sqrt((accel[2]+1.0)/2.0), -accel[1]*fastInvSqrt(2.0*(accel[2]+1.0)), accel[0]*fastInvSqrt(2.0*(accel[2]+1.0)), 0.0)*qI; //First quaternion is qacc calculated as in eq.21
    else //if Az < 0
        q = Quaternion(-accel[1]*fastInvSqrt(2.0*(1.0-accel[2])), sqrt((1.0 - accel[2])/2.0), 0.0, accel[0]*fastInvSqrt(2.0*(1.0 - accel[2])))*qI;
    qDebug()<<"q0.5: "<<q.q[0]<<"\t"<<q.q[1]<<"\t"<<q.q[2]<<"\t"<<q.q[3]<<"\t";
}

void Worker::update(uint16_t GD_t, int16_t* newGyro, int16_t* newAccel, float* newMagn)
{
    /**/
    accel[0] = newAccel[0];
    accel[1] = newAccel[1];
    accel[2] = newAccel[2];
    gyroRates[0] = newGyro[0]/(14.375*180.0)*PI; //Converting from native gyro unit to rad/s (g/(14.375*180)*PI)
    gyroRates[1] = newGyro[1]/(14.375*180.0)*PI;
    gyroRates[2] = newGyro[2]/(14.375*180.0)*PI;

    //qDebug()<<"gyroRates(rad/s): "<<gyroRates[0]<<"\t"<<newGyro[0]/14.375<<"\t"<<gyroRates[1]<<"\t"<<newGyro[1]/14.375<<"\t"<<gyroRates[2]<<"\t"<<newGyro[2]/14.375;
    //qDebug()<<"raw accel: "<<accel[0]<<"\t"<<accel[1]<<"\t"<<accel[2]<<"\t";
    float accelInvNorm = /*fastInvSqrt*/ 1.0f/sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]);
 // qDebug()<<"accelInvNorm: "<<accelInvNorm;

    //Relative magnitude error between measured acceleration local acceleration vector and ideal gravity vector
    float erracc = (abs(sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]) - G)/G); //doing 1.0f/accelInvNorm might introduce a lot more numerical noise than recalculating the non inverted sqrt
 // qDebug()<<"erracc: "<<erracc;

    //Complementary's filter gain for accelerometer
    //     1,             erracc <0.1
    //α =  -10erracc + 2,  0.1<=erracc<0.2 (going from (0.1, 1) to (0.2, 0))
    //     0,             erracc >= 0.2
    alfa = (erracc <= 0.1)?1:((erracc >= 0.2)?0:2.0 - erracc*10.0);
    //qDebug()<<"alfa:"<<alfa;

    //Normalizing accelerometer's vector
    accel[0] *= accelInvNorm;
    accel[1] *= accelInvNorm;
    accel[2] *= accelInvNorm;
    //qDebug()<<"normalized accel module: "<<sqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]);   //

    if(accel[2]>=0) //if Az >= 0, Eq. 25 is used to get the accelerometer's quaternion
        qacc = Quaternion(sqrt((accel[2]+1.0)/2.0), -accel[1]*fastInvSqrt(2.0*(accel[2]+1.0)), accel[0]*fastInvSqrt(2.0*(accel[2]+1.0)), 0.0f); //First quaternion is qacc calculated as in (eq.21)
    else //if Az < 0
        qacc = Quaternion(-accel[1]*fastInvSqrt(2.0*(1.0-accel[2])), sqrt((1.0 - accel[2])/2.0), 0.0, accel[0]*fastInvSqrt(2.0*(1.0 - accel[2])));//(eq.23)


    //qDebug()<<"q: "<<q.q[0]<<"\t"<<q.q[1]<<"\t"<<q.q[2]<<"\t"<<q.q[3]<<"\t";
    //qDebug()<<"q mod: "<<sqrt(q.q[0]*q.q[0] + q.q[1]*q.q[1] + q.q[2]*q.q[2] + q.q[3]*q.q[3]);

    //[L<-G]qω[t] = [L<-G]q[t-1] + [L]Ω([L]ω[t]) x [L<-G]q[t-1]*Δt (Eq. 39)
    Dqw = Quaternion( q.q[1]*gyroRates[0] + q.q[2]*gyroRates[1] + q.q[3]*gyroRates[2],    //qω[t] = q[t-1] + Ωxq[t-1]*Δt
                     -q.q[0]*gyroRates[0] + q.q[2]*gyroRates[2] - q.q[3]*gyroRates[1],
                     -q.q[0]*gyroRates[1] - q.q[1]*gyroRates[2] + q.q[3]*gyroRates[0],
                     -q.q[0]*gyroRates[2] + q.q[1]*gyroRates[1] - q.q[2]*gyroRates[0]);

    qw = q + (Dqw * (GD_t*0.000001));//*/
    //qw.normalize();

    //qDebug()<<"qw: "<<qw.q[0]<<"\t"<<qw.q[1]<<"\t"<<qw.q[2]<<"\t"<<qw.q[3]<<"\t";
    //qDebug()<<"qacc: "<<qacc.q[0]<<"\t"<<qacc.q[1]<<"\t"<<qacc.q[2]<<"\t"<<qacc.q[3]<<"\t";
    //qDebug()<<"qw mod: "<<sqrt(qw.q[0]*qw.q[0] + qw.q[1]*qw.q[1] + qw.q[2]*qw.q[2] + qw.q[3]*qw.q[3]);
    //qDebug()<<"qacc mod: "<<sqrt(qacc.q[0]*qacc.q[0] + qacc.q[1]*qacc.q[1] + qacc.q[2]*qacc.q[2] + qacc.q[3]*qacc.q[3]);

    //Gravity vector calculated from gyro's data applied to accelerometer's normalized vector
    //(Eq.44)
    float gp[3];
    gp[0] = accel[0];
    gp[1] = accel[1];
    gp[2] = accel[2];
    // [g]gp = R([G<-L]qw)*[L]a
    qw.conjugate().rotate3DVector(gp); //<-- Eq. 44

    //qDebug()<<"[G]gp: "<<gp[0]<<"\t"<<gp[1]<<"\t"<<gp[2]<<"\t";
    //qDebug()<<"[G]gp mod: "<<sqrt(gp[0]*gp[0] + gp[1]*gp[1] + gp[2]*gp[2]);
    //finding Δqacc (Eq.47) (solved singularity in gp[2] = -1 as in Eq.18->Eq.25
    if(gp[2] >= 0)//if gp[z] >= 0
        dqacc = Quaternion(sqrt((gp[2]+1.0)/2.0), -gp[1]*fastInvSqrt(2*(gp[2]+1.0f)), gp[0]*fastInvSqrt(2*(gp[2] + 1.0)), 0.0);
    else          //if gp[z] < 0
        dqacc = Quaternion(-gp[1]*fastInvSqrt(2.0*(1.0-gp[2])), sqrt((1.0 - gp[2])/2.0), 0.0, gp[0]*fastInvSqrt(2.0*(1.0 - gp[2])));

    //qDebug()<<"Δqacc: "<<dqacc.q[0]<<"\t"<<dqacc.q[1]<<"\t"<<dqacc.q[2]<<"\t"<<dqacc.q[3]<<"\t";
    //qDebug()<<"Δqacc mod: "<<sqrt(dqacc.q[0]*dqacc.q[0] + dqacc.q[1]*dqacc.q[1] + dqacc.q[2]*dqacc.q[2] + dqacc.q[3]*dqacc.q[3]);

    //Deciding wether to use LERP or SLERP to filter Δqacc
    //ϵ = 0.9 -> treshold for using LERP over SLERP
    if(dqacc.q[0] > 0.9)
    {
        //Use LERP with identity quaternion and Δqacc (Eq.51)
        dqacc = (qI*(1.0-alfa) + dqacc*alfa);
        dqacc.normalize();
    }
    else
    {
        //Use SLERP with identity quaternion and Δqacc (Eq. 53)
        float sindq0acc = fsine(dqacc.q[0]);
        dqacc = qI*(fsine((1.0 - alfa)*dqacc.q[0])/sindq0acc) + dqacc*(fsine(alfa*dqacc.q[0])/sindq0acc);
    }
    q = qw*dqacc;//*dqmag;
    //q.normalize(); //Re-normalizing (because numerical drift is a thing)
}

void Worker::work(uint16_t dtus, int16_t* gyro, int16_t* accel, float* accelAngles, float* magn)
{
    /*fakeSensors.getNextRotation(Gravity,gyro);

    accel[0] = Gravity[0];
    accel[1] = Gravity[1];
    accel[2] = Gravity[2];

    qDebug()<<"fake accel: "<<accel[0]<<"\t"<<accel[1]<<"\t"<<accel[2];
    qDebug()<<"fake gyro: "<<gyro[0]<<"\t"<<gyro[1]<<"\t"<<gyro[2];*/
    update(dtus,gyro,accel,magn);

    //gyro[0] = 0;
    //gyro[1] = 0;
    //gyro[2] = 0;
    //q.rotate3DVector(temp);
    q.toEuler(temp);
    float n = fastInvSqrt(accel[0]*accel[0] + accel[1]*accel[1] + accel[2]*accel[2]);
    accelAngles[0] = (float)accel[0] * n;
    accelAngles[1] = (float)accel[1] * n;
    accelAngles[2] = (float)accel[2] * n;

    //qDebug()<<"roba: "<<asin(float(accel[0])*fastInvSqrt(accel[0]*accel[0] + accel[2]*accel[2]))<<"\t"<<asin(float(accel[1])*fastInvSqrt(accel[1]*accel[1] + accel[2]*accel[2]));

    accelAngles[0] = asin(accelAngles[0]*fastInvSqrt(accelAngles[0]*accelAngles[0] + accelAngles[2]*accelAngles[2]));
    accelAngles[1] = asin(accelAngles[1]*fastInvSqrt(accelAngles[1]*accelAngles[1] + accelAngles[2]*accelAngles[2]));
    accelAngles[2] = acos(accelAngles[0]*fastInvSqrt(accelAngles[0]*accelAngles[0] + accelAngles[1]*accelAngles[1]));

    emit newData(dtus,gyro,accelAngles,temp); //integration time of ~10016 us
}
