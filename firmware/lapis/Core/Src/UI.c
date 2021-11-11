/*
 * UI.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include "UI.h"
#include"timer.h"

void UILED_SET(uint8_t hex){
	if((hex&0b0001)==0b0001){
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,LED_ON);
	}else{
		HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,LED_OFF);
	}
	if((hex&0b0010)==0b0010){
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,LED_OFF);
		}
	if((hex&0b0100)==0b0100){
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,LED_OFF);
		}
	if((hex&0b1000)==0b1000){
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,LED_OFF);
		}
}



extern TIM_HandleTypeDef htim2;

void tone(uint32_t tone,uint32_t ms){
	PWMconfig pwm_config = { BUZZER_TIM_HANDLE, BUZZER_CHANNEL, tone, 10, 50000000 };

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
	Delay_ms(50);
	tone(tone_C, 50);
	Delay_ms(50);
	tone(tone_D, 50);
	Delay_ms(50);
	tone(tone_E, 50);
	Delay_ms(50);
	tone(tone_F, 50);
	Delay_ms(50);
	tone(tone_G, 50);
	Delay_ms(50);
	tone(tone_A, 50);
	Delay_ms(50);
	tone(tone_B, 50);
	Delay_ms(50);
	tone(tone_hiC, 50);
	Delay_ms(50);
}

void fale_safe(uint8_t error) {
	int8_t count = 0,sound=0;
	//mortor_stop();
	//wall_sensor_stop();
	//tim1_stop();
	set_ML_EN(0.0f);
		set_MR_EN(0.0f);
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

void debag_print(float tick,float omega,float deg,float enc_R,float enc_L,float speed_R,float speed_L,float speed,uint32_t wall_RS,uint32_t wall_RF,uint32_t wall_LF,uint32_t wall_LS,float posX,float posY,float batt){
	printf(",%5.1f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%lu,%lu,%lu,%lu,%5.5f,%5.5f,%5.5f\n",tick,omega,deg,enc_R,enc_L,speed_R,speed_L,speed,wall_RS,wall_RF,wall_LF,wall_LS,posX,posY,batt);
}
