/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"
#include "include.h"
/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
   // RTC_WakeUpCmd(DISABLE);
  // radio_hal_DeassertShutdown(); //开启433模块电源
  
   RTC_ClearITPendingBit(RTC_IT_WUT);  //清除中断标志
   //RTC_WakeUpCmd(ENABLE);

}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

 
/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */

u8 KeyFlag = 0;
u8 BeforKeyFlag = 0;
u8 KeyFlagBuff = 0;

u8 TIM_Count = 0;

void closAll(u8 flag){
  
  switch(flag){
    case 0: Relay_1_OFF;
            Relay_2_OFF;
            Relay_3_OFF;
            Relay_4_OFF;
            Relay_5_OFF;
            Relay_6_OFF;
            Relay_7_OFF;
            Relay_8_OFF;
            KeyFlag = 0;
      break;
    case 0xff:
            Relay_1_OFF;
            Relay_2_OFF;
            Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
            Relay_6_OFF;
            Relay_7_OFF;
            Relay_8_OFF;
            KeyFlag = 0;
      break;
      case 0xFE:
            Relay_1_OFF;
            //Relay_2_OFF;
            Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
            Relay_6_OFF;
            Relay_7_OFF;
            Relay_8_OFF;
      break;
      case 0xFC:
            Relay_1_OFF;
           // Relay_2_OFF;
           // Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
            Relay_6_OFF;
            Relay_7_OFF;
            Relay_8_OFF;
      break;
      case 0xf8:
            Relay_1_OFF;
            //Relay_2_OFF;
            //Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
           // Relay_6_OFF;
            Relay_7_OFF;
            Relay_8_OFF;
      break;
      case 0xf0:
            Relay_1_OFF;
            //Relay_2_OFF;
            //Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
            //Relay_6_OFF;
            Relay_7_OFF;
            //Relay_8_OFF;
      break;
      case 0xc0:
           // Relay_1_OFF;
            //Relay_2_OFF;
            //Relay_3_OFF;
            //Relay_4_OFF;
            Relay_5_OFF;
           // Relay_6_OFF;
            //Relay_7_OFF;
           // Relay_8_OFF;
      break;
      
  }
  
}

void closRelay(u8 number){
  switch(number){
    case 1:Relay_1_OFF;
      break;
    case 2:Relay_2_OFF;
      break;
    case 3:Relay_3_OFF;
      break;
    case 4:Relay_4_OFF;
      break;
    case 5:Relay_5_OFF;
      break;
    case 6:Relay_6_OFF;
      break;
    case 7:Relay_7_OFF;
      break;
    case 8:Relay_8_OFF;
      break;
  
  }
  
}
void openRelay(u8 number){
  switch(number){
    case 1:Relay_2_OFF;Relay_3_OFF;Relay_5_OFF;Relay_6_OFF;Relay_7_OFF;Relay_8_OFF;Relay_1_ON;
      break;
    case 2:Relay_1_OFF;Relay_3_OFF;Relay_5_OFF;Relay_6_OFF;Relay_7_OFF;Relay_8_OFF;Relay_2_ON;
      break;
    case 3:Relay_2_OFF;Relay_1_OFF;Relay_5_OFF;Relay_6_OFF;Relay_7_OFF;Relay_8_OFF;Relay_3_ON;
      break;
    case 4:Relay_2_OFF;Relay_3_OFF;Relay_5_OFF;Relay_6_OFF;Relay_7_OFF;Relay_8_OFF;Relay_4_ON;
      break;
    case 5:Relay_2_OFF;Relay_3_OFF;Relay_1_OFF;Relay_6_OFF;Relay_7_OFF;Relay_8_OFF;Relay_5_ON;
      break;
    case 6:Relay_2_OFF;Relay_3_OFF;Relay_1_OFF;Relay_7_OFF;Relay_8_OFF;Relay_6_ON;
      break;
    case 7:Relay_2_OFF;Relay_3_OFF;Relay_5_OFF;Relay_6_OFF;Relay_1_OFF;Relay_8_OFF;Relay_7_ON;
      break;
    case 8:Relay_2_OFF;Relay_3_OFF;Relay_5_OFF;Relay_6_OFF;Relay_7_OFF;Relay_1_OFF;Relay_8_ON;
      break;
  
  }
  
}


