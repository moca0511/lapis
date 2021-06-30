/*
 * timer.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"

extern TIM_HandleTypeDef htim1;
#define INTTERRUPT_10kHz_TIM_HANDLE &htim1






typedef struct {
	TIM_HandleTypeDef *htim;
	uint8_t pin;
	uint32_t hz;
	uint32_t duty;
	uint32_t timeclock;
} PWMconfig;

int PWM_Set(PWMconfig *config);
void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);

#endif /* INC_TIMER_H_ */
