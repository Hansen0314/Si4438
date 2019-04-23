/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "stm8l15x.h"
#include "24c0x.h"
/*******************************************************************************
****��������:IIC��ʼ������
****��������:
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
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
****��������:��ʱ����
****��������:
****�汾:V1.0
****����:14-2-2014     
****��ڲ���:��
****���ڲ���:��
****˵��:
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
****��������:��EEPROMд��һҳ����
****��������:
****�汾:V1.0
****����:14-2-2014
****��ڲ���:buffer-д�����ݻ�����addr-��ַnum-Ҫд���������Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void EEPROM_WriteOnePage(unsigned char *buffer,unsigned char addr,unsigned char num)
{
  /* �ȴ����� */
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    
    /* ����ʼλ */
    I2C_GenerateSTART(I2C1,ENABLE);
    
    /* ����EV5 ��������������һ��Ӧ���ź�*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
    
    /* ����I2C��������ַ��I2C���豸Ϊдģʽ*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Transmitter);
  
    /* ����EV6 ��������������һ��Ӧ���ź�*/
  while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
    
  
    I2C_SendData(I2C1,(uint8_t)((addr & 0xFF00) >> 8)); 
    /* ����EV8 ��������������һ��Ӧ���ź�*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
    I2C_SendData(I2C1,(uint8_t)(addr & 0x00ff)); 
    /* ����EV8 ��������������һ��Ӧ���ź�*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  
    /* ���������豸д����*/
    while(num--)  
    {
      
      I2C_SendData(I2C1,*buffer); 
  
      /*ָ��ָ����һ����ַ*/
      buffer++; 
    
      /* ����EV6 ��������������һ��Ӧ���ź�*/
     while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));
      I2C_AcknowledgeConfig(I2C1,ENABLE);
    }
  
    /* ������λ*/
    I2C_GenerateSTOP(I2C1,ENABLE);
}
/*******************************************************************************
****��������:��EEPROMд������
****��������:
****�汾:V1.0
****����:14-2-2014
****��ڲ���:buffer-д�����ݻ�����addr-��ַnum-Ҫд���������Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void EEPROM_WriteData(unsigned char *buffer,unsigned char addr,unsigned char num)
{
  u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = addr % EEPROM_Page_Byte_Size;/*����һҳ�Ŀ�ʼд�ĵ�ַ*/
  count = EEPROM_Page_Byte_Size - Addr;/*����һҳ�ĵ�ַʣ������*/
  NumOfPage =  num / EEPROM_Page_Byte_Size;/*д��������ҳ��*/
  NumOfSingle = num % EEPROM_Page_Byte_Size;/*д������ҳʣ�������*/
 
  /* д���ĵ�ַ����ҳ���׵�ַ  */
  if(Addr == 0)
  { 
    /*д�����ֽ�������һҳ*/
    if(NumOfPage == 0) 
      EEPROM_WriteOnePage(buffer, addr, NumOfSingle);
     
    /*д�����ֽ�������һҳ*/
    else
    {
      while(NumOfPage--)
      {
        EEPROM_WriteOnePage(buffer, addr, EEPROM_Page_Byte_Size ); /*дһҳ*/
        addr +=  EEPROM_Page_Byte_Size ;
        buffer+= EEPROM_Page_Byte_Size ;
        WaiteI2C_SDA_Idle();
      }/*д����ҳ*/
      if(NumOfSingle!=0)
      {/*дβ��*/
        EEPROM_WriteOnePage(buffer, addr, NumOfSingle);
      }
    }
  }
  /* ����д���ĵ�ַ����ҳ���׵�ַ*/
  else 
  { 
  
    if (NumOfPage == 0) 
    {/*д�����ֽ�������һҳ */
    
      if (NumOfSingle > count)
      {
       /*Ҫд������ҳʣ����������ڲ���һҳ�ĵ�ַʣ������*/
        temp = NumOfSingle - count;
        EEPROM_WriteOnePage(buffer, addr, count);/*�ѵ�ǰҳ�ĵ�ַд��*/
        WaiteI2C_SDA_Idle();
        addr +=  count;
        buffer += count;
        EEPROM_WriteOnePage(buffer, addr, temp);/*���µ�һҳдʣ����ֽ�*/
      }
      else
      {
        EEPROM_WriteOnePage(buffer, addr, num);
      }
    }
    else
    { /*д�����ֽ�������һҳ*/
    
      num -= count;
      NumOfPage =  num / EEPROM_Page_Byte_Size;
      NumOfSingle = num % EEPROM_Page_Byte_Size;

      EEPROM_WriteOnePage(buffer, addr, count);/*�ѵ�ǰҳ�ĵ�ַд��*/
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
****��������:��EEPROM��������
****��������:
****�汾:V1.0
****����:14-2-2014
****��ڲ���:buffer-�������ݻ�����addr-��ַnum-Ҫ������������Ŀ
****���ڲ���:��
****˵��:
********************************************************************************/
void EEPROM_ReadData(unsigned char *buffer,unsigned char addr,unsigned char num)
{
   /* �ȴ����� */
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
  
    /* ����ʼλ */
    I2C_GenerateSTART(I2C1,ENABLE);
    /* ����EV5 ��������������һ��Ӧ���ź�*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
  
    /* ����I2C��������ַ��I2C���豸Ϊдģʽ*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Transmitter);
    /* ����EV6 ��������������һ��Ӧ���ź�*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
   
    I2C_SendData(I2C1,(uint8_t)((addr & 0xFF00) >> 8)); 
    /* ����EV8 ��������������һ��Ӧ���ź�*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED));  
    I2C_SendData(I2C1,(uint8_t)(addr & 0x00ff)); 
    /* ����EV8 ��������������һ��Ӧ���ź�*/
    while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)); 
  
    /* ����ʼλ */ 
    I2C_GenerateSTART(I2C1,ENABLE);
    /* ����EV5 ��������������һ��Ӧ���ź�*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)); 
  
    /* ����I2C��������ַ��I2C���豸Ϊ��ģʽ*/
    I2C_Send7bitAddress(I2C1,EEPROM_ADDRESS, I2C_Direction_Receiver);
    /* ����EV6 ��������������һ��Ӧ���ź�*/
    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    /*�����ڴӴ��豸��ȡ���� */
  while(num)  
  {

      /* ����EV6 */
    if(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)){      
      /*�� EEPROM ��ȡһ���ֽ�*/
      *buffer = I2C_ReceiveData(I2C1);
      /* ָ��ָ���¸�����ֽڵĵ�ַ*/
      buffer++;  
      /* �������һ���ֽ�*/
      if(num == 1){
      /* ����ҪӦ��*/
        I2C_AcknowledgeConfig(I2C1,DISABLE);
      /* ������λ*/
        I2C_GenerateSTOP(I2C1,ENABLE);  
      }
      else      
        /* �������һ���ֽ�����豸����Ӧ���ź�*/
        I2C_AcknowledgeConfig(I2C1,ENABLE);
      num--;
    }   
  }
  
}


  
  
  
  /****************************************************************************
* ���ƣ�I2C_WriteByte(uint8_t addr,uint8_t data)
* ���ܣ�����IIC��д������
* ��ڲ����� uint8_t addr �Ĵ����ĵ�ַ
* uint8_t data д������� 
* ���ڲ�������
* ˵�����Դ������ļĴ�������д���������������16����
****************************************************************************/

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
u8 count = 0;
while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY)); //�ȴ�����

