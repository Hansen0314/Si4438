/****************************************Copyright (c)****************************************************
**                            Guangzhou ZLGMCU Development Co., LTD
**
**                                 http://www.zlgmcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           radio_hal.c
** Last modified Date:  2016-3-22
** Last Version:        V1.00
** Descriptions:         
**
**--------------------------------------------------------------------------------------------------------
** Created by:          yanghongyu
** Created date:        2016-3-22
** Version:             V1.00
** Descriptions:         
**
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:         
*********************************************************************************************************/


#include "stm8l15x.h"                                                    /* STM8L151外设寄存器            */



/*  移值时需要修改的宏定义    */
/*   SPI-SEL   :  PB3      片选       */
/*   SPI-MOSI  :  PA7             */
/*   SPI-MISO  :  PA6             */
/*   SPI-CLK   :  PA5             */
/*   RST	   :  PB2            */
/*   IRQ	   :  PB4             */
/*   DIO1	   :  PB1             */
/*   DIO2      :  PA2             */

#define SEL_L()       GPIO_ResetBits(GPIOB,GPIO_Pin_4)                  // SPI片选信号，低电平有效
#define SEL_H()       GPIO_SetBits(GPIOB,GPIO_Pin_4)  

//#define SDN_L()       GPIO_ResetBits(GPIOB,GPIO_Pin_2)                 //芯片内部LDO使能信号，低电平正常供电，高电平停止供电，功耗最小 
//#define SDN_H()       GPIO_SetBits(GPIOB,GPIO_Pin_2) 

#define IRQ_READ()    GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)         //中断输出引脚，有中断时输出低

//#define DIO1_Level()  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)           
//#define DIO2_Level()  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)   

/*********************************************************************************************************
** Function name:        dellay
** Descriptions:         延时一小段时间
** input parameters:     i 毫秒数据
** output parameters:    无
*********************************************************************************************************/
void dellayus(unsigned int i)
{
   unsigned int j,k;
   
   for (j = 0; j <1; j++)
   {
        for (k = 0; k < i; k++);
   }
}
/*********************************************************************************************************
** Function name:        dellayms
** Descriptions:         延时若干毫秒
** input parameters:     uiNum: 毫秒数据
** output parameters:    无
*********************************************************************************************************/
void dellayxm(unsigned int uiNum)
{
   unsigned int i = 0;
   unsigned int j = 0;
   while(i < uiNum) 
   {
   	i++;
	for(j = 0; j < 4369; j++);
   }
}
/*********************************************************************************************************
** Function name:        dellay
** Descriptions:         延时一小段时间
** input parameters:     i 毫秒数据
** output parameters:    无
*********************************************************************************************************/
void dellay(uint32_t i)
{
  while(i--);
}
/*********************************************************************************************************
** Function name:        dellayms
** Descriptions:         延时若干毫秒
** input parameters:     uiNum: 毫秒数据
** output parameters:    无
*********************************************************************************************************/
void dellayxms(uint32_t uiNum)
{
   uint32_t i = 0;
   uint32_t j = 0;
   while(i < uiNum) 
   {
   	i++;
	for(j = 0; j < 4369; j++);
   }
}
/*********************************************************************************************************
** Function name:       IRQ_STATE
** Descriptions:        返回IRQ引脚的电平状态
** input parameters:    无
** output parameters:   无
*********************************************************************************************************/
unsigned char IRQ_STATE(void)
{
    uint8_t state = 0;

    state = IRQ_READ();
    return ( state );
}
/*********************************************************************************************************
** Function name:       Si433_PinInit
** Descriptions:        初始化与SI4438模块连接的引脚
** input parameters:    无
** output parameters:   无
*********************************************************************************************************/
void MCU_PinInit(void)
{   
    CLK_PeripheralClockConfig(CLK_Peripheral_SPI1,ENABLE);
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_High_Fast);
    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT);
    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_High_Fast);
   
    SPI_DeInit(SPI1);
    SPI_Init(SPI1,SPI_FirstBit_MSB, SPI_BaudRatePrescaler_4, SPI_Mode_Master,\
	   SPI_CPOL_Low, SPI_CPHA_1Edge, \
	   SPI_Direction_2Lines_FullDuplex, SPI_NSS_Soft, 0x07);
	    
    SPI_Cmd(SPI1,ENABLE);	/* 使能SPI */
    SEL_H();
 
}
/*********************************************************************************************************
** Function name:       SpiSendByte
** Descriptions:        向数据总线上发送一个字节
** input parameters:    dat:要发送的数据
** output parameters:   无
*********************************************************************************************************/
uint8_t SpiSendByte(uint8_t dat)
{
     /* Loop while DR register in not emplty */  
    while(SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);  
      
    /* Send byte through the SPI2 peripheral */  
    SPI_SendData(SPI1, dat);  
      
    /* Wait to receive a byte */  
    while(SPI_GetFlagStatus(SPI1, SPI_FLAG_RXNE) == RESET);  
      
    /* Return the byte read from the SPI bus */  
    return SPI_ReceiveData(SPI1);                                                          /* set 0;                       */ 
}
/*********************************************************************************************************
** Function name:       SpiRCVByte
** Descriptions:        从数据总线上接收一个字节
** input parameters:    无
** output parameters:   读到的数据
*********************************************************************************************************/
unsigned char SpiRCVByte(void)
{
    return (SpiSendByte(0x00));
}
/*********************************************************************************************************
** Function name:       SpiReadRegister
** Descriptions:        读Si433寄存器的值
** input parameters:    reg:寄存器的地址
** output parameters:   读到的值
*********************************************************************************************************/
uint8_t SpiReadRegister (uint8_t ucReg)
{
	uint8_t ucTemp;
	
	SEL_L();
	SpiSendByte(ucReg);
	ucTemp = SpiRCVByte();
	SEL_H();
	return ucTemp;	
}
/*********************************************************************************************************
** Function name:       SpiWriteRegister
** Descriptions:        向Si433寄存器中写入字节
** input parameters:    reg:被写入的寄存器地址; data:写入的数据
** output parameters:   无
*********************************************************************************************************/
void SpiWriteRegister(uint8_t ucReg,uint8_t ucData)
{	
	SEL_L();
	SpiSendByte(ucReg|0x80);
	SpiSendByte(ucData);
	SEL_H();
}

void radio_hal_AssertShutdown(void)
{
    //SDN_H();  /* 拉高SDN引脚 */
}
void radio_hal_DeassertShutdown(void)
{
    //SDN_L();
}
void radio_hal_ClearNsel(void)
{
    SEL_L();
}

void radio_hal_SetNsel(void)
{
	SEL_H(); 
}

U8 radio_hal_NirqLevel(void)
{
    return IRQ_READ();	  /* 读IRQ引脚电平 */
}    

void radio_hal_SpiWriteByte(U8 byteToWrite)
{

    SpiSendByte(byteToWrite);

}

U8 radio_hal_SpiReadByte(void)
{

    return SpiRCVByte();
   
}

void radio_hal_SpiWriteData(U8 byteCount, U8* pData)
{
   
    while (byteCount--) 
    {
        SpiSendByte(*pData++);
    }
   
}

void radio_hal_SpiReadData(U8 byteCount, U8* pData)
{
    while (byteCount--) 
    {
      *pData++ = SpiRCVByte();
    }

}

