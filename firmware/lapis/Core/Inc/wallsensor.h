/*
 * wallsensor.h
 *
 *  Created on: Jun 22, 2021
 *      Author: junmo
 */

#ifndef INC_WALLSENSOR_H_
#define INC_WALLSENSOR_H_

#include "main.h"




//LED PWM出力チャンネル
//#define LED_TIM_HANDLE &htim3
#define LED_LFRS_CHANNEL TIM_CHANNEL_1
#define LED_LSRF_CHANNEL TIM_CHANNEL_2
void init_wallSensor(void);
uint32_t wallSensorRead(uint8_t select);
uint32_t read_wall(uint8_t select);//指定のセンサのADC値を複数回取得し平均値を返す
void wall_calibration(void);//センサリファレンス値取得
uint32_t get_sensordata(uint8_t select);//指定センサの値を取得

#endif /* INC_WALLSENSOR_H_ */
