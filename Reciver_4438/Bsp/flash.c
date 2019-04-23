/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/
#include "stm8l15x.h"
#include "flash.h"
/*******************************************************************************
****函数名称:IIC初始化函数
****函数功能:
****版本:V1.0
****日期:14-2-2014
****入口参数:无
****出口参数:无
****说明:
********************************************************************************/
void InitFlash(void)
{
  FLASH_DeInit();
  /* 定义FLASH编程时间 */
  FLASH_SetProgrammingTime(FLASH_ProgramTime_Standard);
  /* 解锁EEPROM */
  FLASH_Unlock(FLASH_MemType_Data);
  /* 等待解锁完成 */
  while(FLASH_GetFlagStatus(FLASH_FLAG_DUL)== RESET);
}


void Flash_Write_Byte(uint8_t addr, uint8_t data)
{
  /* 往EEPROM地址0x1000 + addr 处写入数据 */
  FLASH_ProgramByte(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS + addr, data);
  /* 等待写入完成 */
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
  /* 读出EEPROM地址0x1000 + addr 处的数据 */
  data = FLASH_ReadByte(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS + addr);
return data;  //返回读取到的数据
}


void Flash_Read_Date(uint8_t addr, u8 *buffer,u8 length)
{
  while(length--){
    
   *buffer++ = Flash_Read_Byte(addr++);
  }
  
}


