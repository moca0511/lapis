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

float degree_prev = 0, deg_R = 0, deg_L = 0, deg_R_prev = 0, deg_L_prev = 0,
		degree = 0, speed_R = 0, speed_L = 0, speed = 0, speed_prev = 0,
		raw_speed = 0;
float posX = 0, posY = 0;
float gyro = 0, accel = 0, gyro_prev = 0;
uint8_t debug_print = 0;
uint64_t tick = 0;
void lapis(void) {
	int16_t mode = 0;

	for (;;) {
		printf("mode select\n");

		MENU(&mode);

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
		HAL_Delay(10);
		tone(tone_G, 10);
	}
}
void MENU(int16_t *mode) {
	static char *mode_name[16] = { MODE_NAME0, MODE_NAME1, MODE_NAME2,
	MODE_NAME3, MODE_NAME4, MODE_NAME5, MODE_NAME6, MODE_NAME7,
	MODE_NAME8, MODE_NAME9, MODE_NAME10, MODE_NAME11, MODE_NAME12,
	MODE_NAME13, MODE_NAME14, MODE_NAME15 };
	int16_t now = 0, old = 0, old_mode = 0, move = 0;
	for (;;) {
		now = AS5047_GetAngle(ENC_R);
		move = now - old;
		if (move > 4) {
			(*mode)++;
		}
		if (move < -4) {
			(*mode)--;
		}
		if (*mode > 15)
			*mode = 0;
		if (*mode < 0)
			*mode = 15;

		if (*mode != old_mode) {
			UILED_SET((unsigned int) *mode);
			printf("*mode:%2d %30s\n", *mode, mode_name[*mode]);
			old_mode = *mode;
		}
		old = now;
		if (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == 1) {
			while (HAL_GPIO_ReadPin(SW_GPIO_Port, SW_Pin) == 1) {
				HAL_Delay(50);
			}
			tone(tone_hiC, 50);
			break;
		}
		HAL_Delay(10);
	}
}

void mode0(void) {
	printf(
			",%5.1f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%lu,%lu,%lu,%lu,%5.5f,%5.5f,%5.5f\n",
			(float) tick * 0.001f, gyro, accel, degree, deg_L, deg_R, speed_L,
			speed_R, speed, get_sensordata(RS), get_sensordata(RF),
			get_sensordata(LF), get_sensordata(LS), posX, posY, readBattery());
}
void mode1(void) {
	HAL_Delay(1000);
	tone(tone_hiC, 10);
	icm20602_init();
	degree = 0;
	posX = posY = 0;
}
void mode2(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_BACK);
	set_ML_EN(0.3f);
	set_MR_EN(0.3f);
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode3(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_BACK);
	set_ML_EN(0.5f);
	set_MR_EN(0.5f);
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode4(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_BACK);
	set_ML_EN(1.0f);
	set_MR_EN(1.0f);
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode5(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_BACK);
	set_ML_EN(2.0f);
	set_MR_EN(2.0f);
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode6(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_BACK);
	set_ML_EN(3.0f);
	set_MR_EN(3.0f);
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode7(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.5f);
	set_MR_EN(0.5f);
	HAL_Delay(10000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode8(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(1.0f);
	set_MR_EN(1.0f);
	HAL_Delay(10000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode9(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(2.0f);
	set_MR_EN(2.0f);
	HAL_Delay(10000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode10(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(3.0f);
	set_MR_EN(3.0f);
	HAL_Delay(10000);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode11(void) {
	HAL_Delay(1000);
	set_ML_direction(MOVE_FORWARD);
	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	for (float volt = 0.0f; volt <= 3.0f; volt += 0.1f) {
		set_ML_EN(volt);
		set_MR_EN(volt);
		HAL_Delay(10);
	}
	set_ML_EN(3.0);
				set_MR_EN(3.0);
				HAL_Delay(5000);
	for (float volt = 3.0f; volt >= 0.0f; volt -= 0.1f) {
			set_ML_EN(volt);
			set_MR_EN(volt);
			HAL_Delay(10);
		}

	set_ML_direction(MOVE_FORWARD);
	set_MR_direction(MOVE_FORWARD);
	set_ML_EN(0.0f);
	set_MR_EN(0.0f);
}
void mode12(void) {

}
void mode13(void) {

}
void mode14(void) {

}
void mode15(void) {

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static int32_t loop = 100;

	static int8_t led_select = RS;
	if (htim->Instance == TIM1) { //10kHzカウント

		wallSensorRead(led_select);
		led_select++;
		if (led_select == LS + 1) {
			led_select = RS;
		}

		icm20602_get_accel(&accel);
		icm20602_get_gyro(&gyro);
		icm20602_get_deg(&degree, gyro, gyro_prev, 0.001f);

		deg_L = AS5047_ReloadAngle(ENC_L);
		deg_R = AS5047_ReloadAngle(ENC_R);
		speed_L = AS5047_GetSpeed(ENC_L, deg_L_prev);
		speed_R = AS5047_GetSpeed(ENC_R, deg_R_prev) * -1;
//		speed_L=speed_R;
		raw_speed = (speed_L + speed_R) / 2;
		speed = get_fusioned_speed(raw_speed, accel, speed_prev, 0.001f);
		posX += move_x(degree, speed);
		posY += move_y(degree, speed);
		loop--;
		if (loop == 0) {
//			if (debug_print == 1) {
			printf(
					",%5.1f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%lu,%lu,%lu,%lu,%5.5f,%5.5f,%5.5f\n",
					(float) tick * 0.1f, gyro, accel, degree, deg_L, deg_R,
					speed_L, speed_R, speed, get_sensordata(RS),
					get_sensordata(RF), get_sensordata(LF), get_sensordata(LS),
					posX, posY, readBattery());
//			}

//printf("%f,%f,%f,%f,%f,%f\n",gyro[0],gyro[1],gyro[2],accel[0],accel[1],accel[2]);

			tick++;
			loop = 100;
		}
		degree_prev = degree;
		deg_R_prev = deg_R;
		deg_L_prev = deg_L;
		speed_prev = speed;
		gyro_prev = gyro;
//		readBattery();
//			read_enc();
//			read_wall();
	}
}

/*　外部割込み*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}
