/*
 * agent.h
 *
 *  Created on: 2020/09/11
 *      Author: junmo
 */

#ifndef INC_AGENT_H_
#define INC_AGENT_H_

#include"main.h"

typedef struct RUTE {
	uint8_t direction;	//　進行方向
	uint32_t value;	//　移動距離or旋回角度
} RUTE;


void adachi(RUNConfig RUN_config,TURNConfig turn_config,uint16_t gx,uint16_t gy);
//void saitan(RUNConfig RUN_config,SLALOMConfig slalom90_config,SLALOMConfig slalom180_config,uint16_t gx,uint16_t gy,uint16_t sx,uint16_t sy,int8_t shead);
void saitan(RUNConfig run_config, TURNConfig turn_config, uint16_t gx,
		uint16_t gy, uint16_t sx, uint16_t sy, int8_t shead);
void adachi_s(RUNConfig run_config, TURNConfig turn_config,float adjust_length, uint16_t gx,
		uint16_t gy);
void saitan_s(RUNConfig run_config, TURNConfig turn_config,float adjust_length, uint16_t gx,
		uint16_t gy, uint16_t sx, uint16_t sy, int8_t shead);

#endif /* INC_AGENT_H_ */
