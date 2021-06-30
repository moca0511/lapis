/*
 * error.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_ERROR_H_
#define INC_ERROR_H_
#include"main.h"
void fale_safe(uint8_t error);
typedef enum {
	BATT_EMPTY,
	ACCELE_ERROR,
	GYRO_ERROR,
	ADC_ERROR,
	NON
} ERROR_NAMBER;

#endif /* INC_ERROR_H_ */
