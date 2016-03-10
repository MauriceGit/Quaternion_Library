# Quaternion Library

This repository is all about the files: **quaternions.h** and **quaternions.c**.

They represent an interface (library) of Quaternions and the most common operations on a Quaternion.

Corresponding to the library, I wrote a small sample program, that rotates a simple geometry around a fixed axis
with Quaternions. It is used for all calculations of the new rotated position.

If you want to know how and why Quaternions work - please read it up on the internet. This is just a practical approach
and the implementation of common operations.

# Usage

An example usage for a Quaternion could be, to rotate a given Point around a given axis, using Quaternions.

This example code is in C syntax and serves only to demonstrate a potential use of Quaternions to
calculate a rotation. It uses types and libraries, defined in the files: **quaternions.h**, **vector.h**, **types.h** from the sample code.
It might or might not need some adjustments to work.

```c
// define normalised axis
Vector3D a = {0.0, 1.0, 0.0};
// define angle
double angle = 0.1;
// define point to rotate
Vector3D point = {35.0, -28.3, 5.9};
// create Quaternion
Quaternion q = malloc (sizeof (*q));

q->s = cos (angle/2.0);
multiplyVectorScalar (a, sin(angle/2.0), &a);
q->v[0] = a[0];
q->v[1] = a[1];
q->v[2] = a[2];

normQuaternion(q);

// Create Quaternion of the point to rotate
Quaternion p = malloc(sizeof(*p));
Quaternion qtmp = malloc(sizeof(*qtmp));
Quaternion res = malloc(sizeof(*qtmp));
p->s = 0.0;
p->v[0] = point[0];
p->v[1] = point[1];
p->v[2] = point[2];

qtmp->s = q->s;
qtmp->v[0] = q->v[0];
qtmp->v[1] = q->v[1];
qtmp->v[2] = q->v[2];

// The actual calculations.
//  ---  q p q*  ---
res = multQuaterionQuaterion (qtmp, p);
res = multQuaterionQuaterion (res, inverseQuaternion (qtmp));

// Write new rotated coordinates back to the point
point[0] = res->v[0];
point[1] = res->v[1];
point[2] = res->v[2];

// Of course - free your memory!
free(res);
free(p);
free(q);
free(qtmp);
```

# Compile and Run

I only tested and ran this simulation on a debian-based Linux OS (Ubuntu, Mint, ...). It should run on other machines as well but is not
tested.

## **Requirements**

The following system-attributes are required for running this simulation:

- A graphics card supporting OpenGL.

- Unix-Libraries: xorg-dev, freeglut3-dev and mesa-common-dev

## **Running**

Execute the following steps to run the sample:

- ./compile.sh

- ./quaternions


While the simulation runs, you can rotate the object by clicking and moving the mouse. Pressing **s** on your keyboard toggles
between moving the camera or the object.

# License

Excerpt from the LICENSE file:

"Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the
copyright notice and this permission notice appear in all copies."

See the LICENCE file for more information what you have to include.
