#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QVector>
#include "libs/Eigen/Dense"

using namespace std;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker();
    Worker(const Worker &w);
    double complemetaryFilter(double gyroData, double dTs, double accData);
    double getCurrAngle();
    void setGyroGain(double gain);
    void setAccGain(double gain);

public slots:
    void estimateNewPos(const double acc,int dtInms);

private:
    Eigen::Vector3d x,xPrev,z;
    Eigen::Matrix3d P,PPrev,A,B,H,C,K,Q,R,I;

    double compAngle,gK,aK;

    void predictEstimate(double dtInms);
    void update();
};




#endif // WORKER_H
