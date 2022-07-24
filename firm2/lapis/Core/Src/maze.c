/*
 * maze.c
 *
 *  Created on: Sep 5, 2020
 *      Author: junmo
 */

#include "maze.h"
#include "wallsensor.h"
#include "lapis.h"
#include "UI.h"
#include"flash.h"
#include "adc.h"
#include "run.h"

MAP map[MAP_X_MAX][MAP_Y_MAX]; //ｓマップ情報
extern int16_t map_posX, map_posY;	//　現在の位置
extern int8_t head;	//　現在向いている方向(北東南西(0,1,2,3))

/*
 * 説明：MAP情報出力
 * 引数：無し
 * 戻り値：無し
 */
void print_map(void) {
	printf("\n");
	printf("    ");
	for (int i = 0; i < MAP_X_MAX; i++) {
		printf("  %d%d", i / 10, i % 10);
	}
	printf("\n");
	for (int i = 0; i <= MAP_X_MAX; i++) {
		printf("----");
	}
	printf("\n");
	for (int i = MAP_Y_MAX - 1; i >= 0; i--) {
		printf("%3d|", i);
		for (int f = 0; f < MAP_X_MAX; f++) {
			printf("%4x", map[f][i].wall);
		}
		printf("\n");
	}
	printf("\n");
	printf("    ");
	for (int i = 0; i < MAP_X_MAX; i++) {
		printf("  %d%d", i / 10, i % 10);
	}

	printf("\n");
	for (int i = 0; i <= MAP_X_MAX; i++) {
		printf("----");
	}
	printf("\n");
	for (int i = MAP_Y_MAX - 1; i >= 0; i--) {
		printf("%3d|", i);
		for (int f = 0; f < MAP_X_MAX; f++) {
			if (i == map_posY && f == map_posX) {
				switch (head) {
				case 0:
					printf(" ^^ ");
					break;
				case 1:
					printf(" -> ");
					break;
				case 2:
					printf(" vv ");
					break;
				case 3:
					printf(" <- ");
					break;
				}
			} else {
				printf("%4d", map[f][i].step);
			}
		}
		printf("\n");
	}
	printf("\n");
		printf("    ");
		for (int i = 0; i < MAP_X_MAX; i++) {
			printf("  %d%d", i / 10, i % 10);
		}
		printf("\n");
		for (int i = 0; i <= MAP_X_MAX; i++) {
			printf("----");
		}
		printf("\n");
		for (int i = MAP_Y_MAX - 1; i >= 0; i--) {
			printf("%3d|", i);
			for (int f = 0; f < MAP_X_MAX; f++) {
				printf("%4x", map[f][i].check);
			}
			printf("\n");
		}
}
/*
 * 説明：MAP情報初期化
 * 引数：無し
 * 戻り値：無し
 */
void smap_Init(void) {
	/*
	 マップ設定
	 */
	map_posX = START_X;
	map_posY = START_Y;
	head = 0;

	for (int i = 0; i < MAP_Y_MAX; i++) {
		for (int f = 0; f < MAP_X_MAX; f++) {
			map[f][i].step = 255;
			map[f][i].wall = 0x00;
			map[f][i].check = false;
		}
	}

	for (int i = 0; i < MAP_Y_MAX; i++) {
		map[0][i].wall += 0x11;
		map[MAP_X_MAX - 1][i].wall += 0x44;
	}
	for (int i = 0; i < MAP_X_MAX; i++) {
		map[i][0].wall += 0x22;
		map[i][MAP_Y_MAX - 1].wall += 0x88;
	}

	map[START_X][START_Y].wall |= 0x44;
	map[START_X][START_Y].wall |= 0x80;
	map[START_X + 1][START_Y].wall |= 0x11;
	map[START_X][START_Y + 1].wall |= 0x20;

}
/*
 * 説明：歩数マップ作成
 * 引数：gx 目標X座標
 * 　　　gy 目標Y座標
 * 　　　mode 0:探索モード(未探索込みで作成)　1:最短モード(探索済みのみで作成)
 * 戻り値：無し
 */
