/****************************************Copyright (c)****************************************************
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:         
*********************************************************************************************************/


#include "init.h"  
  
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע����ʼ��LED�̵���GPIO
*******************************************************************************/
void LED_RELAY_GPIO_Init(void)
{
   GPIO_Init(LED_RED_PORT,LED_RED_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
   
   
   GPIO_Init(Relay_1_PORT,Relay_1_PINS,GPIO_Mode_Out_PP_Low_Fast);//��ʼ���˿�
   GPIO_Init(Relay_2_PORT,Relay_2_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_3_PORT,Relay_3_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_4_PORT,Relay_4_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_5_PORT,Relay_5_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_6_PORT,Relay_6_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_7_PORT,Relay_7_PINS,GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(Relay_8_PORT,Relay_8_PINS,GPIO_Mode_Out_PP_Low_Fast);
  

}  
  
  
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������LED
*******************************************************************************/
void LED_RED_ON(void)
{
   GPIO_ResetBits(LED_RED_PORT,LED_RED_PINS);
}

/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��Ϩ��LED
*******************************************************************************/
void LED_RED_OFF(void)
{
  GPIO_SetBits(LED_RED_PORT,LED_RED_PINS);
}


/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע��Ϩ��LED
*******************************************************************************/
void TIM_4_Init(void)
{

  TIM4_DeInit();
  CLK_PeripheralClockConfig (CLK_Peripheral_TIM4,ENABLE); //ʹ������ʱ�ӣ�STM8L����ʱ��Ĭ�Ϲرգ�ʹ��ǰ��ʹ��
  
  TIM4_TimeBaseInit(TIM4_Prescaler_256, 0x9C);//16M/8/128=15.625K��0xff=255,255*��1/15.625��=0.01632S����Լ61���ж���1S
  TIM4_ITConfig(TIM4_IT_Update, ENABLE);//��������ж�ʹ�ܣ��ж�������25
  TIM4_ARRPreloadConfig(ENABLE);
  TIM4_SetCounter(0);
  TIM4_Cmd(ENABLE);//TIM4ʹ��
  
  enableInterrupts();//�����ж��ܿ���
}








