/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "stm8l15x.h"
#include "24c0x.h"
/*******************************************************************************
****函数名称:IIC初始化函数
****函数功能:
****版本:V1.0
****日期:14-2-2014
****入口参数:无
****出口参数:无
****说明:
********************************************************************************/
void InitIIC(void)
{
  GPIO_Init(GPIOD,GPIO_Pin_0,GPIO_Mode_Out_OD_HiZ_Fast);
  GPIO_Init(GPIOD,GPIO_Pin_1,GPIO_Mode_Out_OD_HiZ_Fast);
    
  CLK_PeripheralClockConfig(CLK_Peripheral_I2C1,ENABLE);
  I2C_DeInit(I2C1);
  I2C_Cmd(I2C1,ENABLE);
  I2C_Init(I2C1,IICSPEED, EEPROM_ADDRESS, I2C_Mode_I2C,I2C_DutyCycle_2, I2C_Ack_Enable, I2C_AcknowledgedAddress_7bit);
  
}

/*******************************************************************************
****函数名称:延时函数
****函数功能:
****版本:V1.0
****日期:14-2-2014     
****入口参数:无
****出口参数:无
****说明:
********************************************************************************/
void WaiteI2C_SDA_Idle(void )
{
  unsigned int nCount=0xfffF;
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

/*******************************************************************************
****函数名称:向EEPROM写入一页数据
****函数功能:
****版本:V1.0
****日期:14-2-2014
****入口参数:buffer-写入数据缓冲区addr-地址num-要写入的数据数目
****出口参数:无
****说明:
********************************************************************************/
void EEPROM_WriteOnePage(unsigned char *buffer,unsigned char addr,unsigned char num)
{
  /* 等待空闲 */
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    
    /* 发起始位 */
    I2C_GenerateSTART(I2C1,ENABLE);
    
    /* 测试EV5 ，检测从器件返回一个应答信号*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
    
    /* 设置I2C从器件地址，I2C主设备为写模式*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
    /* 测试EV6 ，检测从器件返回一个应答信号*/
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
  
    I2C_SendData(I2C1,(uint8_t)((addr & 0xFF00) >> 8)); 
    /* 测试EV8 ，检测从器件返回一个应答信号*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
    I2C_SendData(I2C1,(uint8_t)(addr & 0x00ff)); 
    /* 测试EV8 ，检测从器件返回一个应答信号*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  
    /* 不断往从设备写数据*/
    while(num--)  
    {
      
      I2C_SendData(I2C1,*buffer); 
  
      /*指针指向下一个地址*/
      buffer++; 
    
      /* 测试EV6 ，检测从器件返回一个应答信号*/
     while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
      I2C_AcknowledgeConfig(I2C1,ENABLE);
    }
  
    /* 发结束位*/
    I2C_GenerateSTOP(I2C1,ENABLE);
}
/*******************************************************************************
****函数名称:向EEPROM写入数据
****函数功能:
****版本:V1.0
****日期:14-2-2014
****入口参数:buffer-写入数据缓冲区addr-地址num-要写入的数据数目
****出口参数:无
****说明:
********************************************************************************/
void EEPROM_WriteData(unsigned char *buffer,unsigned char addr,unsigned char num)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = addr % EEPROM_Page_Byte_Size;/*不满一页的开始写的地址*/
  count = EEPROM_Page_Byte_Size - Addr;/*不满一页的地址剩余容量*/
  NumOfPage =  num / EEPROM_Page_Byte_Size;/*写了完整的页数*/
  NumOfSingle = num % EEPROM_Page_Byte_Size;/*写完完整页剩余的容量*/
 
  /* 写进的地址是在页的首地址  */
  if(Addr == 0)
  { 
    /*写进的字节数不足一页*/
    if(NumOfPage == 0) 
      EEPROM_WriteOnePage(buffer, addr, NumOfSingle);
     
    /*写进的字节数大于一页*/
    else
    {
      while(NumOfPage--)
      {
        EEPROM_WriteOnePage(buffer, addr, EEPROM_Page_Byte_Size ); /*写一页*/
        addr +=  EEPROM_Page_Byte_Size ;
        buffer+= EEPROM_Page_Byte_Size ;
        WaiteI2C_SDA_Idle();
      }/*写完整页*/
      if(NumOfSingle!=0)
      {/*写尾数*/
        EEPROM_WriteOnePage(buffer, addr, NumOfSingle);
      }
    }
  }
  /* 假如写进的地址不在页的首地址*/
  else 
  { 
  
    if (NumOfPage == 0) 
    {/*写进的字节数不足一页 */
    
      if (NumOfSingle > count)
      {
       /*要写完完整页剩余的容量大于不满一页的地址剩余容量*/
        temp = NumOfSingle - count;
        EEPROM_WriteOnePage(buffer, addr, count);/*把当前页的地址写完*/
        WaiteI2C_SDA_Idle();
        addr +=  count;
        buffer += count;
        EEPROM_WriteOnePage(buffer, addr, temp);/*在新的一页写剩余的字节*/
      }
      else
      {
        EEPROM_WriteOnePage(buffer, addr, num);
      }
    }
    else
    { /*写进的字节数大于一页*/
    
      num -= count;
      NumOfPage =  num / EEPROM_Page_Byte_Size;
      NumOfSingle = num % EEPROM_Page_Byte_Size;

      EEPROM_WriteOnePage(buffer, addr, count);/*把当前页的地址写完*/
      WaiteI2C_SDA_Idle();
      addr +=  count;
      buffer += count;

      while (NumOfPage--)
      {
        EEPROM_WriteOnePage(buffer, addr, EEPROM_Page_Byte_Size);
        WaiteI2C_SDA_Idle();
        addr +=  EEPROM_Page_Byte_Size;
        buffer += EEPROM_Page_Byte_Size;
      }

      if (NumOfSingle != 0)
      {
        EEPROM_WriteOnePage(buffer, addr, NumOfSingle);
      }
    }
  }
  WaiteI2C_SDA_Idle();
}
/*******************************************************************************
****函数名称:从EEPROM读出数据
****函数功能:
****版本:V1.0
****日期:14-2-2014
****入口参数:buffer-读出数据缓冲区addr-地址num-要读出的数据数目
****出口参数:无
****说明:
********************************************************************************/
void EEPROM_ReadData(unsigned char *buffer,unsigned char addr,unsigned char num)
{
   /* 等待空闲 */
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
  
    /* 发起始位 */
    I2C_GenerateSTART(I2C1,ENABLE);
    /* 测试EV5 ，检测从器件返回一个应答信号*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
  
    /* 设置I2C从器件地址，I2C主设备为写模式*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Transmitter);
    /* 测试EV6 ，检测从器件返回一个应答信号*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
   
    I2C_SendData(I2C1,(uint8_t)((addr & 0xFF00) >> 8)); 
    /* 测试EV8 ，检测从器件返回一个应答信号*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
    I2C_SendData(I2C1,(uint8_t)(addr & 0x00ff)); 
    /* 测试EV8 ，检测从器件返回一个应答信号*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  
    /* 发起始位 */ 
    I2C_GenerateSTART(I2C1,ENABLE);
    /* 测试EV5 ，检测从器件返回一个应答信号*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
  
    /* 设置I2C从器件地址，I2C主设备为读模式*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Receiver);
    /* 测试EV6 ，检测从器件返回一个应答信号*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    /*不断在从从设备读取数据 */
  while(num)  
  {

      /* 测试EV6 */
    if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){      
      /*从 EEPROM 读取一个字节*/
      *buffer = I2C_ReceiveData(I2C1);
      /* 指针指向下个存放字节的地址*/
      buffer++;  
      /* 读到最后一个字节*/
      if(num == 1){
      /* 不需要应答*/
        I2C_AcknowledgeConfig(I2C1,DISABLE);
      /* 发结束位*/
        I2C_GenerateSTOP(I2C1,ENABLE);  
      }
      else      
        /* 不是最后一个字节向从设备发送应答信号*/
        I2C_AcknowledgeConfig(I2C1,ENABLE);
      num--;
    }   
  }
  
}


  
  
  
  /****************************************************************************
* 名称：I2C_WriteByte(uint8_t addr,uint8_t data)
* 功能：进行IIC的写操作。
* 入口参数： uint8_t addr 寄存器的地址
* uint8_t data 写入的数据 
* 出口参数：无
* 说明：对触摸屏的寄存器进行写入操作，变量都是16进制
****************************************************************************/

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
u8 count = 0;
while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //等待空闲

