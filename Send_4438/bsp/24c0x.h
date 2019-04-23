#ifndef _iic_h_
#define _iic_h_
/*******************************************************************************
****����Ƕ��ʽϵͳ STM8S105 EasyKit
****LENCHIMCU.TAOBAO.COM
****�汾:V1.0
****����:14-2-2014
****˵��:��оƬSTM8S105C4T6
********************************************************************************/
#define IICSPEED 100000       //100K�ٶȣ�ʱ���ٶ�����1M��400K�ٶȣ�ʱ���ٶ�����4M
#define I2C1_SLAVE_ADDRESS7    0xA0
#define EEPROM_BASE_ADDRESS    0x00
#define EEPROM_Page_Byte_Size  8   /*EEPROM ÿҳ���д8Byte*/
#define EEPROM_ADDRESS         0xA0
extern void InitIIC(void);
extern void EEPROM_WriteData(unsigned char *buffer,unsigned char addr,unsigned char num);
extern void EEPROM_ReadData(unsigned char *buffer,unsigned char addr,unsigned char num);
extern void EEPROM_WriteOnePage(unsigned char *buffer,unsigned char addr,unsigned char num);
extern void IIC_24c02_Write_Date(uint8_t addr, u8 *buffer,u8 length);
extern void IIC_24c02_Read_Date(uint8_t addr, u8 *buffer,u8 length);

#endif