/*
 * error.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include"timer.h"
#include"error.h"
#include"buzzer.h"
void fale_safe(uint8_t error) {
	int8_t count = 0,sound=0;
	//mortor_stop();
	//wall_sensor_stop();
	//tim1_stop();
	printf("fale safe errcode:%d\n", error);
	for (;;) {
		if (sound == 0) {
			sound = 1;
			tone(tone_hiC, 1000);
		} else {
			Delay_ms(1000);
			sound = 0;
		}
	}
	return;
}
