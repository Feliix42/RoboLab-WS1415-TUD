#include "../h/orchester.h"

void sound(int l) {
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
