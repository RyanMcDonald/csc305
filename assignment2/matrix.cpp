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

/**************************
** MATRIX 3X3 OPERATIONS **
**************************/

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

Matrix3x3 Matrix3x3::operator * (float scalar)
{
    Matrix3x3 temp;
    for (int i = 0; i <= 8; i++)
    {
        temp.elements[i] = elements[i] * scalar;
    }
    return temp;
}

Matrix3x3 Matrix3x3::operator * (Matrix3x3 matrix)
{
    Matrix3x3 temp;

    // Get rid of the 1's in the diagonal; we want to start with a zero-matrix
    temp.elements[0] = temp.elements[4] = temp.elements[8] = 0;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            for (int inner = 0; inner < 3; inner++)
            {
                temp.elements[3*col + row] += elements[3*inner + row] * matrix.elements[inner + 3*col];
            }
        }
    }

    return temp;
}

void Matrix3x3::scale(float x, float y, float z)
{
    elements[0] *= x;
    elements[4] *= y;
    elements[8] *= z;
}

void Matrix3x3::translate(float x, float y, float z)
{
    elements[6] += x;
    elements[7] += y;
    elements[8] += z;
}

void Matrix3x3::rotateX(float r)
{
    Matrix3x3 rotation;
    rotation.elements[4] = cos(r);
    rotation.elements[5] = sin(r);
    rotation.elements[7] = -1*sin(r);
    rotation.elements[8] = cos(r);

    *this = *this * rotation;
}

void Matrix3x3::rotateY(float r)
{
    Matrix3x3 rotation;
    rotation.elements[0] = cos(r);
    rotation.elements[2] = -1*sin(r);
    rotation.elements[6] = sin(r);
    rotation.elements[8] = cos(r);

    *this = *this * rotation;
}

void Matrix3x3::rotateZ(float r)
{
    Matrix3x3 rotation;
    rotation.elements[0] = cos(r);
    rotation.elements[1] = sin(r);
    rotation.elements[3] = -1*sin(r);
    rotation.elements[4] = cos(r);

    *this = *this * rotation;
}

Matrix4x4 Matrix3x3::to4x4()
{
    Matrix4x4 temp;

    temp.elements[0] = elements[0];
    temp.elements[1] = elements[1];
    temp.elements[2] = elements[2];
    temp.elements[3] = 0;

    temp.elements[4] = elements[3];
    temp.elements[5] = elements[4];
    temp.elements[6] = elements[5];
    temp.elements[7] = 0;

    temp.elements[8] = elements[6];
    temp.elements[9] = elements[7];
    temp.elements[10] = elements[8];
    temp.elements[11] = 0;

    temp.elements[12] = 0;
    temp.elements[13] = 0;
    temp.elements[14] = 0;
    temp.elements[15] = 1;

    return temp;
}

void Matrix3x3::printMatrix()
{
    std::cout << "|" << elements[0] << ", " << elements[3] << ", " << elements[6] << "|" << std::endl;
    std::cout << "|" << elements[1] << ", " << elements[4] << ", " << elements[7] << "|" << std::endl;
    std::cout << "|" << elements[2] << ", " << elements[5] << ", " << elements[8] << "|" << std::endl;
}

/**************************
** MATRIX 4X4 OPERATIONS **
***************************/

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

Matrix4x4 Matrix4x4::operator * (float scalar)
{
    Matrix4x4 temp;
    for (int i = 0; i <= 15; i++)
    {
        temp.elements[i] = elements[i] * scalar;
    }
    return temp;
}

Matrix4x4 Matrix4x4::operator * (Matrix4x4 matrix)
{
    Matrix4x4 temp;

    // Get rid of the 1's in the diagonal
    temp.elements[0] = temp.elements[5] = temp.elements[10] = temp.elements[15] = 0;

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            for (int inner = 0; inner < 4; inner++)
            {
                temp.elements[4*col + row] += elements[4*inner + row] * matrix.elements[inner + 4*col];
            }
        }
    }

    return temp;
}

void Matrix4x4::scale(float x, float y, float z, float w)
{
    elements[0] *= x;
    elements[5] *= y;
    elements[10] *= z;
    elements[15] *= w;
}

void Matrix4x4::translate(float x, float y, float z, float w)
{
    elements[12] += x;
    elements[13] += y;
    elements[14] += z;
    elements[15] += w;
}

void Matrix4x4::rotateX(float r)
{
    Matrix3x3 rotation;
    rotation.elements[4] = cos(r);
    rotation.elements[5] = sin(r);
    rotation.elements[7] = -1*sin(r);
    rotation.elements[8] = cos(r);

    Matrix4x4 rotation4x4 = rotation.to4x4();
    *this = *this * rotation4x4;
}

