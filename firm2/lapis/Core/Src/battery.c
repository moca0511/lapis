/*
 * battery.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#include"adc.h"
#include"UI.h"
#include"battery.h"
#include"uart.h"
#include"main.h"

float readBattery(void) {
	/* USER CODE BEGIN BatteryCheck */
	/* Infinite loop */
	float batt_level = 0;
	static int8_t count = 0;
	static float batt_level_prev = BATT_NORMAL;
	char buf[100];
	batt_level = get_adc(BATT) * 2.0f;
	batt_level = (batt_level / (ADC_MAX / 3.3f));
	batt_level = (batt_level + batt_level_prev) / 2;

	return batt_level;
}
