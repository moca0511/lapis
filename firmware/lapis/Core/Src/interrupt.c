/*
 * interrupt.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	static int32_t loop = 100;
	static uint64_t tick = 0;
	static float degree_prev=0,deg_R=0,deg_L=0,deg_R_prev=0,deg_L_prev=0,degree=0,speed_R=0,speed_L=0,speed=0,speed_prev=0,raw_speed=0;
	static float posX=0,posY=0;
	static float gyro[3]={0},accel[3]={0};
	static int8_t led_select=RS;
	if (htim->Instance == TIM1) { //1kHzカウント
		wallSensorRead(led_select);
		led_select++;
		if(led_select==LS+1){
			led_select=RS;
		}
//		degree=upload_deg(0.001,degree);
//		imu_acc=upload_acc(0.001);
		icm20602_get_accel(accel);
		icm20602_get_gyro(gyro);
		deg_L=AS5047_ReloadAngle(ENC_L);
		deg_R=AS5047_ReloadAngle(ENC_R);
		speed_L=AS5047_GetSpeed(ENC_L, deg_L_prev);
		speed_R=AS5047_GetSpeed(ENC_R, deg_R_prev)*-1;
//		speed_L=speed_R;
		raw_speed=(speed_L+speed_R)/2;
		speed=get_fusioned_speed(raw_speed,accel[0],speed_prev,0.001);
		posX+=move_x(degree,speed);
		posY+=move_y(degree,speed);
		set_ML_direction(MOVE_FORWARD);
				set_MR_direction(MOVE_FORWARD);
				set_ML_EN(1.0);
				set_MR_EN(1.0);
		loop--;
		if (loop == 0) {
			printf(",%5.1f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%5.5f,%lu,%lu,%lu,%lu,%5.5f,%5.5f,%5.5f\n",
					(float) tick * 0.1,
					gyro[0],gyro[1],gyro[2],accel[0],accel[1],accel[2],
					deg_R, deg_L,speed_L,speed_R,speed,
					get_sensordata(RS),get_sensordata(RF),get_sensordata(LF),get_sensordata(LS),
					posX,posY,
					readBattery());
//printf("%f,%f,%f,%f,%f,%f\n",gyro[0],gyro[1],gyro[2],accel[0],accel[1],accel[2]);

			tick++;
			loop = 100;
		}
		degree_prev=degree;
		deg_R_prev=deg_R;
		deg_L_prev=deg_L;
		speed_prev=speed;
//		readBattery();
//			read_enc();
//			read_wall();
	}
}

/*　外部割込み*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

}
