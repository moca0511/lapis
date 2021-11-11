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

extern ADC_HandleTypeDef hadc1;
//extern TIM_HandleTypeDef htim3;
int32_t sensorData[4] = { 0, 0, 0, 0 };
//uint32_t wall_config[12];
void init_wallSensor(void) {
	HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, RESET);
	HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, RESET);
	return;
}
/*
 * 説明：壁センサ読み取りタスク
 * 引数：無し
 * 戻り値：無し
 */
uint32_t wallSensorRead(uint8_t select) {
	/* USER CODE BEGIN Sensor */

//	HAL_TIM_PWM_Start_IT(LED_TIM_HANDLE, LED_LFRS_CHANNEL);
//	__HAL_TIM_SET_COMPARE(LED_TIM_HANDLE, LED_LFRS_CHANNEL, 1000);
//	//wait20us
////			Delay_us(20);
//
////Sensor RS read
//	ADC_config.channel = ADC_CHANNEL_RS;
//	sensorData.ADC_DATA_RS = data_buf = ADConv(&ADC_config);
//	HAL_TIM_PWM_Stop_IT(LED_TIM_HANDLE, LED_LFRS_CHANNEL);
	int32_t dataBuf=0;
	HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, RESET);
	HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, RESET);
	Delay_us(30);
	switch (select) {
	case RS:
		dataBuf = get_adc(RS);
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, SET);
		//wait30us
		Delay_us(30);

//Sensor RS read
		dataBuf = get_adc(RS);
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, RESET);
		break;
	case RF:
		dataBuf = get_adc(RF);
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, SET);
		//wait30us
		Delay_us(30);

		//Sensor RS read
		dataBuf = get_adc(RF);
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, RESET);
		break;
	case LF:
		dataBuf = get_adc(LF);
		//LED_RS on
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, SET);
		//wait30us
		Delay_us(30);

		//Sensor RS read
		dataBuf = get_adc(LF);
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, RESET);
		break;
	case LS:
		dataBuf = get_adc(LS);
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, SET);
		//wait30us
		Delay_us(30);

		//Sensor RS read
		dataBuf = get_adc(LS);
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, RESET);
		break;
	default:
		HAL_GPIO_WritePin(LED_LSRF_GPIO_Port,LED_LSRF_Pin, RESET);
		HAL_GPIO_WritePin(LED_LFRS_GPIO_Port,LED_LFRS_Pin, RESET);
		break;

	}
	if(dataBuf<0){
		sensorData[select]=0;
	}else{
		sensorData[select]=dataBuf;
	}
	return 0;
	/* USER CODE END Sensor */
}
///*
// * 説明：指定壁センサの値を複数回読み平均をとる
// * 引数：select 壁センサ指定
// * 戻り値：無し
// */
//uint32_t read_wall(uint8_t select) {
//	uint32_t value = 0;
//	uint32_t *pADCdata;
//	switch (select) {
//	case RS:
//		pADCdata = &sensorData.ADC_DATA_RS;
//		break;
//	case RF:
//		pADCdata = &sensorData.ADC_DATA_RF;
//		break;
//	case LS:
//		pADCdata = &sensorData.ADC_DATA_LS;
//		break;
//	case LF:
//		pADCdata = &sensorData.ADC_DATA_LF;
//		break;
//	default:
//		return 0;
//	}
//	value = *pADCdata;
//	for (int i = 0; i < 5; i++) {
//		value += *pADCdata;
//		value /= 2;
//		HAL_Delay(1);
//	}
//	return value;
//}
//
///*
// * 説明：壁センサの各リファレンス値取得
// * 引数：無し
// * 戻り値：無し
// */
//void wall_calibration(void) {
//	RUNConfig RUN_config = { MOVE_FORWARD, 0, 0, 100, 500, (BLOCK_LENGTH
//			- NEZUTAKA_LENGTH) / 2 };
//	RUNConfig turn_config = { TURN_R, 0, 0, 100, 500, 90 };
//
//	tone(tone_hiC, 10);
//	for (int i = 0; i < 12; i++) {
//		wall_config[i] = 0;
//	}
//
//	osThreadFlagsSet(Sensor_TaskHandle, TASK_START);
//	HAL_Delay(100);
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("RS_threshould\n");
//		osMutexRelease(UART_MutexHandle);
//	}
//	UILED_SET(1);
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 1) {
//		HAL_Delay(50);
//	}
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 0) {
//		HAL_Delay(50);
//	}
//	tone(tone_hiC, 50);
//	wall_config[RS_threshold] = read_wall(RS);
//	tone(tone_C, 50);
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("LS_threshould\n");
//		osMutexRelease(UART_MutexHandle);
//	}
//	UILED_SET(8);
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 1) {
//		HAL_Delay(50);
//	}
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 0) {
//		HAL_Delay(50);
//	}
//	tone(tone_hiC, 50);
//
//	wall_config[LS_threshold] = read_wall(LS);
//	tone(tone_C, 50);
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("F_threshould\n");
//		osMutexRelease(UART_MutexHandle);
//	}
//	UILED_SET(6);
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 1) {
//		HAL_Delay(50);
//	}
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 0) {
//		HAL_Delay(50);
//	}
//	tone(tone_hiC, 50);
//	wall_config[RF_threshold] = read_wall(RF);
//	wall_config[LF_threshold] = read_wall(LF);
//	tone(tone_C, 50);
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("ALL_WALL&FREE\n");
//		osMutexRelease(UART_MutexHandle);
//	}
//	UILED_SET(15);
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 1) {
//		HAL_Delay(50);
//	}
//	while (HAL_GPIO_ReadPin(OK_GPIO_Port, OK_Pin) == 0) {
//		HAL_Delay(50);
//	}
//	tone(tone_hiC, 50);
//	osDelay(100);
//	wall_config[RS_WALL] = read_wall(RS);
//	wall_config[LS_WALL] = read_wall(LS);
//	wall_config[RF_FREE] = read_wall(RF);
//	wall_config[LF_FREE] = read_wall(LF);
//	straight(RUN_config, 0, 0, 0);
//	turn(turn_config);
//	osDelay(100);
//	wall_config[LS_FREE] = read_wall(LS);
//	wall_config[RF_WALL] = read_wall(RF);
//	wall_config[LF_WALL] = read_wall(LF);
//	turn_config.value = 180;
//	turn_config.direction = TURN_L;
//	turn(turn_config);
//	osDelay(100);
//	wall_config[RS_FREE] = read_wall(RS);
//	wall_config[RF_WALL] = (wall_config[RF_WALL] + read_wall(RF)) / 2;
//	wall_config[LF_WALL] = (wall_config[LF_WALL] + read_wall(LF)) / 2;
//	osThreadFlagsSet(Sensor_TaskHandle, TASK_STOP);
//	turn_config.value = 90;
//	turn_config.direction = TURN_R;
//	turn(turn_config);
//	sirituke();
////	mortor_sleep();
//
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		for (int i = 0; i < 12; i++) {
//			printf("wall[%d]=%ld,", i, wall_config[i]);
//		}
//		printf("\n");
//		osMutexRelease(UART_MutexHandle);
//	}
//	tone(tone_hiC, 50);
//}

/*
 * 説明：指定壁センサ値取得
 * 引数：select 壁センサ選択
 * 戻り値：センサ値
 */
uint32_t get_sensordata(uint8_t select) {
	switch (select) {
	case RS:
		return sensorData[RS];
	case RF:
		return sensorData[RF];
	case LS:
		return sensorData[LS];
	case LF:
		return sensorData[LF];
	default:
		return 0;
	}
}
