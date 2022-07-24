/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <math.h>
#include "uart.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define	PI            3.14159265358979f
/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOC
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOC
#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOF
#define ENC_SCK_Pin GPIO_PIN_1
#define ENC_SCK_GPIO_Port GPIOF
#define WALL_RS_Pin GPIO_PIN_0
#define WALL_RS_GPIO_Port GPIOA
#define WALL_RF_Pin GPIO_PIN_1
#define WALL_RF_GPIO_Port GPIOA
#define WALL_LF_Pin GPIO_PIN_2
#define WALL_LF_GPIO_Port GPIOA
#define WALL_LS_Pin GPIO_PIN_3
#define WALL_LS_GPIO_Port GPIOA
#define ENC_CS_L_Pin GPIO_PIN_4
#define ENC_CS_L_GPIO_Port GPIOA
#define IMU_SCK_Pin GPIO_PIN_5
#define IMU_SCK_GPIO_Port GPIOA
#define IMU_MISO_Pin GPIO_PIN_6
#define IMU_MISO_GPIO_Port GPIOA
#define IMU_MOSI_Pin GPIO_PIN_7
#define IMU_MOSI_GPIO_Port GPIOA
#define IMU_CS_Pin GPIO_PIN_0
#define IMU_CS_GPIO_Port GPIOB
#define ML_PHASE_Pin GPIO_PIN_1
#define ML_PHASE_GPIO_Port GPIOB
#define MR_PHASE_Pin GPIO_PIN_2
#define MR_PHASE_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_11
#define BUZZER_GPIO_Port GPIOB
#define BATTERY_Pin GPIO_PIN_14
#define BATTERY_GPIO_Port GPIOB
#define ENC_MOSI_Pin GPIO_PIN_15
#define ENC_MOSI_GPIO_Port GPIOB
#define ENC_CS_R_Pin GPIO_PIN_8
#define ENC_CS_R_GPIO_Port GPIOA
#define ENC_MISO_Pin GPIO_PIN_10
#define ENC_MISO_GPIO_Port GPIOA
#define MR_EN_Pin GPIO_PIN_11
#define MR_EN_GPIO_Port GPIOA
#define ML_EN_Pin GPIO_PIN_12
#define ML_EN_GPIO_Port GPIOA
#define LED_LSRF_Pin GPIO_PIN_4
#define LED_LSRF_GPIO_Port GPIOB
#define LED_LFRS_Pin GPIO_PIN_5
#define LED_LFRS_GPIO_Port GPIOB
#define SW_Pin GPIO_PIN_9
#define SW_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
