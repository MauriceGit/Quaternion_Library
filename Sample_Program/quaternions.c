/**
 * Implementation of most relevant functions on Quaternions.
 *
 * @author Maurice Tollmien
 */

/* ---- System Header ---- */
#include <stdlib.h>
#include <math.h>

/* ---- My Header ---- */
#include "quaternions.h"

#define EPS     0.0001

/*
 * Some Vector functions so this library can be used stand-alone.
 */

/**
 * Multiply a vector with a scalar.
 */
static void multiplyVectorScalar_intern (const Vector3D a, double s, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i]*s;
}

/**
 * Add to vectors.
 */
static void addVectorVector_intern (const Vector3D a, const Vector3D b, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] + b[i];
}

/**
 * Convert three separate values to a vector.
 */
static void toVector3D_intern(Vector3D *vector, double x, double y, double z)
{
  (*vector)[0] = x;
  (*vector)[1] = y;
  (*vector)[2] = z;
}

/**
 * Cross product of two vectors
 */
static void crossProduct3D_intern(Vector3D *product, const Vector3D a, const Vector3D b)
{
  toVector3D_intern(product, (a[1]*b[2] - a[2]*b[1]),
                      (a[2]*b[0] - a[0]*b[2]),
                      (a[0]*b[1] - a[1]*b[0]));
}

/**
 * Multiply to vectors (scalar product)
 */
static double multiplyVectorVector_intern (const Vector3D a, const Vector3D b)
{
    int i;
    double res = 0.0;
    for (i=0;i<3;i++)
        res += a[i]*b[i];
    return res;
}

/*
 * Low level operations on Quaternions
 */

/**
 * Multiply to Quaternions with each other.
 * Careful! Not commutative!!!
 * Calculates: q1 * q2
 */
void multQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion * res)
{
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
}

/**
 * Multiplies a Quaternion and a scalar.
 * Therefore the scalar will be converted to a Quaternion.
 * After that the two Quaternions will be muliplied.
 */
void multQuaternionScalar (const Quaternion* q1, double s, Quaternion* res)
{
    Quaternion q2;

    q2.s = s;
    q2.v[0] = 0.0;
    q2.v[1] = 0.0;
    q2.v[2] = 0.0;

    multQuaternionQuaternion (q1, &q2, res);
}

/**
 * Calculates: q1 + q2.
 */
void addQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion* res)
{
    res->s = q1->s + q2->s;
    res->v[0] = q1->v[0] + q2->v[0];
    res->v[1] = q1->v[1] + q2->v[1];
    res->v[2] = q1->v[2] + q2->v[2];
}

/**
 * Calculates q1 - q2.
 */
void subtractQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion* res)
{
    res->s = q1->s - q2->s;
    res->v[0] = q1->v[0] - q2->v[0];
    res->v[1] = q1->v[1] - q2->v[1];
    res->v[2] = q1->v[2] - q2->v[2];
}

/**
 * Complex conjugate the Quaternion.
 */
void conjugateQuaternion (Quaternion* q1)
{
    q1->v[0] *= -1.0;
    q1->v[1] *= -1.0;
    q1->v[2] *= -1.0;
}

/**
 * Invert the Quaternion.
 */
void inverseQuaternion (const Quaternion* q1, Quaternion* res)
{
    double qlen = pow (lengthQuaternion (q1), 2);

    Quaternion tmp = *q1;

    conjugateQuaternion(&tmp);

    multQuaternionScalar (&tmp, 1.0 / qlen, res);
}

/**
 * Normalize the Quaternion to a length of 1.
 */
void normQuaternion (Quaternion* q1)
{
    double qlen = lengthQuaternion (q1);

    q1->s /= qlen;
    q1->v[0] /= qlen;
    q1->v[1] /= qlen;
    q1->v[2] /= qlen;
}

/**
 * Calculates the length of the Quaternion.
 */
double lengthQuaternion (const Quaternion* q1)
{
    return sqrt (q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2]);
}

/**
 * Check if the Quaternion is normalized.
 */
int isNormQuaternion (const Quaternion* q1)
{
    double res = q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2];
    return (res + EPS >= 1.0) && (res - EPS <= 1.0);
}

/* Some higher level functions, using Quaternions */

void rotatePointAxis (Vector3D axis, double angle, Vector3D * point)
{
    // create Quaternion from axis and angle
    Quaternion q;
    Vector3D tmp;
    tmp[0] = axis[0];
    tmp[1] = axis[1];
    tmp[2] = axis[2];
    q.s = cos (angle/2.0);
    multiplyVectorScalar_intern (axis, sin(angle/2.0), &tmp);
    q.v[0] = tmp[0];
    q.v[1] = tmp[1];
    q.v[2] = tmp[2];

    normQuaternion(&q);

    Quaternion p;
    Quaternion res;
    Quaternion inverseQ;

    // Create Quaternion of the point to rotate
    p.s    = 0.0;
    p.v[0] = (*point)[0];
    p.v[1] = (*point)[1];
    p.v[2] = (*point)[2];

    // The actual calculations.
    //  ---  q p q*  ---
    inverseQuaternion(&q, &inverseQ);
    multQuaternionQuaternion (&q, &p, &res);
    multQuaternionQuaternion (&res, &inverseQ, &res);

    // Write new rotated coordinates back to the point
    (*point)[0] = res.v[0];
    (*point)[1] = res.v[1];
    (*point)[2] = res.v[2];
}
