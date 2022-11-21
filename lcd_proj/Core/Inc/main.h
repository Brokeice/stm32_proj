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
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"
#include "gpio.h"
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
#define XPT2046_SPI_MOSI_Pin GPIO_PIN_2
#define XPT2046_SPI_MOSI_GPIO_Port GPIOE
#define XPT2046_SPI_MISO_Pin GPIO_PIN_3
#define XPT2046_SPI_MISO_GPIO_Port GPIOE
#define XPT2046_PENIRQ_GPIO_Pin GPIO_PIN_4
#define XPT2046_PENIRQ_GPIO_GPIO_Port GPIOE
#define LED_G_Pin GPIO_PIN_0
#define LED_G_GPIO_Port GPIOB
#define LED_B_Pin GPIO_PIN_1
#define LED_B_GPIO_Port GPIOB
#define ILI9341_BK_CLK_Pin GPIO_PIN_12
#define ILI9341_BK_CLK_GPIO_Port GPIOD
#define XPT2046_SPI_CS_Pin GPIO_PIN_13
#define XPT2046_SPI_CS_GPIO_Port GPIOD
#define LED_R_Pin GPIO_PIN_5
#define LED_R_GPIO_Port GPIOB
#define XPT2046_SPI_CLK_Pin GPIO_PIN_0
#define XPT2046_SPI_CLK_GPIO_Port GPIOE
#define ILI9341_RST_PIN_Pin GPIO_PIN_1
#define ILI9341_RST_PIN_GPIO_Port GPIOE
    /* USER CODE BEGIN Private defines */

    /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
