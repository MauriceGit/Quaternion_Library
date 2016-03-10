/**
 * Implementation of most relevant functions on Quaternions.
 *
 * @author Maurice Tollmien
 */

/* ---- System Header einbinden ---- */
#include <stdlib.h>
#include <math.h>

/* ---- Eigene Header einbinden ---- */
#include "quaternions.h"

/*
 * Some Vector functions so this library can be used stand-alone.
 */

/**
 * Multiply a vector with a scalar.
 */
void multiplyVectorScalar_intern (Vector3D a, double s, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i]*s;
}

/**
 * Add to vectors.
 */
void addVectorVector_intern (Vector3D a, Vector3D b, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] + b[i];
}

/**
 * Convert three separate values to a vector.
 */
void toVector3D_intern(Vector3D *vector, double x, double y, double z)
{
  (*vector)[0] = x;
  (*vector)[1] = y;
  (*vector)[2] = z;
}

/**
 * Cross product of two vectors
 */
void crossProduct3D_intern(Vector3D *product, Vector3D a, Vector3D b)
{
  toVector3D_intern(product, (a[1]*b[2] - a[2]*b[1]),
                      (a[2]*b[0] - a[0]*b[2]),
                      (a[0]*b[1] - a[1]*b[0]));
}

/**
 * Multiply to vectors (scalar product)
 */
double multiplyVectorVector_intern (Vector3D a, Vector3D b)
{
    int i;
    double res = 0.0;
    for (i=0;i<3;i++)
        res += a[i]*b[i];
    return res;
}

/*
 * Functions regarding operations on Quaternions.
 */

/**
 * Multiply to Quaternions with each other.
 * Careful! Not commutative!!!
 * Calculates: q1 * q2
 */
Quaternion multQuaterionQuaterion (Quaternion q1, Quaternion q2)
{
    Quaternion res = malloc (sizeof(*res));
    Vector3D vres;
    Vector3D tmp;

    res->s = q1->s*q2->s - multiplyVectorVector_intern(q1->v, q2->v);

    crossProduct3D_intern (&vres, q1->v, q2->v);

    multiplyVectorScalar_intern (q2->v, q1->s, &tmp);
    addVectorVector_intern (vres, tmp, &vres);
    multiplyVectorScalar_intern (q1->v, q2->s, &tmp);
    addVectorVector_intern (vres, tmp, &vres);

    res->v[0] = vres[0];
    res->v[1] = vres[1];
    res->v[2] = vres[2];

    return res;
}

/**
 * Multiplies a Quaternion and a scalar.
 * Therefore the scalar will be converted to a Quaternion.
 * After that the two Quaternions will be muliplied.
 */
Quaternion multQuaterionScalar (Quaternion q1, double s)
{
    Quaternion q2 = malloc (sizeof(*q2));

    q2->s = s;
    q2->v[0] = 0.0;
    q2->v[1] = 0.0;
    q2->v[2] = 0.0;

    return multQuaterionQuaterion (q1, q2);
}

/**
 * Calculates: q1 + q2.
 */
Quaternion addQuaternionQuaternion (Quaternion q1, Quaternion q2)
{
    Quaternion res = malloc (sizeof(*res));

    res->s = q1->s + q2->s;
    res->v[0] = q1->v[0] + q2->v[0];
    res->v[1] = q1->v[1] + q2->v[1];
    res->v[2] = q1->v[2] + q2->v[2];

    return res;
}

/**
 * Calculates q1 - q2.
 */
Quaternion subtractQuaternionQuaternion (Quaternion q1, Quaternion q2)
{
    Quaternion res = malloc (sizeof(*res));

    res->s = q1->s - q2->s;
    res->v[0] = q1->v[0] - q2->v[0];
    res->v[1] = q1->v[1] - q2->v[1];
    res->v[2] = q1->v[2] - q2->v[2];

    return res;
}

/**
 * Complex conjugate the Quaternion.
 */
Quaternion conjugateQuaternion (Quaternion q1)
{
    q1->v[0] *= -1.0;
    q1->v[1] *= -1.0;
    q1->v[2] *= -1.0;

    return q1;
}

/**
 * Invert the Quaternion.
 */
Quaternion inverseQuaternion (Quaternion q1)
{
    double qlen = pow (lengthQuaternion (q1), 2);

    return multQuaterionScalar (conjugateQuaternion(q1), 1.0 / qlen);
}

/**
 * Normalize the Quaternion to a length of 1.
 */
Quaternion normQuaternion (Quaternion q1)
{
    double qlen = lengthQuaternion (q1);

    q1->s /= qlen;
    q1->v[0] /= qlen;
    q1->v[1] /= qlen;
    q1->v[2] /= qlen;

    return q1;
}

/**
 * Calculates the length of the Quaternion.
 */
double lengthQuaternion (Quaternion q1)
{
    return sqrt (q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2]);
}

/**
 * Check if the Quaternion is normalized.
 */
int isNormQuaternion (Quaternion q1)
{
    double res = q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2];
    return (res + EPS >= 1.0) && (res - EPS <= 1.0);
}
