#ifndef __QUATERNIONS_H__
#define __QUATERNIONS_H__
#define __DEBUG_GL_H__
/**
 * @file
 * Programmlogik und Datenhaltung
 *
 * @author Maurice Tollmien
 */

/* ---- System Header einbinden ---- */

#include <stdarg.h>

#define EPS     0.0001

typedef double Vector3D[3];

/** Quaternion */
typedef struct
{
    double s;
    Vector3D v;
} * Quaternion;

Quaternion multQuaterionQuaterion (Quaternion q1, Quaternion q2);

Quaternion multQuaterionScalar (Quaternion q1, double s);

Quaternion addQuaternionQuaternion (Quaternion q1, Quaternion q2);

Quaternion subtractQuaternionQuaternion (Quaternion q1, Quaternion q2);

Quaternion conjugateQuaternion (Quaternion q1);

Quaternion inverseQuaternion (Quaternion q1);

Quaternion normQuaternion (Quaternion q1);

double lengthQuaternion (Quaternion q1);

int isNormQuaternion (Quaternion q1);















#endif



