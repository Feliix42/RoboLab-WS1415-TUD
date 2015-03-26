#include "../h/main.h"

int color;		//Mittelwert Schwarz-Weiß, zum Vergleichen
int dir = 0;	//aktuelle Fahrtrichtung N oder Startrichtung = 0
int N;			//Startrichtung
int S;			//Hinten
int E;			//Rechts
int W;			//Links
int colorw;

/// DO NOT DELETE THIS METHOD
/// It is called every 1ms and e.g. can be used for implementing a
/// real time counter / clock.
void user_1ms_isr_type2(void) {
}

void ecrobot_device_initialize(void) {

}

void ecrobot_device_terminate(void) {
}

// Every robot should use a little Kappa.
void kappa() {
    EXTERNAL_BMP_DATA(kappa);

    static unsigned char lcd[8*100];
    memset(lcd, 0x00, sizeof(lcd));

    ecrobot_bmp2lcd(BMP_DATA_START(kappa), lcd, 100, 64);
    display_clear(1);
    display_bitmap_copy(lcd, 100, 8, 0, 0);
    display_update();
}

void kompset(int turndir) {		//Speichert aktelle Fahrtrichtung
	dir = (dir + turndir)%4;
}

void set() {	//Kalibrierung auf Schwarz und Weiß
	//hier möglichst nix ändern, da es zum Glück ordentlich funzt
	int colorb;
	int colors;	//colors means senseless, Name ist Programm.
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

int search(int kind) {				//Suche nach schwarzer Linie
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
  	while (i < 20) {		//Schwarzkontrolle immer nach 20ms
  		systick_wait_ms(20);	//Rechtsdrehen und suchen
  		i++;
  		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
  			return 1;		//= schwarz gefunden
  	}
	turnl();				//Linksdrehen und suchen
	i = 0;
	while (i < 30) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
		return 1;
	}
	if (kind == 2) {
		turnr();				//Zurück-/Rechtsdrehen. Suche eigentlich sinnlooouuus, aber Sicherheit usw.
		i = 0;
		while (i < 15) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
			return 1;
		}
	}
  return 0;
}

int shortsearch(int kind) {
	turnl();				//Linksdrehen und suchen
	int i = 0;
	while (i < 5) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
		return 1;
	}
	turnr();
  	if (kind == 2)
  		i = 0;
	while (i < 10) {		//Schwarzkontrolle immer nach 20ms
		systick_wait_ms(20);	//Rechtsdrehen und suchen
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
			return 1;		//= schwarz gefunden
	}
	turnr();
	if (kind == 2) {
		turnl();				//Linksdrehen und suchen
		i = 0;
  		while (i < 5) {
  			systick_wait_ms(20);
  			i++;
  			if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
  				return 1;
  		}
	}
	return 0;
}

void tokenfound() {			//tokenfound = Token gefunden, okay?!
	ecrobot_set_motor_speed(NXT_PORT_A, 100);
	ecrobot_set_motor_speed(NXT_PORT_B, -50);
	ecrobot_set_motor_speed(NXT_PORT_C, -50);
	systick_wait_ms(300);
	stop();
	kappa();
	sound(VOLUME);				//Superhit des Jahrhunderts wird abgespielt
	ecrobot_set_motor_speed(NXT_PORT_A, 0);
}
/*
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
	int sw = search(2);	//bei 0 ist alles weiß -> Knoten
	if (sw > 0)
	{
		int btokenfound2 = drive();
		if (btokenfound2==2) // ROBOT_TOKENFOUND
			btokenfound=2;
	}

	return btokenfound;
}
*/
void setonline() {			//an richtsche edge gehen
	search(2);
	//turnr();
	//while (ecrobot_get_light_sensor(NXT_PORT_S3) > color) {
	//}
	stop();
}