void Cmd_Flag_Oxff(u8 cmd){
  switch(cmd){
      case 0:closAll(0xff);
        break;
      case 1:if(!Relay_7_OPEN)Relay_1_ON; 
        break;
      case 2:if(!Relay_3_OPEN)Relay_2_ON; 
        break;
      case 3:if(!Relay_2_OPEN)Relay_3_ON; 
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
        Relay_5_ON;
      }else{
        Relay_4_ON;   
      } //设置备用
        break;
      case 6:if(!Relay_8_OPEN)Relay_6_ON; 
        break;
      case 7:if(!Relay_1_OPEN)Relay_7_ON; 
        break;
      case 8:if(!Relay_6_OPEN)Relay_8_ON; 
        break;
  }
}
void Cmd_Flag_Oxfe(u8 cmd){
  switch(cmd){
     case 0:closAll(0xfe);
        break;
      case 1:if(!Relay_7_OPEN)Relay_1_ON; 
        break;
      case 2:if(!Relay_3_OPEN)
            {
                if(Relay_2_OPEN){
                if(BeforKeyFlag != KeyFlag)Relay_2_OFF;
              }else{
                if(BeforKeyFlag != KeyFlag)Relay_2_ON;   
              }
            }
        break;
      case 3:if(!Relay_2_OPEN)Relay_3_ON;   
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
          Relay_5_ON;
        }else{
          Relay_4_ON;   
        } 
        break;
      case 6:if(!Relay_8_OPEN)Relay_6_ON; 
        break;
      case 7:if(!Relay_1_OPEN)Relay_7_ON; 
        break;
      case 8:if(!Relay_6_OPEN)Relay_8_ON; 
        break;
  }
}

void Cmd_Flag_Oxfc(u8 cmd){
  switch(cmd){
      case 0:closAll(0xfc);
        break;
      case 1:if(!Relay_7_OPEN)Relay_1_ON; 
        break;
      case 2:if(!Relay_3_OPEN)if(Relay_2_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_2_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_2_ON;   
        }
        break;
      case 3:if(!Relay_2_OPEN)if(Relay_3_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_3_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_3_ON;   
        }
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
          Relay_5_ON;
        }else{
          Relay_4_ON;   
        } 
        break;
      case 6:if(!Relay_8_OPEN)Relay_6_ON; 
        break;
      case 7:if(!Relay_1_OPEN)Relay_7_ON; 
        break;
      case 8:if(!Relay_6_OPEN)Relay_8_ON; 
        break;
  }
}
void Cmd_Flag_Oxf8(u8 cmd){
  switch(cmd){
      case 0:closAll(0xf8);
        break;
      case 1:if(!Relay_7_OPEN)Relay_1_ON; 
        break;
      case 2:if(!Relay_3_OPEN)if(Relay_2_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_2_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_2_ON;   
        }
        break;
      case 3:if(!Relay_2_OPEN)if(Relay_3_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_3_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_3_ON;   
        }
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
          Relay_5_ON;
        }else{
          Relay_4_ON;   
        } 
        break;
      case 6:if(!Relay_8_OPEN)if(Relay_6_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_6_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_6_ON;   
        }
        break;
      case 7:if(!Relay_1_OPEN)Relay_7_ON; 
        break;
      case 8:if(!Relay_6_OPEN)Relay_8_ON; 
        break;
  }
}
void Cmd_Flag_Oxf0(u8 cmd){
  switch(cmd){
      case 0:closAll(0xf0);
        break;
      case 1:if(!Relay_7_OPEN)Relay_1_ON; 
        break;
      case 2:if(!Relay_3_OPEN)if(Relay_2_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_2_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_2_ON;   
        }
        break;
      case 3:if(!Relay_2_OPEN)if(Relay_3_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_3_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_3_ON;   
        }
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
          Relay_5_ON;
        }else{
          Relay_4_ON;   
        } 
        break;
      case 6:if(!Relay_8_OPEN)if(Relay_6_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_6_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_6_ON;   
        }
        break;
      case 7:if(!Relay_1_OPEN)Relay_7_ON; 
        break;
      case 8:if(!Relay_6_OPEN)if(Relay_8_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_8_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_8_ON;   
        }
        break;
  }
}
void Cmd_Flag_Oxc0(u8 cmd){
  switch(cmd){
      case 0:closAll(0xc0);
        break;
      case 1:if(!Relay_7_OPEN)if(Relay_1_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_1_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_1_ON;   
        }
        break;
      case 2:if(!Relay_3_OPEN)if(Relay_2_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_2_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_2_ON;   
        }
        break;
      case 3:if(!Relay_2_OPEN)if(Relay_3_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_3_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_3_ON;   
        }
        break;
      case 4: closAll(0); KeyFlag = 4;//总开关
        break;
      case 5:if(Relay_4_OPEN){
        if(BeforKeyFlag != KeyFlag)
          Relay_5_ON;
        }else{
          Relay_4_ON;   
        } 
        break;
      case 6:if(!Relay_8_OPEN)if(Relay_6_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_6_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_6_ON;   
        }
        break;
      case 7:if(!Relay_1_OPEN)if(Relay_7_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_7_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_7_ON;   
        }
        break;
      case 8:if(!Relay_6_OPEN)if(Relay_8_OPEN){
          if(BeforKeyFlag != KeyFlag)Relay_8_OFF;
        }else{
          if(BeforKeyFlag != KeyFlag)Relay_8_ON;   
        }
        break;
  }
}


