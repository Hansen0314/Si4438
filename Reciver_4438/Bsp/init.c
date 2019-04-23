/****************************************Copyright (c)****************************************************
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:         
*********************************************************************************************************/


#include "init.h"  
  
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：初始化LED继电器GPIO
*******************************************************************************/
void LED_RELAY_GPIO_Init(void)
{
   GPIO_Init(LED_RED_PORT,LED_RED_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
   
   
   GPIO_Init(Relay_1_PORT,Relay_1_PINS,GPIO_Mode_Out_PP_Low_Fast);//初始化端口
   GPIO_Init(Relay_2_PORT,Relay_2_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_3_PORT,Relay_3_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_4_PORT,Relay_4_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_5_PORT,Relay_5_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_6_PORT,Relay_6_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_7_PORT,Relay_7_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_8_PORT,Relay_8_PINS,GPIO_Mode_Out_PP_Low_Fast);
  

}  
  
  
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：点亮LED
*******************************************************************************/
void LED_RED_ON(void)
{
   GPIO_ResetBits(LED_RED_PORT,LED_RED_PINS);
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：熄灭LED
*******************************************************************************/
void LED_RED_OFF(void)
{
  GPIO_SetBits(LED_RED_PORT,LED_RED_PINS);
}


/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：熄灭LED
*******************************************************************************/
void TIM_4_Init(void)
{

  TIM4_DeInit();
  CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //使能外设时钟，STM8L外设时钟默认关闭，使用前需使能
  
  TIM4_TimeBaseInit(TIM4_Prescaler_256, 0x9C);//16M/8/128=15.625K，0xff=255,255*（1/15.625）=0.01632S，大约61次中断是1S
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);//向上溢出中断使能，中断向量号25
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_SetCounter(0);
  TIM4_Cmd(ENABLE);//TIM4使能
  
  enableInterrupts();//开启中断总开关
}








