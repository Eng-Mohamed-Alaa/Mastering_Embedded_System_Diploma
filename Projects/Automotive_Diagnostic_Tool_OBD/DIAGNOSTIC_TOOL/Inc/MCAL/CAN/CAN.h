/**************************************************************************/
/* Filename						: CAN.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 15, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef CAN_CAN_H_
#define CAN_CAN_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{

	////
	CAN_STATUS_OK = 0b0000,
	CAN_STATUS_FAIL_STUFF_ERROR = 0b0001,
	CAN_STATUS_FAIL_FORM_ERROR= 0b0010,
	CAN_STATUS_FAIL_ACK_ERROR= 0b0011,
	CAN_STATUS_FAIL_BIT_RECESSIVE_ERROR= 0b0100,
	CAN_STATUS_FAIL_BIT_DOMINANT_ERROR= 0b0101,
	CAN_STATUS_FAIL_CRC_ERROR = 0b0110,
	CAN_STATUS_FAIL_BY_HW =0b0111,
	///
	CAN_STATUS_FAIL ,
	CAN_STATUS_NULL_POINTER_ADDRESS,
	CAN_STATUS_TX_MAILBOX_NOT_EMPTY,
	CAN_STATUS_RX_FIFO_MAILBOX_EMPTY,
	CAN_STATUS_FAIL_ARBITRATION_LOST,
	CAN_STATUS_WRONG_MAILBOX_INDEX
}Can_StatusErrorType;

typedef enum{
	CAN_SELECT_TX_FIFO_BY_IDENTIFIER_OF_THE_MESSAGE,
	CAN_SELECT_TX_FIFO_BY_THE_REQUEST_ORDER
}Can_SelectTxFfioPriorityType;

typedef enum{
	CAN_SELECT_RX_FIFO_NOT_LOCKED_ON_OVERRUN,
	CAN_SELECT_RX_FIFO_LOCKED_ON_OVERRUN
}Can_SelectRxFifoLockModeType;


typedef enum{
	CAN_SELECT_RETRANSMISSION_AUTOMATIC,
	CAN_SELECT_RETRANSMISSION_NOT_AUTOMOTIC
}Can_SelectRetransmissionAutomaticType;


typedef enum{
	CAN_SELECT_WAKEUP_NOT_AUTOMATIC_DURING_SLEEP,
	CAN_SELECT_WAKEUP_AUTOMATIC_DURING_SLEEP
}Can_SelectWakeupAutomaticType;



typedef enum{
	CAN_SELECT_BACK_FROM_BUS_OFF_STATE_NOT_AUTOMATIC,
	CAN_SELECT_BACK_FROM_BUS_OFF_STATE_AUTOMATIC
}Can_SelectBackFromBusOffStateAutomaticType;



typedef enum{
	CAN_SELECT_TIME_TRIGGER_COMMUNICATION_MODE_DISABLED,
	CAN_SELECT_TIME_TRIGGER_COMMUNICATION_MODE_ENABLED
}Can_SelectTimeTriggerCommunicationModeType;

typedef enum{
	CAN_SELECT_DURING_DEBUG_MODE_CAN_WORKING,
	CAN_SELECT_DURING_DEBUG_MODE_CAN_NOT_WORKING
}Can_SelectDuringDebugModeCanWorkingType;

typedef enum{
	CAN_SELECT_NODE_MODE_NORMAL =0b00,
	CAN_SELECT_NODE_MODE_LOOPBACK =0b01,
	CAN_SELECT_NODE_MODE_SIELENT =0b10,
	CAN_SELECT_NODE_MODE_LOOPBACK_WITH_SIELENT =0b11,
}Can_SelectNodeModeType;

typedef struct{

	Can_SelectTxFfioPriorityType can_select_tx_fifo_priority;
	Can_SelectRxFifoLockModeType can_select_rx_lock_mode;
	Can_SelectRetransmissionAutomaticType can_select_retransmission_automatic;
	Can_SelectWakeupAutomaticType can_select_wakeup_automatic;
	Can_SelectBackFromBusOffStateAutomaticType can_select_back_from_bus_off_state_automatic;
	Can_SelectTimeTriggerCommunicationModeType can_select_time_trigger_communcation_mode;
	Can_SelectDuringDebugModeCanWorkingType can_select_during_debug_mode_can_working;
	Can_SelectNodeModeType can_select_node_mode;
	uint32 can_bit_time_calculation;  // http://www.bittiming.can-wiki.info/
//	uint32 can_number_of_can1_filters_1_to_28;
}Can_ConfigType;


//////////////////  This Part for Message Handling /////////////////////////

typedef enum{
	CAN_TX_MAIL_BOX_INDEX_0,
	CAN_TX_MAIL_BOX_INDEX_1,
	CAN_TX_MAIL_BOX_INDEX_2,
}Can_TxMailBoxIndexType;

typedef enum{
	CAN_SELECT_IDE_STANDARD,
	CAN_SELECT_IDE_EXTENDED
}Can_SelectIDEModeType;


typedef enum{
	CAN_SELECT_RTR_DATA_FRAME,
	CAN_SELECT_RTR_REMOTE_FRAME
}Can_SelectRTRModeType;


typedef struct{
	// standard+extended = 11+18 = 29
	uint8  can_DLC_FROM_0_TO_8;
	uint16 can_standard_id_11_bit;
	uint32 can_extended_id_remaining_18_bit;
	Can_SelectIDEModeType can_select_ide_mode;
	Can_SelectRTRModeType can_select_rtr_mode;
}Can_MessageType;


//////////////////  This Part for Receive  Handling /////////////////////////

typedef enum{
	CAN_RX_FIFO_MAIL_BOX_INDEX_0,
	CAN_RX_FIFO_MAIL_BOX_INDEX_1
}Can_RxFifoMailBoxIndexType;

typedef enum{
	CAN_SELECT_FILTER_MODE_MASK,
	CAN_SELECT_FILTER_MODE_ID_LIST
}Can_SelectFilterModeType;


typedef enum{
	CAN_SELECT_FILTER_SCALE_16BIT_DUAL,
	CAN_SELECT_FILTER_SCALE_32BIT_SINGLE
}Can_SelectFilterScaleType;



typedef struct{

	uint8  can_filter_index_0_TO_27;
	Can_SelectFilterModeType can_select_filter_mode;
	Can_SelectFilterScaleType can_select_filter_scale;
	Can_RxFifoMailBoxIndexType can_rx_fifo_mail_box_index_for_this_filter;
	uint32 can_filter_reg1_value; // Look At DataSheet Page 1089
	uint32 can_filter_reg2_value; // Look At DataSheet Page 1089


}Can_FilterConfigType;

/********************************** Software Interfaces Declarations *******************/
Can_StatusErrorType Can_enuInit(const Can_ConfigType* Address_Can);
Can_StatusErrorType Can_enuResetMasterSW(void);

