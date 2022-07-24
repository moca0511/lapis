/*
 * agent.c
 *
 *  Created on: 2020/09/11
 *      Author: junmo
 */
#include"main.h"
#include "wallsensor.h"
#include "timer.h"
#include "motor.h"
#include "UI.h"
#include"lapis.h"
#include"run.h"
#include "maze.h"
#include"agent.h"
#include"adc.h"

extern MAP map[MAP_X_MAX][MAP_Y_MAX];
extern int16_t map_posX, map_posY;	//　現在の位置
extern int8_t head;	//　現在向いている方向(北東南西(0,1,2,3))

//足立法探索　ゴール
//1.目標地点確認　現在位置よりステップ数が少なく　未到達かつ壁情報読んでなくてゴールじゃない場所で　一番近い場所
//2.そこまで行くための道のり（最短マップ）算出
//3.最短できなければいけるところまで行く。
//4.ゴールなら終了
//5.1に戻る

/*
 * 説明：足立法探索
 * 引数：run_config 直進パラメータ
 * 　　　turn_config 超新地旋回パラメータ
 * 　　　slalom90_config 90°スラロームパラメータ
 * 　　　gx 目標X座標
 * 　　　gy 目標Y座標
 * 戻り値：無し
 */
void adachi(RUNConfig run_config, TURNConfig turn_config, uint16_t gx,
		uint16_t gy) {
	uint8_t temp_head = 0;
	float speed_buf = run_config.finish_speed;
	int8_t move_f = -1;
	int8_t remenber = 1;

	printf("adachi\n");

	tone(tone_hiC, 10);

	for (;;) {
		if (map[gx][gy].wall == 0xff) {
//			motor_stop();
			if (move_f == 1) {    //中央に移動
				run_config.max_speed = 0.2f;
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				run_config.acceleration = 5.0f;
				straight(run_config);
			}
			printf("can't to goal\n");
			break;
		}

		if (map_posX == gx && map_posY == gy) {
			if (move_f == 1) {    //中央に移動
				run_config.max_speed = 0.2f;
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				run_config.acceleration = 5.0f;
				straight(run_config);
			}
			turn_u();
			printf("G\n");
			break;
		}

		make_smap(gx, gy, 0);
		temp_head = 99;
		remenber = 99;
		if ((map[map_posX][map_posY].wall & 0x22) == 0x20
				&& map[map_posX][map_posY].step
						> map[map_posX][map_posY - 1].step) {
			temp_head = 2;
			if ((map[map_posX][map_posY - 1].wall & 0xf0) != 0xf0) {
				remenber = 2;
			}
		}

		if ((map[map_posX][map_posY].wall & 0x44) == 0x40
				&& map[map_posX][map_posY].step
						> map[map_posX + 1][map_posY].step) {
			temp_head = 1;
			if ((map[map_posX + 1][map_posY].wall & 0xf0) != 0xf0) {
				remenber = 1;
			}
		}
		if ((map[map_posX][map_posY].wall & 0x11) == 0x10
				&& map[map_posX][map_posY].step
						> map[map_posX - 1][map_posY].step) {
			temp_head = 3;
			if ((map[map_posX - 1][map_posY].wall & 0xf0) != 0xf0) {
				remenber = 3;
			}
		}
		if ((map[map_posX][map_posY].wall & 0x88) == 0x80
				&& map[map_posX][map_posY].step
						> map[map_posX][map_posY + 1].step) {
			temp_head = 0;
			if ((map[map_posX][map_posY + 1].wall & 0xf0) != 0xf0) {
				remenber = 0;
			}
		}
		if (remenber != 99) {
			temp_head = remenber;
		}
		if (temp_head == 99) {
			printf("err\n");
			if (move_f == 1) {    //中央に移動
				run_config.max_speed = 0.2f;
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				run_config.acceleration = 5.0f;
				straight(run_config);
			}
			break;
		}

		temp_head += 4;         //マイナス数防止
		temp_head -= head;    //headの考慮
		if (temp_head >= 4) {    //桁上がりの考慮
			temp_head -= 4;
		}
//		print_map();
//		printf("x:%d y:%d\n", map_posX, map_posY);

		switch (temp_head) {
		case 0:
//			printf("S\n");

			run_config.tar_length = BLOCK_LENGTH * 0.5f;

			if (move_f == -1) {    //中央から区切りへ
				run_config.finish_speed = speed_buf;
				straight(run_config);
			} else {    //区切りから中央へ
				if (map_posX == gx && map_posY == gy) {
					run_config.max_speed = 0.2f;
					run_config.finish_speed = 0.0f;
					run_config.acceleration = 5.0f;
					run_config.tar_length = BLOCK_LENGTH / 2;
				}
				run_config.finish_speed = 0.3f;
				straight(run_config);

			}
//			 printf("move_F:%d move:%d\n", move_f, move);

			if ((move_f *= -1) == 1) {    //区切り
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
			}

			break;
		case 1:
			if (move_f == -1) {
				turn_config.dir = TURN_RIGHT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				run_config.finish_speed = speed_buf;
			} else {
				run_config.finish_speed = 0;
				straight(run_config);
				if (((((map[map_posX][map_posY].wall & 0x0f)
						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
						== 0x80) {
					tone(tone_hiC, 10);
					front_adjust();
				}
				turn_config.dir = TURN_RIGHT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				run_config.finish_speed = speed_buf;
				straight(run_config);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
				move_f = 1;
			}

			break;
		case 2:

//				printf("U\n");

			if (move_f == 1) {
				run_config.finish_speed = 0;
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			}
			move_f = -1;
			Delay_ms(100);
			turn_u();
			run_config.finish_speed = speed_buf;
			break;
		case 3:
			if (move_f == -1) {
				turn_config.dir = TURN_LEFT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				run_config.finish_speed = speed_buf;
			} else {
				run_config.finish_speed = 0;
				straight(run_config);
				if (((((map[map_posX][map_posY].wall & 0x0f)
						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
						== 0x80) {
					tone(tone_hiC, 10);
					front_adjust();
				}
				turn_config.dir = TURN_LEFT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				run_config.finish_speed = speed_buf;
				straight(run_config);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
				move_f = 1;
			}

		}
	}
}

void adachi_s(RUNConfig run_config, TURNConfig turn_config, float adjust_length,
		uint16_t gx, uint16_t gy) {
	uint8_t temp_head = 0;
	float speed_buf = run_config.finish_speed;
	int8_t move_f = -1;
	int8_t remenber = 1;

	printf("adachi\n");

	tone(tone_hiC, 10);

	for (;;) {
		if (map[gx][gy].wall == 0xff) {
			if (move_f == 1) {    //中央に移動
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				straight(run_config);
			}
			printf("can't to goal\n");
			break;
		}

		if (map_posX == gx && map_posY == gy) {
			if (move_f == 1) {    //中央に移動
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				straight(run_config);
			}

//			turn_u();
			if (get_sensor_iswall(RF) || get_sensor_iswall(LF)) {
				front_adjust();
			}
			printf("G\n");
			break;
		}

		make_smap(gx, gy, 0);
		temp_head = 99;
		remenber = 99;
		if ((map[map_posX][map_posY].wall & 0x22) == 0x20
				&& map[map_posX][map_posY].step
						> map[map_posX][map_posY - 1].step) {
			temp_head = 2;
			if ((map[map_posX][map_posY - 1].wall & 0xf0) != 0xf0) {
				remenber = 2;
			}
		}

		if ((map[map_posX][map_posY].wall & 0x44) == 0x40
				&& map[map_posX][map_posY].step
						> map[map_posX + 1][map_posY].step) {
			temp_head = 1;
			if ((map[map_posX + 1][map_posY].wall & 0xf0) != 0xf0) {
				remenber = 1;
			}
		}
		if ((map[map_posX][map_posY].wall & 0x11) == 0x10
				&& map[map_posX][map_posY].step
						> map[map_posX - 1][map_posY].step) {
			temp_head = 3;
			if ((map[map_posX - 1][map_posY].wall & 0xf0) != 0xf0) {
				remenber = 3;
			}
		}
		if ((map[map_posX][map_posY].wall & 0x88) == 0x80
				&& map[map_posX][map_posY].step
						> map[map_posX][map_posY + 1].step) {
			temp_head = 0;
			if ((map[map_posX][map_posY + 1].wall & 0xf0) != 0xf0) {
				remenber = 0;
			}
		}
		if (remenber != 99) {
			temp_head = remenber;
		}
		if (temp_head == 99) {
			printf("err\n");
			if (move_f == 1) {    //中央に移動
				run_config.max_speed = 0.2f;
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				run_config.finish_speed = 0.0f;
				run_config.acceleration = 5.0f;
				straight(run_config);
			}
			break;
		}

		temp_head += 4;         //マイナス数防止
		temp_head -= head;    //headの考慮
		if (temp_head >= 4) {    //桁上がりの考慮
			temp_head -= 4;
		}
//		print_map();
//		printf("x:%d y:%d\n", map_posX, map_posY);

		switch (temp_head) {
		case 0:
//				printf("S\n");

			run_config.tar_length = BLOCK_LENGTH * 0.5;

			if (move_f == -1) {    //中央から区切りへ
				run_config.finish_speed = speed_buf;
				straight(run_config);
			} else {    //区切りから中央へ
				if (map_posX == gx && map_posY == gy) {
					run_config.max_speed = 0.2f;
					run_config.finish_speed = 0.0f;
					run_config.acceleration = 5.0f;
					run_config.tar_length = BLOCK_LENGTH / 2;
				}
				run_config.finish_speed = speed_buf;
				straight(run_config);

			}
//			 printf("move_F:%d move:%d\n", move_f, move);

			if ((move_f *= -1) == 1) {    //区切り
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
			}

			break;
		case 1:
			if (move_f == -1) {
				turn_config.dir = TURN_RIGHT;
				turn_config.speed = 0;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				turn_config.speed = run_config.finish_speed = speed_buf;
			} else {
				run_config.tar_length = adjust_length;
				turn_config.dir = TURN_RIGHT;
				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
					LED(15);
					while (1) {
						if (get_sensordata(RF) >= 150
								&& get_sensordata(LF) >= 150) {
							break;
						}
					}
				} else {
					LED(0);
					straight(run_config);
				}
				turn(turn_config);
				straight(run_config);
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
				move_f = 1;
			}

			break;
		case 2:

//				printf("U\n");

			if (move_f == 1) {
				run_config.finish_speed = 0;
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			}
			move_f = -1;
			Delay_ms(100);
			turn_u();
			run_config.finish_speed = speed_buf;
			break;
		case 3:
			if (move_f == -1) {
				turn_config.dir = TURN_LEFT;
				turn_config.speed = 0;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				turn_config.speed = run_config.finish_speed = speed_buf;
			} else {
				run_config.tar_length = adjust_length;
				turn_config.dir = TURN_LEFT;
				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
					LED(15);
					while (1) {
						if (get_sensordata(RF) >= 150
								&& get_sensordata(LF) >= 150) {
							break;
						}
					}
				} else {
					LED(0);
					straight(run_config);
				}
				turn(turn_config);
				straight(run_config);
				run_config.tar_length = BLOCK_LENGTH * 0.5f;
				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
				chenge_pos(1, &map_posX, &map_posY, head);
				wall_set(0x03);
				wall_set_around();
				move_f = 1;
			}

		}
	}
}

void sarch_all(RUNConfig run_config, TURNConfig turn_config,
		float adjust_length) {
	//現在地から一番近い未探索区画をゴールに設定
	uint16_t go_x, go_y;
	uint8_t temp_head = 0;
	float speed_buf = run_config.finish_speed;
	int8_t move_f = -1;
	int8_t remenber = 1;

	while (get_unknow_block(&go_x, &go_y)) {
		LED(go_x * go_y);
		//そこに足立法で移動
		for (;;) {
			if (map[go_x][go_y].wall == 0xff) {
				break;
			}

			if (map_posX == go_x && map_posY == go_y) {
				break;
			}

			temp_head = 99;
			remenber = 99;
			if ((map[map_posX][map_posY].wall & 0x22) == 0x20
					&& map[map_posX][map_posY].step
							> map[map_posX][map_posY - 1].step) {
				temp_head = 2;
				if ((map[map_posX][map_posY - 1].wall & 0xf0) != 0xf0) {
					remenber = 2;
				}
			}

			if ((map[map_posX][map_posY].wall & 0x44) == 0x40
					&& map[map_posX][map_posY].step
							> map[map_posX + 1][map_posY].step) {
				temp_head = 1;
				if ((map[map_posX + 1][map_posY].wall & 0xf0) != 0xf0) {
					remenber = 1;
				}
			}
			if ((map[map_posX][map_posY].wall & 0x11) == 0x10
					&& map[map_posX][map_posY].step
							> map[map_posX - 1][map_posY].step) {
				temp_head = 3;
				if ((map[map_posX - 1][map_posY].wall & 0xf0) != 0xf0) {
					remenber = 3;
				}
			}
			if ((map[map_posX][map_posY].wall & 0x88) == 0x80
					&& map[map_posX][map_posY].step
							> map[map_posX][map_posY + 1].step) {
				temp_head = 0;
				if ((map[map_posX][map_posY + 1].wall & 0xf0) != 0xf0) {
					remenber = 0;
				}
			}
			if (remenber != 99) {
				temp_head = remenber;
			}
			if (temp_head == 99) {
				printf("err\n");
				break;
			}

			temp_head += 4;         //マイナス数防止
			temp_head -= head;    //headの考慮
			if (temp_head >= 4) {    //桁上がりの考慮
				temp_head -= 4;
			}
			//		print_map();
			//		printf("x:%d y:%d\n", map_posX, map_posY);

			switch (temp_head) {
			case 0:
				//				printf("S\n");

				run_config.tar_length = BLOCK_LENGTH * 0.5;

				if (move_f == -1) {    //中央から区切りへ
					run_config.finish_speed = speed_buf;
					straight(run_config);
				} else {    //区切りから中央へ
					if (map_posX == go_x && map_posY == go_y) {
						break;
					}
					run_config.finish_speed = speed_buf;
					straight(run_config);

				}
				//			 printf("move_F:%d move:%d\n", move_f, move);

				if ((move_f *= -1) == 1) {    //区切り
					chenge_pos(1, &map_posX, &map_posY, head);
					wall_set(0x03);
					wall_set_around();
				}

				break;
			case 1:
				if (move_f == -1) {
					turn_config.dir = TURN_RIGHT;
					turn_config.speed = 0;
					Delay_ms(100);
					turn(turn_config);
					Delay_ms(100);
					chenge_head(turn_config.dir, turn_config.tar_deg, &head);
					turn_config.speed = run_config.finish_speed = speed_buf;
				} else {
					run_config.tar_length = adjust_length;
					turn_config.dir = TURN_RIGHT;
					if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//						LED(15);
						while (1) {
							if (get_sensordata(RF) >= 150
									&& get_sensordata(LF) >= 150) {
								break;
							}
						}
					} else {
//						LED(0);
						straight(run_config);
					}
					turn(turn_config);
					straight(run_config);
					run_config.tar_length = BLOCK_LENGTH * 0.5f;
					chenge_head(turn_config.dir, turn_config.tar_deg, &head);
					chenge_pos(1, &map_posX, &map_posY, head);
					wall_set(0x03);
					wall_set_around();
					move_f = 1;
				}

				break;
			case 2:

				//				printf("U\n");

				if (move_f == 1) {
					run_config.finish_speed = 0;
					run_config.tar_length = BLOCK_LENGTH * 0.5;
					straight(run_config);
				}
				move_f = -1;
				Delay_ms(100);
				turn_u();
				run_config.finish_speed = speed_buf;
				break;
			case 3:
				if (move_f == -1) {
					turn_config.dir = TURN_LEFT;
					turn_config.speed = 0;
					Delay_ms(100);
					turn(turn_config);
					Delay_ms(100);
					chenge_head(turn_config.dir, turn_config.tar_deg, &head);
					turn_config.speed = run_config.finish_speed = speed_buf;
				} else {
					run_config.tar_length = adjust_length;
					turn_config.dir = TURN_LEFT;
					if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//						LED(15);
						while (1) {
							if (get_sensordata(RF) >= 150
									&& get_sensordata(LF) >= 150) {
								break;
							}
						}
					} else {
//						LED(0);
						straight(run_config);
					}
					turn(turn_config);
					straight(run_config);
					run_config.tar_length = BLOCK_LENGTH * 0.5f;
					chenge_head(turn_config.dir, turn_config.tar_deg, &head);
					chenge_pos(1, &map_posX, &map_posY, head);
					wall_set(0x03);
					wall_set_around();
					move_f = 1;
				}

			}
		}
//		if (move_f == 1 && (get_sensor_iswall(RF) && get_sensor_iswall(LF))) { //中央に移動
//			run_config.tar_length = BLOCK_LENGTH * 0.5f;
//			run_config.finish_speed = 0.0f;
//			straight(run_config);
//			front_adjust();
//			move_f *= -1;
//		}
	}
	if (move_f == 1) { //中央に移動
		run_config.tar_length = BLOCK_LENGTH * 0.5f;
		run_config.finish_speed = 0.0f;
		straight(run_config);
		if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
			front_adjust();
		}
		move_f *= -1;
	}

	//壁が埋まれば次の未探索区画へ
	//未探索区画がなくなったら終了
}

//void sarch_all(RUNConfig run_config, TURNConfig turn_config,
//		float adjust_length) {
//	//現在地から一番近い未探索区画をゴールに設定
//	uint16_t go_x = MAP_X_MAX, go_y = MAP_Y_MAX;
//	uint8_t temp_head = 0;
//	float speed_buf = run_config.finish_speed;
//	int8_t move_f = -1;
//	int8_t remenber = 1;
//	//そこに足立法で移動
//	for (;;) {
//
//		temp_head = 99;
//		remenber = 99;
//		if ((map[map_posX][map_posY].wall & 0x22) == 0x20) {
//			if ((map[map_posX][map_posY - 1].wall & 0xf0) != 0xf0) {
//				remenber = 2;
//			}
//		}
//
//		if ((map[map_posX][map_posY].wall & 0x44) == 0x40) {
//			if ((map[map_posX + 1][map_posY].wall & 0xf0) != 0xf0) {
//				remenber = 1;
//			}
//		}
//		if ((map[map_posX][map_posY].wall & 0x11) == 0x10) {
//			if ((map[map_posX - 1][map_posY].wall & 0xf0) != 0xf0) {
//				remenber = 3;
//			}
//		}
//		if ((map[map_posX][map_posY].wall & 0x88) == 0x80) {
//			if ((map[map_posX][map_posY + 1].wall & 0xf0) != 0xf0) {
//				remenber = 0;
//			}
//		}
//
//		if (remenber == 99) {
////			if((map[go_x][go_y].wall & 0xf0) != 0xf0){
//			if (move_f == 1
//					&& (get_sensor_iswall(RF) || get_sensor_iswall(LF))) { //中央に移動
//				run_config.tar_length = BLOCK_LENGTH * 0.5f;
//				run_config.finish_speed = 0.0f;
//				straight(run_config);
//				front_adjust();
//				move_f *= -1;
//			}
//			if (get_unknow_block(&go_x, &go_y) == false) {
//				music();
//				break;
//			}
////			}
//			if ((map[map_posX][map_posY].wall & 0x22) == 0x20
//					&& map[map_posX][map_posY].step
//							> map[map_posX][map_posY - 1].step) {
//				temp_head = 2;
//				if ((map[map_posX][map_posY - 1].wall & 0xf0) != 0xf0) {
//					remenber = 2;
//				}
//			}
//
//			if ((map[map_posX][map_posY].wall & 0x44) == 0x40
//					&& map[map_posX][map_posY].step
//							> map[map_posX + 1][map_posY].step) {
//				temp_head = 1;
//				if ((map[map_posX + 1][map_posY].wall & 0xf0) != 0xf0) {
//					remenber = 1;
//				}
//			}
//			if ((map[map_posX][map_posY].wall & 0x11) == 0x10
//					&& map[map_posX][map_posY].step
//							> map[map_posX - 1][map_posY].step) {
//				temp_head = 3;
//				if ((map[map_posX - 1][map_posY].wall & 0xf0) != 0xf0) {
//					remenber = 3;
//				}
//			}
//			if ((map[map_posX][map_posY].wall & 0x88) == 0x80
//					&& map[map_posX][map_posY].step
//							> map[map_posX][map_posY + 1].step) {
//				temp_head = 0;
//				if ((map[map_posX][map_posY + 1].wall & 0xf0) != 0xf0) {
//					remenber = 0;
//				}
//			}
//		}
//		if (remenber != 99) {
//			temp_head = remenber;
//		}
//		if (temp_head == 99) {
//			map[go_x][go_y].wall = 0xff;
//			continue;
//		}
//
//		temp_head += 4;         //マイナス数防止
//		temp_head -= head;    //headの考慮
//		if (temp_head >= 4) {    //桁上がりの考慮
//			temp_head -= 4;
//		}
//		//		print_map();
//		//		printf("x:%d y:%d\n", map_posX, map_posY);
//
//		switch (temp_head) {
//		case 0:
//			//				printf("S\n");
//
//			run_config.tar_length = BLOCK_LENGTH * 0.5;
//
//			if (move_f == -1) {    //中央から区切りへ
//				run_config.finish_speed = speed_buf;
//				straight(run_config);
//			} else {    //区切りから中央へ
//				if (map_posX == go_x && map_posY == go_y) {
//					break;
//				}
//				run_config.finish_speed = speed_buf;
//				straight(run_config);
//
//			}
//			//			 printf("move_F:%d move:%d\n", move_f, move);
//
//			if ((move_f *= -1) == 1) {    //区切り
//				chenge_pos(1, &map_posX, &map_posY, head);
//				wall_set(0x03);
//				wall_set_around();
//			}
//
//			break;
//		case 1:
//			if (move_f == -1) {
//				turn_config.dir = TURN_RIGHT;
//				turn_config.speed = 0;
//				Delay_ms(100);
//				turn(turn_config);
//				Delay_ms(100);
//				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
//				turn_config.speed = run_config.finish_speed = speed_buf;
//			} else {
//				run_config.tar_length = adjust_length;
//				turn_config.dir = TURN_RIGHT;
//				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//					LED(15);
//					while (1) {
//						if (get_sensordata(RF) >= 150
//								&& get_sensordata(LF) >= 150) {
//							break;
//						}
//					}
//				} else {
//					LED(0);
//					straight(run_config);
//				}
//				turn(turn_config);
//				straight(run_config);
//				run_config.tar_length = BLOCK_LENGTH * 0.5f;
//				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
//				chenge_pos(1, &map_posX, &map_posY, head);
//				wall_set(0x03);
//				wall_set_around();
//				move_f = 1;
//			}
//
//			break;
//		case 2:
//
//			//				printf("U\n");
//
//			if (move_f == 1) {
//				run_config.finish_speed = 0;
//				run_config.tar_length = BLOCK_LENGTH * 0.5;
//				straight(run_config);
//			}
//			move_f = -1;
//			Delay_ms(100);
//			turn_u();
//			run_config.finish_speed = speed_buf;
//			break;
//		case 3:
//			if (move_f == -1) {
//				turn_config.dir = TURN_LEFT;
//				turn_config.speed = 0;
//				Delay_ms(100);
//				turn(turn_config);
//				Delay_ms(100);
//				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
//				turn_config.speed = run_config.finish_speed = speed_buf;
//			} else {
//				run_config.tar_length = adjust_length;
//				turn_config.dir = TURN_LEFT;
//				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//					LED(15);
//					while (1) {
//						if (get_sensordata(RF) >= 150
//								&& get_sensordata(LF) >= 150) {
//							break;
//						}
//					}
//				} else {
//					LED(0);
//					straight(run_config);
//				}
//				turn(turn_config);
//				straight(run_config);
//				run_config.tar_length = BLOCK_LENGTH * 0.5f;
//				chenge_head(turn_config.dir, turn_config.tar_deg, &head);
//				chenge_pos(1, &map_posX, &map_posY, head);
//				wall_set(0x03);
//				wall_set_around();
//				move_f = 1;
//			}
//
//		}
//	}
//
//	//壁が埋まれば次の未探索区画へ
//	//未探索区画がなくなったら終了
//}

//
/*
 * 説明：最短走行
 * 引数：run_config 直進パラメータ
 * 　　　slalom90_config 90°スラロームパラメータ
 * 　　　slalom180_config 180°スラロームパラメータ
 * 　　　gx 目標X座標
 * 　　　gy 目標Y座標
 * 　　　sx スタートX座標
 * 　　　sy スタートY座標
 * 　　　shead スタート時の機体の向き
 * 戻り値：無し
 */
void saitan(RUNConfig run_config, TURNConfig turn_config, uint16_t gx,
		uint16_t gy, uint16_t sx, uint16_t sy, int8_t shead) {
	RUTE rute[100] = { 0 };
	uint16_t x = sx, y = sy;
	uint16_t i = 0;
	int8_t temp_head = 0, head_buf = shead;
	uint8_t temp_wall;
	uint32_t acceleration_buf = run_config.acceleration;
//	float speed_buf = run_config.finish_speed;
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("saitan\n");
//		osMutexRelease(UART_MutexHandle);
//	}

	make_smap(gx, gy, 1);
//	print_map();

	while (x != gx || y != gy) {
		temp_wall =
				(((((map[x][y].wall & 0x0f) + ((map[x][y].wall & 0x0f) << 4))
						<< head_buf) & 0xf0) >> 4)
						+ ((((map[x][y].wall & 0xf0) + (map[x][y].wall >> 4))
								<< head_buf) & 0xf0);
		temp_head = 4;
//		if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//			printf("temp_wall=0x%2x,head_buf=%d\n", temp_wall, head_buf);
//			osMutexRelease(UART_MutexHandle);
//		}
		if ((temp_wall & 0x88) == 0x80) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y + 1].wall & 0xf0) == 0xf0) {
					y++;
					temp_head = 0;
				}
				break;
			case 1:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x + 1][y].wall & 0xf0) == 0xf0) {
					x++;
					temp_head = 0;
				}
				break;
			case 2:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y - 1].wall & 0xf0) == 0xf0) {
					y--;
					temp_head = 0;
				}
				break;
			case 3:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x - 1][y].wall & 0xf0) == 0xf0) {
					x--;
					temp_head = 0;
				}
				break;
			}
		}
		if ((temp_wall & 0x44) == 0x40 && temp_head == 4) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x + 1][y].wall & 0xf0) == 0xf0) {
					x++;
					temp_head = 1;
				}
				break;
			case 1:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y - 1].wall & 0xf0) == 0xf0) {
					y--;
					temp_head = 1;
				}
				break;
			case 2:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x - 1][y].wall & 0xf0) == 0xf0) {
					x--;
					temp_head = 1;
				}
				break;
			case 3:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y + 1].wall & 0xf0) == 0xf0) {
					y++;
					temp_head = 1;
				}
				break;
			}
		}
		if ((temp_wall & 0x11) == 0x10 && temp_head == 4) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x - 1][y].wall & 0xf0) == 0xf0) {
					x--;
					temp_head = 3;
				}
				break;
			case 1:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y + 1].wall & 0xf0) == 0xf0) {
					y++;
					temp_head = 3;
				}
				break;
			case 2:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x + 1][y].wall & 0xf0) == 0xf0) {
					x++;
					temp_head = 3;
				}
				break;
			case 3:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y - 1].wall & 0xf0) == 0xf0) {
					y--;
					temp_head = 3;
				}
				break;
			}
		}
		if ((temp_wall & 0x22) == 0x20 && temp_head == 4) {

			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y - 1].wall & 0xf0) == 0xf0) {
					y--;
					temp_head = 2;
				}
				break;
			case 1:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x - 1][y].wall & 0xf0) == 0xf0) {
					x--;
					temp_head = 2;
				}
				break;
			case 2:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y + 1].wall & 0xf0) == 0xf0) {
					y++;
					temp_head = 2;
				}
				break;
			case 3:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x + 1][y].wall & 0xf0) == 0xf0) {
					x++;
					temp_head = 2;
				}
				break;
			}
		}
		if (temp_head == 4) {
			printf("error\n");
			return;
		}

		switch (temp_head) {
		case 0:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("S\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (i > 0 && rute[i - 1].direction == 0) {
				rute[i - 1].value += BLOCK_LENGTH;
				i--;
			} else {
				rute[i].direction = temp_head;
				if (i > 0
						&& (rute[i - 1].direction == 1
								|| rute[i - 1].direction == 3)) {
					rute[i].value = BLOCK_LENGTH;
				} else {
					rute[i].value = BLOCK_LENGTH / 2;
				}
			}

			break;
		case 1:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("R\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i - 1].value += BLOCK_LENGTH / 2;
			rute[i].direction = temp_head;
			rute[i].value = 90;
			chenge_head(TURN_RIGHT, 90, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value += BLOCK_LENGTH / 2;
			break;
		case 2:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("U\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i].direction = temp_head;
			rute[i].value = 180;
			chenge_head(TURN_RIGHT, 180, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value = BLOCK_LENGTH / 2;

			break;
		case 3:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("L\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i - 1].value += BLOCK_LENGTH / 2;
			rute[i].direction = temp_head;
			rute[i].value = 90;
			chenge_head(TURN_LEFT, 90, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value += BLOCK_LENGTH / 2;
			break;
		}
		i++;
//		if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//			printf("x=%d y=%d head=%d i=%d\n", x, y, head_buf, i);
//			osMutexRelease(UART_MutexHandle);
//		}
	}

	if (rute[i - 1].direction == 0) {
		rute[i - 1].value += 45;
	} else {
		rute[i].direction = 0;
		rute[i].value = BLOCK_LENGTH * 0.2f;
		i++;
	}

	for (int f = 0; f < i; f++) {
		printf("%d:direction=%d value=%ld\n", f, rute[f].direction,
				rute[f].value);
	}
	printf("end\n");

	Delay_ms(100);

	for (int f = 0; f < i; f++) {
		switch (rute[f].direction) {
		case 0:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("S\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			run_config.tar_length = rute[f].value;
			straight(run_config);
//			if (f == 0) {
//				run_config.tar_length += 90;
//			}
			chenge_pos(run_config.tar_length / BLOCK_LENGTH, &map_posX,
					&map_posY, head);
			run_config.acceleration = acceleration_buf;
			break;
		case 1:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("R\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (f == 0) {
				turn_config.dir = TURN_RIGHT;
				turn(turn_config);
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			} else {
				if (((((map[map_posX][map_posY].wall & 0x0f)
						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
						== 0x80) {
					tone(tone_hiC, 10);
					front_adjust();
				}
				turn_config.dir = TURN_RIGHT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);
			}
			chenge_head(TURN_RIGHT, 90, &head);
//			chenge_pos(1, &map_posX, &map_posY, head);
			break;
		case 2:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("U\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			turn_u();
			break;
		case 3:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("L\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (f == 0) {
				turn_config.dir = TURN_LEFT;
				turn(turn_config);
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			} else {
				if (((((map[map_posX][map_posY].wall & 0x0f)
						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
						== 0x80) {
					tone(tone_hiC, 10);
					front_adjust();
				}
				turn_config.dir = TURN_LEFT;
				Delay_ms(100);
				turn(turn_config);
				Delay_ms(100);

			}
			chenge_head(TURN_LEFT, 90, &head);
//			chenge_pos(1, &map_posX, &map_posY, head);
			break;
		}
	}
//	run_config.max_speed = 0.2f;
	map_posX = gx;
	map_posY = gy;
	Delay_ms(500);
	turn_u();
	music();
}

void saitan_s(RUNConfig run_config, TURNConfig turn_config, float adjust_length,
		uint16_t gx, uint16_t gy, uint16_t sx, uint16_t sy, int8_t shead) {
	RUTE rute[1024] = { 0 };
	uint16_t x = sx, y = sy;
	uint16_t i = 0;
	int8_t temp_head = 0, head_buf = shead, temp_hed_prev = 4;
	uint8_t temp_wall;
	float acceleration_buf = run_config.acceleration;
	float turn_speed = turn_config.speed;
	float speed_buf = run_config.max_speed;
//	float speed_buf = run_config.finish_speed;
//	if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//		printf("saitan\n");
//		osMutexRelease(UART_MutexHandle);
//	}

	make_smap(gx, gy, 1);
//	print_map();

	while (x != gx || y != gy) {

		temp_wall =
				(((((map[x][y].wall & 0x0f) + ((map[x][y].wall & 0x0f) << 4))
						<< head_buf) & 0xf0) >> 4)
						+ ((((map[x][y].wall & 0xf0) + (map[x][y].wall >> 4))
								<< head_buf) & 0xf0);
		temp_head = 4;

//		if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//			printf("temp_wall=0x%2x,head_buf=%d\n", temp_wall, head_buf);
//			osMutexRelease(UART_MutexHandle);
//		}
		if ((temp_wall & 0x88) == 0x80) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y].wall & 0x80) == 0x80) {
					y++;
					temp_head = 0;
				}
				break;
			case 1:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x][y].wall & 0x10) == 0x10) {
					x++;
					temp_head = 0;
				}
				break;
			case 2:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y].wall & 0x20) == 0x20) {
					y--;
					temp_head = 0;
				}
				break;
			case 3:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x][y].wall & 0x40) == 0x40) {
					x--;
					temp_head = 0;
				}
				break;
			}
		}
		if ((temp_wall & 0x44) == 0x40 && temp_head == 4) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x][y].wall & 0x10) == 0x10) {
					x++;
					temp_head = 1;
				}
				break;
			case 1:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y].wall & 0x20) == 0x20) {
					y--;
					temp_head = 1;
				}
				break;
			case 2:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x][y].wall & 0x40) == 0x40) {
					x--;
					temp_head = 1;
				}
				break;
			case 3:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y].wall & 0x80) == 0x80) {
					y++;
					temp_head = 1;
				}
				break;
			}
		}
		if ((temp_wall & 0x11) == 0x10 && temp_head == 4) {
			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x][y].wall & 0x40) == 0x40) {
					x--;
					temp_head = 3;
				}
				break;
			case 1:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y].wall & 0x80) == 0x80) {
					y++;
					temp_head = 3;
				}
				break;
			case 2:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x][y].wall & 0x10) == 0x10) {
					x++;
					temp_head = 3;
				}
				break;
			case 3:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y].wall & 0x20) == 0x20) {
					y--;
					temp_head = 3;
				}
				break;
			}
		}
		if ((temp_wall & 0x22) == 0x20 && temp_head == 4) {

			switch (head_buf) {
			case 0:
				if (map[x][y].step > map[x][y - 1].step
						&& (map[x][y].wall & 0x20) == 0x20) {
					y--;
					temp_head = 2;
				}
				break;
			case 1:
				if (map[x][y].step > map[x - 1][y].step
						&& (map[x][y].wall & 0x40) == 0x40) {
					x--;
					temp_head = 2;
				}
				break;
			case 2:
				if (map[x][y].step > map[x][y + 1].step
						&& (map[x][y].wall & 0x80) == 0x80) {
					y++;
					temp_head = 2;
				}
				break;
			case 3:
				if (map[x][y].step > map[x + 1][y].step
						&& (map[x][y].wall & 0x10) == 0x10) {
					x++;
					temp_head = 2;
				}
				break;
			}
		}
		if (temp_head == 4) {
			printf("error\n");
			return;
		}

		switch (temp_head) {
		case 0:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("S\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (i > 0 && rute[i - 1].direction == 0) {
				rute[i - 1].value += BLOCK_LENGTH;
				i--;
			} else {
				rute[i].direction = temp_head;
				if (i > 0
						&& (rute[i - 1].direction == 1
								|| rute[i - 1].direction == 3)) {
					rute[i].value = BLOCK_LENGTH;
				} else {
					rute[i].value = BLOCK_LENGTH / 2;
//					if(i==0){
//						rute[i].value += 5;
//					}
				}
			}

			break;
		case 1:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("R\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i - 1].value += adjust_length;
			rute[i].direction = temp_head;
			rute[i].value = 90;
			chenge_head(TURN_RIGHT, 90, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value += adjust_length;
			break;
		case 2:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("U\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i].direction = temp_head;
			rute[i].value = 180;
			chenge_head(TURN_RIGHT, 180, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value = BLOCK_LENGTH / 2;

			break;
		case 3:
//			if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//				printf("L\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			rute[i - 1].value += adjust_length;
			rute[i].direction = temp_head;
			rute[i].value = 90;
			chenge_head(TURN_LEFT, 90, &head_buf);
			i++;
			rute[i].direction = 0;
			rute[i].value += adjust_length;
			break;
		}
		i++;
//		if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//			printf("x=%d y=%d head=%d i=%d\n", x, y, head_buf, i);
//			osMutexRelease(UART_MutexHandle);
//		}
	}

	if (rute[i - 1].direction == 0) {
		rute[i - 1].value += 45;
	} else {
		rute[i].direction = 0;
		rute[i].value = BLOCK_LENGTH * 0.2f;
		i++;
	}

	for (int f = 0; f < i; f++) {
		printf("%d:direction=%d value=%ld\n", f, rute[f].direction,
				rute[f].value);
	}
	printf("end\n");

	Delay_ms(100);

	for (int f = 0; f < i; f++) {
		switch (rute[f].direction) {
		case 0:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("S\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			run_config.tar_length = rute[f].value;

			if (rute[f].value <= BLOCK_LENGTH * 1.0f) {
				run_config.max_speed = turn_speed;
			} else {
//				run_config.tar_length = BLOCK_LENGTH * 0.5f;
//				run_config.max_speed = turn_speed;
//				run_config.finish_speed = turn_speed;
//				straight(run_config);
				run_config.max_speed = speed_buf;
//				run_config.tar_length = rute[f].value - BLOCK_LENGTH;
//				straight(run_config);
//				run_config.tar_length = BLOCK_LENGTH * 0.5f;
//				run_config.max_speed = turn_speed;
			}
			if (f == i - 1) {
				run_config.finish_speed = 0;
			} else {
				run_config.finish_speed = turn_speed;
			}
			straight(run_config);

//			if (f == 0) {
//				run_config.tar_length += 90;
//			}
			chenge_pos(run_config.tar_length / BLOCK_LENGTH, &map_posX,
					&map_posY, head);
			run_config.acceleration = acceleration_buf;
			break;
		case 1:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("R\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (f == 0) {
				turn_config.dir = TURN_RIGHT;
				turn_config.speed = 0;
				turn(turn_config);
				turn_config.speed = turn_speed;
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			} else {
//				if (((((map[map_posX][map_posY].wall & 0x0f)
//						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
//						== 0x80) {
//					tone(tone_hiC, 10);
//					front_adjust();
//				}
				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//					LED(15);
					while (1) {
						if (get_sensordata(RF) >= 150
								&& get_sensordata(LF) >= 150) {
							break;
						}
					}
				} else {
//					LED(0);
				}
				turn_config.dir = TURN_RIGHT;
//				Delay_ms(100);
				turn(turn_config);
//				Delay_ms(100);
			}
			chenge_head(TURN_RIGHT, 90, &head);
//			chenge_pos(1, &map_posX, &map_posY, head);
			break;
		case 2:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("U\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			turn_u();
			break;
		case 3:
//			if (osMutexWait(UART_MutexHandle, 0U) == osOK) {
//				printf("L\n");
//				osMutexRelease(UART_MutexHandle);
//			}
			if (f == 0) {
				turn_config.dir = TURN_LEFT;
				turn_config.speed = 0;
				turn(turn_config);
				turn_config.speed = turn_speed;
				run_config.tar_length = BLOCK_LENGTH * 0.5;
				straight(run_config);
			} else {
//				if (((((map[map_posX][map_posY].wall & 0x0f)
//						| (map[map_posX][map_posY].wall << 4)) << head) & 0x80)
//						== 0x80) {
//					tone(tone_hiC, 10);
//					front_adjust();
//				}
				if (get_sensor_iswall(RF) && get_sensor_iswall(LF)) {
//					LED(15);
					while (1) {
						if (get_sensordata(RF) >= 150
								&& get_sensordata(LF) >= 150) {
							break;
						}
					}
				} else {
//					LED(0);
				}
				turn_config.dir = TURN_LEFT;
//				Delay_ms(100);
				turn(turn_config);
//				Delay_ms(100);

			}
			chenge_head(TURN_LEFT, 90, &head);
//			chenge_pos(1, &map_posX, &map_posY, head);
			break;
		}
	}
//	run_config.max_speed = 0.2f;
	map_posX = gx;
	map_posY = gy;
	Delay_ms(100);
	turn_u();
	music();
}
