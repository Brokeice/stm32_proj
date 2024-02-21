/*
*********************************************************************************************************
*
*	模块名称 : LAN8742驱动
*	文件名称 : lan8742.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LAN8742_H
#define __LAN8742_H

#ifdef __cplusplus
 extern "C" {
#endif   

#include <stdint.h>
 
#define LAN8742_PHY_ADDR	1
 
#define LAN8742_BCR		0x00
	#define LAN8742_BCR_SOFT_RESET         ((uint16_t)0x8000U)
	#define LAN8742_BCR_LOOPBACK           ((uint16_t)0x4000U)
	#define LAN8742_BCR_SPEED_SELECT       ((uint16_t)0x2000U)
	#define LAN8742_BCR_AUTONEGO_EN        ((uint16_t)0x1000U)
	#define LAN8742_BCR_POWER_DOWN         ((uint16_t)0x0800U)
	#define LAN8742_BCR_ISOLATE            ((uint16_t)0x0400U)
	#define LAN8742_BCR_RESTART_AUTONEGO   ((uint16_t)0x0200U)
	#define LAN8742_BCR_DUPLEX_MODE        ((uint16_t)0x0100U) 
	
#define LAN8742_BSR		                 ((uint16_t)0x01) 				/* PHY status register Offset */ 
	#define LAN8742_BSR_100BASE_T4       ((uint16_t)0x8000U)
	#define LAN8742_BSR_100BASE_TX_FD    ((uint16_t)0x4000U)
	#define LAN8742_BSR_100BASE_TX_HD    ((uint16_t)0x2000U)
	#define LAN8742_BSR_10BASE_T_FD      ((uint16_t)0x1000U)
	#define LAN8742_BSR_10BASE_T_HD      ((uint16_t)0x0800U)
	#define LAN8742_BSR_100BASE_T2_FD    ((uint16_t)0x0400U)
	#define LAN8742_BSR_100BASE_T2_HD    ((uint16_t)0x0200U)
	#define LAN8742_BSR_EXTENDED_STATUS  ((uint16_t)0x0100U)
	#define LAN8742_BSR_AUTONEGO_CPLT    ((uint16_t)0x0020U)
	#define LAN8742_BSR_REMOTE_FAULT     ((uint16_t)0x0010U)
	#define LAN8742_BSR_AUTONEGO_ABILITY ((uint16_t)0x0008U)
	#define LAN8742_BSR_LINK_STATUS      ((uint16_t)0x0004U)
	#define LAN8742_BSR_JABBER_DETECT    ((uint16_t)0x0002U)
	#define LAN8742_BSR_EXTENDED_CAP     ((uint16_t)0x0001U)

#define LAN8742_PHYSCSR  				((uint16_t)17)
	#define LAN8742_PHYSCSR_AUTONEGO_MASK   ((uint16_t)0x000F)
	#define LAN8742_PHYSCSR_AUTONEGO_DONE   ((uint16_t)0x0008U)
	
	#define LAN8742_PHYSCSR_HCDSPEEDMASK    ((uint16_t)0xF000)
	#define LAN8742_PHYSCSR_10BT_HD         ((uint16_t)0x1000)
	#define LAN8742_PHYSCSR_10BT_FD         ((uint16_t)0x2000)
	#define LAN8742_PHYSCSR_100BTX_HD       ((uint16_t)0x4000)
	#define LAN8742_PHYSCSR_100BTX_FD       ((uint16_t)0x8000) 
	

/* LAN8742_Status LAN8742 Status */
#define  LAN8742_STATUS_READ_ERROR            ((int32_t)-5)
#define  LAN8742_STATUS_WRITE_ERROR           ((int32_t)-4)
#define  LAN8742_STATUS_ADDRESS_ERROR         ((int32_t)-3)
#define  LAN8742_STATUS_RESET_TIMEOUT         ((int32_t)-2)
#define  LAN8742_STATUS_ERROR                 ((int32_t)-1)
#define  LAN8742_STATUS_OK                    ((int32_t) 0)
#define  LAN8742_STATUS_LINK_DOWN             ((int32_t) 1)
#define  LAN8742_STATUS_100MBITS_FULLDUPLEX   ((int32_t) 2)
#define  LAN8742_STATUS_100MBITS_HALFDUPLEX   ((int32_t) 3)
#define  LAN8742_STATUS_10MBITS_FULLDUPLEX    ((int32_t) 4)
#define  LAN8742_STATUS_10MBITS_HALFDUPLEX    ((int32_t) 5)
#define  LAN8742_STATUS_AUTONEGO_NOTDONE      ((int32_t) 6)

typedef int32_t  (*lan8742_Init_Func) (void);
typedef int32_t  (*lan8742_DeInit_Func) (void);
typedef int32_t  (*lan8742_ReadReg_Func)   (uint32_t, uint32_t, uint32_t *);
typedef int32_t  (*lan8742_WriteReg_Func)  (uint32_t, uint32_t, uint32_t);
typedef int32_t  (*lan8742_GetTick_Func)  (void);

typedef struct 
{                   
  lan8742_Init_Func      Init; 
  lan8742_DeInit_Func    DeInit;
  lan8742_WriteReg_Func  WriteReg;
  lan8742_ReadReg_Func   ReadReg; 
  lan8742_GetTick_Func   GetTick;   
} lan8742_IOCtx_t;  

  
typedef struct 
{
  uint32_t            DevAddr;
  uint32_t            Is_Initialized;
  lan8742_IOCtx_t     IO;
  void               *pData;
}lan8742_Object_t;

int32_t LAN8742_RegisterBusIO(lan8742_Object_t *pObj, lan8742_IOCtx_t *ioctx);
int32_t LAN8742_Init(lan8742_Object_t *pObj);
int32_t LAN8742_GetLinkState(lan8742_Object_t *pObj);

#ifdef __cplusplus
}
#endif
#endif /* __LAN8742_H */

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
