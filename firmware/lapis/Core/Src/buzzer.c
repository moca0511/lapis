/*
 * buzzer.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include"buzzer.h"
#include"timer.h"

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
