/*
 * uart.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include"main.h"

uint8_t ugets(UART_HandleTypeDef *uartHandle,uint8_t* data,uint8_t data_len);
void print_str(char *str);


#endif /* INC_UART_H_ */
