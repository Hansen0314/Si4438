
#include "include.h"



bool isSuccess = FALSE;
bool IDFlag = TRUE;
bool KeyFlag = FALSE;
bool isOpen = FALSE;
#define No_ECard_Mode 0
U8 ChannelNumber = 0;
//定义发送缓冲区和接收缓冲区
u8 RfTxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
u8 RfRxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};

u8 RfTxSize = 15;

u8 bRF_IT_Status=0;//中断状态
u8 Send_Ok=0;      //发送完成标识
U8 ucPackLgth;//接收到的数据长度
U8 rssi=0;    //信号强度
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
        CLK_LSICmd(ENABLE);//使能LSI
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟门控使能
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//RTC时钟源LSI，1分频=38K
        while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);//等待LSI就绪
        
        RTC_WakeUpCmd(DISABLE);
        
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//38K/16=2.375k=0.421ms
        //RTC_ITConfig(RTC_IT_WUT, ENABLE);//开启中断
        RTC_SetWakeUpCounter(2000);//2000*0,421=842MS左右

        //ITC_SetSoftwarePriority(RTC_CSSLSE_IRQn, ITC_PriorityLevel_3);//优先级
        
        enableInterrupts();
        RTC_WakeUpCmd(ENABLE);
}
/*******************************************************************************
****函数说明：主函数
****入口参数:无
****出口参数:无
****函数备注:按键S2，发送数据，本板子的LED被点亮，按键弹起后本板子LED会熄灭；
             接收到发送方发送的数据LED D2会闪烁一次
********************************************************************************/
void main(void)
{
     int i;
   for(i = 0;i < 1000;i++)
   Delay(0xff);
   
    
    LED_GPIO_Init();
    RTC_Config();
    PWR_FastWakeUpCmd(ENABLE);  //快速唤醒使能
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
    
    if((C02_Buf[0] != 0xAA) || (C02_Buf[1] == 0xFF)){//24c02错误
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
  
  RfTxBuffer[0] = FlashBuf[0];//第一位起始位0XAA
  RfTxBuffer[1] = FlashBuf[1];// 1-4位 ID位
  RfTxBuffer[2] = FlashBuf[2];
  RfTxBuffer[3] = FlashBuf[3];
  RfTxBuffer[4] = FlashBuf[4];
                                //第五位 命令位
  RfTxBuffer[6] = FlashBuf[6];//第六位 奈跳
  RfTxBuffer[7] = FlashBuf[7];//第六位 奈跳  某位为0则算作长按
  
   //RfTxBuffer[7] = 0xfc;//第六位 奈跳
   Key_Init();
   MCU_PinInit();//单片机与模块的接口初始化
   vRadio_Init();//模块初始化,默认空中速率9600
   //vRadio_Set_Rate(4);//可以设置空中速率，收发双方空中速率需要相同
   vRadio_StartRX(ChannelNumber,9);//接收模式	
  
   PWR_UltraLowPowerCmd(ENABLE);//超低功耗
    
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
        MCU_PinInit();//单片机与模块的接口初始化
        vRadio_Init();//模块初始化,默认空中速率9600
        //vRadio_Set_Rate(4);//可以设置空中速率，收发双方空中速率需要相同
        vRadio_StartRX(ChannelNumber,9);//接收模式
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
        //磁铁拿起和放下都可以将继电器关机
        
        KeyFlag = KEY_OPEN;
        
        //2 3 6 8
        //4 5 1 7
        //上 下 东 西
        //停 开 南 北
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