void Matrix4x4::rotateY(float r)
{
    Matrix3x3 rotation;
    rotation.elements[0] = cos(r);
    rotation.elements[2] = -1*sin(r);
    rotation.elements[6] = sin(r);
    rotation.elements[8] = cos(r);

    Matrix4x4 rotation4x4 = rotation.to4x4();
    *this = *this * rotation4x4;
}

void Matrix4x4::rotateZ(float r)
{
    Matrix3x3 rotation;
    rotation.elements[0] = cos(r);
    rotation.elements[1] = sin(r);
    rotation.elements[3] = -1*sin(r);
    rotation.elements[4] = cos(r);

    Matrix4x4 rotation4x4 = rotation.to4x4();
    *this = *this * rotation4x4;
}

Matrix3x3 Matrix4x4::to3x3()
{
    Matrix3x3 temp;

    temp.elements[0] = elements[0];
    temp.elements[1] = elements[1];
    temp.elements[2] = elements[2];
    temp.elements[3] = elements[4];
    temp.elements[4] = elements[5];
    temp.elements[5] = elements[6];
    temp.elements[6] = elements[8];
    temp.elements[7] = elements[9];
    temp.elements[8] = elements[10];

    return temp;
}

/*  eye - location that the eye "sees from", i.e., center of a lens.
**  gaze - any vector in the direction that the viewer is looking
**  up - any vector in the plane that both bisects the viewer’s head into right and left halves and points
**      “to the sky” for a person standing on the ground.
*/
Matrix4x4 Matrix4x4::buildViewMatrix(Vector3 eye, Vector3 gaze, Vector3 up)
{
    Matrix4x4 viewMatrix;

    // See page 147 in textbook... had to modify it a bit apparently
    Vector3 w = (eye - gaze).normalizeVector();
    Vector3 u = up.crossProduct(w).normalizeVector();
    Vector3 v = w.crossProduct(u);

    viewMatrix.elements[0] = u.x;
    viewMatrix.elements[1] = u.y;
    viewMatrix.elements[2] = u.z;
    viewMatrix.elements[3] = 0;

    viewMatrix.elements[4] = v.x;
    viewMatrix.elements[5] = v.y;
    viewMatrix.elements[6] = v.z;
    viewMatrix.elements[7] = 0;

    viewMatrix.elements[8] = w.x;
    viewMatrix.elements[9] = w.y;
    viewMatrix.elements[10] = w.z;
    viewMatrix.elements[11] = 0;

    Matrix4x4 moveEyeToOrigin;
    moveEyeToOrigin.translate((-1)*eye.x, (-1)*eye.y, (-1)*eye.z, 0);
    return viewMatrix * moveEyeToOrigin;
}

Matrix4x4 Matrix4x4::buildOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4x4 orthoMatrix;

    orthoMatrix.elements[0] = 2/(right - left);
    orthoMatrix.elements[5] = 2/(top - bottom);
    orthoMatrix.elements[10] = 2/(far - near);
    orthoMatrix.elements[12] = (-1)*((right + left)/(right - left));
    orthoMatrix.elements[13] = (-1)*((top + bottom)/(top - bottom));
    orthoMatrix.elements[14] = (-1)*((far + near)/(far - near));

    return orthoMatrix;
}

Matrix4x4 Matrix4x4::buildPerspectiveProjectionMatrix(float fov, float aspectRatio, float near, float far)
{
    float top = near * tan(fov * 0.5f);
    float bottom = -top;
    float left = bottom * aspectRatio;
    float right = top * aspectRatio;

    Matrix4x4 perspectiveMatrix;
    perspectiveMatrix.elements[0] = near/right;
    perspectiveMatrix.elements[5] = near/top;
    perspectiveMatrix.elements[10] = -(far + near)/(far - near);
    perspectiveMatrix.elements[11] = -1;
    perspectiveMatrix.elements[14] = -2*(far*near)/(far - near);
    perspectiveMatrix.elements[15] = 0;

    return perspectiveMatrix;

}

void Matrix4x4::printMatrix()
{
    std::cout << "|" << elements[0] << ", " << elements[4] << ", " << elements[8]  << ", " << elements[12] << "|" << std::endl;
    std::cout << "|" << elements[1] << ", " << elements[5] << ", " << elements[9]  << ", " << elements[13] << "|" << std::endl;
    std::cout << "|" << elements[2] << ", " << elements[6] << ", " << elements[10] << ", " << elements[14] << "|" << std::endl;
    std::cout << "|" << elements[3] << ", " << elements[7] << ", " << elements[11] << ", " << elements[15] << "|" << std::endl;
}
