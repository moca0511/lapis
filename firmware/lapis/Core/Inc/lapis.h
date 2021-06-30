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

#define TIRE_CIRCUIT    (PI * TIRE_DIAMETER)	//　タイヤの円周 163.363mm
#define TREAD_WIDTH     (38.0)					//　トレッド幅　87.0mm(再計測)
#define TREAD_CIRCUIT   (TREAD_WIDTH * PI)		//360度旋回時にタイヤが動く距離　87*3.14mm 273.18mm

#define	STEP_LENGTH	(TIRE_CIRCUIT * STEP_DEGREE / 360.0)	//1ステップで進む距離　0.408mm
//　迷路のパラメータ
#define	BLOCK_LENGTH  (180.0)					//1区画 180mm
//　定数定義

//　最大速度
#define MAX_SPEED (2000)

#define NEZUTAKA_LENGTH (135)

typedef enum {
	RS_WALL,
	LS_WALL,
	RF_WALL,
	LF_WALL,
	RS_FREE,
	LS_FREE,
	RF_FREE,
	LF_FREE,
	RS_threshold,
	LS_threshold,
	RF_threshold,
	LF_threshold,
	WALL_DATA_MAX
} WALL_DATA;

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

#endif /* INC_LAPIS_H_ */
