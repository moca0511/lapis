/*
 * lapis.h
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#ifndef INC_LAPIS_H_
#define INC_LAPIS_H_
#include"main.h"
//　機体パラメータ
#define TIRE_DIAMETER   (14.3f)					//　タイヤの直径　52mm
#define TIRE_CIRCUIT    (PI * TIRE_DIAMETER)	//　タイヤの円周 163.363mm
#define TREAD_WIDTH     (38.0f)					//　トレッド幅　87.0mm(再計測)
#define LAPIS_LENGTH (45.0f)
#define LAPIS_M (0.012f)	//車体質量
#define GEAR_N (4.0f)	//ギア比
#define K_T (0.594f)	//モータトルク定数
#define K_E (0.062f)	//モータトルク定数
#define MOTOR_REG (6.7f)	//モータ巻き線抵抗
#define V_RETURN (0.062f)	//モータ逆起電圧定数
//#define TREAD_CIRCUIT   (TREAD_WIDTH * PI)		//360度旋回時にタイヤが動く距離　87*3.14mm 273.18mm
//#define	STEP_DEGREE  (360.0 / 16383.0)				//　ステッピングモータ1-2相励ステップ角（度/step) 0.9°
//#define	STEP_LENGTH	(TIRE_CIRCUIT * STEP_DEGREE / 360.0)	//1ステップで進む距離　0.408mm
//　迷路のパラメータ
#define	BLOCK_LENGTH  (90.0f)					//1区画 180mm
//　定数定義

typedef enum
{
	false = 0,	//偽
	true = 1,	//真
}t_bool;		//真偽値を取り扱う列挙型

typedef enum
{
	NON_MODE,
	STRAIGHT_MODE,
	TURN_MODE,
	F_WALL_MODE
}t_run_mode;

typedef struct
{
	float control;		//最終的な制御量
	float omega;		//目標角速度
	float p_omega;
	float theta;		//目標角度
	float p_theta;		//過去の目標角度
	float error;		//偏差
	float p_error;		//過去の偏差
	float diff;		//偏差の微分値
	float sum;		//偏差の積分値
	float sum_max;		//積分値の制限値
	float kp;		//比例制御定数
	float kd;		//微分制御定数
	float ki;		//積分制御定数
	t_bool enable;		//制御のon/off
}t_control;

//　最大速度
#define MAX_SPEED (3.0f)
#define MIN_SPEED (0.1f)
#define SPEED_KP (0.8f)
#define SPEED_KI (0.001f)
#define SPEED_KD (0.5f)
#define ANG_KP (0.3f)
#define ANG_KI (0.0025f)
#define ANG_KD (0.01f)
#define CON_WALL_KP (0.0003f)
#define CON_FWALL_KP (0.006f)

//typedef enum {
//	RS_WALL,
//	LS_WALL,
//	RF_WALL,
//	LF_WALL,
//	RS_FREE,
//	LS_FREE,
//	RF_FREE,
//	LF_FREE,
//	RS_threshold,
//	LS_threshold,
//	RF_threshold,
//	LF_threshold,
//	WALL_DATA_MAX
//} WALL_DATA;

#define MODE_NAME0 "AUTO RUN LO"
#define MODE_NAME1 "AUTO RUN HIGH"
#define MODE_NAME2 "DEBUG PRINT"
#define MODE_NAME3 "SENSOR LSRS CALIBRATION"
#define MODE_NAME4 "SENSOR ON/OFF"
#define MODE_NAME5 "MAZE_SAVE"
#define MODE_NAME6 "MAZE_LOAD"
#define MODE_NAME7 "MAP INIT"
#define MODE_NAME8 "PRINT MAP"
#define MODE_NAME9 "TANSAKU MAP"
#define MODE_NAME10 "SAITAN MAP"
#define MODE_NAME11 "ADACHI LO"
#define MODE_NAME12 "ADACHI HIGH"
#define MODE_NAME13 "SAITAN LO"
#define MODE_NAME14 "SAITAN MID"
#define MODE_NAME15 "SAITAN HIGH"

void lapis(void);
void MENU(int16_t *mode);
void mode0(void);
void mode1(void);
void mode2(void);
void mode3(void);
void mode4(void);
void mode5(void);
void mode6(void);
void mode7(void);
void mode8(void);
void mode9(void);
void mode10(void);
void mode11(void);
void mode12(void);
void mode13(void);
void mode14(void);
void mode15(void);

void init_control(void);

#endif /* INC_LAPIS_H_ */
