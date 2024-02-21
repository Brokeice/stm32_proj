/*
*********************************************************************************************************
*
*	模块名称 : LAN8742驱动
*	文件名称 : lan8742.c
*	版    本 : V1.0
*	说    明 : 这个PHY驱动结构和通常驱动不同，需要先注册SMI总线读写函数才能使用。
*		此驱动结构的优点是驱动文件不加修改就可以移植到不同的CPU平台。
*
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2018-10-20 armfly  首版.
*
*	Copyright (C), 2018-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "lan8742.h"

#define LAN8742_SW_RESET_TO    ((uint32_t)500U)
#define LAN8742_INIT_TO        ((uint32_t)2000U)

/*
*********************************************************************************************************
*	函 数 名: LAN8742_RegisterBusIO
*	功能说明: 注册驱动函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int32_t LAN8742_RegisterBusIO(lan8742_Object_t *pObj, lan8742_IOCtx_t *ioctx)
{
  if(!pObj || !ioctx->ReadReg || !ioctx->WriteReg || !ioctx->GetTick)
  {
    return LAN8742_STATUS_ERROR;
  }
  
  pObj->IO.Init = ioctx->Init;
  pObj->IO.DeInit = ioctx->DeInit;
  pObj->IO.ReadReg = ioctx->ReadReg;
  pObj->IO.WriteReg = ioctx->WriteReg;
  pObj->IO.GetTick = ioctx->GetTick;
  
  return LAN8742_STATUS_OK;
}

/*
*********************************************************************************************************
*	函 数 名: LAN8742_Init
*	功能说明: Initialize the lan8742 and configure the needed hardware resources
*	形    参: 无
*	返 回 值: 状态
*			LAN8742_STATUS_OK  if OK
*			LAN8742_STATUS_ADDRESS_ERROR if cannot find device address
*			LAN8742_STATUS_READ_ERROR if connot read register
*			LAN8742_STATUS_WRITE_ERROR if connot write to register
*			LAN8742_STATUS_RESET_TIMEOUT if cannot perform a software reset
*********************************************************************************************************
*/
int32_t LAN8742_Init(lan8742_Object_t *pObj)
{
   uint32_t tickstart = 0, regvalue = 0;
   int32_t status = LAN8742_STATUS_OK;
   
   if(pObj->Is_Initialized == 0)
   {
     if(pObj->IO.Init != 0)
     {
       /* GPIO and Clocks initialization */
       pObj->IO.Init();
     }
   
     /* for later check */
     pObj->DevAddr = LAN8742_PHY_ADDR;
     
     /* if device address is matched */
     if(status == LAN8742_STATUS_OK)
     {
       /* set a software reset  */
       if(pObj->IO.WriteReg(pObj->DevAddr, LAN8742_BCR, LAN8742_BCR_SOFT_RESET) >= 0)
       { 
         /* get software reset status */
         if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_BCR, &regvalue) >= 0)
         { 
           tickstart = pObj->IO.GetTick();
           
           /* wait until software reset is done or timeout occured  */
           while(regvalue & LAN8742_BCR_SOFT_RESET)
           {
             if((pObj->IO.GetTick() - tickstart) <= LAN8742_SW_RESET_TO)
             {
               if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_BCR, &regvalue) < 0)
               { 
                 status = LAN8742_STATUS_READ_ERROR;
                 break;
               }
             }
             else
             {
               status = LAN8742_STATUS_RESET_TIMEOUT;
             }
           } 
         }
         else
         {
           status = LAN8742_STATUS_READ_ERROR;
         }
       }
       else
       {
         status = LAN8742_STATUS_WRITE_ERROR;
       }
     }
   }
      
   if(status == LAN8742_STATUS_OK)
   {
     tickstart =  pObj->IO.GetTick();
     
     /* Wait for 2s to perform initialization */
     while((pObj->IO.GetTick() - tickstart) <= LAN8742_INIT_TO)
     {
     }
     pObj->Is_Initialized = 1;
   }
   
   return status;
}

