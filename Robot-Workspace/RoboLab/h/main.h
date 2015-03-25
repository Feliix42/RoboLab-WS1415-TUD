#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include "kernel.h"
/* Will be generated: */
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* add user headers here: */
#include "algorithms.h"
#include "orchester.h"

int get_intersection();	//Fährt Sucht auf Knoten mögliche Kanten, gibt Hex der Knoten aus
int robot_move(int hex);	//dreht sich in absolute Richtung
							//muss nach move oder intersection kommen


#endif /* MAIN_H_ */
