/*
 * lapis.c
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */
#include"lapis.h"
#include"main.h"
//#include"mpu6500.h"
#include"ICM20602.h"
#include"uart.h"
#include"UI.h"
#include"battery.h"
#include "AS5047P.h"
#include"run.h"
#include"motor.h"
#include"wallsensor.h"
#include"timer.h"
#include"flash.h"
#include "agent.h"
#include "maze.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
uint8_t gdata[128] = { "lapis flash test 12345678901234567890\n\0" };
float omega_prev = 0, deg_R = 0, deg_L = 0, deg_R_prev = 0, deg_L_prev = 0,
		degree = 0, speed_R = 0, speed_L = 0, speed = 0, speed_prev = 0;
float raw_speed = 0, enc_speed = 0, tar_speed = 0, tar_speed_L = 0,
		tar_speed_R = 0, speed_p = 0, speed_p_prev = 0, speed_i = 0,
		speed_d = 0, volt_R = 0, volt_L = 0, tar_accel = 0, max_tar_speed = 0,
		tar_ang = 0, ang_p = 0, ang_p_prev = 0, ang_i = 0, ang_d = 0,
		max_tar_ang = 0, ang_accel = 0, ang = 0, tar_degree = 0, max_degree = 0;
float posX = 0, posY = 0;
float gyro = 0, accel = 0, gyro_prev = 0;
uint8_t debug_print = 0;
uint64_t tick = 0;
float batt_level = BATT_NORMAL;
uint64_t now_time = 0;
uint8_t run_mode = NON_MODE;
float lapis_length = 0;
uint8_t TURN_DIR = 0;
uint8_t log_flag = false;
int64_t log_timer = 0;
char log_str[1000][100] = { 0 };
int16_t map_posX, map_posY;	//　現在の位置
int8_t head;	//　現在向いている方向(北東南西(0,1,2,3))
t_control con_wall;				//制御構造体
t_control con_fwall;				//制御構造体

void lapis(void) {
	int16_t mode = 1;

	setbuf( stdout, NULL);
	HAL_TIM_Base_Start_IT(&htim1); //1kHz speed conntrol
	HAL_TIM_Base_Start_IT(&htim3); //4kHz wall sensor
	HAL_TIM_Base_Start_IT(&htim5); //10kHz odmetry

	adc_dma_start();
	icm20602_init();
	AS5047_Init();
	init_Motor();
	init_wallSensor();
	AS5047_SetZeroPosition(ENC_R);
	AS5047_SetZeroPosition(ENC_L);
	init_control();

	run_mode = NON_MODE;

	if (batt_level > BATT_FULL) {
		LED(15);
		tone(tone_hiC, 500);
	} else if (batt_level > BATT_HIGH) {
		LED(7);
		tone(tone_G, 500);
	} else if (batt_level > BATT_NORMAL) {
		LED(3);
		tone(tone_E, 500);
	} else {
		LED(1);
		tone(tone_C, 500);
	}
	if (batt_level <= BATT_WARNING) { //warning
		snprintf(buf, 100, "batt=%f\n", batt_level);
		print_dma(buf, 100);
		fale_safe(BATT_EMPTY);
	}
	Delay_ms(500);
	LED(1);

	music();
	for (;;) {
//		tone(tone_C, 100);
//			Delay_ms(100);
//		set_MR_direction(MOVE_FORWARD);
//		set_ML_direction(MOVE_FORWARD);

//		set_ML_EN(0.5);
//				set_MR_EN(0.5);
//		HAL_Delay(100);
//		printf("mode select\n");
//
		MENU(&mode);
//
		printf("\n");

		switch (mode) {
		case 0:
			mode0();
			break;
		case 1:
			mode1();
			break;
		case 2:
			mode2();
			break;
		case 3:
			mode3();
			break;
		case 4:
			mode4();
			break;
		case 5:
			mode5();
			break;
		case 6:
			mode6();
			break;
		case 7:
			mode7();
			break;
		case 8:
			mode8();
			break;
		case 9:
			mode9();
			break;
		case 10:
			mode10();
			break;
		case 11:
			mode11();
			break;
		case 12:
			mode12();
			break;
		case 13:
			mode13();
			break;
		case 14:
			mode14();
			break;
		case 15:
			mode15();
			break;
		default:
			break;
		}
		tone(tone_C, 10);
		Delay_ms(100);
		tone(tone_G, 10);
	}
}
void MENU(int16_t *mode) {
	static char *mode_name[16] = { MODE_NAME0, MODE_NAME1, MODE_NAME2,
	MODE_NAME3, MODE_NAME4, MODE_NAME5, MODE_NAME6, MODE_NAME7,
	MODE_NAME8, MODE_NAME9, MODE_NAME10, MODE_NAME11, MODE_NAME12,
	MODE_NAME13, MODE_NAME14, MODE_NAME15 };
	int16_t old_mode = 1;
	for (;;) {
		if (batt_level <= BATT_WARNING) { //warning
			snprintf(buf, 100, "batt=%f\n", batt_level);
			print_dma(buf, 100);
			fale_safe(BATT_EMPTY);
		}
		if (speed_R > 0.1) {
			(*mode)++;
			tone(tone_hiC, 10);
		}
		if (speed_R < -0.1) {
			(*mode)--;
			tone(tone_C, 10);
		}
		if (*mode > 15)
			*mode = 0;
		if (*mode < 0)
			*mode = 15;

		if (*mode != old_mode) {
			LED((unsigned int) *mode);
//			printf("*mode:%2d %30s\n", *mode, mode_name[*mode]);
			old_mode = *mode;
		}
		if ((get_sensordata(RS) + get_sensordata(RF) + get_sensordata(LF)
				+ get_sensordata(LS)) > 1000 * 4) {
			tone(tone_E, 50);
			Delay_ms(1000);
			break;
		}
		Delay_ms(50);
	}
}

