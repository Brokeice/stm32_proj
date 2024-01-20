/*
*********************************************************************************************************
*
*	???��???? : FMC��???????IO???????��
*	???????? : bsp_fmc_io.c
*	��?    ��? : V1.0
*	??    ?�� : F429??��?��???FMC��???????????32??????IO??FMC???��?? (0x6400 1000)
*
*	???????? :
*		��?��???  ????        ����??     ???��
*		V1.0    2015-10-11  armfly  ????��???
*
*	Copyright (C), 2015-2020, ��???????��? www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp_fmc_io.h"
#include "main.h"

/*
	��?????STM32-V6 ??��?��?????????��???: ��??????�� = 0x6400 0000
	D0  - GPRS_RERM_ON
	D1  - GPRS_RESET
	D2  - NRF24L01_CE
	D3  - NRF905_TX_EN
	D4  - NRF905_TRX_CE/VS1053_XDCS
	D5  - NRF905_PWR_UP
	D6  - ESP8266_G0
	D7  - ESP8266_G2
	
	D8  - LED1
	D9  - LED2
	D10 - LED3
	D11 - LED4
	D12 - TP_NRST
	D13 - AD7606_OS0
	D14 - AD7606_OS1
	D15 - AD7606_OS2
	
	?��????8??5V????IO: Y50_0 - Y50_1
	D16  - Y50_0
	D17  - Y50_1
	D18  - Y50_2
	D19  - Y50_3
	D20  - Y50_4
	D21  - Y50_5
	D22  - Y50_6
	D23  - Y50_7	

	?��????8??3.3V????IO: Y33_0 - Y33_1
	D24  - AD7606_RESET
	D25  - AD7606_RAGE
	D26  - Y33_2
	D27  - Y33_3
	D28  - Y33_4
	D29  - Y33_5
	D30  - Y33_6
	D31  - Y33_7				
*/

#define  HC574_PORT	 *(uint32_t *)0x64001000

__IO uint32_t g_HC574;	/* ��???74HC574????��??? */

static void HC574_ConfigGPIO(void);
static void HC574_ConfigFMC(void);

/*
*********************************************************************************************************
*	?? ?? ??: bsp_InitExtIO
*	???????��: ????????IO?��????GPIO. ??????????????????
*	??    ??: ??
*	��? ?? ??: ??
*********************************************************************************************************
*/
void bsp_InitExtIO(void)
{
	HC574_ConfigGPIO();
	HC574_ConfigFMC();
	
	/* ????��?��???????????LED???��?????? */
	g_HC574 = (NRF24L01_CE | VS1053_XDCS | LED1 | LED2 | LED3 | LED4);
	HC574_PORT = g_HC574;	/* ?????????????��??IO��??? */
}

/*
*********************************************************************************************************
*	?? ?? ??: HC574_SetPin
*	???????��: ?��??74HC574??????
*	??    ??: _pin : ???????? 0-31; ??????1?????????��??
*			  _value : ?��?��??????0?��1
*	��? ?? ??: ??
*********************************************************************************************************
*/
void HC574_SetPin(uint32_t _pin, uint8_t _value)
{
	if (_value == 0)
	{
		g_HC574 &= (~_pin);
	}
	else
	{
		g_HC574 |= _pin;
	}
	HC574_PORT = g_HC574;
}

/*
*********************************************************************************************************
*	?? ?? ??: HC574_TogglePin
*	???????��: ��?��?74HC574??????
*	??    ??: _pin : ???????? 0-31; ??????1?????????��??
*	��? ?? ??: ??
*********************************************************************************************************
*/
void HC574_TogglePin(uint32_t _pin)
{
	if (g_HC574 & _pin)
	{
		g_HC574 &= (~_pin);
	}
	else
	{
		g_HC574 |= _pin;
	}
	HC574_PORT = g_HC574;
}

