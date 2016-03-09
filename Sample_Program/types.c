
/**
 * @file
 * Hier ist die Hilfeausgabe.
 *
 * @author Maurice Tollmien
 */

/* ---- System Header einbinden ---- */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stringOutput.h>

#ifdef MACOSX
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/* ---- Eigene Header einbinden ---- */
#include "types.h"

char * OWN_HELP_OUTPUT [] = {
                        "Allgemeine Funktionalitaeten:",
                        "",
                        "q/Q    beendet das Spiel.",
                        "r      beginnt ein neues Spiel im Ausgangszustand.",
                        "h/H    oeffnet/schliesst den Hilfemodus.",
                        "+/-    Aendert die Anzahl der Quadrate auf dem Boden.",
                        "t/T    Textur wechseln.",
                        "f2     Licht an/aus.",
                        "f3     Texturen an/aus.",
                        "Maus + rechte Maustaste  	 Abstand zum Mittelpunkt.",
                        "Maus + linke Maustaste   	 Bewegung im Raum.",
                        "",
                        "s/S	Schaltet Mausbewegung zwischen Kamera und Quaternion-Berechnung um.",
                        ""
                        };
