#include "vector.h"
#include <iostream>

Vector3::Vector3(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z)
{

}

Vector4::Vector4(float m_x/* = 0.0f*/, float m_y/* = 0.0f*/, float m_z/* = 0.0f*/, float m_w/* = 1.0f*/)
    : x(m_x),
      y(m_y),
      z(m_z),
      w(m_w)
{

}

/***********************
** VECTOR3 OPERATIONS **
***********************/
Vector3 Vector3::operator + (Vector3 vector)
{
    return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator - (Vector3 vector)
{
    return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator * (float multiplier)
{
    return Vector3(x * multiplier, y * multiplier, z * multiplier);
}

// a.dotProduct(b) == 0 if a and b are orthogonal (perpendicular).
float Vector3::dotProduct(Vector3 vector)
{
    return x * vector.x + y * vector.y + z * vector.z;
}

// a.crossProduct(b) == <a2b3 - a3b2, a3b1 - a1b3, a1b2 - a2b1>
// The vector returned is perpendicular to both a and b.
Vector3 Vector3::crossProduct(Vector3 vector)
{
    return Vector3(y*vector.z - z*vector.y, z*vector.x - x*vector.z, x*vector.y - y*vector.x);
}

// length = sqrt(a^2 + b^2 + c^2)
float Vector3::squaredLength()
{
    return dotProduct(*this);
}

Vector3 Vector3::normalizeVector()
{
    float length = sqrt(squaredLength());
    return Vector3(x/length, y/length, z/length);
}

Vector4 Vector3::toVector4()
{
    return Vector4(x, y, z, 1);
}

void Vector3::printVector()
{
    std::cout << "|" << x << "|" << std::endl;
    std::cout << "|" << y << "|" << std::endl;
    std::cout << "|" << z << "|" << std::endl;
}

/***********************
** VECTOR4 OPERATIONS **
***********************/
Vector4 Vector4::operator + (Vector4 vector)
{
    return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

Vector4 Vector4::operator - (Vector4 vector)
{
    return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
}

Vector4 Vector4::operator * (float multiplier)
{
    return Vector4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

// a.dotProduct(b) == 0 if a and b are orthogonal (perpendicular).
float Vector4::dotProduct(Vector4 vector)
{
    return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

// length = sqrt(a^2 + b^2 + c^2 + d^2)
float Vector4::squaredLength()
{
    return dotProduct(*this);
}

Vector4 Vector4::normalizeVector()
{
    float length = sqrt(squaredLength());
    return Vector4(x/length, y/length, z/length, w/length);
}

Vector3 Vector4::toVector3()
{
    return Vector3(x, y, z);
}

void Vector4::printVector()
{
    std::cout << "|" << x << "|" << std::endl;
    std::cout << "|" << y << "|" << std::endl;
    std::cout << "|" << z << "|" << std::endl;
    std::cout << "|" << w << "|" << std::endl;
}