void RX_Data_Cmd(u8 cmd ,u8 flag){
  switch(flag){
      case 0xff:Cmd_Flag_Oxff(cmd);
      break;
      case 0xfe:Cmd_Flag_Oxfe(cmd);
      break;
       case 0xfc:Cmd_Flag_Oxfc(cmd);
      break;
       case 0xf8:Cmd_Flag_Oxf8(cmd);
      break;
       case 0xf0:Cmd_Flag_Oxf0(cmd);
      break;
       case 0xc0:Cmd_Flag_Oxc0(cmd);
      break;
  }
}
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 // GPIO_ToggleBits(GPIOC,GPIO_Pin_3);
  
  //bRF_IT_Status = bRadio_Check_Tx_RX();//读取中断状态并返回值
  
  TIM_Count++;
  //LED_ON;
  if(bRadio_Check_Tx_RX() == SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT){
    // LED_ON;
   //rssi=si446x_get_rssi();
    
    
    if(Si446xCmd.FIFO_INFO.RX_FIFO_COUNT>0){
      
      //RfRxBuffer[7] = 0xc0;
      KeyFlagBuff = RfRxBuffer[7];
       LED_ON;
      if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_1))//判断数据正确与否
      {
        KeyFlag = 1;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_2))//判断数据正确与否
      {
         KeyFlag = 2;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_3))//判断数据正确与否
      {
        KeyFlag = 3;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_4))//判断数据正确与否
      {
        //总开关
        closAll(0); 
        // openRelay(4); 
        KeyFlag = 4;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_5))//判断数据正确与否
      {
        KeyFlag = 5; 
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_6))//判断数据正确与否
      {         
        
        KeyFlag = 6;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_7))//判断数据正确与否
      {      
        KeyFlag = 7;
      }else if((RfRxBuffer[0]==FlashBuf[0])&&(RfRxBuffer[1]==FlashBuf[1])&&(RfRxBuffer[2]==FlashBuf[2])&&(RfRxBuffer[3]==FlashBuf[3])&&(RfRxBuffer[4]==FlashBuf[4])&&(RfRxBuffer[5]==Command_8))//判断数据正确与否
      {       
        KeyFlag = 8;
      }else{
        KeyFlag = 0;
      }

      RX_Data_Cmd(KeyFlag,RfRxBuffer[7]);
      
      
      BeforKeyFlag = KeyFlag;
      TIM_Count = 0;//标志位置零
    
    }
    vRadio_StartRX(ChannelNumber, RfRxSize);
  }
  
  if(TIM_Count >= 4){
    TIM_Count = 0;//标志位置零
    KeyFlag = 0;
    vRadio_StartRX(ChannelNumber, RfRxSize);
    BeforKeyFlag = KeyFlag;
    RX_Data_Cmd(KeyFlag,KeyFlagBuff);
  }//如果没有接收到信息 那么保持原来的状态
  
  
  LED_OFF;
   //vRadio_StartRX(ChannelNumber, RfRxSize);
   TIM4_ClearITPendingBit(TIM4_IT_Update);
}


/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */		
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/