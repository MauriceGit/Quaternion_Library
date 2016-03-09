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
#ifdef WIN32
#include <windows.h>
#endif

#ifdef MACOSX
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdarg.h>

#include "types.h"
#include "vector.h"

#include "vector.h"

#define QUATERNION_MOVEMENT_SPEED 	4.0

/** Quaternion */
typedef struct Y * Quaternion;
struct Y
{
	double s;
	CGVector3D v;
};

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



