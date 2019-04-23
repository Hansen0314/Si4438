/*
 * File:
 *  radio_hal.h
 *
 * Description:
 *  This file contains RADIO HAL.
 *
 * Silicon Laboratories Confidential
 * Copyright 2011 Silicon Laboratories, Inc.
 */

#ifndef _COMMAND_H_
#define _COMMAND_H_

/********************������*******************/

#include "stm8l15x.h"//STM8L051/151��ϵ�й��ÿ⺯��
#include "include.h"

/********************�궨��*******************/
   

//����LED�˿�
   
   
 /********************��������*******************/
extern U8 Command_1;
extern U8 Command_2;
extern U8 Command_3;
extern U8 Command_4;
extern U8 Command_5;
extern U8 Command_6;
extern U8 Command_7;
extern U8 Command_8;
extern U8 CheckData;

extern U8 ChannelNumber;
extern u8 RfRxSize;

extern U8 FlashBuf[8];

extern U8 C02_Buf[8];

/********************��������*******************/


   


         

#endif //_RADIO_HAL_H_
