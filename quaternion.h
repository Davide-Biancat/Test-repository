#ifndef QUATERNION_H
#define QUATERNION_H

#include <QObject>
#include "math_helper.h"

class Quaternion
{
public:
    Quaternion();
    Quaternion(const Quaternion &);
    Quaternion(const float v[3]); //This is actually passing the array by "reference"(only the pointer to the array is being copied, so the function can't change to where v is pointing, but it can change whatever is being pointed by v)
    Quaternion(const float &w, const float &x, const float &y, const float &z);
    Quaternion(const float &theta, const float n[3]);

    Quaternion operator *(const Quaternion &q);
    Quaternion operator *=(const Quaternion &qt);
    Quaternion operator *(const float &f);

    Quaternion operator +(const Quaternion &q);

    Quaternion conjugate();
    void toEuler(float out[3]);
    void normalize();
    void rotate3DVector(float v[3]);
    void rotate3DVector2(float v[3]);

    float lenght();

    float q[4];

private:
    void normalizeVector(float* v);
    //void vector3dCrossProduct(const float* a,const float* b, float* out);
};

#endif // QUATERNION_H