int driveonline () {		//eigentlich drive_on_edge
	setonline();
	int atokenfound = 1;
	float daneben;
	int	equalizer;
	int line = 1;
	setonline();
	int speed;
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (line) {
		daneben = ecrobot_get_light_sensor(NXT_PORT_S3) - color;	//Daneben-fahr-Wert-Berechnung
		if ((ecrobot_get_motor_rev(NXT_PORT_C) - revn) < 450) {
			speed = 80;
			if (ecrobot_get_light_sensor(NXT_PORT_S3) < (colorw + 20)){
				turnr();
					while (ecrobot_get_light_sensor(NXT_PORT_S3) > color) {
					}
				if (shortsearch(2) == 0)		//zur Sicherheit, check again
					search(2);
			}
		}
		else {
			speed = 60;
			if (ecrobot_get_light_sensor(NXT_PORT_S3) < (colorw + 30)){
				if (shortsearch(2) == 0)				//zur Sicherheit, check again
					line = 0;
			}
		}
		equalizer = (int) daneben * 1/3; 			//Wie viel Geschwindigkeitsänderung
		ecrobot_set_motor_speed(NXT_PORT_B, (speed + equalizer));		//Speedanpassung je nach Helligkeit
		ecrobot_set_motor_speed(NXT_PORT_C, (speed - equalizer));
		if(ecrobot_get_touch_sensor(NXT_PORT_S1) || ecrobot_get_touch_sensor(NXT_PORT_S2)) {
			atokenfound = 2;   //laufende Suche ob Token im Weg steht
			tokenfound();
			setonline();
			go();
		}
	}
	return atokenfound;
}


int move() {
	int btokenfound = driveonline();
	go();			//Fährt auf Knoten
	turnrev(200);
	stop();
	return btokenfound;
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
	display_clear(1);
	display_goto_xy(5,3);
	display_string("Knoten.");
	display_update();
	int direct = 1 * search(1);	//guckt ob straight da ist
	turnl();
	int i = 1;
	int j = 0;			//guckt ob left da ist
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (i) {
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (580))
			i = 0;
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (350) && ((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (50)) {
				if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
					j = 1;
		}
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (450)) {
			if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
				i = 0;
		}
	}
	direct = direct + 2 * j;
	j=0;
	i=1;
	revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (i) {
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (270))
			i = 0;
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (150)) {
				if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
					j = 1;
		}
	}
	if (j==0)
		direct = direct + 4 * search(2);	//guckt ob right da ist
	else
		direct = direct + 4 * j;
	N = 0;
	E = 0;
	S = 0;
	W = 0;
	NESW(2);   //Kante umrechnen die zurück geht
	stop();
	//gefundene Richtungen werden

	display_clear(1);
	display_goto_xy(0,0);
	display_string("Richtungen:");
	switch (direct) {
		case 0:
			display_goto_xy(3,6);
			display_string("SACKGASSE!");
			break;
		case 1:
			printDir(0);
			NESW(0);
			break;
		case 2:
			printDir(1);
			NESW(3);
			break;
		case 3:
			printDir(0);
			printDir(1);
			NESW(3);
			NESW(0);
			break;
		case 4:
			printDir(2);
			NESW(1);
			break;
		case 5:
			printDir(0);
			printDir(2);
			NESW(1);
			NESW(0);
			break;
		case 6:
			printDir(1);
			printDir(2);
			NESW(1);
			NESW(3);
			break;
		case 7:
			printDir(0);
			printDir(1);
			printDir(2);
			NESW(0);
			NESW(1);
			NESW(3);
	}
	display_update();

	kompset(1);
	N = N * 0x10;
	S = S * 0x20;
	W = W * 0x40;
	E = E * 0x80;

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
	display_clear(1);
	display_goto_xy(0,3);
	display_string("My name is Horst.");
	display_update();
	stop();
	systick_wait_ms(1000);
	display_goto_xy(3,4);
	display_string("James Horst.");
	display_update();
    systick_wait_ms(1500);
	systick_wait_ms(1500);
	display_goto_xy(3,6);
	display_string("Thanks for");
	display_goto_xy(1,7);
	display_string("driving /w me.");
	display_update();
	systick_wait_ms(4000);

    EXTERNAL_BMP_DATA(kappa);
    EXTERNAL_BMP_DATA(kappa2);


    static unsigned char lcd1[8*100];
    static unsigned char lcd2[8*100];
    memset(lcd1, 0x00, sizeof(lcd1));
    memset(lcd2, 0x00, sizeof(lcd2));

    ecrobot_bmp2lcd(BMP_DATA_START(kappa), lcd1, 100, 64);
    ecrobot_bmp2lcd(BMP_DATA_START(kappa2), lcd2, 100, 64);

	while(1){
        display_clear(1);
        display_bitmap_copy(lcd1, 100, 8, 0, 0);
        display_update();
        systick_wait_ms(50);
        display_clear(1);
        display_bitmap_copy(lcd2, 100, 8, 0, 0);
        display_update();
        systick_wait_ms(50);
		}
}
