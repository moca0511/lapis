/*
 * adc.h
 *
 *  Created on: Jun 14, 2021
 *      Author: junmo
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_
#include "main.h"

//ADC
typedef enum {
	RS,
	RF,
	LF,
	LS,
	BATT,
	ADC_CHANNEL_MAX
} ADC_CHANNEL;


extern ADC_HandleTypeDef hadc1;

#define ADC_MAX (4095)

void adc_dma_start(void);
uint16_t get_adc(uint8_t channel);

#endif /* INC_ADC_H_ */
