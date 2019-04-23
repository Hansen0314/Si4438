#include "include.h"


//定义发送缓冲区和接收缓冲区
u8 RfTxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
u8 RfRxBuffer[RADIO_MAX_PACKET_LENGTH] = {0};
#define No_ECard_Mode 0
bool IDFlag = TRUE;

u8 bRF_IT_Status=0;//中断状态
u8 Send_Ok=0;      //发送完成标识
U8 ucPackLgth;//接收到的数据长度
U8 rssi=0;    //信号强度
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

void RTC_Config(void)
{
        //CLK_LSEConfig(CLK_LSE_ON);
        CLK_LSICmd(ENABLE);//使能LSI
        CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);//RTC时钟门控使能
        CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//RTC时钟源LSI，1分频=38K
        while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);//等待LSI就绪
        
        RTC_WakeUpCmd(DISABLE);
        
        RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//38K/16=2.375k=0.421ms
       // RTC_ITConfig(RTC_IT_WUT, ENABLE);//开启中断
        RTC_SetWakeUpCounter(2375);//2375*0,421=1S左右
        
        
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
****函数说明：主函数
****入口参数:无
****出口参数:无
****函数备注:按键S2，发送数据，本板子的LED被点亮，按键弹起后本板子LED会熄灭；
             接收到发送方发送的数据LED D2会闪烁一次
********************************************************************************/
void main(void)
{
    PWR_FastWakeUpCmd(ENABLE);  //快速唤醒使能
    RTC_Config();
   
    InitIIC();
    InitFlash();
    
   // PWR_UltraLowPowerCmd(ENABLE);//超低功耗
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
        
         Flash_Write_Date(0x04,C02_Buf,8);
         Flash_Read_Date(0x04,FlashBuf,8);
      }
      IDFlag = TRUE;
    }
#endif   
    
    ChannelNumber = FlashBuf[5];
    
                                              //关闭LED
    MCU_PinInit();//单片机与模块的接口初始化
    vRadio_Init();//模块初始化,默认空中速率9600
    //vRadio_Set_Rate(4);//可以设置空中速率，收发双方空中速率需要相同
    vRadio_StartRX(ChannelNumber,RfRxSize);//接收模式	
     //RTC_WakeUpCmd(ENABLE);//RTC唤醒使能
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
