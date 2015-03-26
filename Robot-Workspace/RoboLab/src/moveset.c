#include "../h/moveset.h"

void go() {
	ecrobot_set_motor_speed(NXT_PORT_B, 64);
	ecrobot_set_motor_speed(NXT_PORT_C, 60);
	// 205 rev(C) = 10cm bei 30 speed
	// 205 rev(C) = 10,8cm bei 60 speed
}

void turnrev(int rev) {		//Stoppt Bewegung nach bestimmter Rad-Grad Drehung
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (rev)){
	}
}

void turnl() {		//Linksdrehung
	ecrobot_set_motor_speed(NXT_PORT_B, -60);
	ecrobot_set_motor_speed(NXT_PORT_C, 60);
}

void turnr() {		//Rechtsdrehung
	ecrobot_set_motor_speed(NXT_PORT_B, 60);
	ecrobot_set_motor_speed(NXT_PORT_C, -60);
}

void stop() {		//Bremse
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
}

void turn90 (int t) {		//Drehung um 90°...also fast
	t = t * 270;
	int revn;
	revn = ecrobot_get_motor_rev(NXT_PORT_C);
	if (t>0) {
		turnl();
		while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (t)) {
		}
	}
	else {
		turnr();
		while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (t)) {
		}
	}

}

void printDir(int x) {
	// vor Ausführung display_clear(1), danach update
	// 0 Geradeaus; 1 Links; 2 Rechts
	switch(x) {
		case 0:
			display_goto_xy(4,3);
			display_string("GERADEAUS");
			break;
		case 1:
			display_goto_xy(4,5);
			display_string("LINKS");
			break;
		case 2:
			display_goto_xy(4,4);
			display_string("RECHTS");
			break;
	}
}
