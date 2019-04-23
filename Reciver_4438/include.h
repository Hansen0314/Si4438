#ifndef _include_H
#define _include_H

#include "stm8l15x.h"//STM8L051/151等系列共用库函数

#include "443x//si446x_api_lib.h"
#include "443x//radio.h"
#include "443x//radio_config.h"
#include "443x//radio_hal.h"
#include "443x//rate_config.h"
#include "443x//si446x_cmd.h"
#include "443x//si446x_patch.h"
#include "443x//radio_comm.h"
#include "bsp//init.h"
#include "bsp//command.h"
#include "bsp//24c0x.h"
#include "bsp//flash.h"

extern u8 RfRxBuffer[RADIO_MAX_PACKET_LENGTH];
extern U8 ucPackLgth;//接收到的数据长度
extern U8 rssi;    //信号强度

#define NOP()                 asm("nop")



#endif
