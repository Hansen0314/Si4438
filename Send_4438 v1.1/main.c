
#include "include.h"



bool isSuccess = FALSE;
bool IDFlag = TRUE;
bool KeyFlag = FALSE;
bool isOpen = FALSE;
#define No_ECard_Mode 0
U8 ChannelNumber = 0;
//���巢�ͻ������ͽ��ջ�����
u8 RfTxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
u8 RfRxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};

u8 RfTxSize = 15;

u8 bRF_IT_Status=0;//�ж�״̬
u8 Send_Ok=0;      //������ɱ�ʶ
U8 ucPackLgth;//���յ������ݳ���
U8 rssi=0;    //�ź�ǿ��
u8 keyVaule;


u8 keyScan(){
    
    keyVaule = 0;
    KEY_H1_Set();
    KEY_H2_Reset();

    if(KEY_L1_Read() == 0){
        Delay(5000);
        if(KEY_L1_Read() == 0){
          keyVaule = 8;
          LED_Work_ON(isSuccess);          
          RfTxBuffer[5]=Command_8;
         if(isSuccess)
         vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);  
        }
    }
    if(KEY_L2_Read() == 0){
        Delay(5000);
        if(KEY_L2_Read() == 0){
          keyVaule = 8;
          LED_Work_ON(isSuccess);
          RfTxBuffer[5]=Command_6;
          if(isSuccess)
          vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);          
        }
    }
    if(KEY_L3_Read() == 0){
        keyVaule = 3;
        Delay(5000);
        if(KEY_L3_Read() == 0){
            //return 3;
          keyVaule = 3;
          LED_Work_ON(isSuccess);
          RfTxBuffer[5]=Command_3;
          if(isSuccess)
          vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);          
        }
    }
    if(KEY_L4_Read() == 0){
        Delay(5000);
        if(KEY_L4_Read() == 0){    
          keyVaule = 8;
          LED_Work_ON(isSuccess);
          RfTxBuffer[5]=Command_2;    
          if(isSuccess)
          vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);  
        }
    }
    KEY_H1_Reset();
    KEY_H2_Set();
    
    if(KEY_L1_Read() == 0){
        Delay(5000);
        if(KEY_L1_Read() == 0){
           keyVaule = 1;
           LED_Work_ON(isSuccess);
           RfTxBuffer[5]=Command_7;
           if(isSuccess)
           vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);     
        }
    }
    if(KEY_L2_Read() == 0){
        Delay(5000);
        if(KEY_L2_Read() == 0){
//            return 1;
           keyVaule = 1;
           LED_Work_ON(isSuccess);
           RfTxBuffer[5]=Command_1;
           if(isSuccess)
           vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);             
        }
    }
    if(KEY_L4_Read() == 0){
        Delay(5000);
        if(KEY_L4_Read() == 0){
            keyVaule = 1;
            RfTxBuffer[5]=Command_4;
            isSuccess = FALSE;
            LED_Work_ON(isSuccess);
            isOpen = FALSE;
            vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
        }
    }    
    if(KEY_OPEN_Read() == 0){
        Delay(5000);
        if(KEY_OPEN_Read() == 0){
          RfTxBuffer[5]=Command_5;
          if(keyVaule == 0)
          isSuccess = KeyFlag;
          keyVaule = 1;
          LED_Work_ON(isSuccess);
          if(isSuccess)
          vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
          if(!isOpen){
            
            isOpen = TRUE;
          }
        }
    }

    
    return keyVaule;
    
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
        //RTC_ITConfig(RTC_IT_WUT, ENABLE);//�����ж�
        RTC_SetWakeUpCounter(2000);//2000*0,421=842MS����

        //ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_3);//���ȼ�
        
        enableInterrupts();
        RTC_WakeUpCmd(ENABLE);
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
     int i;
   for(i = 0;i < 1000;i++)
   Delay(0xff);
   
    
    LED_GPIO_Init();
    RTC_Config();
    PWR_FastWakeUpCmd(ENABLE);  //���ٻ���ʹ��
    InitIIC();
    InitFlash();
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
        
         LED_RED_ON();
         Flash_Write_Date(0x04,C02_Buf,8);
         Flash_Read_Date(0x04,FlashBuf,8);
         LED_Work_ON(TRUE);
      }
      IDFlag = TRUE;
    }
