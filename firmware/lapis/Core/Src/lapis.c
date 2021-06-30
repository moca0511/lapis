/*
 * lapis.c
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */
#include"lapis.h"
#include"main.h"
#include"AS5047P.h"
#include"buzzer.h"
#include"UI.h"
void lapis(void) {
	int16_t mode = 0;

	tone(tone_C, 100);
	HAL_Delay(100);
	tone(tone_G, 100);

	for (;;) {
//		printf("mode select\n");
//
//		MENU(&mode);

//		printf("\n");

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
//		tone(tone_C, 10);
		HAL_Delay(10);
//		tone(tone_G, 10);
	}
}
void MENU(int16_t *mode) {
	static char *mode_name[16] = { MODE_NAME0, MODE_NAME1, MODE_NAME2,
	MODE_NAME3, MODE_NAME4, MODE_NAME5, MODE_NAME6, MODE_NAME7,
	MODE_NAME8, MODE_NAME9, MODE_NAME10, MODE_NAME11, MODE_NAME12,
	MODE_NAME13, MODE_NAME14, MODE_NAME15 };
	int16_t now = 0, old = 0, old_mode = 0, move = 0;
//	for (;;) {
//		now = AS5047_GetAngle(ENC_R);
//		move=now-old;
//		if (move>4) {
//			(*mode)++;
//		}
//		if (move<-4) {
//			(*mode)--;
//		}
//		if (*mode > 15)
//			*mode = 0;
//		if (*mode < 0)
//			*mode = 15;
//
//		if (*mode != old_mode) {
//			UILED_SET((unsigned int) *mode);
//			printf("*mode:%2d %30s\n", *mode, mode_name[*mode]);
//			old_mode = *mode;
//		}
//		old = now;
////		if (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == 0) {
////			while (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == 0) {
////				HAL_Delay(50);
////			}
////			tone(tone_hiC, 50);
////			break;
////		}
//		HAL_Delay(10);
//	}
}

void mode0(void) {

}
void mode1(void) {

}
void mode2(void) {

}
void mode3(void) {

}
void mode4(void) {

}
void mode5(void) {

}
void mode6(void) {

}
void mode7(void) {

}
void mode8(void) {

}
void mode9(void) {

}
void mode10(void) {

}
void mode11(void) {

}
void mode12(void) {

}
void mode13(void) {

}
void mode14(void) {

}
void mode15(void) {

}