void make_smap(uint16_t gx, uint16_t gy, uint8_t mode) {
	int16_t value = 0;
	int16_t buf1[2][MAP_SIZE];
	int16_t cnt1 = 0;
	int16_t buf2[2][MAP_SIZE];
	int16_t cnt2 = 0;
	int16_t map_posX, map_posY;

	//	 ｓ等高線マップを初期化する。
	for (int i = 0; i < MAP_Y_MAX; i++) {
		for (int f = 0; f < MAP_X_MAX; f++) {
			map[f][i].step = 255;
		}
	}

	/* ｓ目標区画に値を設定する。 */
	map[buf1[0][cnt1] = gx][buf1[1][cnt1] = gy].step = value++;
	cnt1++;
	if (mode == 1) {
		while (1) {
			do {
				/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
				map_posX = buf1[0][--cnt1];
				map_posY = buf1[1][cnt1];

				/* ｓ隣接区画に値を設定する。 */
				/* ｓ北。 */
				if (map_posY + 1 < MAP_Y_MAX) {
					if ((map[map_posX][map_posY].wall & 0x88) == 0x80
							&& map[map_posX][map_posY + 1].step == 255
							&& (map[map_posX][map_posY + 1].wall & 0xf0)
									== 0xf0) {
						map[buf2[0][cnt2] = map_posX][buf2[1][cnt2] = map_posY
								+ 1].step = value;
						cnt2++;
					}
				}
				/* ｓ東。 */
				if (map_posX + 1 < MAP_X_MAX) {
					if ((map[map_posX][map_posY].wall & 0x44) == 0x40
							&& map[map_posX + 1][map_posY].step == 255
							&& (map[map_posX + 1][map_posY].wall & 0xf0)
									== 0xf0) {
						map[buf2[0][cnt2] = map_posX + 1][buf2[1][cnt2] =
								map_posY].step = value;
						cnt2++;
					}
				}
				/* ｓ南。 */
				if (map_posY != 0) {
					if ((map[map_posX][map_posY].wall & 0x22) == 0x20
							&& map[map_posX][map_posY - 1].step == 255
							&& (map[map_posX][map_posY - 1].wall & 0xf0)
									== 0xf0) {
						map[buf2[0][cnt2] = map_posX][buf2[1][cnt2] = map_posY
								- 1].step = value;
						cnt2++;
					}
				}
				/* ｓ西。 */
				if (map_posX != 0) {
					if ((map[map_posX][map_posY].wall & 0x11) == 0x10
							&& map[map_posX - 1][map_posY].step == 255
							&& (map[map_posX - 1][map_posY].wall & 0xf0)
									== 0xf0) {
						map[buf2[0][cnt2] = map_posX - 1][buf2[1][cnt2] =
								map_posY].step = value;
						cnt2++;
					}
				}

			} while (cnt1 != 0); /* ｓバッファが空になるまで繰り返す。 */

			/* ｓもう一方のバッファが空なら終了する。 */
			if (cnt2 == 0) {
				break;
			}

			/* ｓ設定する値を更新する。 */
			++value;

			do {
				/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
				map_posX = buf2[0][--cnt2];
				map_posY = buf2[1][cnt2];

				/* ｓ隣接区画に値を設定する。 */
				/* ｓ北。 */
				if (map_posY + 1 < MAP_Y_MAX) {
					if ((map[map_posX][map_posY].wall & 0x08) == 0x00
							&& map[map_posX][map_posY + 1].step == 255
							&& (map[map_posX][map_posY + 1].wall & 0xf0)
									== 0xf0) {
						map[buf1[0][cnt1] = map_posX][buf1[1][cnt1] = map_posY
								+ 1].step = value;
						cnt1++;
					}
				}
				/* ｓ東。 */
				if (map_posX + 1 < MAP_X_MAX) {
					if ((map[map_posX][map_posY].wall & 0x04) == 0x00
							&& map[map_posX + 1][map_posY].step == 255
							&& (map[map_posX + 1][map_posY].wall & 0xf0)
									== 0xf0) {
						map[buf1[0][cnt1] = map_posX + 1][buf1[1][cnt1] =
								map_posY].step = value;
						cnt1++;
					}
				}
				/* ｓ南。 */
				if (map_posY != 0) {
					if ((map[map_posX][map_posY].wall & 0x02) == 0x00
							&& map[map_posX][map_posY - 1].step == 255
							&& (map[map_posX][map_posY - 1].wall & 0xf0)
									== 0xf0) {
						map[buf1[0][cnt1] = map_posX][buf1[1][cnt1] = map_posY
								- 1].step = value;
						cnt1++;
					}
				}
				/* ｓ西。 */
				if (map_posX != 0) {
					if ((map[map_posX][map_posY].wall & 0x01) == 0x00
							&& map[map_posX - 1][map_posY].step == 255
							&& (map[map_posX - 1][map_posY].wall & 0xf0)
									== 0xf0) {
						map[buf1[0][cnt1] = map_posX - 1][buf1[1][cnt1] =
								map_posY].step = value;
						cnt1++;
					}
				}
			} while (cnt2 != 0); /* ｓバッファが空になるまで繰り返す。 */

			/* ｓもう一方のバッファが空なら終了する。 */
			if (cnt1 == 0) {
				break;
			}

			/* ｓ設定する値を更新する。 */
			++value;
		}
	} else {
		while (1) {
			do {
				/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
				map_posX = buf1[0][--cnt1];
				map_posY = buf1[1][cnt1];

				/* ｓ隣接区画に値を設定する。 */
				/* ｓ北。 */
				if (map_posY + 1 < MAP_Y_MAX) {
					if ((map[map_posX][map_posY].wall & 0x08) == 0x00
							&& map[map_posX][map_posY + 1].step == 255) {
						map[buf2[0][cnt2] = map_posX][buf2[1][cnt2] = map_posY
								+ 1].step = value;
						cnt2++;
					}
				}
				/* ｓ東。 */
				if (map_posX + 1 < MAP_X_MAX) {
					if ((map[map_posX][map_posY].wall & 0x04) == 0x00
							&& map[map_posX + 1][map_posY].step == 255) {
						map[buf2[0][cnt2] = map_posX + 1][buf2[1][cnt2] =
								map_posY].step = value;
						cnt2++;
					}
				}
				/* ｓ南。 */
				if (map_posY != 0) {
					if ((map[map_posX][map_posY].wall & 0x02) == 0x00
							&& map[map_posX][map_posY - 1].step == 255) {
						map[buf2[0][cnt2] = map_posX][buf2[1][cnt2] = map_posY
								- 1].step = value;
						cnt2++;
					}
				}
				/* ｓ西。 */
				if (map_posX != 0) {
					if ((map[map_posX][map_posY].wall & 0x01) == 0x00
							&& map[map_posX - 1][map_posY].step == 255) {
						map[buf2[0][cnt2] = map_posX - 1][buf2[1][cnt2] =
								map_posY].step = value;
						cnt2++;
					}
				}

			} while (cnt1 != 0); /* ｓバッファが空になるまで繰り返す。 */

			/* ｓもう一方のバッファが空なら終了する。 */
			if (cnt2 == 0) {
				break;
			}

			/* ｓ設定する値を更新する。 */
			++value;

			do {
				/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
				map_posX = buf2[0][--cnt2];
				map_posY = buf2[1][cnt2];

				/* ｓ隣接区画に値を設定する。 */
				/* ｓ北。 */
				if (map_posY + 1 < MAP_Y_MAX) {
					if ((map[map_posX][map_posY].wall & 0x08) == 0x00
							&& map[map_posX][map_posY + 1].step == 255) {
						map[buf1[0][cnt1] = map_posX][buf1[1][cnt1] = map_posY
								+ 1].step = value;
						cnt1++;
					}
				}
				/* ｓ東。 */
				if (map_posX + 1 < MAP_X_MAX) {
					if ((map[map_posX][map_posY].wall & 0x04) == 0x00
							&& map[map_posX + 1][map_posY].step == 255) {
						map[buf1[0][cnt1] = map_posX + 1][buf1[1][cnt1] =
								map_posY].step = value;
						cnt1++;
					}
				}
				/* ｓ南。 */
				if (map_posY != 0) {
					if ((map[map_posX][map_posY].wall & 0x02) == 0x00
							&& map[map_posX][map_posY - 1].step == 255) {
						map[buf1[0][cnt1] = map_posX][buf1[1][cnt1] = map_posY
								- 1].step = value;
						cnt1++;
					}
				}
				/* ｓ西。 */
				if (map_posX != 0) {
					if ((map[map_posX][map_posY].wall & 0x01) == 0x00
							&& map[map_posX - 1][map_posY].step == 255) {
						map[buf1[0][cnt1] = map_posX - 1][buf1[1][cnt1] =
								map_posY].step = value;
						cnt1++;
					}
				}
			} while (cnt2 != 0); /* ｓバッファが空になるまで繰り返す。 */

			/* 　ｓもう一方のバッファが空なら終了する。 */
			if (cnt1 == 0) {
				break;
			}

			/* 　あ設定する値を更新する。 */
			++value;
		}
	}
	//printf("make fin\n");
}

