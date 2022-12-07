/*
*********************************************************************************************************
*
*	模锟斤拷锟斤拷锟斤拷 : 锟斤拷锟斤拷锟叫讹拷+FIFO锟斤拷锟斤拷模锟斤拷
*	锟侥硷拷锟斤拷锟斤拷 : bsp_uart_fifo.c
*	锟斤拷    锟斤拷 : V1.8
*	说    锟斤拷 : 锟斤拷锟矫达拷锟斤拷锟叫讹拷+FIFO模式实锟街讹拷锟斤拷锟斤拷诘锟酵憋拷锟斤拷锟�
*	锟睫改硷拷录 :
*		锟芥本锟斤拷  锟斤拷锟斤拷       锟斤拷锟斤拷    说锟斤拷
*		V1.0    2013-02-01 armfly  锟斤拷式锟斤拷锟斤拷
*		V1.1    2013-06-09 armfly  FiFo锟结构锟斤拷锟斤拷TxCount锟斤拷员锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫断伙拷锟斤拷锟斤拷锟斤拷; 锟斤拷锟斤拷 锟斤拷FiFo锟侥猴拷锟斤拷
*		V1.2	2014-09-29 armfly  锟斤拷锟斤拷RS485 MODBUS锟接口★拷锟斤拷锟秸碉拷锟斤拷锟街节猴拷直锟斤拷执锟叫回碉拷锟斤拷锟斤拷锟斤拷
*		V1.3	2015-07-23 armfly  锟斤拷锟斤拷 UART_T 锟结构锟侥讹拷写指锟诫几锟斤拷锟斤拷员锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 __IO 锟斤拷锟斤拷,锟斤拷锟斤拷锟脚伙拷锟斤拷
*					锟结导锟铰达拷锟节凤拷锟酵猴拷锟斤拷锟斤拷锟斤拷锟斤拷
*		V1.4	2015-08-04 armfly  锟斤拷锟経ART4锟斤拷锟斤拷bug  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART1);
*		V1.5	2015-10-08 armfly  锟斤拷锟斤拷锟睫改诧拷锟斤拷锟绞的接口猴拷锟斤拷
*		V1.6	2018-09-07 armfly  锟斤拷植锟斤拷STM32H7平台
*		V1.7	2018-10-01 armfly  锟斤拷锟斤拷 Sending 锟斤拷志锟斤拷锟斤拷示锟斤拷锟节凤拷锟斤拷锟斤拷
*		V1.8	2018-11-26 armfly  锟斤拷锟斤拷UART8锟斤拷锟斤拷8锟斤拷锟斤拷锟斤拷
*
*	Copyright (C), 2015-2030, 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"

/* 锟斤拷锟斤拷1锟斤拷GPIO  PA9, PA10   RS323 DB9锟接匡拷 */
#define USART1_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE()

#define USART1_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART1_TX_GPIO_PORT              GPIOA
#define USART1_TX_PIN                    GPIO_PIN_9
#define USART1_TX_AF                     GPIO_AF7_USART1

#define USART1_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART1_RX_GPIO_PORT              GPIOA
#define USART1_RX_PIN                    GPIO_PIN_10
#define USART1_RX_AF                     GPIO_AF7_USART1

/* 锟斤拷锟斤拷2锟斤拷GPIO --- PA2 PA3  GPS (只锟斤拷RX锟斤拷 TX锟斤拷锟斤拷太锟斤拷占锟矫ｏ拷 */
#define USART2_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE()

#define USART2_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART2_TX_GPIO_PORT              GPIOA
#define USART2_TX_PIN                    GPIO_PIN_2
#define USART2_TX_AF                     GPIO_AF7_USART2

#define USART2_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART2_RX_GPIO_PORT              GPIOA
#define USART2_RX_PIN                    GPIO_PIN_3
#define USART2_RX_AF                     GPIO_AF7_USART2

/* 锟斤拷锟斤拷3锟斤拷GPIO --- PB10 PB11  RS485 */
#define USART3_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE()

#define USART3_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USART3_TX_GPIO_PORT              GPIOB
#define USART3_TX_PIN                    GPIO_PIN_10
#define USART3_TX_AF                     GPIO_AF7_USART3

#define USART3_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define USART3_RX_GPIO_PORT              GPIOB
#define USART3_RX_PIN                    GPIO_PIN_11
#define USART3_RX_AF                     GPIO_AF7_USART3

/* 锟斤拷锟斤拷4锟斤拷GPIO --- PC10 PC11  锟斤拷SD锟斤拷占锟斤拷 */
#define UART4_CLK_ENABLE()              __HAL_RCC_UART4_CLK_ENABLE()

#define UART4_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define UART4_TX_GPIO_PORT              GPIOC
#define UART4_TX_PIN                    GPIO_PIN_10
#define UART4_TX_AF                     GPIO_AF8_UART4

#define UART4_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define UART4_RX_GPIO_PORT              GPIOC
#define UART4_RX_PIN                    GPIO_PIN_11
#define UART4_RX_AF                     GPIO_AF8_UART4

/* 锟斤拷锟斤拷5锟斤拷GPIO --- PC12/UART5_TX PD2/UART5_RX (锟斤拷SD锟斤拷占锟矫ｏ拷 */
#define UART5_CLK_ENABLE()              __HAL_RCC_UART5_CLK_ENABLE()

#define UART5_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define UART5_TX_GPIO_PORT              GPIOC
#define UART5_TX_PIN                    GPIO_PIN_12
#define UART5_TX_AF                     GPIO_AF8_UART5

#define UART5_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define UART5_RX_GPIO_PORT              GPIOD
#define UART5_RX_PIN                    GPIO_PIN_2
#define UART5_RX_AF                     GPIO_AF8_UART5

/* 锟斤拷锟斤拷6锟斤拷GPIO --- PG14 PC7  GPRS */
#define USART6_CLK_ENABLE()              __HAL_RCC_USART6_CLK_ENABLE()

