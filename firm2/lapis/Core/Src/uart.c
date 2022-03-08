/*
 * uart.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */


#include "main.h"
#include "uart.h"

char buf[100] = { 0 };

/* USER CODE BEGIN PV */

/*
 * printf用関数
 * uart1から文字列ptrを1文字ずつlen回出力。タイムアウト1000秒
 */
void __io_putchar(uint8_t ch) {
	HAL_UART_Transmit(&huart1, &ch, 1,1);
}
void print_dma(char* str,uint8_t size){
	HAL_UART_Transmit_DMA(&huart1, (uint8_t*)str, size);
}