t_bool get_unknow_block(uint16_t *x, uint16_t *y) {
	*x = map_posX;
	*y = map_posY;
	int i = 0, f = 0;
	int finish = 0;
	for (int i = 0; i < MAP_X_MAX; i++) {
		for (int f = 0; f < MAP_Y_MAX; f++) {
			if ((map[i][f].wall & 0xf0) == 0xf0) {
				map[i][f].check = true;
			}
		}
	}
	make_smap(0,0,0);
	for (i = 0; i < MAP_X_MAX; i++) {
		for (f = 0; f < MAP_Y_MAX; f++) {

			*x = map_posX + i;

			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
			*y = map_posY + f;
			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
			*y = map_posY - f;
			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
			*x = map_posX - i;
			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
			*y = map_posY + f;
			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
			*y = map_posY - f;
			if ((*x >= 0 && *x < MAP_X_MAX) && (*y >= 0 && *y < MAP_Y_MAX)) {

				if (map[*x][*y].check == false) {
//					printf("%d,%d\n",*x,*y);
					map[*x][*y].check = true;
					if (map[*x][*y].step != 255) {
						make_smap(*x, *y, 0);
						if (map[map_posX][map_posY].step != 255) {
							finish = 1;
							break;
						}
					}
				}
			}
		}
		if (finish) {
			break;
		}
	}
	if (finish) {
		return true;
	}
	return false;

}