/*
*********************************************************************************************************
*	函 数 名: LAN8742_GetLinkState
*	功能说明: Get the link state of LAN8742 device.
*	形    参: 无
*	返 回 值: pLinkState: Pointer to link state
*			LAN8742_STATUS_LINK_DOWN  if link is down
*			LAN8742_STATUS_AUTONEGO_NOTDONE if Auto nego not completed 
*			LAN8742_STATUS_100MBITS_FULLDUPLEX if 100Mb/s FD
*			LAN8742_STATUS_100MBITS_HALFDUPLEX if 100Mb/s HD
*			LAN8742_STATUS_10MBITS_FULLDUPLEX  if 10Mb/s FD
*			LAN8742_STATUS_10MBITS_HALFDUPLEX  if 10Mb/s HD       
*			LAN8742_STATUS_READ_ERROR if connot read register
*			LAN8742_STATUS_WRITE_ERROR if connot write to register
*********************************************************************************************************
*/
int32_t LAN8742_GetLinkState(lan8742_Object_t *pObj)
{
  uint32_t readval = 0;
  
  /* Read Status register  */
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_BSR, &readval) < 0)
  {
    return LAN8742_STATUS_READ_ERROR;
  }
  
  /* Read Status register again */
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_BSR, &readval) < 0)
  {
    return LAN8742_STATUS_READ_ERROR;
  }
  
  if((readval & LAN8742_BSR_LINK_STATUS) == 0)
  {
    /* Return Link Down status */
    return LAN8742_STATUS_LINK_DOWN;    
  }
  
  /* Check Auto negotiaition */
  if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_BCR, &readval) < 0)
  {
    return LAN8742_STATUS_READ_ERROR;
  }
  
  if((readval & LAN8742_BCR_AUTONEGO_EN) != LAN8742_BCR_AUTONEGO_EN)
  {
    if(((readval & LAN8742_BCR_SPEED_SELECT) == LAN8742_BCR_SPEED_SELECT) && ((readval & LAN8742_BCR_DUPLEX_MODE) == LAN8742_BCR_DUPLEX_MODE)) 
    {
      return LAN8742_STATUS_100MBITS_FULLDUPLEX;
    }
    else if ((readval & LAN8742_BCR_SPEED_SELECT) == LAN8742_BCR_SPEED_SELECT)
    {
      return LAN8742_STATUS_100MBITS_HALFDUPLEX;
    }        
    else if ((readval & LAN8742_BCR_DUPLEX_MODE) == LAN8742_BCR_DUPLEX_MODE)
    {
      return LAN8742_STATUS_10MBITS_FULLDUPLEX;
    }
    else
    {
      return LAN8742_STATUS_10MBITS_HALFDUPLEX;
    }  		
  }
  else /* Auto Nego enabled */
  {
    if(pObj->IO.ReadReg(pObj->DevAddr, LAN8742_PHYSCSR, &readval) < 0)
    {
      return LAN8742_STATUS_READ_ERROR;
    }
    
    /* Check if auto nego not done */
    if((readval & LAN8742_PHYSCSR_AUTONEGO_MASK) != LAN8742_PHYSCSR_AUTONEGO_DONE)
    {
      return LAN8742_STATUS_AUTONEGO_NOTDONE;
    }
    
    if((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_100BTX_FD)
    {
      return LAN8742_STATUS_100MBITS_FULLDUPLEX;
    }
    else if ((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_100BTX_HD)
    {
      return LAN8742_STATUS_100MBITS_HALFDUPLEX;
    }
    else if ((readval & LAN8742_PHYSCSR_HCDSPEEDMASK) == LAN8742_PHYSCSR_10BT_FD)
    {
      return LAN8742_STATUS_10MBITS_FULLDUPLEX;
    }
    else
    {
      return LAN8742_STATUS_10MBITS_HALFDUPLEX;
    }				
  }
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
