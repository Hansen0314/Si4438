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
#define LED_RED_PORT  GPIOC
#define LED_RED_PINS  GPIO_Pin_4

#define LED_OFF      GPIO_SetBits(LED_RED_PORT,LED_RED_PINS)
#define LED_ON       GPIO_ResetBits(LED_RED_PORT,LED_RED_PINS)

//继电器端口   
#define Relay_1_PORT  GPIOD
#define Relay_1_PINS  GPIO_Pin_0   
#define Relay_2_PORT  GPIOC
#define Relay_2_PINS  GPIO_Pin_5   
#define Relay_3_PORT  GPIOC
#define Relay_3_PINS  GPIO_Pin_6   
#define Relay_4_PORT  GPIOB
#define Relay_4_PINS  GPIO_Pin_3   
#define Relay_5_PORT  GPIOB
#define Relay_5_PINS  GPIO_Pin_1   
#define Relay_6_PORT  GPIOB
#define Relay_6_PINS  GPIO_Pin_0   
#define Relay_7_PORT  GPIOA
#define Relay_7_PINS  GPIO_Pin_3   
#define Relay_8_PORT  GPIOA
#define Relay_8_PINS  GPIO_Pin_2      
   

#define Relay_1_OFF      GPIO_ResetBits(Relay_1_PORT,Relay_1_PINS)  //南
#define Relay_1_ON       GPIO_SetBits(Relay_1_PORT,Relay_1_PINS)
#define Relay_2_OFF      GPIO_ResetBits(Relay_2_PORT,Relay_2_PINS)  //上
#define Relay_2_ON       GPIO_SetBits(Relay_2_PORT,Relay_2_PINS);
#define Relay_3_OFF      GPIO_ResetBits(Relay_3_PORT,Relay_3_PINS)  //下
#define Relay_3_ON       GPIO_SetBits(Relay_3_PORT,Relay_3_PINS);
#define Relay_4_OFF      GPIO_ResetBits(Relay_4_PORT,Relay_4_PINS)  //停
#define Relay_4_ON       GPIO_SetBits(Relay_4_PORT,Relay_4_PINS);
#define Relay_5_OFF      GPIO_ResetBits(Relay_5_PORT,Relay_5_PINS)  //开
#define Relay_5_ON       GPIO_SetBits(Relay_5_PORT,Relay_5_PINS);
#define Relay_6_OFF      GPIO_ResetBits(Relay_6_PORT,Relay_6_PINS)  //东
#define Relay_6_ON       GPIO_SetBits(Relay_6_PORT,Relay_6_PINS);
#define Relay_7_OFF      GPIO_ResetBits(Relay_7_PORT,Relay_7_PINS)  //北
#define Relay_7_ON       GPIO_SetBits(Relay_7_PORT,Relay_7_PINS);
#define Relay_8_OFF      GPIO_ResetBits(Relay_8_PORT,Relay_8_PINS)  //西
#define Relay_8_ON       GPIO_SetBits(Relay_8_PORT,Relay_8_PINS);

#define Relay_1_OPEN     GPIO_ReadOutputDataBit(Relay_1_PORT,Relay_1_PINS)
#define Relay_2_OPEN     GPIO_ReadOutputDataBit(Relay_2_PORT,Relay_2_PINS)
#define Relay_3_OPEN     GPIO_ReadOutputDataBit(Relay_3_PORT,Relay_3_PINS)
#define Relay_4_OPEN     GPIO_ReadOutputDataBit(Relay_4_PORT,Relay_4_PINS)
#define Relay_5_OPEN     GPIO_ReadOutputDataBit(Relay_5_PORT,Relay_5_PINS)
#define Relay_6_OPEN     GPIO_ReadOutputDataBit(Relay_6_PORT,Relay_6_PINS)
#define Relay_7_OPEN     GPIO_ReadOutputDataBit(Relay_7_PORT,Relay_7_PINS)
#define Relay_8_OPEN     GPIO_ReadOutputDataBit(Relay_8_PORT,Relay_8_PINS)


/********************函数引用*******************/
void LED_RELAY_GPIO_Init(void); 
void LED_RED_ON(void);
void LED_RED_OFF(void);
void TIM_4_Init(void);



         

#endif //_RADIO_HAL_H_