/*
*********************************************************************************************************
*	?? ?? ??: HC574_GetPin
*	???????��: ???????��????????????1????0
*	??    ??: _pin : ???????? 0-31; ??????1?????????��??
*	��? ?? ??: 0?��1
*********************************************************************************************************
*/
uint8_t HC574_GetPin(uint32_t _pin)
{
	if (g_HC574 & _pin)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
*********************************************************************************************************
*	?? ?? ??: HC574_ConfigGPIO
*	???????��: ????GPIO??FMC?????��????????????
*	??    ??:  ??
*	��? ?? ??: ??
*********************************************************************************************************
*/
static void HC574_ConfigGPIO(void)
{
/*
	��?????STM32-V6??��?��?????��?����??4??74HC574????FMC 32??��???????1?????��??????????????32??IO
	PD0/FMC_D2
	PD1/FMC_D3
	PD4/FMC_NOE		---- ????????????OE = Output Enable ?? N ����???????��
	PD5/FMC_NWE		-XX- ????????????AD7606 ????????????????
	PD8/FMC_D13
	PD9/FMC_D14
	PD10/FMC_D15
	PD14/FMC_D0
	PD15/FMC_D1

	PE7/FMC_D4
	PE8/FMC_D5
	PE9/FMC_D6
	PE10/FMC_D7
	PE11/FMC_D8
	PE12/FMC_D9
	PE13/FMC_D10
	PE14/FMC_D11
	PE15/FMC_D12
	
	PG0/FMC_A10		--- ???��????FMC_NE2????????
	PG1/FMC_A11		--- ???��????FMC_NE2????????
	PG9/FMC_NE2		--- ?��?????��OLED, 74HC574, DM9000, AD7606??	
	
	 +-------------------+------------------+
	 +   32-bits Mode: D31-D16              +
	 +-------------------+------------------+
	 | PH8 <-> FMC_D16   | PI0 <-> FMC_D24  |
	 | PH9 <-> FMC_D17   | PI1 <-> FMC_D25  |
	 | PH10 <-> FMC_D18  | PI2 <-> FMC_D26  |
	 | PH11 <-> FMC_D19  | PI3 <-> FMC_D27  |
	 | PH12 <-> FMC_D20  | PI6 <-> FMC_D28  |
	 | PH13 <-> FMC_D21  | PI7 <-> FMC_D29  |
	 | PH14 <-> FMC_D22  | PI9 <-> FMC_D30  |
	 | PH15 <-> FMC_D23  | PI10 <-> FMC_D31 |
	 +------------------+-------------------+	
*/	

	GPIO_InitTypeDef gpio_init_structure;

	/* ???? GPIO?��?? */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();


	/* ????FMC?��?? */
	__HAL_RCC_FMC_CLK_ENABLE();

	/* ?��?? GPIOD ?��????IO?????????��???? */
	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	gpio_init_structure.Alternate = GPIO_AF12_FMC;
	
	/* ????GPIOD */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
	                            GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOD, &gpio_init_structure);

	/* ????GPIOE */
	gpio_init_structure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
	                            GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 |
	                            GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE, &gpio_init_structure);

	/* ????GPIOG */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_9;
	HAL_GPIO_Init(GPIOG, &gpio_init_structure);
	
	/* ????GPIOH */
	gpio_init_structure.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12
						| GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	HAL_GPIO_Init(GPIOH, &gpio_init_structure);

	/* ????GPIOI */
	gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_6
						| GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOI, &gpio_init_structure);
}

/*
*********************************************************************************************************
*	?? ?? ??: HC574_ConfigFMC
*	???????��: ????FMC????��????��?��
*	??    ??:  ??
*	��? ?? ??: ??
*********************************************************************************************************
*/
static void HC574_ConfigFMC(void)
{
	SRAM_HandleTypeDef hsram = {0};
	FMC_NORSRAM_TimingTypeDef SRAM_Timing = {0};
		
	hsram.Instance  = FMC_NORSRAM_DEVICE;
	hsram.Extended  = FMC_NORSRAM_EXTENDED_DEVICE;

    /* FMC??????HCLK???��??168MHz??1??FMC?��??????????5.95ns */
	SRAM_Timing.AddressSetupTime       = 3;  /* 3*5.95ns=17.85ns?????��?��???��????��??��0 -15??FMC?��?????????? */
	SRAM_Timing.AddressHoldTime        = 0;  /* ???����????��??????????????A?��?????????????? ��??��1 -15???��?????????? */
	SRAM_Timing.DataSetupTime          = 6;  /* 6*5.95ns=35.7ns??????��????��????��??��1 -255???��?????????? */
	SRAM_Timing.BusTurnAroundDuration  = 3;  /* 6*5.95ns???????????????????��?????? */
	SRAM_Timing.CLKDivision            = 0;  /* ???????????????????? */
	SRAM_Timing.DataLatency            = 0;  /* ???????????????????? */
	SRAM_Timing.AccessMode             = FMC_ACCESS_MODE_A; /* ??????????A */

	hsram.Init.NSBank             = FMC_NORSRAM_BANK2;              /* ??????BANK2??????????????FMC_NE2 */
	hsram.Init.DataAddressMux     = FMC_DATA_ADDRESS_MUX_DISABLE;   /* ???????��???????? */
	hsram.Init.MemoryType         = FMC_MEMORY_TYPE_SRAM;           /* ?????��?��??SRAM */
	hsram.Init.MemoryDataWidth    = FMC_NORSRAM_MEM_BUS_WIDTH_32;	/* 32??��????��?? */
	hsram.Init.BurstAccessMode    = FMC_BURST_ACCESS_MODE_DISABLE;  /* ??��???��????? */
	hsram.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;   /* ?????��????????????????????��???��????????????????�� */
	hsram.Init.WaitSignalActive   = FMC_WAIT_TIMING_BEFORE_WS;      /* ??��???��????????????????�� */
	hsram.Init.WriteOperation     = FMC_WRITE_OPERATION_ENABLE;     /* ?????????��????????��??�� */
	hsram.Init.WaitSignal         = FMC_WAIT_SIGNAL_DISABLE;        /* ??��???��????????????????�� */
	hsram.Init.ExtendedMode       = FMC_EXTENDED_MODE_DISABLE;      /* ???????????? */
	hsram.Init.AsynchronousWait   = FMC_ASYNCHRONOUS_WAIT_DISABLE;  /* ?????��?????????????????��??????????????????????????��? */
	hsram.Init.WriteBurst         = FMC_WRITE_BURST_DISABLE;        /* ????????��? */
	hsram.Init.ContinuousClock    = FMC_CONTINUOUS_CLOCK_SYNC_ONLY; /* ????????????��??��?????? */
     hsram.Init.WriteFifo          = 0;          /* ??????FIFO */

	/* ??????SRAM?????�� */
	if (HAL_SRAM_Init(&hsram, &SRAM_Timing, &SRAM_Timing) != HAL_OK)
	{
		/* ???????��?�� */
		Error_Handler();
	}
}

