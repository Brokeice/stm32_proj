/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
static void LCD_Test(void);
static void Delay(__IO uint32_t nCount);
void Printf_Charater(void);
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_USART1_UART_Init();
    HAL_TIM_Base_Start_IT(&htim2);

    ILI9341_Init();

    ILI9341_GramScan(6);
    while (1)
    {
        uint32_t id = ILI9341_ReadID();
        printf("draw, id = %d\r\n", id);
        LCD_Test();
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

static void LCD_Test(void)
{
    /*锟斤拷示锟斤拷示锟斤拷锟斤拷*/
    static uint8_t testCNT = 0;
    char dispBuff[100];

    testCNT++;

    LCD_SetFont(&Font8x16);
    LCD_SetColors(RED, BLACK);

    ILI9341_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH); /* 锟斤拷锟斤拷锟斤拷锟斤拷示全锟斤拷 */
                                                     /********锟斤拷示锟街凤拷锟斤拷示锟斤拷*******/
    ILI9341_DispStringLine_EN(LINE(0), "BH 3.2 inch LCD para:");
    ILI9341_DispStringLine_EN(LINE(1), "Image resolution:240x320 px");
    ILI9341_DispStringLine_EN(LINE(2), "ILI9341 LCD driver");
    ILI9341_DispStringLine_EN(LINE(3), "XPT2046 Touch Pad driver");

    /********锟斤拷示锟斤拷锟斤拷示锟斤拷*******/
    LCD_SetFont(&Font16x24);
    LCD_SetTextColor(GREEN);

    /*使锟斤拷c锟斤拷准锟斤拷驯锟斤拷锟阶拷锟斤拷锟斤拷址锟斤拷锟�*/
    sprintf(dispBuff, "Count : %d ", testCNT);
    LCD_ClearLine(LINE(4)); /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */

    /*然锟斤拷锟斤拷示锟斤拷锟街凤拷锟斤拷锟斤拷锟缴ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷也锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷*/
    ILI9341_DispStringLine_EN(LINE(4), dispBuff);

    /*******锟斤拷示图锟斤拷示锟斤拷******/
    LCD_SetFont(&Font24x32);
    /* 锟斤拷直锟斤拷 */

    LCD_ClearLine(LINE(4)); /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */
    LCD_SetTextColor(BLUE);

    ILI9341_DispStringLine_EN(LINE(4), "Draw line:");

    LCD_SetTextColor(RED);
    ILI9341_DrawLine(50, 170, 210, 230);
    ILI9341_DrawLine(50, 200, 210, 240);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawLine(100, 170, 200, 230);
    ILI9341_DrawLine(200, 200, 220, 240);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawLine(110, 170, 110, 230);
    ILI9341_DrawLine(130, 200, 220, 240);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8); /* 锟斤拷锟斤拷锟斤拷锟斤拷示全锟斤拷 */

    /*锟斤拷锟斤拷锟斤拷*/

    LCD_ClearLine(LINE(4)); /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */
    LCD_SetTextColor(BLUE);

    ILI9341_DispStringLine_EN(LINE(4), "Draw Rect:");

    LCD_SetTextColor(RED);
    ILI9341_DrawRectangle(50, 200, 100, 30, 1);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawRectangle(160, 200, 20, 40, 0);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawRectangle(170, 200, 50, 20, 1);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8); /* 锟斤拷锟斤拷锟斤拷锟斤拷示全锟斤拷 */

    /* 锟斤拷圆 */
    LCD_ClearLine(LINE(4)); /* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� */
    LCD_SetTextColor(BLUE);

    ILI9341_DispStringLine_EN(LINE(4), "Draw Cir:");

    LCD_SetTextColor(RED);
    ILI9341_DrawCircle(100, 200, 20, 0);

    LCD_SetTextColor(GREEN);
    ILI9341_DrawCircle(100, 200, 10, 1);

    LCD_SetTextColor(BLUE);
    ILI9341_DrawCircle(140, 200, 20, 0);

    Delay(0xFFFFFF);

    ILI9341_Clear(0, 16 * 8, LCD_X_LENGTH, LCD_Y_LENGTH - 16 * 8); /* 锟斤拷锟斤拷锟斤拷锟斤拷示全锟斤拷 */
}

static void Delay(volatile uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}