#endif
    //Flash_Write_Date(0x04,C02_Buf,8);

  ChannelNumber = FlashBuf[5];//
  
  RfTxBuffer[0] = FlashBuf[0];//��һλ��ʼλ0XAA
  RfTxBuffer[1] = FlashBuf[1];// 1-4λ IDλ
  RfTxBuffer[2] = FlashBuf[2];
  RfTxBuffer[3] = FlashBuf[3];
  RfTxBuffer[4] = FlashBuf[4];
                                //����λ ����λ
  RfTxBuffer[6] = FlashBuf[6];//����λ ����
  RfTxBuffer[7] = FlashBuf[7];//����λ ����  ĳλΪ0����������
  
   //RfTxBuffer[7] = 0xfc;//����λ ����
   Key_Init();
   MCU_PinInit();//��Ƭ����ģ��Ľӿڳ�ʼ��
   vRadio_Init();//ģ���ʼ��,Ĭ�Ͽ�������9600
   //vRadio_Set_Rate(4);//�������ÿ������ʣ��շ�˫������������Ҫ��ͬ
   vRadio_StartRX(ChannelNumber,9);//����ģʽ	
  
   PWR_UltraLowPowerCmd(ENABLE);//���͹���
    
   LED_Work_OFF();
   //LED_G_ON();
   KeyFlag = KEY_OPEN;   
  CLK_PeripheralClockConfig(CLK_Peripheral_I2C1,DISABLE);
  I2C_Cmd(I2C1,DISABLE);
   while(1)
   {    
      if(Weak_Up == 1)
      {
        LED_GPIO_Init();
        RTC_Config();
        Key_Init();
        radio_hal_DeassertShutdown();
        MCU_PinInit();//��Ƭ����ģ��Ľӿڳ�ʼ��
        vRadio_Init();//ģ���ʼ��,Ĭ�Ͽ�������9600
        //vRadio_Set_Rate(4);//�������ÿ������ʣ��շ�˫������������Ҫ��ͬ
        vRadio_StartRX(ChannelNumber,9);//����ģʽ
        Weak_Up = 2;
      } 
      else if(Weak_Up == 2)
      {   
        LED_Work_OFF();
        while(!IDFlag){
          LED_RED_ON();
        };
        
        if((KeyFlag || isSuccess) && (!KEY_OPEN)){
          LED_G_ON();
          RfTxBuffer[5]=Command_4;
          u8 k = 3;
          while(k--){
            vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
            Delay(0xff);
          }
          LED_G_OFF();
          isSuccess = FALSE;
        }
        //��������ͷ��¶����Խ��̵����ػ�
        
        KeyFlag = KEY_OPEN;
        
        //2 3 6 8
        //4 5 1 7
        //�� �� �� ��
        //ͣ �� �� ��
        keyScan();
        if(RTC_GetFlagStatus(RTC_FLAG_WUTF))
        {
          if(keyVaule == 0)
            RTC_Time++;
          else
            RTC_Time = 0;
          if(RTC_Time>20)
          {
            Weak_Up = 0;
            RTC_Time = 0;
          }
          RTC_ClearFlag(RTC_FLAG_WUTF);
        }
        Delay(0xff);
        LED_G_OFF();
        LED_RED_OFF();
        
      }
      else if(Weak_Up == 0)
      {
        Weak_Up = 4;
        //RTC_WakeUpCmd(DISABLE);

        GPIO_DeInit(GPIOA);
        GPIO_DeInit(GPIOB);
        GPIO_DeInit(GPIOC);
        GPIO_DeInit(GPIOD);
        radio_hal_AssertShutdown();
        LED_Work_OFF();
        KEY_H1_Set();
        KEY_H2_Set();
        GPIO_Init(KEY_L1_PORT, KEY_L1_PINS, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_L2_PORT, KEY_L2_PINS, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_L3_PORT, KEY_L3_PINS, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_L4_PORT, KEY_L4_PINS, GPIO_Mode_In_PU_IT);
        GPIO_Init(KEY_OPEN_PORT, KEY_OPEN_PINS, GPIO_Mode_In_PU_IT);
        EXTI_DeInit(); 
        EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling);
        EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Falling);
        EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling);
        EXTI_SetPinSensitivity(EXTI_Pin_3,EXTI_Trigger_Falling);
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, DISABLE);
        CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
        PWR_UltraLowPowerCmd(ENABLE);        
        enableInterrupts();
      }
      else
      {
        halt();
      }
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
