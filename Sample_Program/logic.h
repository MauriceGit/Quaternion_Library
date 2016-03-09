#ifndef __LOGIC_H__
#define __LOGIC_H__
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

/* eig. Funktionen */

/* ------- GETTER / SETTER ------- */
InitType getLightStatus(void);
void setLightStatus(InitType state);
InitType getHelpStatus(void);
void setHelpStatus(InitType state);
InitType getTextureStatus(void);
void setTextureStatus(InitType state);
void setMouseEvent(MouseInterpretType state,int x, int y);
MouseInterpretType getMouseEvent(void);
double getCameraPosition (int axis);
int getTextureSize(void);
void setCameraMovement(int x,int y);
void setCameraZoom(int x,int y);
void toggleLight (void);
void incQuadCount();
void decQuadCount();
int getQuadCount();
int getTextureCount();
void nextTexture();
void toggleShadows(void);
int getDrawShadows(void);
void setKey (int key, int value);
int getFPS(void);
int getObjectIndicesCount(void);
GLuint * getObjectIndices(void);
void toggleMouseAction (void);
int isCameraMode (void);
void setQuaternionMovement (int x,int y);

/* ------- BERECHNUNGEN ------- */
void moveCamera(int x, int y);
void zoomCamera(int x, int y);
void calcTimeRelatedStuff (double interval);
void drawRecursiveQuad(CGPoint3f p1, CGPoint3f p2, CGPoint3f p3, CGPoint3f p4, int rek, int color);
/* ------- INIT ------- */

void initGame ();



#endif
