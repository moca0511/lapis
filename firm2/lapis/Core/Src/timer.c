/*
 * timer.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include"uart.h"
#include "timer.h"
#include"main.h"

extern TIM_HandleTypeDef htim1;
int32_t timer_us = 0;
int8_t wait_usHandle = 0;
extern uint64_t now_time;

int PWM_Set(PWMconfig *config) {
	config->htim->Init.Prescaler = config->timeclock / 100 / (config->hz) - 1;
	config->htim->Init.Period = 100;
	if (HAL_TIM_PWM_Init(config->htim) != HAL_OK) {
		return -1;
	}
	__HAL_TIM_SET_COMPARE(config->htim, config->pin, config->duty);
	return 0;
}

void Delay_us(uint32_t us) {
	while (us > 0) {
		//NOP100回@100MHz = 1us
		//実際はwhile文、iの減算の処理がある。実測でNOP90回が1usに相当する。
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		asm("NOP");
		us--;
	}
}

void Delay_ms(uint32_t ms) {
	uint64_t start=now_time;
	if(start+ms>10000000){
		start=now_time=0;
	}
	while(now_time-start<ms);
	now_time=0;
	return;
}