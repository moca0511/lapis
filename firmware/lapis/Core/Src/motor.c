/*
 * motor.c
 *
 *  Created on: 2021/06/22
 *      Author: junmo
 */
#include"motor.h"
#include"main.h"
#include"battery.h"

uint32_t MotorSPEED_R = 0;
uint32_t MotorSPEED_L = 0;
extern TIM_HandleTypeDef htim4;
void init_Motor(void) {
	HAL_TIM_PWM_Start_IT(MR_TIM_HANDLE, MR_EN_CHANNEL);
		HAL_TIM_PWM_Start_IT(ML_TIM_HANDLE, ML_EN_CHANNEL);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0);
	set_MR_EN(0);
	return;
}

void set_ML_direction(uint8_t direction) {
	switch (direction) {
	case MOVE_FORWARD:
		HAL_GPIO_WritePin(ML_PHASE_GPIO_Port, ML_PHASE_Pin, RESET);
		break;
	case MOVE_BACK:
		HAL_GPIO_WritePin(ML_PHASE_GPIO_Port, ML_PHASE_Pin, SET);
		break;
	default:
		HAL_GPIO_WritePin(ML_PHASE_GPIO_Port, ML_PHASE_Pin, RESET);
		break;
	}
	return;
}
void set_MR_direction(uint8_t direction) {
	switch (direction) {
	case MOVE_FORWARD:
		HAL_GPIO_WritePin(MR_PHASE_GPIO_Port, MR_PHASE_Pin, SET);
		break;
	case MOVE_BACK:
		HAL_GPIO_WritePin(MR_PHASE_GPIO_Port, MR_PHASE_Pin, RESET);
		break;
	default:
		HAL_GPIO_WritePin(MR_PHASE_GPIO_Port, MR_PHASE_Pin, SET);
		break;
	}
	return;
}
/*
 * 説明：左モータ速度設定
 * 引数：speed 速度(mm/s)
 * 戻り値：無し
 */
void set_ML_EN(float volt) {

//	HAL_TIM_PWM_Stop_IT(ML_TIM_HANDLE, ML_EN_CHANNEL);
	__HAL_TIM_SET_COMPARE(ML_TIM_HANDLE, ML_EN_CHANNEL, (volt/readBattery())*1000);
//	HAL_TIM_PWM_Start_IT(ML_TIM_HANDLE, ML_EN_CHANNEL);
	//	osSemaphoreRelease(SchengeRSemHandle);
	return;
}
/*
 * 説明：右モータ速度設定
 * 引数：speed 速度(mm/s)
 * 戻り値：無し
 */
void set_MR_EN(float volt) {
//	HAL_TIM_PWM_Stop_IT(MR_TIM_HANDLE, MR_EN_CHANNEL);
	__HAL_TIM_SET_COMPARE(MR_TIM_HANDLE, MR_EN_CHANNEL, (volt/readBattery())*1000);
//	HAL_TIM_PWM_Start_IT(MR_TIM_HANDLE, MR_EN_CHANNEL);
	//	osSemaphoreRelease(SchengeRSemHandle);
	return;
}
