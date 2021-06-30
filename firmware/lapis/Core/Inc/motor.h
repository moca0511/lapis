/*
 * motor.h
 *
 *  Created on: 2021/06/22
 *      Author: junmo
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_


#include "main.h"




//motor
#define MR (0)
#define ML (1)

#define MOVE_FORWARD 0
#define MOVE_BACK 1
//タイマチャンネル
#define MR_EN_CHANNEL TIM_CHANNEL_2
#define ML_EN_CHANNEL TIM_CHANNEL_4
#define MR_TIM_HANDLE &htim4
#define ML_TIM_HANDLE &htim4
void init_Motor(void);
void set_ML_direction(uint8_t direction);
void set_MR_direction(uint8_t direction);
void set_ML_EN(float volt);
void set_MR_EN(float volt);
#endif /* INC_MOTOR_H_ */