I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0xD0
while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

I2C_SendData(I2C1, addr);//�Ĵ�����ַ
while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

I2C_SendData(I2C1, data);//��������
while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)){
    count++;
    if(count >= 0xfe){
      return;
    }
}
I2C_AcknowledgeConfig(I2C1,ENABLE);

I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
}

/****************************************************************************
* ���ƣ�uint8_t I2C_ReadByte(uint8_t addr)
* ���ܣ�����IIC�Ķ�������
* ��ڲ����� uint8_t addr �Ĵ����ĵ�ַ 
* ���ڲ����� uint8_t i ������������ݲ���Ϊ��������
* ˵�����Դ������ļĴ������ж�����������������16���ƣ�IICд����Ҫ
��д�Ĵ����ٽ��ж��Ĵ����Ĳ����������ʧ��
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

  I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

  I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0xD0
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  I2C_SendData(I2C1, addr);//�Ĵ�����ַ
  while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));



  I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/

  I2C_Send7bitAddress(I2C1, EEPROM_ADDRESS, I2C_Direction_Receiver);//������ַ -- Ĭ��0xD1
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));


  while (!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));

  i=I2C_ReceiveData(I2C1);//��ȡ����

  I2C_AcknowledgeConfig(I2C1,DISABLE);

  I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
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