void mode0(void) {
	for (int i = 0; i < 1000; i++) {
		printf("%s", log_str[i]);
		Delay_ms(10);
	}
}
void mode1(void) {
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	run_mode = STRAIGHT_MODE;
	tone(tone_hiC, 10);
	while (1) {
		tar_speed = 0;
		tar_ang = 0;
	}
}
void mode2(void) {
	RUNConfig run_config = { 10.0f, 0.3f, 0.1f, 0.3f, 90.0f / 2 };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	tone(tone_hiC, 10);
	posX = posY = lapis_length = 0;
//	HAL_Delay(1000);
	con_wall.enable = true;
	log_timer = 0;
	log_flag = true;
	straight(run_config);
	straight(run_config);
	straight(run_config);
	run_config.finish_speed = 0;
	straight(run_config);
	con_wall.enable = false;
//	turn(90,
//			5.0f * PI, PI / 30, 1.5f * PI, 0.3, 0);
//	straight(2.0f, 0.3f, 0.2f, 0.0f, 90.0f);

	HAL_Delay(500);
	log_flag = false;
	run_mode = NON_MODE;
	tar_speed = 0;
}
void mode3(void) {
	RUNConfig run_config = { 2.0f, 0.3f, 0.1f, 0.3f, 90.0f };
	TURNConfig turn_config = { 90, 100.0f * PI, PI / 30, 20.0f * PI, 0.3, 1 };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	tone(tone_hiC, 10);
	posX = posY = lapis_length = 0;
	log_timer = 0;
	log_flag = true;
	straight(run_config);
	turn(turn_config);
	run_config.finish_speed = 0;
	straight(run_config);

	log_flag = false;
	HAL_Delay(500);
	run_mode = NON_MODE;
	tar_speed = 0;

}
void mode4(void) {
	RUNConfig run_config = { 20.0f, 2.0f, 0.1f, 0.8f, BLOCK_LENGTH };
	TURNConfig turn_config = { 90, 20.0f * PI, PI / 30, 3.0f * PI, 0.8f, 1 };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	tone(tone_hiC, 10);
	posX = posY = lapis_length = 0;
	log_timer = 0;
	log_flag = true;
	//	HAL_Delay(1000);
	straight(run_config);
	turn(turn_config);
	run_config.finish_speed = 0;
	straight(run_config);
	run_mode = NON_MODE;
	log_flag = false;
	HAL_Delay(500);
	tar_speed = 0;
}
void mode5(void) {
	TURNConfig turn_config =
			{ 90, 30.0f * PI, PI / 10, 5.0f * PI, 0, TURN_RIGHT };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	tone(tone_hiC, 10);
	posX = posY = lapis_length = 0;
	log_timer = 0;
	log_flag = true;
	turn(turn_config);
	log_flag = false;
	tone(tone_hiC, 10);
	HAL_Delay(500);
	run_mode = NON_MODE;
	tar_speed = 0;
}
void mode6(void) {
	TURNConfig turn_config =
			{ 90, 10.0f * PI, PI / 30, 1.0f * PI, 0, TURN_RIGHT };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	tone(tone_hiC, 10);
	posX = posY = lapis_length = 0;
	degree = 0;

	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(1000);

	turn_config.dir = TURN_LEFT;
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(1000);

	turn_config.dir = TURN_RIGHT;
	turn_config.tar_deg = 180;
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);
	turn_config.dir = TURN_LEFT;
	turn(turn_config);
	tone(tone_hiC, 10);
	HAL_Delay(500);

	run_mode = NON_MODE;
	tar_speed = 0;
}
void mode7(void) {
//	HAL_Delay(1000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(0.5f);
//	set_MR_EN(0.5f);
//	HAL_Delay(10000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(0.0f);
//	set_MR_EN(0.0f);
}
void mode8(void) {
//	HAL_Delay(1000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(1.0f);
//	set_MR_EN(1.0f);
//	HAL_Delay(10000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(0.0f);
//	set_MR_EN(0.0f);
}
void mode9(void) {
//	HAL_Delay(1000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(2.0f);
//	set_MR_EN(2.0f);
//	HAL_Delay(10000);
//	set_ML_direction(MOVE_FORWARD);
//	set_MR_direction(MOVE_FORWARD);
//	set_ML_EN(0.0f);
//	set_MR_EN(0.0f);
}
void mode10(void) {
	RUNConfig run_config = { 10.0f, 0.3f, 0.1f, 0.3f, 90.0f / 2 };
		TURNConfig turn_config =
				{ 90, 30.0f * PI, PI / 5, 5.0f * PI, 0, TURN_RIGHT };
		RUNConfig saitan_run_config = { 20.0f, 0.5f, 0.1f, 0.0f, 90.0f / 2 };
		HAL_Delay(1000);
		tone(tone_hiC, 10);
		maze_load();
		icm20602_init();
		degree = 0;
		posX = posY = 0;
		ang_p = 0;
		ang_i = 0;
		ang_d = 0;
		ang_p_prev = 0;
		posX = posY = lapis_length = 0;
		map_posX = START_X;
		map_posY = START_Y;
		head = 0;
		log_timer = 0;
		log_flag = true;
//
//		adachi(run_config, turn_config, GOAL_X, GOAL_Y);
//		run_mode = NON_MODE;
//		tar_speed = 0;
//		HAL_TIM_Base_Stop_IT(&htim1); //1kHz speed conntrol
//		HAL_TIM_Base_Stop_IT(&htim3); //4kHz wall sensor
//		HAL_TIM_Base_Stop_IT(&htim5); //10kHz odmetry
//		maze_save();
//		HAL_TIM_Base_Start_IT(&htim1); //1kHz speed conntrol
//		HAL_TIM_Base_Start_IT(&htim3); //4kHz wall sensor
//		HAL_TIM_Base_Start_IT(&htim5); //10kHz odmetry
//		Delay_ms(1000);
//		adachi(run_config, turn_config, START_X, START_Y);
//		run_mode = NON_MODE;
		tone(tone_hiC, 10);
		Delay_ms(1000);
		music();
		saitan(saitan_run_config,turn_config,GOAL_X,GOAL_Y,map_posX, map_posY, head);
		HAL_Delay(500);
		run_mode = NON_MODE;
}
void mode11(void) {
	RUNConfig run_config = { 15.0f, 0.3f, 0.3f, 0.3f, 90.0f / 2 };
	TURNConfig turn_config =
			{ 90, 30.0f * PI, PI / 5, 5.0f * PI, 0, TURN_RIGHT };
	RUNConfig saitan_run_config = { 10.0f, 0.5f, 0.1f, 0.0f, 90.0f / 2 };
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	smap_Init();
	icm20602_init();
	degree = 0;
	posX = posY = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	posX = posY = lapis_length = 0;
	map_posX = START_X;
	map_posY = START_Y;
	head = 0;
	log_timer = 0;
	log_flag = true;

	adachi(run_config, turn_config, GOAL_X, GOAL_Y);
	run_mode = NON_MODE;
	tar_speed = 0;
	HAL_TIM_Base_Stop_IT(&htim1); //1kHz speed conntrol
	HAL_TIM_Base_Stop_IT(&htim3); //4kHz wall sensor
	HAL_TIM_Base_Stop_IT(&htim5); //10kHz odmetry
	maze_save();
	HAL_TIM_Base_Start_IT(&htim1); //1kHz speed conntrol
	HAL_TIM_Base_Start_IT(&htim3); //4kHz wall sensor
	HAL_TIM_Base_Start_IT(&htim5); //10kHz odmetry
	Delay_ms(1000);
	adachi(run_config, turn_config, START_X, START_Y);
	run_mode = NON_MODE;
	tone(tone_hiC, 10);
	Delay_ms(1000);
	music();
	saitan(saitan_run_config,turn_config,GOAL_X,GOAL_Y,map_posX, map_posY, head);
	HAL_Delay(500);
	run_mode = NON_MODE;
}
void mode12(void) {
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	while (1) {
		degree = 0;
		posX = posY = 0;
		ang_p = 0;
		ang_i = 0;
		ang_d = 0;
		ang_p_prev = 0;
		posX = posY = lapis_length = 0;
		log_timer = 0;
		log_flag = true;
		front_adjust();
		run_mode = NON_MODE;
		tar_speed = 0;
	}
	tone(tone_hiC, 10);
	HAL_Delay(500);
}
void mode13(void) {
	while (1) {
		printf("%d,%d,%d,%d\n", get_sensordata(LS), get_sensordata(RS),
				get_sensordata(LF), get_sensordata(RF));
		Delay_ms(500);
	}
}
void mode14(void) {
	print_map();

}
void mode15(void) {

	maze_load();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static int32_t loop = 100;
	static int8_t led_select = RS;

	/*-----------------------------------------------------------
	 左右モータ制御用1kHzカウント
	 -----------------------------------------------------------*/
	if (htim->Instance == TIM1) { //1kHzカウント 速度制御用
		/*-----------------------------------------------------------
		 delay_msカウント
		 -----------------------------------------------------------*/
		now_time++;
		if (now_time > 100000000) {
			now_time = 0;
		}

		//目標速度・角速度設定
		if (run_mode == STRAIGHT_MODE || run_mode == TURN_MODE
				|| run_mode == F_WALL_MODE) {
			//目標速度算出
			tar_speed += (tar_accel * 0.001f);
			if (max_tar_speed > 0 && tar_speed > max_tar_speed) {
				tar_speed = max_tar_speed;
			}
			if (max_tar_speed < 0 && tar_speed < max_tar_speed) {
				tar_speed = max_tar_speed;
			}
			//目標角速度算出
			tar_ang += (ang_accel * 0.001f);
			tar_degree += (tar_ang * 180.0f / PI) * 0.001f;
			if (max_tar_ang > 0 && tar_ang > max_tar_ang) {
				tar_ang = max_tar_ang;
			}
			if (max_tar_ang < 0 && tar_ang < max_tar_ang) {
				tar_ang = max_tar_ang;
			}
		}

		/*****************************************************************************************
		 壁制御
		 横壁センサによる目標角度生成
		 *****************************************************************************************/
		if (run_mode == STRAIGHT_MODE) {
			if (con_wall.enable == true
					&& get_sensordata(RF) + get_sensordata(LF)
							<= (RF_TH + LF_TH) * 5)	//壁制御が許可されているかチェック
									{
				con_wall.p_error = con_wall.error;	//過去の偏差を保存

				//左右のセンサが、それぞれ使える状態であるかどうかチェックして、姿勢制御の偏差を計算
				if ((get_sensor_iscontrol(RS) == true)
						&& (get_sensor_iscontrol(LS) == true)) {//両方とも有効だった場合の偏差を計算
					LED(15);
					con_wall.error = get_sensor_error(RS)
							- get_sensor_error(LS);
				} else								//片方もしくは両方のセンサが無効だった場合の偏差を計算
				{
					LED(3);
					con_wall.error = 2.0
							* (get_sensor_error(RS) - get_sensor_error(LS));//片方しか使用しないので2倍する
				}

				//DI制御計算
				con_wall.diff = con_wall.error - con_wall.p_error;	//偏差の微分値を計算
				con_wall.sum += con_wall.error;				//偏差の積分値を計算

				if (con_wall.sum > con_wall.sum_max)			//偏差の積分値の最大値を制限
						{
					con_wall.sum = con_wall.sum_max;
				} else if (con_wall.sum < (-con_wall.sum_max))	//偏差の積分値の最低値を制限
						{
					con_wall.sum = -con_wall.sum_max;
				}

				con_wall.p_omega = con_wall.omega;
				con_wall.omega = con_wall.kp * con_wall.error * 0.5
						+ con_wall.p_omega * 0.5;	//現在の目標角速度[rad/s]を計算
				tar_ang = con_wall.omega;
			} else {
				LED(0);
				tar_ang = 0;
			}

		}

		/*****************************************************************************************
		 前壁制御
		 前壁センサによる目標角度生成
		 *****************************************************************************************/
		if (run_mode == F_WALL_MODE) {
			if (con_fwall.enable == true)	//壁制御が許可されているかチェック
					{
				LED(14);
				con_fwall.p_error = con_fwall.error;	//過去の偏差を保存

				//左右のセンサが、それぞれ使える状態であるかどうかチェックして、姿勢制御の偏差を計算
				if ((get_sensor_iscontrol(RF) == true)
						&& (get_sensor_iscontrol(LF) == true)) {//両方とも有効だった場合の偏差を計算
					con_fwall.error = get_sensor_error(LF)
							- get_sensor_error(RF);
				} else								//片方もしくは両方のセンサが無効だった場合の偏差を計算
				{
					con_fwall.error = 2.0
							* (get_sensor_error(LF) - get_sensor_error(RF));//片方しか使用しないので2倍する
				}

				//DI制御計算
				con_fwall.diff = con_fwall.error - con_fwall.p_error;//偏差の微分値を計算
				con_fwall.sum += con_fwall.error;				//偏差の積分値を計算

				if (con_fwall.sum > con_fwall.sum_max)			//偏差の積分値の最大値を制限
						{
					con_fwall.sum = con_fwall.sum_max;
				} else if (con_fwall.sum < (-con_fwall.sum_max))//偏差の積分値の最低値を制限
						{
					con_fwall.sum = -con_fwall.sum_max;
				}

				con_fwall.p_omega = con_fwall.omega;
				con_fwall.omega = con_fwall.kp * con_fwall.error * 0.5
						+ con_fwall.p_omega * 0.5;	//現在の目標角速度[rad/s]を計算
				tar_ang = con_fwall.omega;
			} else {
				tar_ang = 0;
			}

		}

		if (run_mode == STRAIGHT_MODE || run_mode == TURN_MODE
				|| run_mode == F_WALL_MODE) {
			//目標速度・角速度にするためにPIDパラメータ算出
			speed_p = tar_speed - speed;
			speed_i += speed_p;
			speed_d = speed_p_prev - speed_p;
			speed_p_prev = speed_p;

			if (speed_i > 1000) {
				speed_i = 1000;
			}
			if (speed_i < -1000) {
				speed_i = -1000;
			}

			ang_p = tar_ang - ang;
			ang_i += ang_p;
			ang_d = ang_p_prev - ang_p;
			ang_p_prev = ang_p;
			if (ang_i > 1000) {
				ang_i = 1000;
			}
			if (ang_i < -1000) {
				ang_i = -1000;
			}

		}

		if (run_mode == STRAIGHT_MODE || run_mode == TURN_MODE
				|| run_mode == F_WALL_MODE) {
			//目標速度
			volt_R = volt_L = speed_p * SPEED_KP + speed_i * SPEED_KI
					+ speed_d * SPEED_KD;
			volt_R += ang_p * ANG_KP + ang_i * ANG_KI + ang_d * ANG_KD;
			volt_L -= ang_p * ANG_KP + ang_i * ANG_KI + ang_d * ANG_KD;

			if (volt_R > 0) {
				set_MR_direction(MOVE_FORWARD);
			} else {
				set_MR_direction(MOVE_BACK);
				volt_R *= -1;
			}
			if (volt_L > 0) {
				set_ML_direction(MOVE_FORWARD);
			} else {
				set_ML_direction(MOVE_BACK);
				volt_L *= -1;
			}

			set_ML_EN(volt_L);
			set_MR_EN(volt_R);
		} else {
			set_ML_EN(0);
			set_MR_EN(0);
		}

		if (log_flag == true) {
			snprintf(log_str[log_timer], 100,
					"%1.3f,%1.3f,%1.3f,%1.3f,%1.3f,%3.3f,%3.3f\n",
					log_timer * 0.001f, speed, tar_speed, ang, tar_ang, degree,
					tar_degree);
			if (log_timer == 999) {
				log_flag = false;
			}
			log_timer++;
		}

	}

	/*-----------------------------------------------------------
	 wallsensor用4kHzカウント 各センサを1kHzで読み取り
	 -----------------------------------------------------------*/
	if (htim->Instance == TIM3) { //4kHzカウント wallsensor
//		printf("sensor\n");
		wallSensorRead(led_select);
		led_select++;
		if (led_select == LS + 1) {
			led_select = RS;
		}
	}

	if (htim->Instance == TIM5) { //1kHzカウント odometry
		batt_level = readBattery();
		icm20602_get_accel(&accel);
		icm20602_get_gyro(&gyro);
		icm20602_get_deg(&degree, gyro, gyro_prev, 0.001f);
		ang = gyro * PI / 180.0f;
		deg_L = AS5047_ReloadAngle(ENC_L);
		deg_R = AS5047_ReloadAngle(ENC_R);
		speed_L = AS5047_GetSpeed(ENC_L, deg_L_prev);
		speed_R = AS5047_GetSpeed(ENC_R, deg_R_prev) * -1;
		//		speed_L=speed_R;
		raw_speed = (speed_L + speed_R) / 2.0;
//		if (((tar_speed < 0 && raw_speed > 0)
//				|| (tar_speed > 0 && raw_speed < 0)) && tar_speed != 0) {
//			raw_speed *= -1;
//		}
		enc_speed = (raw_speed + speed_prev) / 2;
		speed = get_fusioned_speed(enc_speed, accel, speed_prev, 0.001f);
		posX += move_x(degree, speed);
		posY += move_y(degree, speed);
		lapis_length += raw_speed;
		omega_prev = degree;
		deg_R_prev = deg_R;
		deg_L_prev = deg_L;
		speed_prev = speed;
		gyro_prev = gyro;
	}

}

void init_control(void) {
	con_wall.kp = CON_WALL_KP;
	con_fwall.kp = CON_FWALL_KP;
}

/*　外部割込み*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}
