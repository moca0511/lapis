/*
 * adc.c
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#include "adc.h"
#include "uart.h"
static uint16_t   aADCxConvertedData[5];
uint16_t get_adc(uint8_t channel) {
	return aADCxConvertedData[channel];
}

void adc_dma_start(void){
	  if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)  aADCxConvertedData, 5)
	              == HAL_OK)
	          printf("Start ADC Successfully\n\r");
	      else
	          printf("Start ADC failed\n\r");
}
