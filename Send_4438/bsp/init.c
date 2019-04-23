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
****函数备注：不精确延时函数
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
} 

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：初始化LED继电器GPIO
*******************************************************************************/
void LED_GPIO_Init(void)
{
   GPIO_Init(LED_RED_PORT,LED_RED_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
   GPIO_Init(LED_G_PORT,LED_G_PINS,GPIO_Mode_Out_PP_High_Slow);//初始化LED端口
}  
  
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：点亮LED
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void LED_RED_ON(void)
{
   GPIO_ResetBits(LED_RED_PORT,LED_RED_PINS);
}

void LED_G_ON(void)
{
   GPIO_ResetBits(LED_G_PORT,LED_G_PINS);
}
/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：熄灭LED
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void LED_RED_OFF(void)
{
  GPIO_SetBits(LED_RED_PORT,LED_RED_PINS);
}
void LED_G_OFF(void)
{
  GPIO_SetBits(LED_G_PORT,LED_G_PINS);
}

/*******************************************************************************
****入口参数：无
****出口参数：无
****函数备注：LED
****版权信息：蓝旗嵌入式系统
*******************************************************************************/
void LED_Work_OFF(void)
{
  LED_RED_OFF();
  LED_G_OFF();
}
void LED_Work_ON(bool isSUCCESS)
{
   if(isSUCCESS){
    LED_RED_OFF();
    LED_G_ON();
    
  }else{
    
    LED_G_OFF();
    LED_RED_ON();
    
  }
}



void LED_G_S(void)
{
  GPIO_ToggleBits(LED_G_PORT,LED_G_PINS);
}


void Key_Init(void)
{ 
   GPIO_Init(KEY_H1_PORT,KEY_H1_PINS,GPIO_Mode_Out_PP_High_Fast);    //初始化按键端口，
   GPIO_Init(KEY_H2_PORT,KEY_H2_PINS,GPIO_Mode_Out_PP_High_Fast);    //初始化按键端口，
   
   GPIO_Init(KEY_L1_PORT,KEY_L1_PINS,GPIO_Mode_In_PU_No_IT);    //初始化按键端口，带上拉无中断
   GPIO_Init(KEY_L2_PORT,KEY_L2_PINS,GPIO_Mode_In_PU_No_IT);    //初始化按键端口，带上拉无中断
   GPIO_Init(KEY_L3_PORT,KEY_L3_PINS,GPIO_Mode_In_PU_No_IT);    //初始化按键端口，带上拉无中断
   GPIO_Init(KEY_L4_PORT,KEY_L4_PINS,GPIO_Mode_In_PU_No_IT);    //初始化按键端口，带上拉无中断
   
   GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);
} 















