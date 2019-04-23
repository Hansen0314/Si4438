/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#include "stm8l15x.h"
#include "flash.h"
/*******************************************************************************
****��������:IIC��ʼ������
****��������:
****�汾:V1.0
****����:14-2-2014
****��ڲ���:��
****���ڲ���:��
****˵��:
********************************************************************************/
void InitFlash(void)
{
  FLASH_DeInit();
  /* ����FLASH���ʱ�� */
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
  /* ����EEPROM */
  FLASH_Unlock(FLASH_MemType_Data);
  /* �ȴ�������� */
  while(FLASH_GetFlagStatus(FLASH_FLAG_DUL)== RESET);
}


void Flash_Write_Byte(uint8_t addr, uint8_t data)
{
  /* ��EEPROM��ַ0x1000 + addr ��д������ */
  FLASH_ProgramByte(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS + addr, data);
  /* �ȴ�д����� */
while(FLASH_GetFlagStatus(FLASH_FLAG_EOP)== RESET);
}

void Flash_Write_Date(uint8_t addr, u8 *buffer,u8 length)
{
  while(length--){
    Flash_Write_Byte(addr++,*buffer++);
  }
  
}


uint8_t Flash_Read_Byte(uint8_t addr)
{
  uint8_t data;
  /* ����EEPROM��ַ0x1000 + addr �������� */
  data = FLASH_ReadByte(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS + addr);
return data;  //���ض�ȡ��������
}


void Flash_Read_Date(uint8_t addr, u8 *buffer,u8 length)
{
  while(length--){
    
   *buffer++ = Flash_Read_Byte(addr++);
  }
  
}


