#ifndef __TYPES_H__
#define __TYPES_H__

/**
 * @file
 * Typenschnittstelle.
 * Das Modul kapselt die Typdefinitionen und globalen Konstanten des Programms.
 *
 * @author Maurice Tollmien
 */

/* ---- System Header einbinden ---- */
#ifdef WIN32
#include <windows.h>
#endif

#ifdef MACOSX
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

/* ---- Eigene Konstanten */



#define CAMERA_X        0.1
#define CAMERA_Y        50.0
#define CAMERA_Z        60.0
#define CAMERA_SPEED    15.0

#define CAMERA_MOVEMENT_SPEED   4.0
#define CAMERA_ZOOM_SPEED 10.0

#define CAMERA_PARTICLE_DISTANCE    0.5

#define COUNTOWNTEX 2
#define WORLD_SIZE 300.0

#define SLICE_CNT   10

#define QUATERNION_MOVEMENT_SPEED   4.0

#define E           2.71828183
#define PI             3.14159265
#define EPS     0.0001

/** Anzahl der Aufrufe der Timer-Funktion pro Sekunde */
#define TIMER_CALLS_PS      60

/** Reihen des Images */
#define IMAGE_ROWS  128
#define IMAGE_COLS  128

#define SPHERE_R    1.5
#define SPHERE_TRANSPARENCY     0.3
#define SPHERE_CNT  3

#define RED                     0.7, 0.0, 0.0
#define BLUE                    0.0, 0.0, 0.7
#define GREEN                   0.0, 0.7, 0.0
#define BLACK                   0.0, 0.0, 0.0
#define WHITE                   1.0, 1.0, 1.0
#define GREY                    0.4, 0.4, 0.4
#define YELLOW                  0.7, 0.7, 0.0

char * OWN_HELP_OUTPUT [14];
#define LINE_DISTANCE   0.025

/* Tastatur */
/** Keyboardtaste ESC definieren */
#define ESC     27
/** Keyboardtaste SPACE definieren */
#define SPACE   32

/** Datentyp fuer  den aktuellen SPIEelmodus */
enum e_gameIntiType { OFF, ON };
typedef enum e_gameIntiType InitType;

/** Mausereignisse. */
enum e_MouseEventType
{ mouseButton, mouseMotion, mousePassiveMotion };
/** Datentyp fuer Mausereignisse. */
typedef enum e_MouseEventType CGMouseEventType;

/** Mausereignisse. */
enum e_MouseInterpretType
{ NONE, MOVE, ZOOM};
/** Datentyp fuer Mausereignisse. */
typedef enum e_MouseInterpretType MouseInterpretType;

/** Datentyp fuer die Texturart */
enum e_textureType
{ NORMALTEXTURE, CHECKER, DIAGONAL };
/** Datentyp die Texturart */
typedef enum e_textureType textureType;

/** Datentyp fuer  den aktuellen SPIEelmodus */
enum e_gameModi { normal, help };
typedef enum e_gameModi GameMode;

/** Datentyp fuer die Verlaengerung/Verkuerzung des Kameravektors */
enum e_cameraVector { closer, further };
typedef enum e_cameraVector CameraVector;

/** Datentyp fuer die Richtungsaenderungen */
enum e_gameDirection {left, right, up, down};
typedef enum e_gameDirection Directions;

/** Punkt im 3D-Raum (homogene Koordinaten) */
typedef GLfloat CGPoint4f[4];
typedef GLfloat CGPoint3f[3];
typedef CGPoint3f CGColor;

/** Datentyp fuer einen Vektor */
typedef double Vector4D[4];
typedef Vector4D Punkt4D;

/** Vektor im 3D-Raum */
typedef double CGVector3D[3];

typedef double Vertex[3];

typedef int Movement[3];

typedef double VertexTexture[2];

enum e_particleType {line, triangle};
typedef enum e_particleType ParticleType;

enum e_mouseType { camera, quaternion };
typedef enum e_mouseType MouseType;



#endif
