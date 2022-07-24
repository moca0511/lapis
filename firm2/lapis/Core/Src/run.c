/*
 * run.c
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#include "run.h"
#include "AS5047P.h"
#include<math.h>
#include"UI.h"
#include "wallsensor.h"
#include "adc.h"
#include "timer.h"
#include "maze.h"

extern float tar_speed, speed_p, speed_p_prev, speed_i, speed_d, tar_speed,
		tar_speed, tar_speed_R, tar_speed_L, tar_accel, max_tar_speed, tar_ang,
		ang_p, ang_p_prev, ang_i, ang_d, accel, max_tar_ang, ang_accel, degree,
		ang, tar_degree, max_degree;
extern uint8_t run_mode;
extern float posX, posY, lapis_length;
extern t_control con_fwall, con_wall;				//制御構造体
extern int8_t head;	//　現在向いている方向(北東南西(0,1,2,3))
extern int16_t map_posX, map_posY;	//　現在の位置
extern MAP map[MAP_X_MAX][MAP_Y_MAX]; //ｓマップ情報

float move_x(float degree, float speed) {
//	printf("deg=%fspeed=%fx=%f",degree,speed,(float)(speed*cos((double)degree)));
	return (float) (speed * cos((double) degree));
}
float move_y(float degree, float speed) {
	return (float) (speed * sin((double) degree));
}

float get_fusioned_speed(float speed, float accel, float speed_prev, float tick) {
	const float alpha = 0.9f;
	return alpha * (speed_prev + tick * accel) + (1.0f - alpha) * speed;
}

void run(float acc, float max_speed, float finish_speed) {
	speed_p = 0;
	speed_p_prev = 0;
	speed_i = 0;
	speed_d = 0;
	tar_accel = acc;
	max_tar_speed = max_speed;
	run_mode = STRAIGHT_MODE;
}

void straight(RUNConfig config) {
	tar_ang = 0;
	//ang_p = 0;
	//ang_i = 0;
	//ang_d = 0;
	ang_p_prev = 0;
	//speed_p = 0;
	//speed_p_prev = 0;
	//speed_i = 0;
	//speed_d = 0;
	tar_degree = 0;
	tar_accel = config.acceleration;
	max_tar_speed = config.max_speed;
	max_tar_ang = 0;
	if (config.finish_speed > config.min_speed) {
		config.min_speed = config.finish_speed;
	}
	run_mode = STRAIGHT_MODE;
	con_wall.enable = true;
	while (((config.tar_length) - lapis_length - 20)
			> 1000.0f * (tar_speed - config.finish_speed)
					* ((tar_speed - config.finish_speed) / config.acceleration)
					/ 2.0f) {
//		printf("p\n");
	}
	tar_accel = config.acceleration * -1.0f;
	while (lapis_length < config.tar_length) {
//		printf("%f\n",lapis_length);
		if (tar_speed < config.min_speed) {
			tar_accel = 0.0f;
			tar_speed = config.min_speed;
		}
		if (tar_speed < config.finish_speed) {
			tar_accel = 0.0f;
			tar_speed = config.finish_speed;
		}
	}
	tar_accel = 0.0f;
	tar_speed = config.finish_speed;
	//speed_p = 0;
	//speed_p_prev = 0;
	//speed_i = 0;
	//speed_d = 0;
	lapis_length = 0;
	con_wall.enable = false;
}

void turn(TURNConfig config) {
	tar_ang = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	speed_p = 0;
	speed_p_prev = 0;
	speed_i = 0;
	speed_d = 0;
	tar_accel = 0;
	max_tar_speed = 0;
	degree=0;
	tar_speed = config.speed;
	max_tar_ang = 0;
	float local_degree = 0;

	//車体の現在角度を取得
	local_degree = (degree/90) * degree + (degree/90);
	tar_degree = 0;
//	printf("local=%f,tar_deg=%f\n", local_degree, tar_degree);
	run_mode = TURN_MODE;
	if (config.dir == TURN_LEFT) {
		//角加速度、加速度、最高角速度設定
		ang_accel = config.gyro_acc;			//角加速度を設定
		max_tar_ang = config.max_gyro;
		//走行モードをスラロームモードにする
		max_degree = config.tar_deg;
		while(((float)(max_degree - (float)(degree - local_degree))* (float) (PI / 180.0f))
					> (ang * (ang/ang_accel) / 2.0f)){
		}
	} else {
		//角加速度、加速度、最高角速度設定
		ang_accel = config.gyro_acc * -1.0f;			//角加速度を設定
		max_tar_ang = config.max_gyro * -1.0f;
		//走行モードをスラロームモードにする
		max_degree = config.tar_deg * -1.0f;
//		while (-1.0f * (float)(max_degree - 3.0f- (float)(degree - local_degree))
//				* (float) (PI / 180.0f)
//				> (float) ((tar_ang * tar_ang) / (float) (-2.0f * ang_accel))) {
//		}
		while(((float)(max_degree - (float)(degree - local_degree))* (float) (PI / 180.0f))
			< (ang * (ang/ang_accel) / 2.0f)){
//			printf("%3.3f,%3.3f\n",((float)(max_degree - (float)(degree - local_degree))* (float) (PI / 180.0f)),tar_ang * (tar_ang/ang_accel) / 2.0f);
			}
	}

	ang_i = 0;
	//BEEP();
	//角減速区間に入るため、角加速度設定
	if (config.dir == TURN_LEFT) {
		ang_accel = -1.0f * config.gyro_acc;			//角加速度を設定
		//減速区間走行
		while ((degree - local_degree) < max_degree) {
			if (tar_ang < config.min_jyro) {
				ang_accel = 0;
				tar_ang = config.min_jyro;
			}
		}

		ang_accel = 0;
		tar_ang = 0;
		tar_degree = max_degree;
	} else {
		ang_accel = config.gyro_acc;			//角加速度を設定
		//減速区間走行
		while ((degree - local_degree) > max_degree) {
			if (-1.0f * tar_ang < config.min_jyro) {
				ang_accel = 0;
				tar_ang = config.min_jyro * -1.0f;
			}
		}

		ang_accel = 0;
		tar_ang = 0;
		tar_degree = max_degree;
	}
//	tone(tone_D, 10);
//	while (ang >= 0.1f || ang <= -0.1f)
//		;
//	tone(tone_F, 10);
	tar_ang = 0;
	ang_accel = 0;
	//現在距離を0にリセット
	lapis_length = 0;
}

void front_adjust(void) {
	tar_ang = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	speed_p = 0;
	speed_p_prev = 0;
	speed_i = 0;
	speed_d = 0;
	tar_accel = 0;
	max_tar_speed = 0;
	tar_speed = 0;
	max_tar_ang = 0;
	//走行モードを前壁調整にする
	run_mode = F_WALL_MODE;
	//前壁制御を有効にする
	con_fwall.enable = true;
	//目標距離をグローバル変数に代入する
	//len_target = len;
	//目標速度を設定
	//tar_speed = 0;
	//最高速度を設定
	max_tar_speed = 0.1;

	int32_t now_pos = get_sensordata(RF) + get_sensordata(LF);
	int32_t target_pos = RF_WALL + LF_WALL;

	//モータ出力をON
	while (true) {
		if ((now_pos - target_pos) < -10) {
			//中央より前壁より離れている場合前進
			tar_accel = 0.2f;
		} else if ((now_pos - target_pos) > 10) {
			//中央より前壁に近い場合後退
			tar_accel = -0.2f;
		} else {
			//加速度を0にする
			tar_accel = 0;
			tar_speed = 0;
			if ((con_fwall.error) < 10 && (con_fwall.error) > -10) {
				break;
			}
		}
		now_pos = get_sensordata(RF) + get_sensordata(LF);
	}
	while (ang >= 0.1f || ang <= -0.1f)
		;
	tar_ang = 0;
	ang_accel = 0;
	//現在距離を0にリセット
	lapis_length = 0;
	ang_p = 0;
	ang_i = 0;
	ang_d = 0;
	ang_p_prev = 0;
	run_mode = NON_MODE;
//	Delay_ms(100);
}

void turn_u(void) {
	//引数の座標x,yに壁情報を書き込む
	int8_t f_adjust = false, r_adjust = false, l_adjust = false;

	TURNConfig turn_config =
			{ 90, 20.0f * PI, PI / 5, 3.0f * PI, 0, TURN_RIGHT };

	//自分の方向に応じて書き込むデータを生成
	//CONV_SEN2WALL()はmacro.hを参照
	if (((((map[map_posX][map_posY].wall & 0x0f)
			| (map[map_posX][map_posY].wall << 4)) << head) & 0x80) == 0x80) {
		f_adjust = true;
	}
	if (((((map[map_posX][map_posY].wall & 0x0f)
			| (map[map_posX][map_posY].wall << 4)) << head) & 0x10) == 0x10) {
		l_adjust = true;
	}
	if (((((map[map_posX][map_posY].wall & 0x0f)
			| (map[map_posX][map_posY].wall << 4)) << head) & 0x40) == 0x40) {
		r_adjust = true;
	}

	if (f_adjust == true) {
		front_adjust();
		if (r_adjust == true) {
			turn_config.dir = TURN_RIGHT;
			turn_config.tar_deg = 90;
			turn(turn_config);
			front_adjust();
//			music();
			turn(turn_config);
//			music();
		} else if (l_adjust == true) {
			turn_config.dir = TURN_LEFT;
			turn_config.tar_deg = 90;
			turn(turn_config);
			front_adjust();
			turn(turn_config);
		} else {
			turn_config.dir = TURN_RIGHT;
			turn_config.tar_deg = 180;
			turn(turn_config);
		}
	} else {
		turn_config.dir = TURN_RIGHT;
		turn_config.tar_deg = 180;
		turn(turn_config);				//180ターン
	}
	chenge_head(TURN_RIGHT, 180, &head);
	lapis_length = 0;
	degree = 0;
	run_mode = NON_MODE;
}
