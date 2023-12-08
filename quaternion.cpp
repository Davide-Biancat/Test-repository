#include "quaternion.h"

Quaternion::Quaternion()
{
    //Identity quaternion
    q[0] = 1;
    q[1] = q[2] = q[3] = 0;
}


Quaternion::Quaternion(const float v[3]) //Turns v into a pure quaternion
{
    this->q[0] = 0;
    this->q[1] = v[0];
    this->q[2] = v[1];
    this->q[3] = v[2];
}

Quaternion::Quaternion(const Quaternion &q)
{
    this->q[0] = q.q[0];
    this->q[1] = q.q[1];
    this->q[2] = q.q[2];
    this->q[3] = q.q[3];
}

Quaternion::Quaternion(const float &w, const float &x, const float &y, const float &z)
{
    this->q[0] = w;
    this->q[1] = x;
    this->q[2] = y;
    this->q[3] = z;
}

Quaternion::Quaternion(const float &theta, const float n[3])
{
    q[0] = cosf(theta/2.0f);

    float half_sinthetha = sinf(theta/2);
    q[1] = n[0]*half_sinthetha;
    q[2] = n[1]*half_sinthetha;
    q[3] = n[2]*half_sinthetha;
}

Quaternion Quaternion::conjugate()
{
    return Quaternion(q[0],-q[1],-q[2],-q[3]);
}

void Quaternion::toEuler(float out[3])
{
  float jj = q[2]*q[2];
  out[0] = atan2f(2.0f*(q[0]*q[1] + q[2]*q[3]),1.0f - 2.0f*(q[1]*q[1] + jj));
  out[1] = asinf(2.0f*(q[0]*q[2] - q[3]*q[1]));
  out[2] = atan2f(2.0f*(q[0]*q[3] + q[1]*q[2]),1.0f - 2.0f*(jj+ q[3]*q[3]));
}

void Quaternion::normalize()
{
    float n = fastInvSqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    q[0] *= n;
    q[1] *= n;
    q[2] *= n;
    q[3] *= n;
}

void Quaternion:: rotate3DVector(float v[3])
{
    float x = v[0], y = v[1], z = v[2];
    v[0] = (q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3])*x + 2*(q[1]*q[2] - q[0]*q[3])*y                       + 2*(q[1]*q[3] + q[0]*q[2])*z;
    v[1] = 2 * (q[1]*q[2] + q[0]*q[3])*x                     + (q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3])*y + 2*(q[2]*q[3] - q[0]*q[1])*z;
    v[2] = 2 * (q[1]*q[3] - q[0]*q[2])*x                     + 2*(q[2]*q[3] + q[0]*q[1])*y                       + (q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3])*z;
}

void Quaternion:: rotate3DVector2(float v[3])
{
    Quaternion t(v);
    t = (*this) * t * this->conjugate();
    v[0] = t.q[1];
    v[1] = t.q[2];
    v[2] = t.q[3];
}

float Quaternion::lenght()
{
    return sqrtf(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
}

Quaternion Quaternion::operator *(const Quaternion &qt)
{
    Quaternion res({ q[0]*qt.q[0] - q[1]*qt.q[1] - q[2]*qt.q[2] - q[3]*qt.q[3],
                     q[0]*qt.q[1] + q[1]*qt.q[0] + q[2]*qt.q[3] - q[3]*qt.q[2],
                     q[0]*qt.q[2] - q[1]*qt.q[3] + q[2]*qt.q[0] + q[3]*qt.q[1],
                     q[0]*qt.q[3] + q[1]*qt.q[2] - q[2]*qt.q[1] + q[3]*qt.q[0]});
    return res;
}

Quaternion Quaternion::operator *=(const Quaternion &qt)
{
    float temp[4];
    temp[0] = q[0]*qt.q[0] - q[1]*qt.q[1] - q[2]*qt.q[2] - q[3]*qt.q[3];
    temp[1] = q[0]*qt.q[1] + q[1]*qt.q[0] + q[2]*qt.q[3] - q[3]*qt.q[2];
    temp[2] = q[0]*qt.q[2] - q[1]*qt.q[3] + q[2]*qt.q[0] + q[3]*qt.q[1];
    temp[3] = q[0]*qt.q[3] + q[1]*qt.q[2] - q[2]*qt.q[1] + q[3]*qt.q[0];

    q[0] = temp[0];
    q[1] = temp[1];
    q[2] = temp[2];
    q[3] = temp[3];
    return *this;
}

Quaternion Quaternion::operator *(const float &f)
{
    return Quaternion(q[0] *= f, q[1] *= f, q[2] *= f, q[3] *= f);
}

Quaternion Quaternion::operator +(const Quaternion &qt)
{
    return Quaternion(q[0]+qt.q[0], q[1]+qt.q[1], q[2]+qt.q[2], q[3]+qt.q[3]);
}
