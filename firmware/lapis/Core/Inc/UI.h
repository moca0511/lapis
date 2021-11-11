/*
 * UI.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include "main.h"

#define BUZZER_TIM_HANDLE &htim2
#define BUZZER_CHANNEL TIM_CHANNEL_1

//ブザー設定
typedef struct {
	uint32_t tone;
	uint32_t ms;
} BuzzerConfig;

//音階周波数
typedef enum {
	tone_C = 1046,
	tone_D = 1174,
	tone_E = 1318,
	tone_F = 1396,
	tone_G = 1567,
	tone_A = 1760,
	tone_B = 1975,
	tone_hiC = 2093
} BUZZER_TONE;

typedef enum {
	BATT_EMPTY,
	ACCELE_ERROR,
	GYRO_ERROR,
	ADC_ERROR,
	NON
} ERROR_NAMBER;



void UILED_SET(uint8_t HEX);
void debag_print(float tick,float omega,float deg,float enc_R,float enc_L,float speed_R,float speed_L,float speed,uint32_t wall_RS,uint32_t wall_RF,uint32_t wall_LF,uint32_t wall_LS,float posX,float posY,float batt);
#define LED_ON GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET
void tone(uint32_t tone,uint32_t ms);//指定周波数の音を指定秒数流す
void music(void);//ピロピロ
void fale_safe(uint8_t error);

#endif /* INC_UI_H_ */
