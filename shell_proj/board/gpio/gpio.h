/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOB
#define LED_R_Pin GPIO_PIN_5


void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
void led_toggle(void);

void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