/*
 * 説明：指定方向の壁の有無確認・壁情報更新
 * 引数：mode 0x01:前　0x02:左右　0x03:前左右
 * 戻り値：無し
 */
void wall_set(uint8_t mode) {

	//printf("wallset Y=%d,X=%d\n", map_posY, map_posX);
	uint8_t wall_info = 0;

	if ((mode & 0x01) == 0x01) {
		if (get_sensor_iswall(LF) && get_sensor_iswall(RF)) {
			wall_info += 0x88;
		}
	}
	if ((mode & 0x02) == 0x02) {
		if (get_sensor_iswall(LS)) {
			wall_info += 0x11;
		}
		if (get_sensor_iswall(RS)) {
			wall_info += 0x44;
		}
	}
	wall_info >>= head;
	wall_info &= 0x0f;
	wall_info |= (wall_info << 4);

	if (mode == 0x02) {
		wall_info |= (((0x55 >> head) & 0x0f) << 4);
	} else if (mode == 0x01) {
		wall_info |= (((0x88 >> head) & 0x0f) << 4);
	} else if (mode == 0x03) {
		wall_info |= (((0xdd >> head) & 0x0f) << 4);
	}

	map[map_posX][map_posY].wall |= wall_info;

//	LED(map[map_posX][map_posY].wall & 0x0f);
}

/*
 * 説明：現在いるマスの壁情報を周囲のマスに反映
 * 引数：無し
 * 戻り値：無し
 */
void wall_set_around(void) {

	if ((map[map_posX][map_posY].wall & 0x88) == 0x88) {
		if (map_posY < MAP_Y_MAX - 1) {
			map[map_posX][map_posY + 1].wall |= 0x22;
		}
	} else {
		if (map_posY < MAP_Y_MAX - 1) {
			map[map_posX][map_posY + 1].wall |= 0x20;
		}
	}

	if ((map[map_posX][map_posY].wall & 0x44) == 0x44) {
		if (map_posX < MAP_X_MAX - 1) {
			map[map_posX + 1][map_posY].wall |= 0x11;
		}
	} else {
		if (map_posX < MAP_X_MAX - 1) {
			map[map_posX + 1][map_posY].wall |= 0x10;
		}
	}

	if ((map[map_posX][map_posY].wall & 0x22) == 0x22) {
		if (map_posY > 0) {
			map[map_posX][map_posY - 1].wall |= 0x88;
		}
	} else {
		if (map_posY > 0) {
			map[map_posX][map_posY - 1].wall |= 0x80;
		}
	}

	if ((map[map_posX][map_posY].wall & 0x11) == 0x11) {
		if (map_posX > 0) {
			map[map_posX - 1][map_posY].wall |= 0x44;
		}
	} else {
		if (map_posX > 0) {
			map[map_posX - 1][map_posY].wall |= 0x40;
		}
	}
}

