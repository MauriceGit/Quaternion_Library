/**
 * @file
 * Quaternionen
 *
 * @author Maurice Tollmien
 */

/* ---- System Header einbinden ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stringOutput.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* ---- Eigene Header einbinden ---- */
#include "types.h"
#include "quaternions.h"

/**
 * Multipliziert zwei Quaternions miteinander.
 * Vorsicht --> Nicht kommutativ!
 * Rechnet q1 * q2.
 */
Quaternion multQuaterionQuaterion (Quaternion q1, Quaternion q2)
{
	Quaternion res = malloc (sizeof(*res));
	CGVector3D vres;
	CGVector3D tmp;
	
	res->s = q1->s*q2->s - multiplyVectorVector(q1->v, q2->v);
	
	crossProduct3D (vres, q1->v, q2->v);
	
	multiplyVectorScalar (q2->v, q1->s, &tmp);
	addVectorVector (vres, tmp, &vres);
	multiplyVectorScalar (q1->v, q2->s, &tmp);
	addVectorVector (vres, tmp, &vres);
	
	res->v[0] = vres[0];
	res->v[1] = vres[1];
	res->v[2] = vres[2];
	
	return res;
}

/**
 * Multipliziert ein Quaternion mit einem Skalar.
 * Dabei wird der Skalar in ein Quaternion umgewandelt und 
 * es werden zwei Quaternions miteinander multipliziert.
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
 * Rechnet q1 + q2.
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
 * Rechnet q1 - q2.
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
 * Komplex konjugiert das Quaternion.
 */
Quaternion conjugateQuaternion (Quaternion q1)
{
	q1->v[0] *= -1.0;
	q1->v[1] *= -1.0;
	q1->v[2] *= -1.0;
	
	return q1;
}

/**
 * Invertiert das Quaternion.
 */
Quaternion inverseQuaternion (Quaternion q1)
{
	double qlen = pow (lengthQuaternion (q1), 2);
	
	return multQuaterionScalar (conjugateQuaternion(q1), 1.0 / qlen);
}

/**
 * Normalisiert das Quaternion auf eine Länge von 1.
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
 * Gibt die Länge des Quaternions zurück.
 */
double lengthQuaternion (Quaternion q1)
{
	return sqrt (q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2]);
}

/**
 * Checkt, ob ein Quaternion normalisier ist.
 */
int isNormQuaternion (Quaternion q1)
{
	double res = q1->s*q1->s + q1->v[0]*q1->v[0] + q1->v[1]*q1->v[1] + q1->v[2]*q1->v[2];
	return (res + EPS >= 1.0) && (res - EPS <= 1.0);
}