/*
*********************************************************************************************************
*	?? ?? ??: bsp_TestExtIO
*	???????��: ????74HC475????IO. 32??????IO????��?��???????200+200ms
*	??    ??: ??
*	��? ?? ??: ??
*********************************************************************************************************
*/
void bsp_TestExtIO(void)
{
	while(1)
	{		
		HC574_SetPin(GPIO_PIN_0, 0);
		HC574_SetPin(GPIO_PIN_1, 0);
		HC574_SetPin(GPIO_PIN_2, 0);
		HC574_SetPin(GPIO_PIN_3, 0);
		HC574_SetPin(GPIO_PIN_4, 0);
		HC574_SetPin(GPIO_PIN_5, 0);
		HC574_SetPin(GPIO_PIN_6, 0);
		HC574_SetPin(GPIO_PIN_7, 0);
		HC574_SetPin(GPIO_PIN_8, 0);
		HC574_SetPin(GPIO_PIN_9, 0);
		HC574_SetPin(GPIO_PIN_10, 0);
		HC574_SetPin(GPIO_PIN_11, 0);
		HC574_SetPin(GPIO_PIN_12, 0);
		HC574_SetPin(GPIO_PIN_13, 0);
		HC574_SetPin(GPIO_PIN_14, 0);
		HC574_SetPin(GPIO_PIN_15, 0);
		
		HC574_SetPin(GPIO_PIN_16, 0);
		HC574_SetPin(GPIO_PIN_17, 1);
		HC574_SetPin(GPIO_PIN_18, 0);
		HC574_SetPin(GPIO_PIN_19, 1);
		HC574_SetPin(GPIO_PIN_20, 0);
		HC574_SetPin(GPIO_PIN_21, 1);
		HC574_SetPin(GPIO_PIN_22, 0);
		HC574_SetPin(GPIO_PIN_23, 1);
		HC574_SetPin(GPIO_PIN_24, 0);
		HC574_SetPin(GPIO_PIN_25, 1);
		HC574_SetPin(GPIO_PIN_26, 0);
		HC574_SetPin(GPIO_PIN_27, 1);		
		HC574_SetPin(GPIO_PIN_28, 0);
		HC574_SetPin(GPIO_PIN_29, 1);
		HC574_SetPin(GPIO_PIN_30, 0);	
		HC574_SetPin(GPIO_PIN_31, 1);			
		
		HAL_Delay(200);

		HC574_SetPin(GPIO_PIN_0, 1);
		HC574_SetPin(GPIO_PIN_1, 1);
		HC574_SetPin(GPIO_PIN_2, 1);
		HC574_SetPin(GPIO_PIN_3, 1);
		HC574_SetPin(GPIO_PIN_4, 1);
		HC574_SetPin(GPIO_PIN_5, 1);
		HC574_SetPin(GPIO_PIN_6, 1);
		HC574_SetPin(GPIO_PIN_7, 1);
		HC574_SetPin(GPIO_PIN_8, 1);
		HC574_SetPin(GPIO_PIN_9, 1);
		HC574_SetPin(GPIO_PIN_10, 1);
		HC574_SetPin(GPIO_PIN_11, 1);
		HC574_SetPin(GPIO_PIN_12, 1);
		HC574_SetPin(GPIO_PIN_13, 1);
		HC574_SetPin(GPIO_PIN_14, 1);
		HC574_SetPin(GPIO_PIN_15, 1);
		
		HC574_SetPin(GPIO_PIN_16, 1);
		HC574_SetPin(GPIO_PIN_17, 0);
		HC574_SetPin(GPIO_PIN_18, 1);
		HC574_SetPin(GPIO_PIN_19, 0);
		HC574_SetPin(GPIO_PIN_20, 1);
		HC574_SetPin(GPIO_PIN_21, 0);
		HC574_SetPin(GPIO_PIN_22, 1);
		HC574_SetPin(GPIO_PIN_23, 0);
		HC574_SetPin(GPIO_PIN_24, 1);
		HC574_SetPin(GPIO_PIN_25, 0);
		HC574_SetPin(GPIO_PIN_26, 1);
		HC574_SetPin(GPIO_PIN_27, 0);		
		HC574_SetPin(GPIO_PIN_28, 1);
		HC574_SetPin(GPIO_PIN_29, 0);
		HC574_SetPin(GPIO_PIN_30, 1);	
		HC574_SetPin(GPIO_PIN_31, 0);	
		
		HAL_Delay(200);			
	}
}

/***************************** ��???????��? www.armfly.com (END OF FILE) *********************************/