/*
 * 説明：現在位置と隣接マスの歩数の差を返す
 * 引数：map_posX 現在位置のX座標
 * 戻り値：現在位置と隣接マスの歩数の差
 */
uint8_t wall_check(uint8_t direction) {
	uint8_t and = 0x00;
	switch (direction) {
	case 0:	//前方
		switch (head) {
		case 0:
			and = 0x88;
			break;
		case 1:
			and = 0x44;
			break;
		case 2:
			and = 0x22;
			break;
		case 3:
			and = 0x11;
			break;

		}
		break;
	case 1:	//左方
		switch (head) {
		case 0:
			and = 0x11;
			break;
		case 1:
			and = 0x88;
			break;
		case 2:
			and = 0x44;
			break;
		case 3:
			and = 0x22;
			break;

		}
		break;
	case 2:	//右方
		switch (head) {
		case 0:
			and = 0x44;
			break;
		case 1:
			and = 0x22;
			break;
		case 2:
			and = 0x11;
			break;
		case 3:
			and = 0x88;
			break;
		}
		break;
	}
	printf("and:%4x,wall:%4x,wall_check:%4x\n", and,
			map[map_posX][map_posY].wall, map[map_posX][map_posY].wall & and);
	return (map[map_posX][map_posY].wall & and) % 0x10;
}

/*
 * 説明：現在位置と隣接マスの歩数の差を返す
 * 引数：map_posX 現在位置のX座標
 * 		map_posY　現在位置のY座標
 * 		direction　進行方向
 * 戻り値：現在位置と隣接マスの歩数の差
 */
int16_t step_check(uint16_t map_posX, uint16_t map_posY, uint8_t direction) {
	int16_t step = -1;
	switch (direction) {
	case 0:
		switch (head) {
		case 0:
			if (map_posY + 1 < MAP_Y_MAX) {
				step = map[map_posX][map_posY + 1].step
						- map[map_posX][map_posY].step;
			}
			break;
		case 1:
			if (map_posX + 1 < MAP_X_MAX) {
				step = map[map_posX + 1][map_posY].step
						- map[map_posX][map_posY].step;
			}
			break;
		case 2:
			if (map_posY > 0) {
				step = map[map_posX][map_posY - 1].step
						- map[map_posX][map_posY].step;
			}
			break;
		case 3:
			if (map_posX > 0) {
				step = map[map_posX + 1][map_posY].step
						- map[map_posX][map_posY].step;
			}
			break;
		}
		break;
	case 1:
		switch (head) {
		case 0:
			if (map_posX > 0) {
				step = map[map_posX][map_posY].step
						- map[map_posX - 1][map_posY].step;
			}
			break;
		case 1:
			if (map_posY + 1 < MAP_Y_MAX) {
				step = map[map_posX][map_posY].step
						- map[map_posX][map_posY + 1].step;
			}
			break;
		case 2:
			if (map_posX + 1 < MAP_X_MAX) {
				step = map[map_posX][map_posY].step
						- map[map_posX + 1][map_posY].step;
			}
			break;
		case 3:
			if (map_posY > 0) {
				step = map[map_posX][map_posY].step
						- map[map_posX][map_posY - 1].step;
			}
			break;
		}
		break;
	case 2:
		switch (head) {
		case 0:
			if (map_posX + 1 < MAP_X_MAX) {
				step = map[map_posX][map_posY].step
						- map[map_posX + 1][map_posY].step;
			}
			break;
		case 1:
			if (map_posY > 0) {
				step = map[map_posX][map_posY].step
						- map[map_posX][map_posY - 1].step;
			}
			break;
		case 2:
			if (map_posX > 0) {
				step = map[map_posX][map_posY].step
						- map[map_posX - 1][map_posY].step;
			}
			break;
		case 3:
			if (map_posY + 1 < MAP_Y_MAX) {
				step = map[map_posX][map_posY].step
						- map[map_posX][map_posY + 1].step;
			}
			break;
		}
		break;
	}
	return step;
}

