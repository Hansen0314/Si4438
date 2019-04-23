#include "include.h"


//���巢�ͻ������ͽ��ջ�����
u8 RfTxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
u8 RfRxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
#define No_ECard_Mode 0
bool IDFlag = TRUE;

u8 bRF_IT_Status=0;//�ж�״̬
u8 Send_Ok=0;      //������ɱ�ʶ
U8 ucPackLgth;//���յ������ݳ���
U8 rssi=0;    //�ź�ǿ��
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

void RTC_Config(void)
{
        //CLK_LSEConfig(CLK_LSE_ON);
        CLK_LSICmd(ENABLE);//ʹ��LSI
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTCʱ���ſ�ʹ��
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//RTCʱ��ԴLSI��1��Ƶ=38K
        while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);//�ȴ�LSI����
        
        RTC_WakeUpCmd(DISABLE);
        
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//38K/16=2.375k=0.421ms
       // RTC_ITConfig(RTC_IT_WUT, ENABLE);//�����ж�
        RTC_SetWakeUpCounter(2375);//2375*0,421=1S����
        
        
        enableInterrupts();
}

void openRelay1(u8 number){
  switch(number){
    case 1:Relay_1_ON;
      break;
    case 2:Relay_2_ON;
      break;
    case 3:Relay_3_ON;
      break;
    case 4:Relay_4_ON;
      break;
    case 5:Relay_5_ON;
      break;
    case 6:Relay_6_ON;
      break;
    case 7:Relay_7_ON;
      break;
    case 8:Relay_8_ON;
      break;
  
  }
}
/*******************************************************************************
****����˵����������
****��ڲ���:��
****���ڲ���:��
****������ע:����S2���������ݣ������ӵ�LED����������������󱾰���LED��Ϩ��
             ���յ����ͷ����͵�����LED D2����˸һ��
********************************************************************************/
void main(void)
{
    PWR_FastWakeUpCmd(ENABLE);  //���ٻ���ʹ��
    RTC_Config();
   
    InitIIC();
    InitFlash();
    
   // PWR_UltraLowPowerCmd(ENABLE);//���͹���
#if No_ECard_Mode
    
    FlashBuf[0] = 0xaa;
    FlashBuf[1] = 0x19;
    FlashBuf[2] = 0x03;
    FlashBuf[3] = 0x00;
    FlashBuf[4] = 0x02;
    FlashBuf[5] = 0x02;
    FlashBuf[6] = 0xff;
    FlashBuf[7] = 0xfF; 
   

    //IIC_24c02_Write_Date(0x04,FlashBuf,8);
#else
    IIC_24c02_Read_Date(0x04,C02_Buf,8);
    Flash_Read_Date(0x04,FlashBuf,8);
    
    if((C02_Buf[0] != 0xAA) || (C02_Buf[1] == 0xFF)){//24c02����
      if((FlashBuf[0] == 0) || (FlashBuf[1] == 0) || (FlashBuf[2] == 0xff)){
          IDFlag = FALSE;
      }else{
          IDFlag = TRUE;
      }
    }else{
      if((FlashBuf[0] == C02_Buf[0]) & (FlashBuf[1] == C02_Buf[1]) & (FlashBuf[2] == C02_Buf[2])
         & (FlashBuf[3] == C02_Buf[3])& (FlashBuf[4] == C02_Buf[4])& (FlashBuf[5] == C02_Buf[5])
           & (FlashBuf[6] == C02_Buf[6])& (FlashBuf[7] == C02_Buf[7])){
          
      }else{
        
         Flash_Write_Date(0x04,C02_Buf,8);
         Flash_Read_Date(0x04,FlashBuf,8);
      }
      IDFlag = TRUE;
    }
#endif   
    
    ChannelNumber = FlashBuf[5];
    
                                              //�ر�LED
    MCU_PinInit();//��Ƭ����ģ��Ľӿڳ�ʼ��
    vRadio_Init();//ģ���ʼ��,Ĭ�Ͽ�������9600
    //vRadio_Set_Rate(4);//�������ÿ������ʣ��շ�˫������������Ҫ��ͬ
    vRadio_StartRX(ChannelNumber,RfRxSize);//����ģʽ	
     //RTC_WakeUpCmd(ENABLE);//RTC����ʹ��
    LED_RELAY_GPIO_Init();
    TIM_4_Init();

    
    while(1)
    {   
      
      
    }
  
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
