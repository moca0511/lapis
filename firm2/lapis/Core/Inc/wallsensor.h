/*
 * wallsensor.h
 *
 *  Created on: Jun 22, 2021
 *      Author: junmo
 */

#ifndef INC_WALLSENSOR_H_
#define INC_WALLSENSOR_H_

#include "main.h"
#include "lapis.h"

typedef struct
{
	uint16_t value;		//現在の値
	uint16_t d_value;		//差分フィルタ用
	uint16_t p_value;		//１mS過去の値
	uint16_t p2_value;
	int16_t error;		//value - ref
	uint16_t ref;		//リファレンス値
	uint16_t th_wall;		//壁があるか否かの閾値
	uint16_t th_control;	//制御をかけるか否かの閾値
	t_bool is_wall;		//壁があるか無いか ( true = 壁あり false = 壁なし )
	t_bool is_control;	//制御に使うか否か
}t_sensor;			//センサ構造体

#define RF_WALL 1630
#define LF_WALL 1220
#define RS_WALL 620
#define LS_WALL 850

#define RF_TH 90
#define LF_TH 80
#define RS_TH 300
#define LS_TH 330

#define RS_CON 400
#define LS_CON 500

//LED PWM出力チャンネル
//#define LED_TIM_HANDLE &htim3
//#define LED_LFRS_CHANNEL TIM_CHANNEL_1
//#define LED_LSRF_CHANNEL TIM_CHANNEL_2
void init_wallSensor(void);
uint32_t wallSensorRead(uint8_t select);
uint32_t read_wall(uint8_t select);//指定のセンサのADC値を複数回取得し平均値を返す
void wall_calibration(void);//センサリファレンス値取得
uint32_t get_sensordata(uint8_t select);//指定センサの値を取得
t_bool get_sensor_iswall(uint8_t select);
t_bool get_sensor_iscontrol(uint8_t select);
int16_t get_sensor_error(uint8_t select);
#endif /* INC_WALLSENSOR_H_ */
