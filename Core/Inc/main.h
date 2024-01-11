/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VS_04_Pin GPIO_PIN_0
#define VS_04_GPIO_Port GPIOC
#define VS_01_Pin GPIO_PIN_1
#define VS_01_GPIO_Port GPIOC
#define VS_02_Pin GPIO_PIN_2
#define VS_02_GPIO_Port GPIOC
#define VS_03_Pin GPIO_PIN_3
#define VS_03_GPIO_Port GPIOC
#define PS_04_Pin GPIO_PIN_0
#define PS_04_GPIO_Port GPIOA
#define PS_03_Pin GPIO_PIN_1
#define PS_03_GPIO_Port GPIOA
#define PS_02_Pin GPIO_PIN_2
#define PS_02_GPIO_Port GPIOA
#define PS_01_Pin GPIO_PIN_3
#define PS_01_GPIO_Port GPIOA
#define VS_07_Pin GPIO_PIN_6
#define VS_07_GPIO_Port GPIOA
#define VS_06_Pin GPIO_PIN_7
#define VS_06_GPIO_Port GPIOA
#define VS_08_Pin GPIO_PIN_4
#define VS_08_GPIO_Port GPIOC
#define VS_05_Pin GPIO_PIN_5
#define VS_05_GPIO_Port GPIOC
#define GSense_Pin GPIO_PIN_12
#define GSense_GPIO_Port GPIOB
#define HBeat_Pin GPIO_PIN_13
#define HBeat_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
