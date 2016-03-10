# Quaternion_Library

This repository is all about the files: **quaternions.h** and **quaternions.c**.

They represent an interface (library) of Quaternions and the most common operations on a Quaternion.

Corresponding to the library, I wrote a small sample program, that rotates a simple geometry around a fixed axis
with Quaternions. It is used for all calculations of the new rotated position.

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
    p->s = 0.0;
    p->v[0] = point[0];
    p->v[1] = point[1];
    p->v[2] = point[2];

    // The actual calculations.
    //  ---  q p q*  ---
    p = multQuaterionQuaterion (multQuaterionQuaterion (q, p), inverseQuaternion (q));

    // Write new rotated coordinates back to the point
    point[0] = p->v[0];
    point[1] = p->v[1];
    point[2] = p->v[2];

    // Of course - free your memory!
    free(q);
    free(p);
```

# License

Excerpt from the LICENSE file:

"Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the
copyright notice and this permission notice appear in all copies."

See the LICENCE file for more information what you have to include.
