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

/* ---- Eigene Header einbinden ---- */
#include "quaternions.h"


/*
 * Some Vector functions so this library can be used stand-alone.
 */

/**
 * Multipliziert einen Vektor mit einem Skalar.
 */
void multiplyVectorScalar_intern (Vector3D a, double s, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i]*s;
}

/**
 * Addiert a und b und schreibt das Ergebnis in res.
 */
void addVectorVector_intern (Vector3D a, Vector3D b, Vector3D * res)
{
    int i;
    for (i=0;i<3;i++)
        (*res)[i] = a[i] + b[i];
}

/**
 * Konvertierungsfunktion,
 * wandelt drei Koordinaten in den dazugehörigen Vektor um
 * @param x
 * @param y
 * @param z
 */
void toVector3D_intern(Vector3D vector, double x, double y, double z)
{
  vector[0] = x;
  vector[1] = y;
  vector[2] = z;
}

/**
 * Berechnet das Kreuzprodukt zweier Vektoren
 * @param
 * @param
 * @return
 */
void crossProduct3D_intern(Vector3D product, Vector3D a, Vector3D b)
{
  toVector3D_intern(product, (a[1]*b[2] - a[2]*b[1]),
                      (a[2]*b[0] - a[0]*b[2]),
                      (a[0]*b[1] - a[1]*b[0]));
}

/**
 * Multipliziert zwei Vektoren miteinander (Skalarprodukt)
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
 * Multipliziert zwei Quaternions miteinander.
 * Vorsicht --> Nicht kommutativ!
 * Rechnet q1 * q2.
 */
Quaternion multQuaterionQuaterion (Quaternion q1, Quaternion q2)
{
    Quaternion res = malloc (sizeof(*res));
    Vector3D vres;
    Vector3D tmp;

    res->s = q1->s*q2->s - multiplyVectorVector_intern(q1->v, q2->v);

    crossProduct3D_intern (vres, q1->v, q2->v);

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
