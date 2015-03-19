#include "../h/main.h"
int color;

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
	ecrobot_set_motor_speed(NXT_PORT_B, 53);
	ecrobot_set_motor_speed(NXT_PORT_C, 50);

	// 205 rev(C) = 10cm bei 30 speed
	// 205 rev(C) = 10,8cm bei 60 speed
}

void turnrev(int rev) {
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (rev)){
	}
}

void turnl() {
	ecrobot_set_motor_speed(NXT_PORT_B, -40);
	ecrobot_set_motor_speed(NXT_PORT_C, 40);
}

void turnr() {
	ecrobot_set_motor_speed(NXT_PORT_B, 40);
	ecrobot_set_motor_speed(NXT_PORT_C, -40);
}

void stop() {
	ecrobot_set_motor_speed(NXT_PORT_B, 0);
	ecrobot_set_motor_speed(NXT_PORT_C, 0);
}

void sound(){
	//ecrobot_sound_tone(200, 200, 40);
	ecrobot_sound_tone(262, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(294, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(330, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(349, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(392, 3000, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(392, 3000, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(440, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(440, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(440, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(440, 1500, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(392, 3000, 30);
	systick_wait_ms(500);
	ecrobot_sound_tone(392, 3000, 30);
}

void set() {
	//Kalibrierung auf Schwarz und Weiß
	int colorb;

	int colors;
	int i = 0;
	colors = ecrobot_get_light_sensor(NXT_PORT_S3);
	systick_wait_ms(300);
	while (i<10) {
		colorb = ecrobot_get_light_sensor(NXT_PORT_S3);
		i++;
	}
		display_int(colorb,4);
	turnr();
	systick_wait_ms(400);
	stop();
	int colorw;
	while (i<20) {
		colorw = ecrobot_get_light_sensor(NXT_PORT_S3);
		i++;
	}
	display_int(colorw,4);
	display_update();
	turnl();
	systick_wait_ms(400);
	color = (colorw + colorb)/2;
	stop();
	systick_wait_ms(100);
}

int search() {
  	int i;
	turnr();
  	i = 0;
  	while (i < 20) {
  		systick_wait_ms(20);
  		i++;
  		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
  			return 1;
  	}
	turnl();
	i = 0;
	while (i < 40) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
		return 1;
	}
	turnr();
	i = 0;
	while (i < 20) {
		systick_wait_ms(20);
		i++;
		if ((ecrobot_get_light_sensor(NXT_PORT_S3)) > (color))
			return 1;
	}
  return 0;
}

void drive() {
	int running = 1;
	int colort;
	go();
	systick_wait_ms(50);
	//gucken obs noch schwarz ist, sonst wird gesucht
	while(running){
		colort = ecrobot_get_light_sensor(NXT_PORT_S3);
		if ((colort) < (color))
			running = 0;
	}
	//bei 0 ist alles weiß -> Knoten
	int sw = search();
	if (sw > 0)
		{ecrobot_status_monitor("Weiter gehts!");
		drive();
		}
}

void turn90 (int t) {
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	if (t>0) {
		turnl();
		t = t * 275;
		int revn = ecrobot_get_motor_rev(NXT_PORT_C);
		while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) < (t)) {
		}
	}
	else {
		turnr();
		t = t * 275;
		int revn = ecrobot_get_motor_rev(NXT_PORT_C);
		while (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (t)) {
		}
	}

}

void knoten() {
	ecrobot_status_monitor("Knoten");
	stop();
	// sound();
	go();
	turnrev(200);
							//100ms = 0,9...cm
							//5800ms = 365°
							//980rev(B) = 360°
	int direct = 1 * search();	//guckt ob straight da ist
	turnl();
	int i = 1;
	int j = 0;			//guckt ob left da ist
	int revn = ecrobot_get_motor_rev(NXT_PORT_C);
	while (i) {
		if (((ecrobot_get_motor_rev(NXT_PORT_C)) - revn) > (815))
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
	switch (direct) {
		case 0: ecrobot_status_monitor("haha Sackgasse"); break;
		case 1: ecrobot_status_monitor("nur Gerade"); break;
		case 2: ecrobot_status_monitor("nur Links"); break;
		case 3: ecrobot_status_monitor("Links u Gerade"); break;
		case 4: ecrobot_status_monitor("nur Rechts"); break;
		case 5: ecrobot_status_monitor("Rechts u Gerade"); break;
		case 6: ecrobot_status_monitor("Links u Rechts"); break;
		case 7: ecrobot_status_monitor("ueberall Kanten");
	}
	//ohne was zu tun gehts nach rechts
	switch (direct) {
		case 0: turn90(-1); break;
		case 1: turn90(1); break;
		case 2: turn90(2); break;
		case 3: turn90(1); break;
		case 4: break;
		case 5: turn90(1); break;
		case 6: turn90(0); break;
		case 7: turn90(2); break;
	}
}

TASK(OSEK_Main_Task) {

		ecrobot_set_light_sensor_active(NXT_PORT_S3);
		int a=0;
		set();
		while (a<10){
			a++;
			drive();
			knoten();
		}


		/*turnl();
		int i = 1;
		while(i) {
			if ((ecrobot_get_motor_rev(NXT_PORT_C)) > 1080)
				i=0;
		}*/
		//search();

		/* Touch Control:
		int running = 1;
		int i=0;
		while(running) {
				if(ecrobot_get_touch_sensor(NXT_PORT_S1))
					running = 0;
				if(i>4)
					break;
				i++;
				display_clear(1);
				display_int(ecrobot_get_light_sensor(NXT_PORT_S3), 4);
				display_update();
				systick_wait_ms(500);
		}
		if ((ecrobot_get_motor_rev(NXT_PORT_B) > 980) //360°
		systick_wait_ms(5000);
		*/
		ecrobot_status_monitor("Ende im Gelaende!");
		stop();
		while(1){

		}
}
