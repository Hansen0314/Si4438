#ifndef _flash_h_
#define _flash_h_
/*******************************************************************************
****蓝旗嵌入式系统 STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****版本:V1.0
****日期:14-2-2014
****说明:主芯片STM8S105C4T6
********************************************************************************/

extern void InitFlash(void);
extern void Flash_Write_Date(uint8_t addr, u8 *buffer,u8 length);
extern void Flash_Read_Date(uint8_t addr, u8 *buffer,u8 length);

#endif