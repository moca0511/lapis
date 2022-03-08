/*
 * wallsensor.c
 *
 *  Created on: Jun 22, 2021
 *      Author: junmo
 */

#include "wallsensor.h"
#include "timer.h"
#include "adc.h"
#include "UI.h"
#include"main.h"

t_sensor sensorData[4] = { 0 };

//uint32_t wall_config[12];
void init_wallSensor(void) {
	sensorData[RS].ref = RS_WALL;
	sensorData[LS].ref = LS_WALL;
	sensorData[RF].ref = RF_WALL;
	sensorData[LF].ref = LF_WALL;
	sensorData[RS].th_wall =  RS_TH;
	sensorData[RF].th_wall = sensorData[RF].th_control = RF_TH;
	sensorData[LS].th_wall =  LS_TH;
	sensorData[LF].th_wall = sensorData[LF].th_control = LF_TH;
	sensorData[RS].th_control = RS_CON;
	sensorData[LS].th_control = LS_CON;
	HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, RESET);
	HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, RESET);
	return;
}

/*
 * 説明：壁センサ読み取りタスク
 * 引数：無し
 * 戻り値：無し
 */
uint32_t wallSensorRead(uint8_t select) {
	HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, RESET);
	HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, RESET);
	for (int i = 0; i < 700; i++)
		;
	sensorData[select].d_value = get_adc(select);
	switch (select) {
	case RS:
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, SET);
		break;
	case RF:
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, SET);
		break;
	case LF:
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, SET);
		break;
	case LS:
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, SET);
		break;
	default:
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, RESET);
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, RESET);
		break;

	}

	for (int i = 0; i < 700; i++)
		;

	sensorData[select].value = get_adc(select) - sensorData[select].d_value;
	HAL_GPIO_WritePin(LED_LSRF_GPIO_Port, LED_LSRF_Pin, RESET);
	HAL_GPIO_WritePin(LED_LFRS_GPIO_Port, LED_LFRS_Pin, RESET);

	sensorData[select].p_value = sensorData[select].value;



	if (sensorData[select].value >= sensorData[select].th_wall) {
		sensorData[select].error = sensorData[select].value
					- sensorData[select].ref;
		sensorData[select].is_wall = sensorData[select].is_control = true;
	} else {
		sensorData[select].is_wall = sensorData[select].is_control = false;
		sensorData[select].error = 0;
	}

	return 0;
}

/*
 * 説明：指定壁センサ値取得
 * 引数：select 壁センサ選択
 * 戻り値：センサ値
 */
uint32_t get_sensordata(uint8_t select) {
	switch (select) {
	case RS:
		return sensorData[RS].value;
	case RF:
		return sensorData[RF].value;
	case LS:
		return sensorData[LS].value;
	case LF:
		return sensorData[LF].value;
	default:
		return 0;
	}
}

t_bool get_sensor_iswall(uint8_t select) {
	switch (select) {
	case RS:
		return sensorData[RS].is_wall;
	case RF:
		return sensorData[RF].is_wall;
	case LS:
		return sensorData[LS].is_wall;
	case LF:
		return sensorData[LF].is_wall;
	default:
		return 0;
	}
}

t_bool get_sensor_iscontrol(uint8_t select) {
	switch (select) {
	case RS:
		return sensorData[RS].is_control;
	case RF:
		return sensorData[RF].is_control;
	case LS:
		return sensorData[LS].is_control;
	case LF:
		return sensorData[LF].is_control;
	default:
		return 0;
	}
}

int16_t get_sensor_error(uint8_t select) {
	switch (select) {
	case RS:
		return sensorData[RS].error;
	case RF:
		return sensorData[RF].error;
	case LS:
		return sensorData[LS].error;
	case LF:
		return sensorData[LF].error;
	default:
		return 0;
	}
}
