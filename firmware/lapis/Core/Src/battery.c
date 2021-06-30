/*
 * battery.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#include"battery.h"
#include"adc.h"
#include"buzzer.h"
float readBattery(void) {
	/* USER CODE BEGIN BatteryCheck */
	/* Infinite loop */
	float batt_level = 0;
	static int8_t count = 0;

	batt_level = get_adc(BATT) * 2;
	batt_level = (batt_level / (ADC_MAX / 3.3)) ;

	if (batt_level <= BATT_WARNING) { //warning
		count++;
		if (count == 10) {
			printf("datt=%f\n", batt_level);
			fale_safe(BATT_EMPTY);
		}
	} else {
		count = 0;
	}
	return batt_level;
}
