
#include "include.h"



bool isSuccess = FALSE;
bool IDFlag = TRUE;
bool KeyFlag = FALSE;
bool isOpen = FALSE;
#define No_ECard_Mode 1
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
    if(KEY_L3_Read() == 0){
        Delay(5000);
        if(KEY_L3_Read() == 0){
          RfTxBuffer[5]=Command_5;
          if(keyVaule == 0)
          isSuccess = KeyFlag;
          
          LED_Work_ON(isSuccess);
          if(isSuccess)
          vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
          if(!isOpen){
            
            isOpen = TRUE;
          }
        }
    }
    if(KEY_L4_Read() == 0){
        Delay(5000);
        if(KEY_L4_Read() == 0){
            return 4;
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
        RTC_ITConfig(RTC_IT_WUT, ENABLE);//�����ж�
        RTC_SetWakeUpCounter(25);//25*0,421=10MS����

        //ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_3);//���ȼ�
        
        enableInterrupts();
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
    FlashBuf[7] = 0xfe;   
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
    
    RTC_ITConfig(RTC_IT_WUT, ENABLE);//���Ѷ�ʱ���ж�ʹ��
    RTC_WakeUpCmd(ENABLE);//RTC����ʹ��    
   
    
   LED_Work_OFF();
   LED_G_ON();
   KeyFlag = KEY_OPEN;
   while(1)
   {      
      if(Weak_Up)
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
        switch(keyScan()){
            case 0:
                //halt();
                break;
            case 1:     
              
  //               LED_Work_ON(isSuccess);
  //               RfTxBuffer[5]=Command_1;
  //               if(isSuccess)
  //               vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);  
                  break;
            case 2:
  //                LED_Work_ON(isSuccess);
  //                RfTxBuffer[5]=Command_2;
  //                if(isSuccess)
  //                vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                  
                break;
            case 3:
  //                LED_Work_ON(isSuccess);
  //                RfTxBuffer[5]=Command_3;
  //                if(isSuccess)
  //                vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                  
                break;
            case 4:
                  RfTxBuffer[5]=Command_4;
                  isSuccess = FALSE;
                  LED_Work_ON(isSuccess);
                  isOpen = FALSE;
                  vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                break;
            case 5:
              
                  RfTxBuffer[5]=Command_5;
                  if(keyVaule == 0)
                  isSuccess = KeyFlag;
                  
                  LED_Work_ON(isSuccess);
                  if(isSuccess)
                  vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                  if(!isOpen){
                    
                    isOpen = TRUE;
                  }
                  
                break; 
            case 6:
  //                LED_Work_ON(isSuccess);
  //                RfTxBuffer[5]=Command_6;
  //                if(isSuccess)
  //                vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                 
                break;
            case 7:
  //                LED_Work_ON(isSuccess);
  //                RfTxBuffer[5]=Command_7;
  //                if(isSuccess)
  //                vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                 
                break;
            case 8:
  //                LED_Work_ON(isSuccess);
  //                RfTxBuffer[5]=Command_8;
  //                if(isSuccess)
  //                vRadio_StartTx_Variable_Packet(ChannelNumber, &RfTxBuffer[0],RfTxSize);
                 
                break;
        }
        Delay(0xff);
        LED_G_OFF();
        LED_RED_OFF();
        Weak_Up = FALSE;
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
