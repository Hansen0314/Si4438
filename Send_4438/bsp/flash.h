#ifndef _flash_h_
#define _flash_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/

extern void InitFlash(void);
extern void Flash_Write_Date(uint8_t addr, u8 *buffer,u8 length);
extern void Flash_Read_Date(uint8_t addr, u8 *buffer,u8 length);

#endif