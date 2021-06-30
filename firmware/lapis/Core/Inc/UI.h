/*
 * UI.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include "main.h"

void UILED_SET(uint8_t HEX);
void debag_print(float tick,float omega,float deg,float enc_R,float enc_L,float speed_R,float speed_L,float speed,uint32_t wall_RS,uint32_t wall_RF,uint32_t wall_LF,uint32_t wall_LS,float posX,float posY,float batt);
#define LED_ON GPIO_PIN_RESET
#define LED_OFF GPIO_PIN_SET


#endif /* INC_UI_H_ */
