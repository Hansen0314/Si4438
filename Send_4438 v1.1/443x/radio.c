/*! @file radio.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

#include "include.h"


/*****************************************************************************
 *  Local Macros & Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Global Variables
 *****************************************************************************/


//const SEGMENT_VARIABLE(Radio_Configuration_Data_Array[], U8, SEG_CODE) = \
//              RADIO_CONFIGURATION_DATA_ARRAY;

U8 Radio_Configuration_Data_Array[] = RADIO_CONFIGURATION_DATA_ARRAY;


//const SEGMENT_VARIABLE(RadioConfiguration, tRadioConfiguration, SEG_CODE) = \
//              RADIO_CONFIGURATION_DATA;

tRadioConfiguration RadioConfiguration = RADIO_CONFIGURATION_DATA;

//const SEGMENT_VARIABLE_SEGMENT_POINTER(pRadioConfiguration, tRadioConfiguration, SEG_CODE, SEG_CODE) = \
//                        &RadioConfiguration;

tRadioConfiguration *pRadioConfiguration = &RadioConfiguration;

/*! @file radio.c
 * @brief This file contains functions to interface with the radio chip.
 *
 * @b COPYRIGHT
 * @n Silicon Laboratories Confidential
 * @n Copyright 2012 Silicon Laboratories, Inc.
 * @n http://www.silabs.com
 */

/*****************************************************************************
 *  Local Function Declarations
 *****************************************************************************/


void vRadio_PowerUp(void)
{
  U16 wDelay = 100;
  /* Hardware reset the chip */
  si446x_reset();

  /* Wait until reset timeout or Reset IT signal */
  for (; wDelay < pRadioConfiguration->Radio_Delay_Cnt_After_Reset; wDelay++);
}


/*!
 *  Radio Initialization.
 *
 *  @author Sz. Papp
 *
 *  @note
 *
 */
void vRadio_Init(void)
{
  U16 wDelay;
  
  /* Power Up the radio chip */
  vRadio_PowerUp();
  si446x_part_info();//获取芯片信息
  if((Si446xCmd.PART_INFO.CHIPREV==0x11)&&(Si446xCmd.PART_INFO.PART==0x4438))//如果是4438芯片
  {	
        /* Load radio configuration */
      while (SI446X_SUCCESS != si446x_configuration_init(pRadioConfiguration->Radio_ConfigurationArray))//下载4438芯片配置信息
      //while (SI446X_SUCCESS != si446x_configuration_init(Radio_Configuration_Data_Array))
      {
            /* Error hook */
            for (wDelay = 0x7FFF; wDelay--; ) ;
            /* Power Up the radio chip */
            vRadio_PowerUp();
        }
   }
    // Read ITs, clear pending ones
    si446x_get_int_status(0u, 0u, 0u);
}

/*!
 *  Check if Packet sent IT flag or Packet Received IT is pending.
 *
 *  @return   SI4455_CMD_GET_INT_STATUS_REP_PACKET_SENT_PEND_BIT / SI4455_CMD_GET_INT_STATUS_REP_PACKET_RX_PEND_BIT
 *
 *  @note
 *
 */
U8 bRadio_Check_Tx_RX(void)
{
	if (radio_hal_NirqLevel() == 0)
	{
		/* Read ITs, clear pending ones */
		si446x_get_int_status(0u, 0u, 0u);

		if (Si446xCmd.GET_INT_STATUS.CHIP_PEND & SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_BIT)
		{
			/* State change to */
			si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_SLEEP);
		
			/* Reset FIFO */
			si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
		  
			/* State change to */
			si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_RX);
		}

		if(Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT)
		{
			return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_SENT_PEND_BIT;
		}

		if(Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT)//SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_CRC_ERROR_BIT)//
		{				
			/* Packet RX */
			si446x_get_modem_status(0);
			/* 读取rssi */
			rssi = Si446xCmd.GET_MODEM_STATUS.LATCH_RSSI;
			/* Get payload length */
			si446x_fifo_info(0x00);
			/* 读取芯片接收FIFO中数据 */
			si446x_read_rx_fifo(Si446xCmd.FIFO_INFO.RX_FIFO_COUNT, &RfRxBuffer[0]); 
			/* 长度传递变量赋值 */
			ucPackLgth = Si446xCmd.FIFO_INFO.RX_FIFO_COUNT;	  
			return SI446X_CMD_GET_INT_STATUS_REP_PH_PEND_PACKET_RX_PEND_BIT;
		}
		  
		if (Si446xCmd.GET_INT_STATUS.PH_PEND & SI446X_CMD_GET_INT_STATUS_REP_PH_STATUS_CRC_ERROR_BIT){
			/* Reset FIFO */
			si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);
		}
	}
	return 0;
}

/*!
 *  Set Radio to RX mode. .
 *
 *  @param channel Freq. Channel,  packetLength : 0 Packet handler fields are used , nonzero: only Field1 is used
 *
 *  @note
 *
 */
void vRadio_StartRX(U8 channel, U8 packetLenght )
{
	
	si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_RX);
	
  // Read ITs, clear pending ones
  si446x_get_int_status(0u, 0u, 0u);
	
   // Reset the Rx Fifo
   si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_RX_BIT);

  /* Start Receiving packet, channel 0, START immediately, Packet length used or not according to packetLength */
  si446x_start_rx(channel, 0u, packetLenght,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE1_RXTIMEOUT_STATE_ENUM_NOCHANGE,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE2_RXVALID_STATE_ENUM_READY,
                  SI446X_CMD_START_RX_ARG_NEXT_STATE3_RXINVALID_STATE_ENUM_RX );
}

