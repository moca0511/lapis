/*
 * UI.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */
#include "UI.h"


void UILED_SET(uint8_t hex){
	if((hex&0b0001)==0b0001){
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,LED_ON);
	}else{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin,LED_OFF);
	}
	if((hex&0b0010)==0b0010){
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin,LED_OFF);
		}
	if((hex&0b0100)==0b0100){
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin,LED_OFF);
		}
	if((hex&0b1000)==0b1000){
			HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,LED_ON);
		}else{
			HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin,LED_OFF);
		}
}

void debag_print(float tick,float omega,float deg,float enc_R,float enc_L,float speed_R,float speed_L,float speed,uint32_t wall_RS,uint32_t wall_RF,uint32_t wall_LF,uint32_t wall_LS,float posX,float posY,float batt){
	printf(",%5.1f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%lu,%lu,%lu,%lu,%5.5f,%5.5f,%5.5f\n",tick,omega,deg,enc_R,enc_L,speed_R,speed_L,speed,wall_RS,wall_RF,wall_LF,wall_LS,posX,posY,batt);
}
