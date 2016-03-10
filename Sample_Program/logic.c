
/**
 * @file
 * Hier ist die Datenhaltung und Programmlogik
 *
 * @author Tilman Nedele, Maurice Tollmien
 */

/* ---- System Header einbinden ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stringOutput.h>
#include <assert.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* ---- Eigene Header einbinden ---- */
#include "logic.h"
#include "vector.h"
#include "scene.h"
#include "types.h"
#include "quaternions.h"

/* Globale Variablen */
/** Licht an/aus */
InitType G_Light = ON;
/** Hilfe an/aus */
InitType G_Help  = OFF;
/** Mausbewegung zoom/move/none */
MouseInterpretType G_Mouse;
/** Kameraposition */
CGVector3D G_CameraPosition = {CAMERA_X,CAMERA_Y,CAMERA_Z};
/** Position der Maus */
Movement G_MouseMove = {0.0,0.0,0.0};
/** Startpunkt der Mausbewegung */
CGVector3D G_LastMouseCenter = {0.0,0.0,0.0};
/** Anzahl der Quadrate für den Boden */
int G_QuadCount = 5;
/** Partikel hinzufügen? */
int G_UpDownKeys[2] = {0,0};
/** FPS */
int G_FPS = 0;
/** FPS counter */
double G_Counter = 0.0-EPS;



/** Position der Maus */
Movement G_QuaternionMove = {0.0,0.0,0.0};
/** Startpunkt der Mausbewegung */
CGVector3D G_LastQuaternionCenter = {0.0,0.0,0.0};
/** Das sich zu drehende Objekt */
Vertex * G_Object;
/** Anzahl der Punkte */
int G_ObjectSize;
/** Die Indizes von Object */
int G_IndicesCount = 0;
/** Indices */
GLuint * G_Indices;
/** Mouse Action */
MouseType G_MouseType;

/* ------- GETTER / SETTER ------- */

int isCameraMode (void)
{
    return G_MouseType == camera;
}

/**
 * Schaltet um, ob mit einer Mouse-Bewegung entweder die Kamera
 * bewegt werden soll, oder das Objekt gedreht (Quaternionen!).
 */
void toggleMouseAction (void)
{
    G_MouseType = (G_MouseType == camera) ? quaternion : camera;
    printf("Mouse type set to: ");
    printf ("%s\n", (G_MouseType == quaternion) ? "Quaternion" : "Camera");
}

int getFPS(void)
{
    return G_FPS;
}

int getObjectIndicesCount(void)
{
    return G_IndicesCount;
}

GLuint * getObjectIndices(void)
{
    return G_Indices;
}

/**
 * Setzt, ob ein Up/Down-Key gedrückt ist.
 * key == 0 = down
 * key == 1 = up
 * value = gesetzt/nicht gesetzt.
 */
void setKey (int key, int value)
{
    if (key < 2)
        G_UpDownKeys[key] = value;
}

/**
 * Get-Function für den Status des Lichts
 * @return Status des Lichts
 */
InitType getLightStatus() {
    return G_Light;
}

/**
 * Set-Function für den Status des Lichts
 * @param Status des Lichts
 */
void setLightStatus(InitType state) {
    G_Light = state;
}

void toggleLight (void)
{
    G_Light = !G_Light;
}

/**
 * Get-Function für den Status der Hilfe
 * @return Status der Hilfe
 */
InitType getHelpStatus() {
    return G_Help;
}

/**
 * Set-Function für den Status der Hilfe
 * @param Status der Hilfe
 */
void setHelpStatus(InitType state) {
    G_Help = state;
}


/**
 * Set-Function für den Status der Maus
 * @param Status der Maus
 */
void setMouseEvent(MouseInterpretType state,int x, int y) {
    G_MouseMove[0] = 0.0;
    G_MouseMove[2] = 0.0;
    G_LastMouseCenter[0] = x;
    G_LastMouseCenter[2] = y;


    G_Mouse = state;
}

/**
 * Get-Function für den Status der Maus
 * @return Status der Maus
 */
MouseInterpretType getMouseEvent() {
    return G_Mouse;
}

/**
 * Gibt die Kamerakoordinate zurück.
 */
double getCameraPosition (int axis)
{
    if (axis >= 0 && axis < 3)
        return G_CameraPosition[axis];

    return 0.0;
}


/**
 * Erhöht die Größe der Unterteilungen um den Faktor 2
 */
