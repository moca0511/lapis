/*
 * run.h
 *
 *  Created on: Jun 18, 2021
 *      Author: junmo
 */

#ifndef INC_RUN_H_
#define INC_RUN_H_

#include"main.h"

float move_x(float degree,float speed);
float move_y(float degree,float speed);

float get_fusioned_speed(float speed,float accel,float speed_prev,float tick);
#endif /* INC_RUN_H_ */
