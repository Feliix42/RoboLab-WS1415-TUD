#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* add user headers here: */

void set();				//Kalibriert. Einmal am Anfang
void move();			//Fährt auf schwarzer Linie und auf Knoten drauf
void knoten();			//Sucht auf Knoten mögliche Kanten, gibt Hex der Knoten aus
void godi(int hex);			//dreht sich in absolute Richtung
						//godi() muss nach knoten() kommen
						//selbstständig für Rückweg nutzbar



#endif /* MAIN_H_ */