/*!
 *  Set Radio to TX mode, variable packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent length of of the packet sent to TXFIFO
 *
 *  @note
 *
 */
void vRadio_StartTx_Variable_Packet(U8 channel, U8 *pioRadioPacket, U8 length)
{
  /* Leave RX state */
  si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_READY);

  /* Read ITs, clear pending ones */
  si446x_get_int_status(0u, 0u, 0u);

  /* Reset the Tx Fifo */
  si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);

  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(length, pioRadioPacket);

  /* Start sending packet, channel 0, START immediately */
   si446x_start_tx(channel, 0x80, length);
 
}


/*!
 *  Set Radio to TX mode, variable packet length.
 *
 *  @param channel Freq. Channel, Packet to be sent length of of the packet sent to TXFIFO
 *
 *  @note
 *
 */
void vRadio_StartTx_Variable_Packet_2(U8 channel, U8 *pioRadioPacket, U8 length)
{
	U8 buffer[64]={0},i,*p=pioRadioPacket;
	buffer[0] = length;
	for(i=0;i<length;i++)
	{
		buffer[i+1]=*p++;
	}
  /* Leave RX state */
  si446x_change_state(SI446X_CMD_CHANGE_STATE_ARG_NEXT_STATE1_NEW_STATE_ENUM_READY);

  /* Read ITs, clear pending ones */
  si446x_get_int_status(0u, 0u, 0u);

  /* Reset the Tx Fifo */
  si446x_fifo_info(SI446X_CMD_FIFO_INFO_ARG_FIFO_TX_BIT);

  /* Fill the TX fifo with datas */
  si446x_write_tx_fifo(length+1, buffer);

  /* Start sending packet, channel 0, START immediately */
   si446x_start_tx(channel, 0x80, length+1);
 
}

/*!
 *  Set Radio PA Level
 *
 *  @param level: 0→20dBm  1→15dBm  2→10dBm  3→5dBm ...
 *
 *  @note
 *
 */
U8 vRadio_Set_PA_Level(U8 level)
{
	const U8 PA_Level[8] = {0x00,0x55,0x68,0x72,0x78,0x7b,0x7d,0x7e};
	U8 Pro2Cmd[16] = {
		RF_PA_MODE_4
	};
	
	Pro2Cmd[5] = 0x7F-PA_Level[level];
	if (radio_comm_SendCmdGetResp(0x07, Pro2Cmd, 0, 0) != 0xFF)
    {
      /* Timeout occured */
      return SI446X_CTS_TIMEOUT;
    }

    if (radio_hal_NirqLevel() == 0)
    {
      /* Get and clear all interrupts.  An error has occured... */
      si446x_get_int_status(0, 0, 0);
      if (Si446xCmd.GET_INT_STATUS.CHIP_PEND &    SI446X_CMD_GET_CHIP_STATUS_REP_CHIP_PEND_CMD_ERROR_PEND_MASK)
      {
        return SI446X_COMMAND_ERROR;
      }
    }
	return SI446X_SUCCESS;
}

/*!
 *  Change State
 *
 *  @param 
 *
 *  @note 从发送模式切换到接收模式需要从新配置RF_PKT_LEN
 *
 */
void vRadio_Tx_TO_Rx(void)
{
	const U8 Array[]={
  0x10, RF_PKT_LEN_12,0x00
	};
	si446x_configuration_init(Array);
}


/*!
 *  Set Communication Rate
 *
 *  @param 
 *
 *  @note 
 *
 */
const U8  rate_600_config[]=RATE_600;
const U8 rate_1200_config[]=RATE_1200;
const U8 rate_2400_config[]=RATE_2400;
const U8 rate_4800_config[]=RATE_4800;
const U8 rate_9600_config[]=RATE_9600;
const U8  rate_40k_config[]=RATE_40K;
const U8 rate_100k_config[]=RATE_100K;
const U8 rate_200k_config[]=RATE_200K;
U8 vRadio_Set_Rate(U8 rate)
{
	si446x_configuration_init(rate_9600_config);
	if(rate==0)
		si446x_configuration_init(rate_600_config);
	else if(rate==1)
		si446x_configuration_init(rate_1200_config);
	else if(rate==2)
		si446x_configuration_init(rate_2400_config);
	else if(rate==3)
		si446x_configuration_init(rate_4800_config);
	else if(rate==4)
		si446x_configuration_init(rate_9600_config);
	else if(rate==5)
		si446x_configuration_init(rate_40k_config);
	else if(rate==6)
		si446x_configuration_init(rate_100k_config);
	else if(rate==7)
		si446x_configuration_init(rate_200k_config);
	else
		return SI446X_COMMAND_ERROR;
	return SI446X_SUCCESS;
}

/*!
 *  ShutDown The Chip
 *
 *  @param 
 *
 *  @note 
 *
 */
void vRadio_ShutDown(void)
{
    U8 loopCount;
    /* Put radio in shutdown, wait then release */
    radio_hal_AssertShutdown();
    //! @todo this needs to be a better delay function.
    for (loopCount = 255; loopCount != 0; loopCount--);

}
