/*
 * battery.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_
#include "adc.h"
#include"main.h"

#define ADC_CHANNEL_BATTERY ADC_CHANNEL_4

#define BATT_WARNING 3.6
#define BATT_NORMAL 3.8
#define BATT_HIGH 4.0
#define BATT_FULL 4.2

float readBattery(void);


#endif /* INC_BATTERY_H_ */
