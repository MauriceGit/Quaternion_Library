#ifndef __QUATERNIONS_H__
#define __QUATERNIONS_H__
/**
 * Interface for some operations on Quaternions.
 *
 * @author Maurice Tollmien
 */

#include <stdarg.h>

#define EPS     0.0001

typedef double Vector3D[3];

/** Quaternion */
typedef struct
{
    double s;
    Vector3D v;
} Quaternion;

void multQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion * res);

void multQuaternionScalar (const Quaternion* q1, double s, Quaternion* res);

void addQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion* res);

void subtractQuaternionQuaternion (const Quaternion* q1, const Quaternion* q2, Quaternion* res);

void conjugateQuaternion (Quaternion* q1);

void inverseQuaternion (const Quaternion* q1, Quaternion* res);

void normQuaternion (Quaternion* q1);

double lengthQuaternion (const Quaternion* q1);

int isNormQuaternion (const Quaternion* q1);















#endif