/*
 * 説明：searchX,searchYのマスから1番近い未探索で最短経路の可能性のある場所を探索しsearchX,searchYに結果を入れる
 * 引数：*searchX 初期値：探索開始X座標，終了時：探索先のX座標を入れる変数のポインタ
 * 		*searchY 初期値：探索開始Y座標，終了時：探索先のY座標を入れる変数のポインタ
 * 戻り値：無し
 */
void check_searchBlock(uint16_t *searchX, uint16_t *searchY) {
	int16_t buf1[2][MAP_SIZE];
	int16_t cnt1 = 0;
	int16_t buf2[2][MAP_SIZE];
	int16_t cnt2 = 0;
	int16_t temp_posX, temp_posY;

	make_smap(*searchX, *searchY, 0);
	/* ｓ目標区画に値を設定する。 */
	buf1[0][cnt1] = START_X;
	buf1[1][cnt1] = START_Y;
	cnt1++;

	while (1) {
		do {
			/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
			temp_posX = buf1[0][--cnt1];
			temp_posY = buf1[1][cnt1];

			/* 最短の可能性があり未探索のマスを探索 */
			/* ｓ北。 */
			if (temp_posY + 1 < MAP_Y_MAX) {
				if (map[temp_posX][temp_posY + 1].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x88) != 0x88) {
					if ((map[temp_posX][temp_posY + 1].wall & 0xf0) == 0xf0) {
						buf2[0][cnt2] = temp_posX;
						buf2[1][cnt2++] = temp_posY + 1;
					} else {
						*searchX = temp_posX;
						*searchY = temp_posY + 1;
						return;
					}
				}
			}
			/* ｓ東。 */
			if (temp_posX != MAP_X_MAX - 1) {
				if (map[temp_posX + 1][temp_posY].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x44) != 0x44) {
					if ((map[temp_posX + 1][temp_posY].wall & 0xf0) == 0xf0) {
						buf2[0][cnt2] = temp_posX + 1;
						buf2[1][cnt2++] = temp_posY;
					} else {
						*searchX = temp_posX + 1;
						*searchY = temp_posY;
						return;
					}
				}
			}
			/* ｓ南。 */
			if (temp_posY != 0) {
				if (map[temp_posX][temp_posY - 1].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x22) != 0x22) {
					if ((map[temp_posX][temp_posY - 1].wall & 0xf0) == 0xf0) {
						buf2[0][cnt2] = temp_posX;
						buf2[1][cnt2++] = temp_posY - 1;
					} else {
						*searchX = temp_posX;
						*searchY = temp_posY - 1;
						return;
					}
				}
			}
			/* ｓ西。 */
			if (temp_posX != 0) {
				if (map[temp_posX - 1][temp_posY].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x11) != 0x11) {
					if ((map[temp_posX - 1][temp_posY].wall & 0xf0) == 0xf0) {
						buf2[0][cnt2] = temp_posX - 1;
						buf2[1][cnt2++] = temp_posY;
					} else {
						*searchX = temp_posX - 1;
						*searchY = temp_posY;
						return;
					}
				}
			}

		} while (cnt1 != 0); /* ｓバッファが空になるまで繰り返す。 */
		/* ｓもう一方のバッファが空なら終了する。 */
		if (cnt2 == 0) {
			break;
		}

		do {
			/* ｓバッファから値設定済み区画の座標を1つ取り出す。 */
			temp_posX = buf2[0][--cnt2];
			temp_posY = buf2[1][cnt2];
			/* 最短の可能性があり未探索のマスを探索 */
			/* ｓ北。 */
			if (temp_posY + 1 < MAP_Y_MAX) {
				if (map[temp_posX][temp_posY + 1].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x88) != 0x88) {
					if ((map[temp_posX][temp_posY + 1].wall & 0xf0) == 0xf0) {
						buf1[0][cnt1] = temp_posX;
						buf1[1][cnt1++] = temp_posY + 1;
					} else {
						*searchX = temp_posX;
						*searchY = temp_posY + 1;
						return;
					}
				}
			}
			/* ｓ東。 */
			if (temp_posX != MAP_X_MAX - 1) {
				if (map[temp_posX + 1][temp_posY].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x44) != 0x44) {
					if ((map[temp_posX + 1][temp_posY].wall & 0xf0) == 0xf0) {
						buf1[0][cnt1] = temp_posX + 1;
						buf1[1][cnt1++] = temp_posY;
					} else {
						*searchX = temp_posX + 1;
						*searchY = temp_posY;
						return;
					}
				}
			}
			/* ｓ南。 */
			if (temp_posY != 0) {
				if (map[temp_posX][temp_posY - 1].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x22) != 0x22) {
					if ((map[temp_posX][temp_posY - 1].wall & 0xf0) == 0xf0) {
						buf1[0][cnt1] = temp_posX;
						buf1[1][cnt1++] = temp_posY - 1;
					} else {
						*searchX = temp_posX;
						*searchY = temp_posY - 1;
						return;
					}
				}
			}
			/* ｓ西。 */
			if (temp_posX != 0) {
				if (map[temp_posX - 1][temp_posY].step
						== map[temp_posX][temp_posY].step - 1
						&& (map[temp_posX][temp_posY].wall & 0x11) != 0x11) {
//					if (osMutexWait(UART_MutexHandle, osWaitForever) == osOK) {
//						printf("W\n");
//						osMutexRelease(UART_MutexHandle);
//					}
					if ((map[temp_posX - 1][temp_posY].wall & 0xf0) == 0xf0) {
						buf1[0][cnt1] = temp_posX - 1;
						buf1[1][cnt1++] = temp_posY;
					} else {
						*searchX = temp_posX - 1;
						*searchY = temp_posY;
						return;
					}
				}
			}
		} while (cnt2 != 0); /* ｓバッファが空になるまで繰り返す。 */

		/* ｓもう一方のバッファが空なら終了する。 */
		if (cnt1 == 0) {
			break;
		}
	}

}