Can_StatusErrorType Can_enuIsNodeCurrentlyTransmitter(Std_True_or_FalseType* Address_Result);
Can_StatusErrorType Can_enuIsNodeCurrentlyReceiver(Std_True_or_FalseType* Address_Result);
Can_StatusErrorType Can_enuGetCurrentReceivedBitValue(Std_HIGH_or_LowType* Address_Result);
Can_StatusErrorType Can_enuGetActualValueOfCanRxPin(Std_HIGH_or_LowType* Address_Result);

Can_StatusErrorType Can_enuIsTxMailBoxLowestPriority(Can_TxMailBoxIndexType Copy_enuTxMailBoxIndex, Std_True_or_FalseType* Address_Result);
Can_StatusErrorType Can_enuAbortTransmitInMailBox_x(Can_TxMailBoxIndexType Copy_enuTxMailBoxIndex);


/* Not Implemented Yet */
Can_StatusErrorType Can_enuTransmitMessage_CheckOneTime(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]);
Can_StatusErrorType Can_enuTransmitMessage_MustSend(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]);
Can_StatusErrorType Can_enuTransmitMessage_MustSendWithTimeOut(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]);


Can_StatusErrorType Can_enuTransmitMessageAsync(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]);

Can_StatusErrorType Can_enuReceiveMessageSync(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]);
Can_StatusErrorType Can_enuReceiveMessageAsync(const Can_MessageType* Address_Message);


// Flag And Counters

Can_StatusErrorType Can_enuGetTEC_TransimissionErrorCounter(uint8* Address_Result);
Can_StatusErrorType Can_enuGetREC_ReceiveErrorCounter(uint8* Address_Result);

Can_StatusErrorType Can_enuGetErrorWarningFlag_TEC_OR_REC_GREATER_THAN_95(uint8* Address_Result);
Can_StatusErrorType Can_enuGetErrorPassiveFlag_TEC_OR_REC_GREATER_THAN_127(uint8* Address_Result);
Can_StatusErrorType Can_enuIsNodeInBusOffMode(uint8* Address_Result);

// Receive Part
Can_StatusErrorType Can_enuConfigFilterx(const Can_FilterConfigType* Address_Filter);

Can_StatusErrorType Can_enuReceiveMessageBothFifo_CheckOneTime(Can_MessageType* Address_Message0,uint8 _ArrMessageData0[EIGHT_VALUE],uint8* Address_FilterIndex0
																, Can_MessageType* Address_Message1,uint8 _ArrMessageData1[EIGHT_VALUE],uint8* Address_FilterIndex1);

Can_StatusErrorType Can_enuReceiveMessageFifox_CheckOneTime(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex);

Can_StatusErrorType Can_enuReceiveMessageFifox_MustReceive(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex);

Can_StatusErrorType Can_enuReceiveMessageFifox_MustReceiveWithTimeOut(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex);

Can_StatusErrorType Can_enuEnableRxInterruptFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex);
Can_StatusErrorType Can_enuDisableRxInterruptFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex);
Can_StatusErrorType Can_enuSetCallbackRxFunctionFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,void (*callback)(Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8 Copy_uint8FilterIndex));




#endif /* CAN_CAN_H_ */