#define USART6_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOG_CLK_ENABLE()
#define USART6_TX_GPIO_PORT              GPIOG
#define USART6_TX_PIN                    GPIO_PIN_14
#define USART6_TX_AF                     GPIO_AF7_USART6

#define USART6_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOC_CLK_ENABLE()
#define USART6_RX_GPIO_PORT              GPIOC
#define USART6_RX_PIN                    GPIO_PIN_7
#define USART6_RX_AF                     GPIO_AF7_USART6

/* 锟斤拷锟斤拷7锟斤拷GPIO --- PB4/UART7_TX, PB3/UART7_RX   (锟斤拷SPI3 占锟斤拷) */
#define UART7_CLK_ENABLE()              __HAL_RCC_UART7_CLK_ENABLE()

#define UART7_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define UART7_TX_GPIO_PORT              GPIOB
#define UART7_TX_PIN                    GPIO_PIN_4
#define UART7_TX_AF                     GPIO_AF11_UART7

#define UART7_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define UART7_RX_GPIO_PORT              GPIOB
#define UART7_RX_PIN                    GPIO_PIN_3
#define UART7_RX_AF                     GPIO_AF11_UART7

/* 锟斤拷锟斤拷8锟斤拷GPIO --- PJ8/UART8_TX, PJ9/UART8_RX   (RGB硬锟斤拷锟接匡拷占锟斤拷) */
#define UART8_CLK_ENABLE()              __HAL_RCC_UART8_CLK_ENABLE()

#define UART8_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOJ_CLK_ENABLE()
#define UART8_TX_GPIO_PORT              GPIOJ
#define UART8_TX_PIN                    GPIO_PIN_8
#define UART8_TX_AF                     GPIO_AF8_UART8

#define UART8_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOJ_CLK_ENABLE()
#define UART8_RX_GPIO_PORT              GPIOJ
#define UART8_RX_PIN                    GPIO_PIN_9
#define UART8_RX_AF                     GPIO_AF8_UART8

