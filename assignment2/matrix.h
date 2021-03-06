#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

class Matrix3x3;
class Matrix4x4;

/**
 *  @todo assignment two
 *  1. extend these matrix classes to support all the basic linear algebra functions
 *  (add, subtract, multiply)
 *  2. add convenience functions to create scale & rotation matrices around the available axes,
 *  and a translation matrix
 *  3. add functions to create the projection matrix versions.
 *  for perspective projection, this function should take the field of view, image ratio, near plane and far plane distance
 *  for orthographic projection it should take the left, right, top, bottom, near plane and far plane values
 *  4. add functions to create the view matrix using eye position, at position and the up vector
 */

/**
 *	@class	Matrix3x3
 *	@brief	3 by 3 Matrix class
 *	Homogenous 3x3 Matrix, onedimensional array (like opengl), column major
 *	|0 3 6|
 *	|1 4 7|
 *	|2 5 8|
 */
class Matrix3x3
{
public:

    float elements[9];/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix3x3();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

    Matrix3x3 operator + (Matrix3x3);
    Matrix3x3 operator - (Matrix3x3);
    Matrix3x3 operator * (float);
    Matrix3x3 operator * (Matrix3x3);

    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    void rotateX(float r);
    void rotateY(float r);
    void rotateZ(float r);

    Matrix4x4 to4x4();

    void printMatrix();

};

/**
 *	@class	Matrix4x4
 *	@brief	4 by 4 matrix
 *	Homogenous 4x4 Matrix, onedimensional array (like opengl), column major
 *	|0 4 8  12|
 *	|1 5 9  13|
 *	|2 6 10 14|
 *	|3 7 11 15|
 */
class Matrix4x4
{
public:

    float elements[16];	/**< array storing the values of the matrix. */

    /**
     *	default constructor
     *	generates the identity matrix
     */
    Matrix4x4();

    /**
     *	generates the identity matrix
     */
    void loadIdentity();

    Matrix4x4 operator + (Matrix4x4);
    Matrix4x4 operator - (Matrix4x4);
    Matrix4x4 operator * (float);
    Matrix4x4 operator * (Matrix4x4);

    void scale(float x, float y, float z, float w);
    void translate(float x, float y, float z, float w);
    void rotateX(float r);
    void rotateY(float r);
    void rotateZ(float r);

    Matrix3x3 to3x3();

    Matrix4x4 buildOrthoProjectionMatrix(float left, float right, float bottom, float top, float near, float far);
    Matrix4x4 buildPerspectiveProjectionMatrix(float fov, float aspectRatio, float near, float far);
    Matrix4x4 buildViewMatrix(Vector3 eye, Vector3 gaze, Vector3 up);

    void printMatrix();

};

#endif // MATRIX_H
