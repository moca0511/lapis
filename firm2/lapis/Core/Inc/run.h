/*
 * run.h
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#ifndef INC_RUN_H_
#define INC_RUN_H_

#include"main.h"

#define TURN_RIGHT 1
#define TURN_LEFT 0

typedef struct {
	float acceleration;	//加速度
	float max_speed;	//初速 (mm/s)
	float min_speed;	//終了速度 (mm/s)
	float finish_speed;	//最大速度 (mm/s)
	float tar_length;	//各設定値
} RUNConfig;

typedef struct {
	float tar_deg;
	float gyro_acc;
	float min_jyro;
	float max_gyro;
	float speed;
	uint8_t dir;
} TURNConfig;

float move_x(float degree, float speed);
float move_y(float degree, float speed);

float get_fusioned_speed(float speed, float accel, float speed_prev, float tick);

void run(float acc, float max_speed, float finish_speed);
void straight(RUNConfig config);
void turn(TURNConfig config);
void front_adjust(void);
void turn_u(void);
#endif /* INC_RUN_H_ */
