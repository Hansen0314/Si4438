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

#ifndef _INIT_H_
#define _INIT_H_

/********************库引用*******************/

#include "stm8l15x.h"//STM8L051/151等系列共用库函数


/********************宏定义*******************/



//定义LED端口
//定义LED端口
#define LED_RED_PORT  GPIOA
#define LED_RED_PINS  GPIO_Pin_2
#define LED_G_PORT  GPIOA
#define LED_G_PINS  GPIO_Pin_3

//按键端口   
#define KEY_H1_PORT  GPIOC
#define KEY_H1_PINS  GPIO_Pin_6
#define KEY_H2_PORT  GPIOD
#define KEY_H2_PINS  GPIO_Pin_0
   
#define KEY_H1_Set()    GPIO_SetBits(KEY_H1_PORT,KEY_H1_PINS)
#define KEY_H1_Reset()  GPIO_ResetBits(KEY_H1_PORT,KEY_H1_PINS)   
#define KEY_H2_Set()    GPIO_SetBits(KEY_H2_PORT,KEY_H2_PINS)
#define KEY_H2_Reset()  GPIO_ResetBits(KEY_H2_PORT,KEY_H2_PINS)   
   
   
#define KEY_L1_PORT  GPIOB
#define KEY_L1_PINS  GPIO_Pin_0
#define KEY_L2_PORT  GPIOB
#define KEY_L2_PINS  GPIO_Pin_1
#define KEY_L3_PORT  GPIOB
#define KEY_L3_PINS  GPIO_Pin_2
#define KEY_L4_PORT  GPIOB
#define KEY_L4_PINS  GPIO_Pin_3
   
#define KEY_L1_Read()  GPIO_ReadInputDataBit(KEY_L1_PORT,KEY_L1_PINS)
#define KEY_L2_Read()  GPIO_ReadInputDataBit(KEY_L2_PORT,KEY_L2_PINS)
#define KEY_L3_Read()  GPIO_ReadInputDataBit(KEY_L3_PORT,KEY_L3_PINS)
#define KEY_L4_Read()  GPIO_ReadInputDataBit(KEY_L4_PORT,KEY_L4_PINS)
   
#define KEY_H1_Read()  GPIO_ReadOutputDataBit(KEY_H1_PORT,KEY_H1_PINS)
#define KEY_H2_Read()  GPIO_ReadOutputDataBit(KEY_H2_PORT,KEY_H2_PINS)
   
#define KEY_PORT  GPIOC
#define KEY_PINS  GPIO_Pin_4
   
#define KEY_OPEN  (bool)(GPIO_ReadInputDataBit(KEY_PORT,KEY_PINS) == 0)

/********************函数引用*******************/
void Delay(__IO uint16_t nCount); 
void LED_GPIO_Init(void); 
void LED_RED_ON(void); 
void LED_RED_OFF(void); 
void LED_G_ON(void); 
void LED_G_OFF(void); 
void Key_Init(void); 
void LED_Work_OFF(void);
void LED_Work_ON(bool isSUCCESS);


         

#endif //_RADIO_HAL_H_
