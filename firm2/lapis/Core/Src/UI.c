/*
 * UI.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include "UI.h"
#include "timer.h"
#include "motor.h"
#include"main.h"

void LED(uint8_t hex) {
	if ((hex & 0b0001) == 0b0001) {
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_ON);
	} else {
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, LED_OFF);
	}
	if ((hex & 0b0010) == 0b0010) {
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_ON);
	} else {
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, LED_OFF);
	}
	if ((hex & 0b0100) == 0b0100) {
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_ON);
	} else {
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, LED_OFF);
	}
	if ((hex & 0b1000) == 0b1000) {
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_ON);
	} else {
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, LED_OFF);
	}
}

extern TIM_HandleTypeDef htim2;

void tone(uint32_t tone, uint32_t ms) {
	PWMconfig pwm_config = { BUZZER_TIM_HANDLE, BUZZER_CHANNEL, tone, 10,
			170000000 };

	/* Infinite loop */
	PWM_Set(&pwm_config);
	HAL_TIM_PWM_Start_IT(BUZZER_TIM_HANDLE, BUZZER_CHANNEL);
	//		printf("start\n");
	Delay_ms(ms);
	HAL_TIM_PWM_Stop_IT(BUZZER_TIM_HANDLE, BUZZER_CHANNEL);
	//		printf("stop\n");
}

//music
void music(void) {
//	HAL_Delay(50);
	tone(tone_C, 50);
//	HAL_Delay(50);
	tone(tone_D, 50);
//	HAL_Delay(50);
	tone(tone_E, 50);
//	HAL_Delay(50);
	tone(tone_F, 50);
//	HAL_Delay(50);
	tone(tone_G, 50);
//	HAL_Delay(50);
	tone(tone_A, 50);
//	HAL_Delay(50);
	tone(tone_B, 50);
//	HAL_Delay(50);
	tone(tone_hiC, 50);
//	HAL_Delay(50);
}

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim5;

void fale_safe(uint8_t error) {
	HAL_TIM_Base_Stop_IT(&htim1); //1kHz speed conntrol
	HAL_TIM_Base_Stop_IT(&htim3); //4kHz wall sensor
	HAL_TIM_Base_Stop_IT(&htim5); //10kHz odmetry
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
//	Delay_ms(10);
	printf("fale safe errcode:%d\n", error);
	for (;;) {
		LED(16);
		tone(tone_hiC, 100);
		HAL_Delay(100);

	}
	return;
}

