#include "../h/main.h"
int color;		//Mittelwert Schwarz-Weiß, zum Vergleichen
int dir = 0;	//aktuelle Fahrtrichtung N oder Startrichtung = 0
int N;			//Startrichtung
int S;			//Hinten
int E;			//Rechts
int W;			//Links

/// DO NOT DELETE THIS METHOD
/// It is called every 1ms and e.g. can be used for implementing a
/// real time counter / clock.
void user_1ms_isr_type2(void) {
}

void ecrobot_device_initialize(void) {

}

void ecrobot_device_terminate(void) {
}

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

void kompset(int turndir) {		//Speichert aktelle Fahrtrichtung
	dir = (dir + turndir)%4;
}

void sound(int l){
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(587, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(698, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(587, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(523, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(698, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);

		ecrobot_sound_tone(587, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(587, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(698, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(622, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, 0);			//Viertelpause, Frrequenz egal?
		systick_wait_ms(400);

		ecrobot_sound_tone(622, 208, 0);			//Achtelpause
		systick_wait_ms(200);
		ecrobot_sound_tone(698, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, 0);			//Pause zwischen den f
		systick_wait_ms(5);
		ecrobot_sound_tone(698, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(831, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(1047, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(932, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(831, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(784, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(698, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);

		ecrobot_sound_tone(587, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(587, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(622, 208, l);
		systick_wait_ms(200);
		ecrobot_sound_tone(698, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(784, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(622, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, l);
		systick_wait_ms(400);
		ecrobot_sound_tone(523, 416, 0);
		systick_wait_ms(400);
	}

void set() {	//Kalibrierung auf Schwarz und Weiß
	//hier möglichst nix ändern, da es zum Glück ordentlich funzt
	int colorb;
	int colors;	//colors means senseless, Name ist Programm.
	int colorw;
	colorw = 0;	//sonst gibts Warnings
	int i = 0;
	colors = ecrobot_get_light_sensor(NXT_PORT_S3);		//Soll ersten Fehler verhindert. colors de perfect one 4 dis job
	systick_wait_ms(300);
	while (i<10) {
		colorb = ecrobot_get_light_sensor(NXT_PORT_S3);
		i++;
	}

	turnr();
	systick_wait_ms(400);
	stop();
	while (i<20) {
		colorw = ecrobot_get_light_sensor(NXT_PORT_S3);
		i++;
	}
	color = (colorw + colorb)/2;		// sw-Vergleichswert für gesamten Durchlauf
	display_int(colorb,4);				// s- und w-Werte ausgeben
	display_int(colorw,4);
	display_update();
	turnl();
	systick_wait_ms(400);
	stop();
}

int search() {				//Suche nach schwarzer Linie
		turnl();				//Linksdrehen und suchen
		int i = 0;
		while (i < 5) {
			systick_wait_ms(20);
			i++;
			if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
			return 1;
		}					//optimierbar, zB add kleineres Schwenken am Anfang -> schneller
	turnr();				//oder spezielle Suche am Knoten, letztes turnr(zurückgehen) entfernen
  	i = 0;					//WICHTG: großflächige Suche aber lassen, zum schwarze Kanten finden
  	while (i < 25) {		//Schwarzkontrolle immer nach 20ms
  		systick_wait_ms(20);	//Rechtsdrehen und suchen
  		i++;
  		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
  			return 1;		//= schwarz gefunden
  	}
	turnl();				//Linksdrehen und suchen
	i = 0;
	while (i < 40) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
		return 1;
	}
	turnr();				//Zurück-/Rechtsdrehen. Suche eigentlich sinnlooouuus, aber Sicherheit usw.
	i = 0;
	while (i < 20) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
			return 1;
	}
  return 0;
}

void tokenfound() {			//tokenfound = Token gefunden, okay?!
	ecrobot_set_motor_speed(NXT_PORT_B, -53);
	ecrobot_set_motor_speed(NXT_PORT_C, -50);
	systick_wait_ms(500);
	stop();
	sound(10);				//Superhit des Jahrhunderts wird abgespielt
	systick_wait_ms(3000);
}

int drive() {				//fahren auf dem Strich
	int running = 1;
	int colort;
	int btokenfound=1; // ROBOT_SUCCESS
	go();
	systick_wait_ms(50);
	while(running){
		if(ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S2)) {
					tokenfound();		//laufende Suche ob Token im Weg steht
					btokenfound = 2; // ROBOT_TOKENFOUND
					go();  }
		colort = ecrobot_get_light_sensor(NXT_PORT_S3);
		if ((colort) < (color))			//checkt ob es noch schwarz ist
			running = 0;
	}
	int sw = search();	//bei 0 ist alles weiß -> Knoten
	if (sw > 0)
		drive();
	return btokenfound;
}

int move() {
	int btokenfound = drive();
	go();			//Fährt auf Knoten
	turnrev(200);
	stop();
	return btokenfound;
}

void turn90 (int t) {		//Drehung um 90°...also fast
	t = t * 285;
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


void NESW(int s) {	//passt Richtungsangaben an die absolute Richtung an
	s = (dir + s)%4;
	switch (s) {
		case 0: N = 1; break;
		case 1: E = 1; break;
		case 2: S = 1; break;
		case 3: W = 1; break;
	}

}

int knoten() {		//Startet suche nach Kanten am Koten, wandelt sie um, lässt Richtung speichern und lässt alles in die perfekte Richtung drehen. Also ein alles in allem total mega geiles Teil hier :)  Lass uns diese Funktion Gott umtaufen.
	ecrobot_status_monitor("Knoten");
	int direct = 1 * search();	//guckt ob straight da ist
	turnl();
	int i = 1;
	int j = 0;			//guckt ob left da ist
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (i) {
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (835))
			i = 0;
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (350)) {
			if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (200)) {
				if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
					j = 1;
			}
		}
	}
	direct = direct + 2 * j;
	direct = direct + 4 * search();	//guckt ob right da ist
	N = 0;
	E = 0;
	S = 0;
	W = 0;
	NESW(2);   //Kante umrechnen die zurück geht
	switch (direct) {
		case 0: ecrobot_status_monitor("haha Sackgasse"); break;
		case 1: ecrobot_status_monitor("nur Gerade"); NESW(0); break;
		case 2: ecrobot_status_monitor("nur Links"); NESW(3); break;
		case 3: ecrobot_status_monitor("Links u Gerade"); NESW(3); NESW(0); break;
		case 4: ecrobot_status_monitor("nur Rechts"); NESW(1); break;
		case 5: ecrobot_status_monitor("Rechts u Gerade"); NESW(1); NESW(0); break;
		case 6: ecrobot_status_monitor("Links u Rechts"); NESW(1); NESW(3); break;
		case 7: ecrobot_status_monitor("ueberall Kanten"); NESW(0); NESW(1); NESW(3);
	}
	kompset(1);
	N = N * 0x10;
	S = S * 0x20;
	W = W * 0x40;
	E = E * 0x80;
	stop();
	return (N+S+W+E);
}

void godi(int a) {
	int newdir = a;
	a = dir - a;		//Berechnet aus absoluter Richtung, ob er L R usw. muss
	if (a==3) a=-1;
	if (a==-3) a=1;

	turn90(a);
	dir = newdir;
}

int get_intersection () {
	return (knoten());		//startet Kantensuche am Knoten
}

int robot_move (int nothex) {
	godi(nothex);		//dreht in die angegebene absolute Richtung
	return move();
}

TASK(OSEK_Main_Task) {
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
	set();
	brain();

	ecrobot_status_monitor("My name is Horst");
	stop();
	systick_wait_ms(3000);
	ecrobot_status_monitor("James Horst");
	while(1){

		}
}
