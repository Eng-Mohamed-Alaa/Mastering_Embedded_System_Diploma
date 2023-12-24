#include "../../../Inc/HAL/UDS/UDS.h"
#include "../../../SERVICES/Standard_Data_Types.h"
uint8 Session_Id     = DEFAULT_SESSION;
uint8 Security_Level = SECURITY_LEVEL_1;

uint8  SID   = 0 ;
uint8  SUBfn = 0 ;
uint8  DID   = 0 ;
uint8  RSID  = 0 ;
uint32 DATA  = 0 ;
uint8  NRC   = 0 ;

extern Can_MessageType G_Receive_Message;
extern uint8 G_ArrMessageData[8];
extern uint8  G_UDS_SID;
extern uint8  G_UDS_SubFun;
extern uint8  G_UDS_DID;
extern uint32 G_UDS_DATA;

extern uint8 APP_CURRENT_SECURITY_LEVEL ;
extern uint8 APP_CURRENT_SESSION        ;
extern const uint16 LED_Feature;

void UDS_VoidInit(void)
{


	Can_ConfigType can1 ={
		    	     		.can_select_back_from_bus_off_state_automatic = CAN_SELECT_BACK_FROM_BUS_OFF_STATE_AUTOMATIC,
		    	     		.can_select_during_debug_mode_can_working = CAN_SELECT_DURING_DEBUG_MODE_CAN_WORKING,
		    	     		.can_select_node_mode = CAN_SELECT_NODE_MODE_NORMAL,
		    	     		.can_select_retransmission_automatic = CAN_SELECT_RETRANSMISSION_NOT_AUTOMOTIC,
		    	     		.can_select_rx_lock_mode = CAN_SELECT_RX_FIFO_NOT_LOCKED_ON_OVERRUN,
		    	     		.can_select_time_trigger_communcation_mode = CAN_SELECT_TIME_TRIGGER_COMMUNICATION_MODE_DISABLED,
		    	     		.can_select_tx_fifo_priority = CAN_SELECT_TX_FIFO_BY_THE_REQUEST_ORDER,
		    	     		.can_select_wakeup_automatic = CAN_SELECT_WAKEUP_AUTOMATIC_DURING_SLEEP,
		    	     		.can_bit_time_calculation = 0x001c0003  // http://www.bittiming.can-wiki.info/
		    	     };
	 Can_enuInit(&can1);
	 Can_enuEnableRxInterruptFifox(CAN_RX_FIFO_MAIL_BOX_INDEX_0);
	 Nvic_enuEnableInterrupt(NVIC_USB_LP_CAN_RX0);
}

void UDS_Request(uint8 Copy_SID, uint8 Copy_SUBfn, uint8 Copy_DID, uint32 Copy_Data)
{
    // uint64 uint64RequestFrame = 0;
    // uint64RequestFrame = ((uint64)Copy_SID << 48) + ((uint64)Copy_SUBfn << 40) + ((uint64)Copy_DID << 32) + Copy_Data;
    // return uint64RequestFrame;
	Can_MessageType message1={
	     		.can_DLC_FROM_0_TO_8 = SEVEN_VALUE,
	     		.can_extended_id_remaining_18_bit = ZERO_VALUE,
	     		.can_select_ide_mode = CAN_SELECT_IDE_STANDARD,
	     		.can_select_rtr_mode = CAN_SELECT_RTR_DATA_FRAME,
	     		.can_standard_id_11_bit = 0x100
	     };

    uint8 frame[7];
    frame[0] = Copy_SID;
    frame[1] = Copy_SUBfn;
    frame[2] = Copy_DID;
    *((uint32*)(frame+3)) = Copy_Data;

    Can_enuTransmitMessage_MustSend(&message1, frame);
}