I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//器件地址 -- 默认0xD0
while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

I2C_SendData(I2C1, addr);//寄存器地址
while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_SendData(I2C1, data);//发送数据
while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
    count++;
    if(count >= 0xfe){
      return;
    }
}
I2C_AcknowledgeConfig(I2C1,ENABLE);

I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
}

/****************************************************************************
* 名称：uint8_t I2C_ReadByte(uint8_t addr)
* 功能：进行IIC的读操作。
* 入口参数： uint8_t addr 寄存器的地址 
* 出口参数： uint8_t i 保存读到的数据并作为参数返回
* 说明：对触摸屏的寄存器进行读出操作，变量都是16进制，IIC写操作要
先写寄存器再进行读寄存器的操作，否则会失败
****************************************************************************/
uint8_t I2C_ReadByte(uint8_t addr)
{
  uint8_t i;
  u8 count = 0;

  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)){
  
    count++;
    if(count >= 0xfe){
      return 0xff;
    }
  }

  I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

  I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//器件地址 -- 默认0xD0
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  I2C_SendData(I2C1, addr);//寄存器地址
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));



  I2C_GenerateSTART(I2C1, ENABLE);//开启I2C1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/

  I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Receiver);//器件地址 -- 默认0xD1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));


  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));

  i=I2C_ReceiveData(I2C1);//读取数据

  I2C_AcknowledgeConfig(I2C1,DISABLE);

  I2C_GenerateSTOP(I2C1, ENABLE);//关闭I2C1总线
  return i;
}

void IIC_24c02_Write_Date(uint8_t addr, u8 *buffer,u8 length)
{
  while(length--){
    I2C_WriteByte(addr++,*buffer++);
    WaiteI2C_SDA_Idle();
  }
  
}


void IIC_24c02_Read_Date(uint8_t addr, u8 *buffer,u8 length)
{
  while(length--){
   *buffer++ = I2C_ReadByte(addr++);
  }
  
}
