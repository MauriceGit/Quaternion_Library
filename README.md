# Quaternion Library

This repository represent an interface (library) of Quaternions and the most common operations on a Quaternion.
No extended knowledge of Quaternions is neccesary for the use of this library. If you like to get familiar with Quaternions,
I recommend the relevant Wikipedia article: [https://en.wikipedia.org/wiki/Quaternion](https://en.wikipedia.org/wiki/Quaternion).

# Library Dependencies

Because some vector based math is required to calculate Quaterions, I provide the appropriate Vector library needed to use the Quaternion library here:

[https://github.com/MauriceGit/Vector_Library](https://github.com/MauriceGit/Vector_Library).

Just place both the **mtVector.c** and **mtVector.h** in the same directory and compile it with your project.

# Interface

The following functions are provided by this library.

## Low level Quaternion operations

* MTQuaternion **mtCreateMTQuaternion** (MTVec3D axis, double angle)

    Creates a new Quaternion and returns it.

* MTQuaternion **mtMultMTQuaternionMTQuaternion** (const MTQuaternion* q1, const MTQuaternion* q2)

    Multiplies two Quaternions with each other and returns a new Quaternion.

* MTQuaternion **mtMultMTQuaternionScalar** (const MTQuaternion* q1, double s)

    Multiplies a Quaternion with a scalar and returnes a new Quaternion.

* MTQuaternion **mtAddMTQuaternionMTQuaternion** (const MTQuaternion* q1, const MTQuaternion* q2)

    Adds two Quaternions with eath other and returnes a new Quaternion.

* MTQuaternion **mtSubtractMTQuaternionMTQuaternion** (const MTQuaternion* q1, const MTQuaternion* q2)

    Subtracts a Quaternion q2 from a Quaternion q1. Returnes new Quaternion.

* void **mtConjugateMTQuaternion** (MTQuaternion* q1)

    Complex conjugates a Quaternion.

* MTQuaternion **mtInverseMTQuaternion** (const MTQuaternion* q1)

    Calculates the inverse of a Quaternion and returnes a a new inverted Quaternion.

* void **mtNormMTQuaternion** (MTQuaternion* q1)

    Normalises a Quaternion.

* double **mtLengthMTQuaternion** (const MTQuaternion* q1)

    Calculates the length of a Quaternion.

* int **mtIsNormMTQuaternion** (const MTQuaternion* q1)

    Checks, if a Quaternion is normalised.

## High level Quaternion operations

* MTVec3D mtRotatePointWithMTQuaternion(MTQuaternion q, MTVec3D point)**

    Rotates a given point with a given Quaternion and returnes a new point.

* MTVec3D mtRotatePointAxis (MTVec3D axis, double angle, MTVec3D point)**

    Given an axis, angle and a point, the return value will equal the given point, rotated around the given axis at a given angle (counter-clocwise).

# Usage

An example usage for a Quaternion could be, to rotate a given Point around a given axis, using Quaternions.

## Low level approach

```c
// define normalised axis
MTVec3D axis = {0.0, 1.0, 0.0};
// define angle
double angle = 0.1;
// define point to rotate
MTVec3D point = {35.0, -28.3, 5.9};

// create Quaternion from axis and angle
Quaternion q;
q.s = cos (angle/2.0);
q.v = mtMultiplyVectorScalar(axis, sin(angle/2.0))

mtNormMTQuaternion(&q);

// Create MTQuaternion of the point to rotate
MTQuaternion p;
p.s    = 0.0;
p.v = point;

// The actual calculations.
//  ---  q p q*  ---
MTQuaternion inverseQ = mtInverseMTQuaternion(&q);
MTQuaternion res = mtMultMTQuaternionMTQuaternion (&q, &p);
res = mtMultMTQuaternionMTQuaternion (&res, &inverseQ);

// Write new rotated coordinates back to the point
point = res.v;

```

## High level approach

```c
MTVec3D axis = {100.9, -35.0, 3.0};
double angle = 0.1;
MTVec3D point = {0.5, 4.9, 1.0};

// The rotated coordinates will be written back to point.
point = mtRotatePointAxis (axis, angle, point);
```

# License

Excerpt from the LICENSE file:

"Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the
copyright notice and this permission notice appear in all copies."

See the LICENCE file for more information what you have to include.