/*
 * 説明：マップ保存
 * 引数：無し
 * 戻り値：無し
 */
void maze_save(void) {
	MAP temp_map[MAP_X_MAX][MAP_Y_MAX];
	uint8_t end = 1;
	while (end) {
		end = 0;
		writeFlash(MAZE_FLASH_START_ADD, (uint64_t*) map, sizeof(map));
		loadFlash(MAZE_FLASH_START_ADD, (uint8_t*) temp_map, sizeof(temp_map));
		for (int i = 0; i < MAP_X_MAX; i++) {
			for (int f = 0; f < MAP_Y_MAX; f++) {
				if (map[i][f].wall != temp_map[i][f].wall
						|| map[i][f].step != temp_map[i][f].step) {
					end = 1;
					break;
				}
			}
			if (end) {
				break;
			}
		}
	}
}
/*
 * 説明：マップ読み出し
 * 引数：無し
 * 戻り値：無し
 */
void maze_load(void) {
	loadFlash(MAZE_FLASH_START_ADD, (uint8_t*) map, sizeof(map));
}

/*
 * 説明：現在位置変更処理
 * 引数：block 移動マス数
 * 戻り値：無し
 */
void chenge_pos(int16_t block, int16_t *temp_posX, int16_t *temp_posY,
		int8_t temp_head) {
	switch (temp_head) {
	case 0:
		*temp_posY += block;
		break;
	case 1:
		*temp_posX += block;
		break;
	case 2:
		*temp_posY -= block;
		break;
	case 3:
		*temp_posX -= block;
		break;
	}
}

/*
 * 説明：車体の向き変更
 * 引数：direction 旋回方向
 * 		value 旋回角度
 * 		*head_buf 変更したい進行方向を持つ変数のポインタ
 * 戻り値：無し
 */
void chenge_head(uint16_t direction, uint32_t value, int8_t *head_buf) {
	if (direction == TURN_RIGHT) {
		*head_buf += value / 90;
	} else {
		*head_buf -= value / 90;
	}
	if (*head_buf > 3) {
		*head_buf -= 4;
	}
	if (*head_buf < 0) {
		*head_buf += 4;
	}
}