void UDS_requestHandler(){
	switch (G_UDS_SID)
	{
	case SID_DIAGNOSTIC_SESSION_CONTROL:
		if (G_UDS_SubFun == PROGRAMMING_SESSION && APP_CURRENT_SECURITY_LEVEL == SECURITY_LEVEL_3)
		{
			APP_CURRENT_SESSION = PROGRAMMING_SESSION;
			UDS_GeneratePositiveResponse(0);
		}
		else
		{
			if (APP_CURRENT_SECURITY_LEVEL != SECURITY_LEVEL_3)
			{
				UDS_GenerateNegativeResponse(NRC_SECURITY_ACCESS_DENIED);
			}
			if (G_UDS_SubFun != PROGRAMMING_SESSION)
			{
				UDS_GenerateNegativeResponse(NRC_SUB_FUNCTION_NOT_SUPPORTED);
			}
		}
		break;

	case SID_SECURITY_ACCESS:
		Security_LevelHandler();
		break;
	#if UDS_APPLICATION == UDS_CAR
	case SID_READ_DATA_BY_IDENTIFIER:
		if (APP_CURRENT_SECURITY_LEVEL == SECURITY_LEVEL_2){
			uint8 Local_u8DataTemp = 0 ;
			uint16 Local_u16Data = 0 ;

			EEPROM_Read_byte( G_UDS_DID , &Local_u8DataTemp);//read dtc from eeprom
			Local_u16Data=Local_u8DataTemp;//store the dtc

			EEPROM_Read_byte( G_UDS_DID+1 , &Local_u8DataTemp);//read data from eeprom
			Local_u16Data=(Local_u16Data<<8)|Local_u8DataTemp;//store the dtc + data

			UDS_GeneratePositiveResponse(Local_u16Data);
		}else{
			UDS_GenerateNegativeResponse(NRC_SUB_FUNCTION_NOT_SUPPORTED);
		}
		break;

	case SID_WRITE_DATA_BY_IDENTIFIER:
		if (APP_CURRENT_SESSION == PROGRAMMING_SESSION && APP_CURRENT_SECURITY_LEVEL == SECURITY_LEVEL_3){

			if (G_UDS_DID == DID_LED_FEATURE){
				if (G_UDS_DATA == DATA_ENABLE)
				{
					// LED init
					LED_Init();
					// Enable feature
					Nvram_EnableFeature((uint32)(&LED_Feature));
					UDS_GeneratePositiveResponse(0);
				}
				else if (G_UDS_DATA == DATA_DISABLE)
				{
					// LED init
					LED_DeInit();
					// Enable feature
					Nvram_DisableFeature((uint32)(&LED_Feature));
					UDS_GeneratePositiveResponse(0);
				} 
				else 
				{
					UDS_GenerateNegativeResponse(NRC_GENERAL_REJECT);
				}
			}
			else
			{
				UDS_GenerateNegativeResponse(NRC_REQUEST_OUT_OF_RANGE);
			}
		}
		break;
	#endif
		// case SID_CLEAR_DIAGNOSTIC_INFORMATION:
		//     if (APP_CURRENT_SESSION == PROGRAMMING_SESSION && APP_CURRENT_SECURITY_LEVEL == SECURITY_LEVEL_3){
		//         for(uint8 i=0;i<1024;i++)
		//         {
		//             EEPROM_Write_byte( i,0xff );
		//         }
		//     }else {
		//         if (APP_CURRENT_SECURITY_LEVEL != SECURITY_LEVEL_3){
		//             UDS_GenerateNegativeResponse(NRC_SECURITY_ACCESS_DENIED);
		//         }
		//         if (G_UDS_SubFun != PROGRAMMING_SESSION){
		//             UDS_GenerateNegativeResponse(NRC_SUB_FUNCTION_NOT_SUPPORTED);
		//         }
		//     }
		//     break;

	default:
		UDS_GenerateNegativeResponse(NRC_SERVICE_NOT_SUPPORTED);
		break;
	}
}


void UDS_GenerateNegativeResponse(uint8 Copy_uint8NRC){

    UDS_Request(RSID_NEGATIVE_RESPONSE, G_UDS_SubFun, 0, Copy_uint8NRC);

}

void UDS_GeneratePositiveResponse(uint32 Copy_Data){

    UDS_Request(RSID_POSITIVE_RESPONSE + G_UDS_SID, G_UDS_SubFun, G_UDS_DID, Copy_Data);
}



void UDS_voidSetCallBack( void (*callback)(Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8 Copy_uint8FilterIndex))
{
	Can_enuSetCallbackRxFunctionFifox(CAN_RX_FIFO_MAIL_BOX_INDEX_0, callback);
}