/* 锟斤拷锟斤拷每锟斤拷锟斤拷锟节结构锟斤拷锟斤拷锟� */
#if UART1_FIFO_EN == 1
	static UART_T g_tUart1;
	static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART2_FIFO_EN == 1
	static UART_T g_tUart2;
	static uint8_t g_TxBuf2[UART2_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf2[UART2_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART3_FIFO_EN == 1
	static UART_T g_tUart3;
	static uint8_t g_TxBuf3[UART3_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf3[UART3_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART4_FIFO_EN == 1
	static UART_T g_tUart4;
	static uint8_t g_TxBuf4[UART4_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf4[UART4_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART5_FIFO_EN == 1
	static UART_T g_tUart5;
	static uint8_t g_TxBuf5[UART5_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf5[UART5_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART6_FIFO_EN == 1
	static UART_T g_tUart6;
	static uint8_t g_TxBuf6[UART6_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf6[UART6_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART7_FIFO_EN == 1
	static UART_T g_tUart7;
	static uint8_t g_TxBuf7[UART7_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf7[UART7_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif

#if UART8_FIFO_EN == 1
	static UART_T g_tUart8;
	static uint8_t g_TxBuf8[UART8_TX_BUF_SIZE];		/* 锟斤拷锟酵伙拷锟斤拷锟斤拷 */
	static uint8_t g_RxBuf8[UART8_RX_BUF_SIZE];		/* 锟斤拷锟秸伙拷锟斤拷锟斤拷 */
#endif
		
static void UartVarInit(void);

static void InitHardUart(void);
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen);
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte);
static void UartIRQ(UART_T *_pUart);

void RS485_InitTXE(void);

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: bsp_InitUart
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷始锟斤拷锟斤拷锟斤拷硬锟斤拷锟斤拷锟斤拷锟斤拷全锟街憋拷锟斤拷锟斤拷锟斤拷值.
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void bsp_InitUart(void)
{
	
	UartVarInit();		/* 锟斤拷锟斤拷锟饺筹拷始锟斤拷全锟街憋拷锟斤拷,锟斤拷锟斤拷锟斤拷硬锟斤拷 */

	InitHardUart();		/* 锟斤拷锟矫达拷锟节碉拷硬锟斤拷锟斤拷锟斤拷(锟斤拷锟斤拷锟绞碉拷) */

	RS485_InitTXE();	/* 锟斤拷锟斤拷RS485芯片锟侥凤拷锟斤拷使锟斤拷硬锟斤拷锟斤拷锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟� */
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: ComToUart
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷COM锟剿口猴拷转锟斤拷为UART指锟斤拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*	锟斤拷 锟斤拷 值: uart指锟斤拷
*********************************************************************************************************
*/
UART_T *ComToUart(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return &g_tUart1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return &g_tUart2;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return &g_tUart3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return &g_tUart4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return &g_tUart5;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM6)
	{
		#if UART6_FIFO_EN == 1
			return &g_tUart6;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM7)
	{
		#if UART7_FIFO_EN == 1
			return &g_tUart7;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM8)
	{
		#if UART8_FIFO_EN == 1
			return &g_tUart8;
		#else
			return 0;
		#endif
	}	
	else
	{
		Error_Handler(__FILE__, __LINE__);
		return 0;
	}
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: ComToUart
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷COM锟剿口猴拷转锟斤拷为 USART_TypeDef* USARTx
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*	锟斤拷 锟斤拷 值: USART_TypeDef*,  USART1, USART2, USART3, UART4, UART5锟斤拷USART6锟斤拷UART7锟斤拷UART8锟斤拷
*********************************************************************************************************
*/
USART_TypeDef *ComToUSARTx(COM_PORT_E _ucPort)
{
	if (_ucPort == COM1)
	{
		#if UART1_FIFO_EN == 1
			return USART1;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM2)
	{
		#if UART2_FIFO_EN == 1
			return USART2;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM3)
	{
		#if UART3_FIFO_EN == 1
			return USART3;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM4)
	{
		#if UART4_FIFO_EN == 1
			return UART4;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM5)
	{
		#if UART5_FIFO_EN == 1
			return UART5;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM6)
	{
		#if UART6_FIFO_EN == 1
			return USART6;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM7)
	{
		#if UART7_FIFO_EN == 1
			return UART7;
		#else
			return 0;
		#endif
	}
	else if (_ucPort == COM8)
	{
		#if UART8_FIFO_EN == 1
			return UART8;
		#else
			return 0;
		#endif
	}	
	
	else
	{
		/* 锟斤拷锟斤拷锟轿何达拷锟斤拷 */
		return 0;
	}
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comSendBuf
*	锟斤拷锟斤拷说锟斤拷: 锟津串口凤拷锟斤拷一锟斤拷锟斤拷锟捷★拷锟斤拷锟捷放碉拷锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷诤锟教拷锟缴凤拷锟斤拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*			  _ucaBuf: 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷伙拷锟斤拷锟斤拷
*			  _usLen : 锟斤拷锟捷筹拷锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	if (pUart->SendBefor != 0)
	{
		pUart->SendBefor();		/* 锟斤拷锟斤拷锟絉S485通锟脚ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷薪锟絉S485锟斤拷锟斤拷为锟斤拷锟斤拷模式 */
	}

	UartSend(pUart, _ucaBuf, _usLen);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comSendChar
*	锟斤拷锟斤拷说锟斤拷: 锟津串口凤拷锟斤拷1锟斤拷锟街节★拷锟斤拷锟捷放碉拷锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟截ｏ拷锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷诤锟教拷锟缴凤拷锟斤拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*			  _ucByte: 锟斤拷锟斤拷锟酵碉拷锟斤拷锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte)
{
	comSendBuf(_ucPort, &_ucByte, 1);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comGetChar
*	锟斤拷锟斤拷说锟斤拷: 锟接斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷取1锟街节ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟捷撅拷锟斤拷锟斤拷锟斤拷锟截★拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*			  _pByte: 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷达拷锟斤拷锟斤拷锟斤拷锟斤拷址
*	锟斤拷 锟斤拷 值: 0 锟斤拷示锟斤拷锟斤拷锟斤拷, 1 锟斤拷示锟斤拷取锟斤拷锟斤拷效锟街斤拷
*********************************************************************************************************
*/
uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return 0;
	}

	return UartGetChar(pUart, _pByte);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comClearTxFifo
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟姐串锟节凤拷锟酵伙拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void comClearTxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usTxWrite = 0;
	pUart->usTxRead = 0;
	pUart->usTxCount = 0;
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comClearRxFifo
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟姐串锟节斤拷锟秸伙拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void comClearRxFifo(COM_PORT_E _ucPort)
{
	UART_T *pUart;

	pUart = ComToUart(_ucPort);
	if (pUart == 0)
	{
		return;
	}

	pUart->usRxWrite = 0;
	pUart->usRxRead = 0;
	pUart->usRxCount = 0;
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: comSetBaud
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟矫达拷锟节的诧拷锟斤拷锟斤拷. 锟斤拷锟斤拷锟斤拷锟教讹拷锟斤拷锟斤拷为锟斤拷校锟介，锟秸凤拷锟斤拷使锟斤拷模式
*	锟斤拷    锟斤拷: _ucPort: 锟剿口猴拷(COM1 - COM8)
*			  _BaudRate: 锟斤拷锟斤拷锟绞ｏ拷8锟斤拷锟斤拷锟斤拷锟斤拷  锟斤拷锟斤拷锟斤拷.0-12.5Mbps
*                                16锟斤拷锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷锟斤拷.0-6.25Mbps
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void comSetBaud(COM_PORT_E _ucPort, uint32_t _BaudRate)
{
	USART_TypeDef* USARTx;
	
	USARTx = ComToUSARTx(_ucPort);
	if (USARTx == 0)
	{
		return;
	}
	
	bsp_SetUartParam(USARTx,  _BaudRate, UART_PARITY_NONE, UART_MODE_TX_RX);
}

/* 锟斤拷锟斤拷锟絉S485通锟脚ｏ拷锟诫按锟斤拷锟铰革拷式锟斤拷写锟斤拷锟斤拷锟斤拷 锟斤拷锟角斤拷锟斤拷锟斤拷 USART3锟斤拷为RS485锟斤拷锟斤拷锟斤拷 */

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_InitTXE
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟斤拷RS485锟斤拷锟斤拷使锟杰匡拷锟斤拷 TXE
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_InitTXE(void)
{
	GPIO_InitTypeDef gpio_init;
	
	/* 锟斤拷GPIO时锟斤拷 */
	RS485_TXEN_GPIO_CLK_ENABLE();
	
	/* 锟斤拷锟斤拷锟斤拷锟斤拷为锟斤拷锟斤拷锟斤拷锟� */
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP;			/* 锟斤拷锟斤拷锟斤拷锟� */
	gpio_init.Pull = GPIO_NOPULL;					/* 锟斤拷锟斤拷锟斤拷锟斤拷锟借不使锟斤拷 */
	gpio_init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;	/* GPIO锟劫度等硷拷 */
	gpio_init.Pin = RS485_TXEN_PIN;
	HAL_GPIO_Init(RS485_TXEN_GPIO_PORT, &gpio_init);	
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_SetBaud
*	锟斤拷锟斤拷说锟斤拷: 锟睫革拷485锟斤拷锟节的诧拷锟斤拷锟绞★拷
*	锟斤拷    锟斤拷: _baud : 8锟斤拷锟斤拷锟斤拷锟斤拷  锟斤拷锟斤拷锟斤拷.0-12.5Mbps
*                     16锟斤拷锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷锟斤拷.0-6.25Mbps
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_SetBaud(uint32_t _baud)
{
	comSetBaud(COM3, _baud);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_SendBefor
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟斤拷锟斤拷锟斤拷前锟斤拷准锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷RS485通锟脚ｏ拷锟斤拷锟斤拷锟斤拷RS485芯片为锟斤拷锟斤拷状态锟斤拷
*			  锟斤拷锟睫革拷 UartVarInit()锟叫的猴拷锟斤拷指锟斤拷锟斤拷诒锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� g_tUart2.SendBefor = RS485_SendBefor
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_SendBefor(void)
{
	RS485_TX_EN();	/* 锟叫伙拷RS485锟秸凤拷芯片为锟斤拷锟斤拷模式 */
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_SendOver
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟斤拷一锟斤拷锟斤拷锟捷斤拷锟斤拷锟斤拷锟斤拷坪锟斤拷锟斤拷锟斤拷锟斤拷锟絉S485通锟脚ｏ拷锟斤拷锟斤拷锟斤拷RS485芯片为锟斤拷锟斤拷状态锟斤拷
*			  锟斤拷锟睫革拷 UartVarInit()锟叫的猴拷锟斤拷指锟斤拷锟斤拷诒锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟� g_tUart2.SendOver = RS485_SendOver
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_SendOver(void)
{
	RS485_RX_EN();	/* 锟叫伙拷RS485锟秸凤拷芯片为锟斤拷锟斤拷模式 */
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_SendBuf
*	锟斤拷锟斤拷说锟斤拷: 通锟斤拷RS485芯片锟斤拷锟斤拷一锟斤拷锟斤拷锟捷★拷注锟解，锟斤拷锟斤拷锟斤拷锟斤拷锟饺达拷锟斤拷锟斤拷锟斤拷稀锟�
*	锟斤拷    锟斤拷: _ucaBuf : 锟斤拷锟捷伙拷锟斤拷锟斤拷
*			  _usLen : 锟斤拷锟捷筹拷锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_SendBuf(uint8_t *_ucaBuf, uint16_t _usLen)
{
	comSendBuf(COM3, _ucaBuf, _usLen);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_SendStr
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷485锟斤拷锟竭凤拷锟斤拷一锟斤拷锟街凤拷锟斤拷锟斤拷0锟斤拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: _pBuf 锟街凤拷锟斤拷锟斤拷0锟斤拷锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void RS485_SendStr(char *_pBuf)
{
	RS485_SendBuf((uint8_t *)_pBuf, strlen(_pBuf));
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: RS485_ReciveNew
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟秸碉拷锟铰碉拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: _byte 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
//extern void MODH_ReciveNew(uint8_t _byte);
void RS485_ReciveNew(uint8_t _byte)
{
//	MODH_ReciveNew(_byte);
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: UartVarInit
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷始锟斤拷锟斤拷锟斤拷锟斤拷氐谋锟斤拷锟�
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
static void UartVarInit(void)
{
#if UART1_FIFO_EN == 1
	g_tUart1.uart = USART1;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart1.pTxBuf = g_TxBuf1;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart1.pRxBuf = g_RxBuf1;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart1.usTxBufSize = UART1_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart1.usRxBufSize = UART1_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart1.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart1.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart1.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart1.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart1.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart1.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart1.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart1.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart1.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart1.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART2_FIFO_EN == 1
	g_tUart2.uart = USART2;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart2.pTxBuf = g_TxBuf2;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart2.pRxBuf = g_RxBuf2;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart2.usTxBufSize = UART2_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart2.usRxBufSize = UART2_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart2.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart2.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart2.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart2.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart2.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart2.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart2.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart2.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart2.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart2.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART3_FIFO_EN == 1
	g_tUart3.uart = USART3;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart3.pTxBuf = g_TxBuf3;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart3.pRxBuf = g_RxBuf3;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart3.usTxBufSize = UART3_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart3.usRxBufSize = UART3_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart3.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart3.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart3.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart3.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart3.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart3.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart3.SendBefor = RS485_SendBefor;		/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart3.SendOver = RS485_SendOver;			/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart3.ReciveNew = RS485_ReciveNew;		/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart3.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART4_FIFO_EN == 1
	g_tUart4.uart = UART4;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart4.pTxBuf = g_TxBuf4;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart4.pRxBuf = g_RxBuf4;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart4.usTxBufSize = UART4_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart4.usRxBufSize = UART4_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart4.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart4.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart4.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart4.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart4.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart4.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart4.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart4.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart4.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart4.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART5_FIFO_EN == 1
	g_tUart5.uart = UART5;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart5.pTxBuf = g_TxBuf5;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart5.pRxBuf = g_RxBuf5;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart5.usTxBufSize = UART5_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart5.usRxBufSize = UART5_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart5.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart5.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart5.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart5.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart5.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart5.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart5.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart5.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart5.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart5.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif


#if UART6_FIFO_EN == 1
	g_tUart6.uart = USART6;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart6.pTxBuf = g_TxBuf6;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart6.pRxBuf = g_RxBuf6;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart6.usTxBufSize = UART6_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart6.usRxBufSize = UART6_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart6.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart6.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart6.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart6.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart6.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart6.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart6.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart6.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart6.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart6.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART7_FIFO_EN == 1
	g_tUart7.uart = UART7;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart7.pTxBuf = g_TxBuf7;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart7.pRxBuf = g_RxBuf7;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart7.usTxBufSize = UART7_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart7.usRxBufSize = UART7_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart7.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart7.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart7.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart7.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart7.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart7.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart7.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart7.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart7.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart7.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif

#if UART8_FIFO_EN == 1
	g_tUart8.uart = UART8;						/* STM32 锟斤拷锟斤拷锟借备 */
	g_tUart8.pTxBuf = g_TxBuf8;					/* 锟斤拷锟酵伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart8.pRxBuf = g_RxBuf8;					/* 锟斤拷锟秸伙拷锟斤拷锟斤拷指锟斤拷 */
	g_tUart8.usTxBufSize = UART8_TX_BUF_SIZE;	/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart8.usRxBufSize = UART8_RX_BUF_SIZE;	/* 锟斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷小 */
	g_tUart8.usTxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart8.usTxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart8.usRxWrite = 0;						/* 锟斤拷锟斤拷FIFO写锟斤拷锟斤拷 */
	g_tUart8.usRxRead = 0;						/* 锟斤拷锟斤拷FIFO锟斤拷锟斤拷锟斤拷 */
	g_tUart8.usRxCount = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart8.usTxCount = 0;						/* 锟斤拷锟斤拷锟酵碉拷锟斤拷锟捷革拷锟斤拷 */
	g_tUart8.SendBefor = 0;						/* 锟斤拷锟斤拷锟斤拷锟斤拷前锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart8.SendOver = 0;						/* 锟斤拷锟斤拷锟斤拷虾锟侥回碉拷锟斤拷锟斤拷 */
	g_tUart8.ReciveNew = 0;						/* 锟斤拷锟秸碉拷锟斤拷锟斤拷锟捷猴拷幕氐锟斤拷锟斤拷锟� */
	g_tUart8.Sending = 0;						/* 锟斤拷锟节凤拷锟斤拷锟叫憋拷志 */
#endif
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: bsp_SetUartParam
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟矫达拷锟节碉拷硬锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞ｏ拷锟斤拷锟斤拷位锟斤拷停止位锟斤拷锟斤拷始位锟斤拷校锟斤拷位锟斤拷锟叫讹拷使锟杰ｏ拷锟绞猴拷锟斤拷STM32- H7锟斤拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: Instance   USART_TypeDef锟斤拷锟酵结构锟斤拷
*             BaudRate   锟斤拷锟斤拷锟斤拷
*             Parity     校锟斤拷锟斤拷锟酵ｏ拷锟斤拷校锟斤拷锟斤拷锟脚夹ｏ拷锟�
*             Mode       锟斤拷锟酵和斤拷锟斤拷模式使锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
void bsp_SetUartParam(USART_TypeDef *Instance,  uint32_t BaudRate, uint32_t Parity, uint32_t Mode)
{
	UART_HandleTypeDef UartHandle;	
	
	/*##-1- 锟斤拷锟矫达拷锟斤拷硬锟斤拷锟斤拷锟斤拷 ######################################*/
	/* 锟届步锟斤拷锟斤拷模式 (UART Mode) */
	/* 锟斤拷锟斤拷锟斤拷锟斤拷:
	  - 锟街筹拷    = 8 位
	  - 停止位  = 1 锟斤拷停止位
	  - 校锟斤拷    = 锟斤拷锟斤拷Parity
	  - 锟斤拷锟斤拷锟斤拷  = 锟斤拷锟斤拷BaudRate
	  - 硬锟斤拷锟斤拷锟斤拷锟狡关憋拷 (RTS and CTS signals) */

	UartHandle.Instance        = Instance;

	UartHandle.Init.BaudRate   = BaudRate;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = Parity;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = Mode;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		Error_Handler(__FILE__, __LINE__);
	}
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: InitHardUart
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟矫达拷锟节碉拷硬锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟绞ｏ拷锟斤拷锟斤拷位锟斤拷停止位锟斤拷锟斤拷始位锟斤拷校锟斤拷位锟斤拷锟叫讹拷使锟杰ｏ拷锟绞猴拷锟斤拷STM32-H7锟斤拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
static void InitHardUart(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;


#if UART1_FIFO_EN == 1		/* 锟斤拷锟斤拷1 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	USART1_TX_GPIO_CLK_ENABLE();
	USART1_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	USART1_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = USART1_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = USART1_TX_AF;
	HAL_GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = USART1_RX_PIN;
	GPIO_InitStruct.Alternate = USART1_RX_AF;
	HAL_GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
  
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(USART1,  UART1_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	// USART_CR1_PEIE | USART_CR1_RXNEIE
	SET_BIT(USART1->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART2_FIFO_EN == 1		/* 锟斤拷锟斤拷2 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	USART2_TX_GPIO_CLK_ENABLE();
	USART2_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	USART2_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = USART2_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = USART2_TX_AF;
	HAL_GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = USART2_RX_PIN;
	GPIO_InitStruct.Alternate = USART2_RX_AF;
	HAL_GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
  
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(USART2,  UART2_BAUD, UART_PARITY_NONE, UART_MODE_RX);	// UART_MODE_TX_RX

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(USART2->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART3_FIFO_EN == 1			/* 锟斤拷锟斤拷3 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	USART3_TX_GPIO_CLK_ENABLE();
	USART3_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	USART3_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = USART3_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = USART3_TX_AF;
	HAL_GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = USART3_RX_PIN;
	GPIO_InitStruct.Alternate = USART3_RX_AF;
	HAL_GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(USART3_IRQn, 0, 3);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
  
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(USART3,  UART3_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(USART3->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART4_FIFO_EN == 1			/* 锟斤拷锟斤拷4 TX = PC10   RX = PC11 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	UART4_TX_GPIO_CLK_ENABLE();
	UART4_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	UART4_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = UART4_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = UART4_TX_AF;
	HAL_GPIO_Init(UART4_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = UART4_RX_PIN;
	GPIO_InitStruct.Alternate = UART4_RX_AF;
	HAL_GPIO_Init(UART4_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(UART4_IRQn, 0, 4);
	HAL_NVIC_EnableIRQ(UART4_IRQn);
  
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(UART4,  UART4_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(UART4->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART5_FIFO_EN == 1			/* 锟斤拷锟斤拷5 TX = PC12   RX = PD2 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	UART5_TX_GPIO_CLK_ENABLE();
	UART5_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	UART5_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = UART5_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = UART5_TX_AF;
	HAL_GPIO_Init(UART5_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = UART5_RX_PIN;
	GPIO_InitStruct.Alternate = UART5_RX_AF;
	HAL_GPIO_Init(UART5_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(UART5_IRQn, 0, 5);
	HAL_NVIC_EnableIRQ(UART5_IRQn);
  
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(UART5,  UART5_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(UART5->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART6_FIFO_EN == 1			/* USART6 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	USART6_TX_GPIO_CLK_ENABLE();
	USART6_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	USART6_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = USART6_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = USART6_TX_AF;
	HAL_GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = USART6_RX_PIN;
	GPIO_InitStruct.Alternate = USART6_RX_AF;
	HAL_GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(USART6_IRQn, 0, 6);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
	
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(USART6,  UART6_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(USART6->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART7_FIFO_EN == 1			/* UART7 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	UART7_TX_GPIO_CLK_ENABLE();
	UART7_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	UART7_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = UART7_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = UART7_TX_AF;
	HAL_GPIO_Init(UART7_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = UART7_RX_PIN;
	GPIO_InitStruct.Alternate = UART7_RX_AF;
	HAL_GPIO_Init(UART7_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(UART7_IRQn, 0, 6);
	HAL_NVIC_EnableIRQ(UART7_IRQn);
	
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(UART7,  UART7_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);

	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(UART7->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif

#if UART8_FIFO_EN == 1			/* UART8 */
	/* 使锟斤拷 GPIO TX/RX 时锟斤拷 */
	UART8_TX_GPIO_CLK_ENABLE();
	UART7_RX_GPIO_CLK_ENABLE();
	
	/* 使锟斤拷 USARTx 时锟斤拷 */
	UART8_CLK_ENABLE();	

	/* 锟斤拷锟斤拷TX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin       = UART8_TX_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = UART8_TX_AF;
	HAL_GPIO_Init(UART8_TX_GPIO_PORT, &GPIO_InitStruct);	
	
	/* 锟斤拷锟斤拷RX锟斤拷锟斤拷 */
	GPIO_InitStruct.Pin = UART8_RX_PIN;
	GPIO_InitStruct.Alternate = UART8_RX_AF;
	HAL_GPIO_Init(UART8_RX_GPIO_PORT, &GPIO_InitStruct);

	/* 锟斤拷锟斤拷NVIC the NVIC for UART */   
	HAL_NVIC_SetPriority(UART8_IRQn, 0, 6);
	HAL_NVIC_EnableIRQ(UART8_IRQn);
	
	/* 锟斤拷锟矫诧拷锟斤拷锟绞★拷锟斤拷偶校锟斤拷 */
	bsp_SetUartParam(UART8,  UART8_BAUD, UART_PARITY_NONE, UART_MODE_TX_RX);
	
	CLEAR_BIT(USART1->SR, USART_SR_TC);   /* 锟斤拷锟絋C锟斤拷锟斤拷锟斤拷杀锟街� */
    CLEAR_BIT(USART1->SR, USART_SR_RXNE); /* 锟斤拷锟絉XNE锟斤拷锟秸憋拷志 */
	SET_BIT(UART8->CR1, USART_CR1_RXNEIE);	/* 使锟斤拷PE. RX锟斤拷锟斤拷锟叫讹拷 */
#endif
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: UartSend
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷写锟斤拷锟捷碉拷UART锟斤拷锟酵伙拷锟斤拷锟斤拷,锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫断★拷锟叫断达拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷虾锟斤拷远锟斤拷乇辗锟斤拷锟斤拷卸锟�
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
static void UartSend(UART_T *_pUart, uint8_t *_ucaBuf, uint16_t _usLen)
{
	uint16_t i;

	for (i = 0; i < _usLen; i++)
	{
		/* 锟斤拷锟斤拷锟斤拷突锟斤拷锟斤拷锟斤拷丫锟斤拷锟斤拷耍锟斤拷锟饺达拷锟斤拷锟斤拷锟斤拷锟斤拷 */
		while (1)
		{
			__IO uint16_t usCount;

			DISABLE_INT();
			usCount = _pUart->usTxCount;
			ENABLE_INT();

			if (usCount < _pUart->usTxBufSize)
			{
				break;
			}
			else if(usCount == _pUart->usTxBufSize)/* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
			{
				if((_pUart->uart->CR1 & USART_CR1_TXEIE) == 0)
				{
					SET_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);
				}  
			}
		}

		/* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟诫发锟酵伙拷锟斤拷锟斤拷 */
		_pUart->pTxBuf[_pUart->usTxWrite] = _ucaBuf[i];

		DISABLE_INT();
		if (++_pUart->usTxWrite >= _pUart->usTxBufSize)
		{
			_pUart->usTxWrite = 0;
		}
		_pUart->usTxCount++;
		ENABLE_INT();
	}

	SET_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);	/* 使锟杰凤拷锟斤拷锟叫断ｏ拷锟斤拷锟斤拷锟斤拷锟秸ｏ拷 */
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: UartGetChar
*	锟斤拷锟斤拷说锟斤拷: 锟接达拷锟节斤拷锟秸伙拷锟斤拷锟斤拷锟斤拷取1锟街斤拷锟斤拷锟斤拷 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷茫锟�
*	锟斤拷    锟斤拷: _pUart : 锟斤拷锟斤拷锟借备
*			  _pByte : 锟斤拷哦锟饺★拷锟斤拷莸锟街革拷锟�
*	锟斤拷 锟斤拷 值: 0 锟斤拷示锟斤拷锟斤拷锟斤拷  1锟斤拷示锟斤拷取锟斤拷锟斤拷锟斤拷
*********************************************************************************************************
*/
static uint8_t UartGetChar(UART_T *_pUart, uint8_t *_pByte)
{
	uint16_t usCount;

	/* usRxWrite 锟斤拷锟斤拷锟斤拷锟叫断猴拷锟斤拷锟叫憋拷锟斤拷写锟斤拷锟斤拷锟斤拷锟斤拷锟饺★拷帽锟斤拷锟绞憋拷锟斤拷锟斤拷锟斤拷锟斤拷锟劫斤拷锟斤拷锟斤拷锟斤拷 */
	DISABLE_INT();
	usCount = _pUart->usRxCount;
	ENABLE_INT();

	/* 锟斤拷锟斤拷锟斤拷锟叫达拷锟斤拷锟斤拷锟酵拷锟斤拷蚍祷锟�0 */
	//if (_pUart->usRxRead == usRxWrite)
	if (usCount == 0)	/* 锟窖撅拷没锟斤拷锟斤拷锟斤拷 */
	{
		return 0;
	}
	else
	{
		*_pByte = _pUart->pRxBuf[_pUart->usRxRead];		/* 锟接达拷锟节斤拷锟斤拷FIFO取1锟斤拷锟斤拷锟斤拷 */

		/* 锟斤拷写FIFO锟斤拷锟斤拷锟斤拷 */
		DISABLE_INT();
		if (++_pUart->usRxRead >= _pUart->usRxBufSize)
		{
			_pUart->usRxRead = 0;
		}
		_pUart->usRxCount--;
		ENABLE_INT();
		return 1;
	}
}

/*
*********************************************************************************************************
*   锟斤拷 锟斤拷 锟斤拷: UartTxEmpty
*   锟斤拷锟斤拷说锟斤拷: 锟叫断凤拷锟酵伙拷锟斤拷锟斤拷锟角凤拷为锟秸★拷
*   锟斤拷    锟斤拷:  _pUart : 锟斤拷锟斤拷锟借备
*   锟斤拷 锟斤拷 值: 1为锟秸★拷0为锟斤拷锟秸★拷
*********************************************************************************************************
*/
uint8_t UartTxEmpty(COM_PORT_E _ucPort)
{
   UART_T *pUart;
   uint8_t Sending;
   
   pUart = ComToUart(_ucPort);
   if (pUart == 0)
   {
      return 0;
   }

   Sending = pUart->Sending;

   if (Sending != 0)
   {
      return 0;
   }
   return 1;
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: UartIRQ
*	锟斤拷锟斤拷说锟斤拷: 锟斤拷锟叫断凤拷锟斤拷锟斤拷锟斤拷锟矫ｏ拷通锟矫达拷锟斤拷锟叫断达拷锟斤拷锟斤拷锟斤拷
*	锟斤拷    锟斤拷: _pUart : 锟斤拷锟斤拷锟借备
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
static void UartIRQ(UART_T *_pUart)
{
	uint32_t isrflags   = READ_REG(_pUart->uart->SR);
	uint32_t cr1its     = READ_REG(_pUart->uart->CR1);
	uint32_t cr3its     = READ_REG(_pUart->uart->CR3);
	
	/* 锟斤拷锟斤拷锟斤拷锟斤拷锟叫讹拷  */
	if ((isrflags & USART_SR_RXNE) != RESET)
	{
		/* 锟接达拷锟节斤拷锟斤拷锟斤拷锟捷寄达拷锟斤拷锟斤拷取锟斤拷锟捷达拷诺锟斤拷锟斤拷锟紽IFO */
		uint8_t ch;

		ch = READ_REG(_pUart->uart->DR);
		_pUart->pRxBuf[_pUart->usRxWrite] = ch;
		if (++_pUart->usRxWrite >= _pUart->usRxBufSize)
		{
			_pUart->usRxWrite = 0;
		}
		if (_pUart->usRxCount < _pUart->usRxBufSize)
		{
			_pUart->usRxCount++;
		}

		/* 锟截碉拷锟斤拷锟斤拷,通知应锟矫筹拷锟斤拷锟秸碉拷锟斤拷锟斤拷锟斤拷,一锟斤拷锟角凤拷锟斤拷1锟斤拷锟斤拷息锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷锟� */
		//if (_pUart->usRxWrite == _pUart->usRxRead)
		//if (_pUart->usRxCount == 1)
		{
			if (_pUart->ReciveNew)
			{
				_pUart->ReciveNew(ch); /* 锟斤拷锟界，锟斤拷锟斤拷MODBUS锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷纸锟斤拷锟� */
			}
		}
	}

	/* 锟斤拷锟斤拷锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟叫讹拷 */
	if ( ((isrflags & USART_SR_TXE) != RESET) && (cr1its & USART_CR1_TXEIE) != RESET)
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
			/* 锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取锟斤拷时锟斤拷 锟斤拷止锟斤拷锟酵伙拷锟斤拷锟斤拷锟斤拷锟叫讹拷 锟斤拷注锟解：锟斤拷时锟斤拷锟�1锟斤拷锟斤拷锟捷伙拷未锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷希锟�*/
			//USART_ITConfig(_pUart->uart, USART_IT_TXE, DISABLE);
			CLEAR_BIT(_pUart->uart->CR1, USART_CR1_TXEIE);

			/* 使锟斤拷锟斤拷锟捷凤拷锟斤拷锟斤拷锟斤拷卸锟� */
			//USART_ITConfig(_pUart->uart, USART_IT_TC, ENABLE);
			SET_BIT(_pUart->uart->CR1, USART_CR1_TCIE);
		}
		else
		{
			_pUart->Sending = 1;
			
			/* 锟接凤拷锟斤拷FIFO取1锟斤拷锟街斤拷写锟诫串锟节凤拷锟斤拷锟斤拷锟捷寄达拷锟斤拷 */
			//USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			_pUart->uart->DR = _pUart->pTxBuf[_pUart->usTxRead];
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}

	}
	/* 锟斤拷锟斤拷bit位全锟斤拷锟斤拷锟斤拷锟斤拷系锟斤拷卸锟� */
	if (((isrflags & USART_SR_TC) != RESET) && ((cr1its & USART_CR1_TCIE) != RESET))
	{
		//if (_pUart->usTxRead == _pUart->usTxWrite)
		if (_pUart->usTxCount == 0)
		{
			/* 锟斤拷锟斤拷锟斤拷锟紽IFO锟斤拷锟斤拷锟斤拷全锟斤拷锟斤拷锟斤拷锟斤拷希锟斤拷锟街癸拷锟斤拷莘锟斤拷锟斤拷锟斤拷锟叫讹拷 */
			//USART_ITConfig(_pUart->uart, USART_IT_TC, DISABLE);
			CLEAR_BIT(_pUart->uart->CR1, USART_CR1_TCIE);

			/* 锟截碉拷锟斤拷锟斤拷, 一锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷RS485通锟脚ｏ拷锟斤拷RS485芯片锟斤拷锟斤拷为锟斤拷锟斤拷模式锟斤拷锟斤拷锟斤拷锟斤拷占锟斤拷锟斤拷 */
			if (_pUart->SendOver)
			{
				_pUart->SendOver();
			}
			
			_pUart->Sending = 0;
		}
		else
		{
			/* 锟斤拷锟斤拷锟斤拷锟斤拷拢锟斤拷锟斤拷锟斤拷锟斤拷朔锟街� */

			/* 锟斤拷锟斤拷锟斤拷锟紽IFO锟斤拷锟斤拷锟捷伙拷未锟斤拷希锟斤拷锟接凤拷锟斤拷FIFO取1锟斤拷锟斤拷锟斤拷写锟诫发锟斤拷锟斤拷锟捷寄达拷锟斤拷 */
			//USART_SendData(_pUart->uart, _pUart->pTxBuf[_pUart->usTxRead]);
			_pUart->uart->DR = _pUart->pTxBuf[_pUart->usTxRead];
			if (++_pUart->usTxRead >= _pUart->usTxBufSize)
			{
				_pUart->usTxRead = 0;
			}
			_pUart->usTxCount--;
		}
	}
}

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler锟斤拷
*	锟斤拷锟斤拷说锟斤拷: USART锟叫断凤拷锟斤拷锟斤拷锟�
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	UartIRQ(&g_tUart1);
}
#endif

#if UART2_FIFO_EN == 1
void USART2_IRQHandler(void)
{
	UartIRQ(&g_tUart2);
}
#endif

#if UART3_FIFO_EN == 1
void USART3_IRQHandler(void)
{
	UartIRQ(&g_tUart3);
}
#endif

#if UART4_FIFO_EN == 1
void UART4_IRQHandler(void)
{
	UartIRQ(&g_tUart4);
}
#endif

#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	UartIRQ(&g_tUart5);
}
#endif

#if UART6_FIFO_EN == 1
void USART6_IRQHandler(void)
{
	UartIRQ(&g_tUart6);
}
#endif

#if UART7_FIFO_EN == 1
void UART7_IRQHandler(void)
{
	UartIRQ(&g_tUart7);
}
#endif

#if UART8_FIFO_EN == 1
void UART8_IRQHandler(void)
{
	UartIRQ(&g_tUart8);
}
#endif

/*
*********************************************************************************************************
*	锟斤拷 锟斤拷 锟斤拷: fputc
*	锟斤拷锟斤拷说锟斤拷: 锟截讹拷锟斤拷putc锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷使锟斤拷printf锟斤拷锟斤拷锟接达拷锟斤拷1锟斤拷印锟斤拷锟�
*	锟斤拷    锟斤拷: 锟斤拷
*	锟斤拷 锟斤拷 值: 锟斤拷
*********************************************************************************************************
*/
int fputc(int ch, FILE *f)
{
#if 1	/* 锟斤拷锟斤拷要printf锟斤拷锟街凤拷通锟斤拷锟斤拷锟斤拷锟叫讹拷FIFO锟斤拷锟酵筹拷去锟斤拷printf锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 */
	comSendChar(COM1, ch);
	
	return ch;
#else	/* 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷式锟斤拷锟斤拷每锟斤拷锟街凤拷,锟饺达拷锟斤拷锟捷凤拷锟斤拷锟斤拷锟� */
	/* 写一锟斤拷锟街节碉拷USART1 */
	USART1->DR = ch;
	
	/* 锟饺达拷锟斤拷锟酵斤拷锟斤拷 */
	while((USART1->SR & USART_SR_TC) == 0)
	{}
	
	return ch;
#endif
}

// /*
// *********************************************************************************************************
// *	锟斤拷 锟斤拷 锟斤拷: fgetc
// *	锟斤拷锟斤拷说锟斤拷: 锟截讹拷锟斤拷getc锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷使锟斤拷getchar锟斤拷锟斤拷锟接达拷锟斤拷1锟斤拷锟斤拷锟斤拷锟斤拷
// *	锟斤拷    锟斤拷: 锟斤拷
// *	锟斤拷 锟斤拷 值: 锟斤拷
// *********************************************************************************************************
// */
// int fgetc(FILE *f)
// {

// #if 1	/* 锟接达拷锟节斤拷锟斤拷FIFO锟斤拷取1锟斤拷锟斤拷锟斤拷, 只锟斤拷取锟斤拷锟斤拷锟捷才凤拷锟斤拷 */
// 	uint8_t ucData;

// 	while(comGetChar(COM1, &ucData) == 0);

// 	return ucData;
// #else
// 	/* 锟饺达拷锟斤拷锟秸碉拷锟斤拷锟斤拷 */
// 	while((USART1->SR & USART_SR_RXNE) == 0)
// 	{}

// 	return (int)USART1->DR;
// #endif
// }

int _write(int fd, char *pbuf, int len)
{
	for (int i = 0; i < len; i++)
    {
		comSendChar(COM1, pbuf[i]);
	}
}

/***************************** 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 www.armfly.com (END OF FILE) *********************************/
