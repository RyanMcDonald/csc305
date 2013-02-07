#include "matrix.h"
#include <iostream>

Matrix3x3::Matrix3x3()
{
    this->loadIdentity();
}

void Matrix3x3::loadIdentity()
{
    elements[0] = elements[4] = elements[8] = 1;
    elements[1] = elements[2] = elements[3] = elements[5] = elements[6] = elements[7] = 0;
}

Matrix4x4::Matrix4x4()
{
    loadIdentity();
}

void Matrix4x4::loadIdentity()
{
    elements[0] = elements[5] = elements[10] = elements[15] = 1;
    elements[1] = elements[2] = elements[3] = elements[4] = elements[6] = elements[7]
    = elements[8] = elements[9] = elements[11] = elements[12] = elements[13] = elements[14] = 0;
}

Matrix3x3 Matrix3x3::operator + (Matrix3x3 matrix)
{
    Matrix3x3 temp;
    for (int i = 0; i <= 8; i++)
    {
        temp.elements[i] = this->elements[i] + matrix.elements[i];
    }
    return temp;
}

Matrix3x3 Matrix3x3::operator - (Matrix3x3 matrix)
{
    Matrix3x3 temp;
    for (int i = 0; i <= 8; i++)
    {
        temp.elements[i] = this->elements[i] - matrix.elements[i];
    }
    return temp;
}

Matrix3x3 Matrix3x3::operator * (Matrix3x3 matrix)
{
    Matrix3x3 temp;
    for (int i = 0; i <= 8; i++)
    {
        temp.elements[i] = this->elements[i] * matrix.elements[i];
    }
    return temp;
}

Matrix4x4 Matrix4x4::operator + (Matrix4x4 matrix)
{
    Matrix4x4 temp;
    for (int i = 0; i <= 15; i++)
    {
        temp.elements[i] = this->elements[i] + matrix.elements[i];
    }
    return temp;
}

Matrix4x4 Matrix4x4::operator - (Matrix4x4 matrix)
{
    Matrix4x4 temp;
    for (int i = 0; i <= 15; i++)
    {
        temp.elements[i] = this->elements[i] - matrix.elements[i];
    }
    return temp;
}

Matrix4x4 Matrix4x4::operator * (Matrix4x4 matrix)
{
    Matrix4x4 temp;
    for (int i = 0; i <= 15; i++)
    {
        temp.elements[i] = this->elements[i] * matrix.elements[i];
    }
    return temp;
}

void Matrix3x3::printMatrix()
{
    std::cout << "|" << elements[0] << ", " << elements[3] << ", " << elements[6] << "|" << std::endl;
    std::cout << "|" << elements[1] << ", " << elements[4] << ", " << elements[7] << "|" << std::endl;
    std::cout << "|" << elements[2] << ", " << elements[5] << ", " << elements[8] << "|" << std::endl;
}

void Matrix4x4::printMatrix()
{
    std::cout << "|" << elements[0] << ", " << elements[4] << ", " << elements[8]  << ", " << elements[12] << "|" << std::endl;
    std::cout << "|" << elements[1] << ", " << elements[5] << ", " << elements[9]  << ", " << elements[13] << "|" << std::endl;
    std::cout << "|" << elements[2] << ", " << elements[6] << ", " << elements[10] << ", " << elements[14] << "|" << std::endl;
    std::cout << "|" << elements[3] << ", " << elements[7] << ", " << elements[11] << ", " << elements[15] << "|" << std::endl;
}
