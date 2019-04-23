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
****������ע������ȷ��ʱ����
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****��ڲ�������
****���ڲ�������
****������ע����ʼ��LED�̵���GPIO
*******************************************************************************/
void LED_GPIO_Init(void)
{
   GPIO_Init(LED_RED_PORT,LED_RED_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
   GPIO_Init(LED_G_PORT,LED_G_PINS,GPIO_Mode_Out_PP_High_Slow);//��ʼ��LED�˿�
}  
  
/*******************************************************************************
****��ڲ�������
****���ڲ�������
****������ע������LED
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****��ڲ�������
****���ڲ�������
****������ע��Ϩ��LED
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
****��ڲ�������
****���ڲ�������
****������ע��LED
****��Ȩ��Ϣ������Ƕ��ʽϵͳ
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
   GPIO_Init(KEY_H1_PORT,KEY_H1_PINS,GPIO_Mode_Out_PP_High_Fast);    //��ʼ�������˿ڣ�
   GPIO_Init(KEY_H2_PORT,KEY_H2_PINS,GPIO_Mode_Out_PP_High_Fast);    //��ʼ�������˿ڣ�
   
   GPIO_Init(KEY_L1_PORT,KEY_L1_PINS,GPIO_Mode_In_PU_No_IT);    //��ʼ�������˿ڣ����������ж�
   GPIO_Init(KEY_L2_PORT,KEY_L2_PINS,GPIO_Mode_In_PU_No_IT);    //��ʼ�������˿ڣ����������ж�
   GPIO_Init(KEY_L3_PORT,KEY_L3_PINS,GPIO_Mode_In_PU_No_IT);    //��ʼ�������˿ڣ����������ж�
   GPIO_Init(KEY_L4_PORT,KEY_L4_PINS,GPIO_Mode_In_PU_No_IT);    //��ʼ�������˿ڣ����������ж�
   
   GPIO_Init(KEY_PORT,KEY_PINS,GPIO_Mode_In_PU_No_IT);
} 















