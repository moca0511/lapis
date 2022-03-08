/*
 * uart.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include"main.h"

void print_dma(char* str,uint8_t size);

extern UART_HandleTypeDef huart1;
extern char buf[100];

#endif /* INC_UART_H_ */