void incQuadCount() {
    if (G_QuadCount < 9)
        ++G_QuadCount;
}

/**
 * Verkleinert die Größe der Unterteilungen um den Divisor 2
 */
void decQuadCount() {
    if (G_QuadCount > 2)
        --G_QuadCount;
}

/**
 * Rekursionstiefe für die Bodenfläche
 */
int getQuadCount() {
    return G_QuadCount;
}

/**
 * Bewegt die Kamera auf einem Kugelradius um den Szenenmittelpunkt.
 */
void setCameraMovement(int x,int y)
{
    CGVector3D tmp;
    double factor, radius = vectorLength3D(G_CameraPosition);

    tmp[0] = G_CameraPosition[0];
    tmp[1] = G_CameraPosition[1];
    tmp[2] = G_CameraPosition[2];

    G_MouseMove[0] = x-G_LastMouseCenter[0];
    G_MouseMove[2] = y-G_LastMouseCenter[2];

    G_LastMouseCenter[0] = x;
    G_LastMouseCenter[2] = y;

    /* Bewegung um Y-Achse: */
    G_CameraPosition[0] = cos(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[0] + sin(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[2];
    G_CameraPosition[2] = -sin(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[0] + cos(-G_MouseMove[0]*PI/180.0/CAMERA_MOVEMENT_SPEED)*tmp[2];

    /* Bewegung oben/unten */
    G_CameraPosition[1] += G_MouseMove[2]/(CAMERA_MOVEMENT_SPEED/2)*(vectorLength3D(G_CameraPosition)/100.0);
    factor = 1.0 / (vectorLength3D(G_CameraPosition) / radius);
    multiplyVectorScalar (G_CameraPosition, factor, &G_CameraPosition);

}

/**
 * Bewegt alle Punkte des Objektes um einen kleinen Winkel und nutzt dabei Quaternionen.
 */
void setQuaternionMovement (int x,int y)
{
    int i;
    /* Quaternion der Drehachse */
    Quaternion q = malloc (sizeof (*q));
    /* Drehachse */
    CGVector3D a;
    /* Winkel */
    double angle;

    a[0] = 100.9;
    a[1] = -35.0;
    a[2] = 3.0;
    normVector3D (a);

    G_QuaternionMove[0] = x-G_LastQuaternionCenter[0];
    G_QuaternionMove[2] = y-G_LastQuaternionCenter[2];

    G_LastQuaternionCenter[0] = x;
    G_LastQuaternionCenter[2] = y;

    angle = G_QuaternionMove[0]*PI/180.0/QUATERNION_MOVEMENT_SPEED;
    /*printf("angle : %f\n", angle/PI*180.0);*/

    q->s = cos (angle/2.0);
    multiplyVectorScalar (a, sin(angle/2.0), &a);
    /* Random Drehachse^^ */
    q->v[0] = a[0];
    q->v[1] = a[1];
    q->v[2] = a[2];

    normQuaternion(q);

    for (i=0;i<G_ObjectSize; i++)
    {
        /* Quaternion des Punktes */
        Quaternion p = malloc(sizeof(*p));
        Quaternion qtmp = malloc(sizeof(*qtmp));
        Quaternion res = malloc(sizeof(*res));

        p->s = 0.0;
        p->v[0] = G_Object[i][0];
        p->v[1] = G_Object[i][1];
        p->v[2] = G_Object[i][2];

        qtmp->s = q->s;
        qtmp->v[0] = q->v[0];
        qtmp->v[1] = q->v[1];
        qtmp->v[2] = q->v[2];

        /*  ---  q p q*  ---  */
        res = multQuaterionQuaterion (qtmp, p);

        res = multQuaterionQuaterion (res, inverseQuaternion (qtmp));

        /* Ergebnis zurück schreiben */
        G_Object[i][0] = res->v[0];
        G_Object[i][1] = res->v[1];
        G_Object[i][2] = res->v[2];

        free(res);
        free(p);
        free(qtmp);
    }

}

/**
 * Verlängert/verkürzt den Vektor zur Kamera.
 */
void setCameraZoom(int x,int y)
{
    double factor = 1.0 + (CAMERA_ZOOM_SPEED / 1000.0) * ((G_MouseMove[2] < 0.0) ? -1.0 : 1.0);

    G_MouseMove[0] = x-G_LastMouseCenter[0];
    G_MouseMove[2] = y-G_LastMouseCenter[2];

    G_LastMouseCenter[0] = x;
    G_LastMouseCenter[2] = y;

    G_CameraPosition[0] *= factor;
    G_CameraPosition[1] *= factor;
    G_CameraPosition[2] *= factor;
}

/* ------- BERECHNUNGEN ------- */

/**
 * Berechnet alle Funktionen, die vom interval abhängig sind
 * @param interval - Zeit
 */
void calcTimeRelatedStuff (double interval)
{


    G_Counter += interval;

    if (G_Counter >= 1.0)
        G_Counter = 0.0 -EPS;

    if (G_Counter <= 0.0)
        G_FPS = (int) 1.0/interval;
}

/**
 * Berechnet anhand der Rekursionstiefe die Anzahl der Quadrate auf dem Boden
 * @param p1,p2,p3,p4 - Die Ecken des Quadrats
 * @param rek - Rekursionstiefe
 * @param color - die Farbe der Quadrate
 *
 */
void drawRecursiveQuad(CGPoint3f p1, CGPoint3f p2, CGPoint3f p3, CGPoint3f p4, int rek, int color)
{
    CGPoint3f middle0 = {0.0,0.0,0.0},
              middle1 = {0.0,0.0,0.0},
              middle2 = {0.0,0.0,0.0},
              middle3 = {0.0,0.0,0.0},
              center = {0.0,0.0,0.0};

    center[0] = (p1[0] + p3[0]) / 2;
    center[2] = (p1[2] + p3[2]) / 2;

    middle0[0] = (p1[0] + p2[0]) / 2;
    middle0[2] = (p1[2] + p2[2]) / 2;

    middle1[0] = (p2[0] + p3[0]) / 2;
    middle1[2] = (p2[2] + p3[2]) / 2;

    middle2[0] = (p3[0] + p4[0]) / 2;
    middle2[2] = (p3[2] + p4[2]) / 2;


    middle3[0] = (p4[0] + p1[0]) / 2;
    middle3[2] = (p4[2] + p1[2]) / 2;

    if (rek > 0)
    {
      drawRecursiveQuad(center,middle0,p2,middle1, rek-1, color);
      drawRecursiveQuad(center,middle1,p3,middle2, rek-1, !color);
      drawRecursiveQuad(center,middle2,p4,middle3, rek-1, color);
      drawRecursiveQuad(center,middle3,p1,middle0, rek-1, !color);


    } else {
        drawVertex(p1,p2,p3,p4, color);
    }
}

/* ------- INIT ------- */

/**
 * Initialisiert die Kamera.
 */
void initCameraPosition ()
{
    G_CameraPosition[0] = CAMERA_X;
    G_CameraPosition[1] = CAMERA_Y;
    G_CameraPosition[2] = CAMERA_Z;
}

/**
 * Objekt
 */
void initObject (void)
{
    G_ObjectSize = 4;

    G_Object = malloc (G_ObjectSize * sizeof (Vertex));

    G_IndicesCount = 12;

    G_Indices = malloc (G_IndicesCount * sizeof(GLuint));

    G_Object[0][0] = 0.0;
    G_Object[0][1] = 0.0;
    G_Object[0][2] = 0.0;

    G_Object[1][0] = 20.0;
    G_Object[1][1] = 0.0;
    G_Object[1][2] = 0.0;

    G_Object[2][0] = 10.0;
    G_Object[2][1] = 0.0;
    G_Object[2][2] = -20.0;

    G_Object[3][0] = 10.0;
    G_Object[3][1] = 20.0;
    G_Object[3][2] = 20.0;

    G_Indices[0] = 0;
    G_Indices[1] = 1;
    G_Indices[2] = 3;

    G_Indices[3] = 0;
    G_Indices[4] = 3;
    G_Indices[5] = 2;

    G_Indices[6] = 1;
    G_Indices[7] = 2;
    G_Indices[8] = 3;

    G_Indices[9] = 1;
    G_Indices[10] = 0;
    G_Indices[11] = 2;

    glVertexPointer(3,
                GL_DOUBLE,
                0,
                &(G_Object[0][0]));
}

/**
 * Hier findet die komplette Initialisierung des kompletten SPIEeles statt.
 * Inklusive der Datenhaltung und des SPIEelfeldes.
 */
void initGame ()
{
    initCameraPosition();

    initObject ();

}

