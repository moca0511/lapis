/*
 * run.c
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#include "run.h"
#include "AS5047P.h"
#include<math.h>


float move_x(float degree,float speed){
//	printf("deg=%fspeed=%fx=%f",degree,speed,(float)(speed*cos((double)degree)));
	return (float)(speed*cos((double)degree));
}
float move_y(float degree,float speed){
	return (float)(speed*sin((double)degree));
}

float get_fusioned_speed(float speed,float accel,float speed_prev,float tick){
	const float alpha=0.65;
	return alpha*(speed_prev + tick*accel)+ (1-alpha)*speed;
}
