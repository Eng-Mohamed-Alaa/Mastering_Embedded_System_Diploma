/**************************************************************************/
/* Filename						: CAN.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 15, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/





/********************************** Includes *********************************************/

#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"



#include "../../../Inc/MCAL/RCC/RCC.h"
#include "../../../Inc/MCAL/GPIO/GPIO.h"

#include "../../../Inc/MCAL/CAN/CAN.h"
#include "../../../Inc/MCAL/CAN/CAN_config.h"
#include "../../../Inc/MCAL/CAN/CAN_private.h"



/********************************** Private declaration **********************************/

static Can_StatusErrorType enuFiltersInit(void);

//static uint8 GlobalStatic_uint8NumberOfCan1Fitlers = ZERO_VALUE;

/********************************** Data Type Declarations ****************************/


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/




/******************************* Software Interfaces Implementation *******************/
Can_StatusErrorType Can_enuInit(const Can_ConfigType* Address_Can){


	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Can){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		/* Enable CAN1 Rcc Clock */
		Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_CAN,RCC_Periph_ENABLE);

		Rcc_enuControl_APB2_Peripheral(RCC_APB2_Periph_IOPA, RCC_Periph_ENABLE);

		/* CAN TX */
			GPIO_PIN_INIT(GPIO_PIN_12,GPIO_PORT_A,AF_output_Push_pull,GPIO_max_speed_2_MHz,pull_UP);

		/* CAN RX */
			GPIO_PIN_INIT(GPIO_PIN_11,GPIO_PORT_A,InputFloating,GPIO_INPUT,FLOATING);

		/* exit from sleep mode and enable init mode */
		Can_GoToInitMode();

		/* Choose Tx Fifo Priority */
		Can_SelectTxFifoPriority(Address_Can->can_select_tx_fifo_priority);


		/* Choose Rx Lock Mode */
		Can_SelectRxFifoLockMode(Address_Can->can_select_rx_lock_mode);

		/* enable/disable Retransmission Mode */
		Can_SelectRetransmissionAutomatic(Address_Can->can_select_retransmission_automatic);

		/* enable/disable WakeUp During Sleep Mode */
		Can_SelectWakeupAutomatic(Address_Can->can_select_wakeup_automatic);

		/* enable/disable Bus Off Left Automatically Mode */
		Can_SelectBackFromBusOffStateAutomatic(Address_Can->can_select_back_from_bus_off_state_automatic);

		/* enable/disable Time Trigger Communciation Mode */
		Can_SelectTimeTriggerCommunicationMode(Address_Can->can_select_time_trigger_communcation_mode);


		/* enable/disable CAN during Debugging Mode */
		Can_SelectDuringDebugModeCanWorking(Address_Can->can_select_during_debug_mode_can_working);

		/* Select Node Mode */
		Can_SelectNodeMode(Address_Can->can_select_node_mode);

		/* Set Bit Time Calculation,, http://www.bittiming.can-wiki.info/ */
		Can_SetBitTimeCalulation(Address_Can->can_bit_time_calculation);

		/* Exit From Init Mode */
		Can_GoOutFromInitMode();

//		/* It's Used for Filters Configuration */
//		GlobalStatic_uint8NumberOfCan1Fitlers = Address_Can->can_number_of_can1_filters_1_to_28;

		/* Filter Init */
		(void)enuFiltersInit();

//		while( READ_BIT(CAN_1->CAN_MSR,ZERO_VALUE) ==ONE_VALUE );

	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuResetMasterSW(void){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;


		Can_ResetMasterSW() ;


	return Loc_enuCanStatusError;
}



Can_StatusErrorType Can_enuIsNodeCurrentlyTransmitter(Std_True_or_FalseType* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = (Std_True_or_FalseType)Can_IsNodeCurrentlyTransmitter();
	}

	return Loc_enuCanStatusError;
}
Can_StatusErrorType Can_enuIsNodeCurrentlyReceiver(Std_True_or_FalseType* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Result = (Std_True_or_FalseType)Can_IsNodeCurrentlyReceiver();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuGetActualValueOfCanRxPin(Std_HIGH_or_LowType* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Result = (Std_HIGH_or_LowType)Can_GetActualValueOfCanRxPin();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuGetCurrentReceivedBitValue(Std_HIGH_or_LowType* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{

		*Address_Result = (Std_HIGH_or_LowType)Can_GetCurrentReceivedBitValue();
	}

	return Loc_enuCanStatusError;
}


Can_StatusErrorType Can_enuIsTxMailBoxLowestPriority(Can_TxMailBoxIndexType Copy_enuTxMailBoxIndex, Std_True_or_FalseType* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_FAIL;
	}
	else if (Copy_enuTxMailBoxIndex > CAN_MAX_TX_MAILBOX_INDEX ){

		Loc_enuCanStatusError = CAN_STATUS_WRONG_MAILBOX_INDEX;
	}

	else{
		*Address_Result = (Std_True_or_FalseType)Can_IsMailBox_x_LowestPriority(Copy_enuTxMailBoxIndex);
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuAbortTransmitInMailBox_x(Can_TxMailBoxIndexType Copy_enuTxMailBoxIndex){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;

	Can_AbortRequestForMailBox_x(Copy_enuTxMailBoxIndex);

	return Loc_enuCanStatusError;

}

Can_StatusErrorType Can_enuTransmitMessage_CheckOneTime(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;

	uint8 Loc_uint8BestMailBoxIndex = Can_GetBestMailBoxIndex();

	if(NULL == Address_Message){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}

	else{

		/* check is any mail box is empty */

		if(Can_IsMailBox_x_Empty(Loc_uint8BestMailBoxIndex) == STD_FALSE){
			Loc_enuCanStatusError = CAN_STATUS_TX_MAILBOX_NOT_EMPTY;
		}

//		if(Can_IsMailBox_x_Empty(0) != STD_TRUE && Can_IsMailBox_x_Empty(1)!= STD_TRUE && Can_IsMailBox_x_Empty(1)!= STD_TRUE  ){
//			Loc_enuCanStatusError = CAN_STATUS_TX_MAILBOX_NOT_EMPTY;
//		}

		else{
			/* Set DLC */
			Can_SetDLCinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_DLC_FROM_0_TO_8 ));

			/* SET extended ID */
			Can_SetExtendedIDinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_extended_id_remaining_18_bit));

			/* SET  IDE */
			Can_SetIDEinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_ide_mode);

			/* SET  RTR */
			Can_SetRTRinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_rtr_mode);

			/* SET Standard IDE */
			Can_SetStandardIDinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_standard_id_11_bit);

			/* SET  Message Data  */
			Can_SetDataMessaginMailBox_x(Loc_uint8BestMailBoxIndex,_ArrMessageData);

			/* Request For Transmit */
			Can_StartTransmit(Loc_uint8BestMailBoxIndex);

		}

	}

	return Loc_enuCanStatusError;


}

Can_StatusErrorType Can_enuTransmitMessage_MustSend(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]){

	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	uint8 Loc_uint8BestMailBoxIndex = Can_GetBestMailBoxIndex();
	if(NULL == Address_Message){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}

	else{

		/* check is any mail box is empty */
			while(Can_IsMailBox_x_Empty(Loc_uint8BestMailBoxIndex) == STD_FALSE);

			/* Set DLC */
			Can_SetDLCinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_DLC_FROM_0_TO_8 ));

			/* SET extended ID */
			Can_SetExtendedIDinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_extended_id_remaining_18_bit));

			/* SET  IDE */
			Can_SetIDEinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_ide_mode);

			/* SET  RTR */
			Can_SetRTRinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_rtr_mode);

			/* SET Standard IDE */
			Can_SetStandardIDinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_standard_id_11_bit);

			/* SET  Message Data  */
			Can_SetDataMessaginMailBox_x(Loc_uint8BestMailBoxIndex,_ArrMessageData);

			/* Request For Transmit */
			Can_StartTransmit(Loc_uint8BestMailBoxIndex);

//			while( (Can_IsRequestCompletedMailBox_x(Loc_uint8BestMailBoxIndex) == STD_TRUE &&
//						Can_IsTransmissionCompletedMailBox_x(Loc_uint8BestMailBoxIndex) == STD_TRUE) != STD_TRUE
//
//					|| Can_IsArbitrationLostHappenedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE ||
//						Can_IsTransmissionErrorHappenedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE
//						);

		//	while( Can_IsRequestCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE);


			// Request here's Done
			while(Can_IsMailBox_x_Empty(Loc_uint8BestMailBoxIndex) == STD_FALSE);

			if(	Can_IsTransmissionCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE){
				// Error Happenes
				Loc_enuCanStatusError = Can_IsArbitrationLostHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*CAN_STATUS_FAIL_ARBITRATION_LOST +
												Can_IsTransmissionErrorHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*Can_GetLastErrorCode();
			}




	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuTransmitMessage_MustSendWithTimeOut(const Can_MessageType* Address_Message,uint8 _ArrMessageData[]){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	uint16 Loc_uint16TimeOut = CAN_MAX_TIMEOUT_COUNTER_VALUE;
	uint8 Loc_uint8BestMailBoxIndex = Can_GetBestMailBoxIndex();
	if(NULL == Address_Message){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}

	else{

		/* check is any mail box is empty */

		while(Can_IsMailBox_x_Empty(Loc_uint8BestMailBoxIndex) != STD_TRUE && Loc_uint16TimeOut != ZERO_VALUE){
			Loc_uint16TimeOut--;
		}

		if(Loc_uint16TimeOut == ZERO_VALUE){
			Loc_enuCanStatusError = CAN_STATUS_TX_MAILBOX_NOT_EMPTY;
		}


		else{
			/* Reset The Time Out Counter TO max Value Again */
			Loc_uint16TimeOut = CAN_MAX_TIMEOUT_COUNTER_VALUE;

			/* Set DLC */
			Can_SetDLCinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_DLC_FROM_0_TO_8 ));

			/* SET extended ID */
			Can_SetExtendedIDinTxMailBox_x(Loc_uint8BestMailBoxIndex, (Address_Message->can_extended_id_remaining_18_bit));

			/* SET  IDE */
			Can_SetIDEinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_ide_mode);

			/* SET  RTR */
			Can_SetRTRinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_select_rtr_mode);

			/* SET Standard IDE */
			Can_SetStandardIDinTxMailBox_x(Loc_uint8BestMailBoxIndex,Address_Message->can_standard_id_11_bit);

			/* SET  Message Data  */
			Can_SetDataMessaginMailBox_x(Loc_uint8BestMailBoxIndex,_ArrMessageData);

			/* Request For Transmit */
			Can_StartTransmit(Loc_uint8BestMailBoxIndex);

//			while( (Can_IsRequestCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE &&
//									Can_IsTransmissionCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE)
//					            && Loc_uint16TimeOut != ZERO_VALUE){
//				Loc_uint16TimeOut--;
//			}
//
//			if(Loc_uint16TimeOut == ZERO_VALUE){
//				/* it must be arbirtration lost or error, if error, return which one */
//				Loc_enuCanStatusError = Can_IsArbitrationLostHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*CAN_STATUS_FAIL_ARBITRATION_LOST +
//												Can_IsTransmissionErrorHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*Can_GetLastErrorCode();
//			}
			while( Can_IsRequestCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE && Loc_uint16TimeOut != ZERO_VALUE){
				Loc_uint16TimeOut--;
			}

			if(Loc_uint16TimeOut == ZERO_VALUE){
				Loc_enuCanStatusError = Can_IsArbitrationLostHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*CAN_STATUS_FAIL_ARBITRATION_LOST ;
			}
			else{
				/* Reset The Time Out Counter TO max Value Again */
				Loc_uint16TimeOut = CAN_MAX_TIMEOUT_COUNTER_VALUE;

				// Request here's Done
				while(Can_IsMailBox_x_Empty(Loc_uint8BestMailBoxIndex) == STD_FALSE  && Loc_uint16TimeOut != ZERO_VALUE ){
					Loc_uint16TimeOut--;
				}


				if(	Can_IsTransmissionCompletedMailBox_x(Loc_uint8BestMailBoxIndex) != STD_TRUE){
					// Error Happenes
					Loc_enuCanStatusError = Can_IsArbitrationLostHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*CAN_STATUS_FAIL_ARBITRATION_LOST +
													Can_IsTransmissionErrorHappenedMailBox_x(Loc_uint8BestMailBoxIndex)*Can_GetLastErrorCode();
				}
			}




		}

	}

	return Loc_enuCanStatusError;


}


Can_StatusErrorType Can_enuGetTEC_TransimissionErrorCounter(uint8* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Can_GetTEC_TransimissionErrorCounter();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuGetREC_ReceiveErrorCounter(uint8* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Can_GetREC_ReceiveErrorCounter();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuGetErrorWarningFlag_TEC_OR_REC_GREATER_THAN_95(uint8* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Can_GetErrorWarningFlag_TEC_OR_REC_GREATER_THAN_95();
	}

	return Loc_enuCanStatusError;
}
Can_StatusErrorType Can_enuGetErrorPassiveFlag_TEC_OR_REC_GREATER_THAN_127(uint8* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Can_GetErrorPassiveFlag_TEC_OR_REC_GREATER_THAN_127();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuIsNodeInBusOffMode(uint8* Address_Result){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Result){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		*Address_Result = Can_IsNodeInBusOffMode();
	}

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuConfigFilterx(const Can_FilterConfigType* Address_Filter){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;
	if(NULL == Address_Filter){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		/* Start Filter Init Mode	 */
		Can_GoToFilterInitMode();


		/* Init All Filters */
		/*
		 * 1- mode
		 * 2- scale
		 * 3- reg1 value
		 * 4- reg2 value
		 * 5- Which Fifo Index
		 */

		/* config Mode */
		Can_SelectFilterMode((Address_Filter->can_filter_index_0_TO_27),(Address_Filter->can_select_filter_mode));

		/* config Scale */
		Can_SelectFilterScale((Address_Filter->can_filter_index_0_TO_27),(Address_Filter->can_select_filter_scale));

		/* Config Fifo Index for this Filter */
		Can_SelectFilterFifo((Address_Filter->can_filter_index_0_TO_27),(Address_Filter->can_rx_fifo_mail_box_index_for_this_filter));

		/* Set Value for Reg0 */
		Can_SetBankRegister(ZERO_VALUE,(Address_Filter->can_filter_index_0_TO_27),(Address_Filter->can_filter_reg1_value));

		/* Set Value for Reg1 */
		Can_SetBankRegister(ONE_VALUE,(Address_Filter->can_filter_index_0_TO_27),(Address_Filter->can_filter_reg2_value));

		/* Activate The Filter Bank */
		Can_ActivateFilter(((Address_Filter->can_filter_index_0_TO_27)));


		/* Go to Normal Mode */
		Can_GoOutFromFilterInitMode();


	}

	return Loc_enuCanStatusError;
}


Can_StatusErrorType Can_enuReceiveMessageBothFifo_CheckOneTime( Can_MessageType* Address_Message0,uint8 _ArrMessageData0[EIGHT_VALUE],uint8* Address_FilterIndex0
																, Can_MessageType* Address_Message1,uint8 _ArrMessageData1[EIGHT_VALUE],uint8* Address_FilterIndex1){

	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;
	Loc_enuCanStatusError = Can_enuReceiveMessageFifox_CheckOneTime(CAN_RX_FIFO_MAIL_BOX_INDEX_0, Address_Message0, _ArrMessageData0, Address_FilterIndex0);

	Loc_enuCanStatusError = Can_enuReceiveMessageFifox_CheckOneTime(CAN_RX_FIFO_MAIL_BOX_INDEX_1, Address_Message1, _ArrMessageData1, Address_FilterIndex1);



return Loc_enuCanStatusError;


}


Can_StatusErrorType Can_enuReceiveMessageFifox_CheckOneTime(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex){

	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;

	if(NULL == Address_Message ){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}

	else{
			if(Can_GetNumberOfPendingMessages_FIFOx(Copy_enuFifoIndex) != ZERO_VALUE){

				/* Get DLC of Message */
				Address_Message->can_DLC_FROM_0_TO_8 = Can_GetDLCinRxFifoMailBox_x(Copy_enuFifoIndex);


				/* Get EXID of Message */
				Address_Message->can_extended_id_remaining_18_bit = Can_GetExtendedIDinRxFifoMailBox_x(Copy_enuFifoIndex);


				/* Get IDE of Message */
				Address_Message->can_select_ide_mode = Can_GetIDEinRxFifoMailBox_x(Copy_enuFifoIndex);

				/* Get RTR of Message */
				Address_Message->can_select_rtr_mode = Can_GetRTRinRxFifoMailBox_x(Copy_enuFifoIndex);

				/* Get Standard ID of Message */
				Address_Message->can_standard_id_11_bit = Can_GetStandardIDinRxFifoMailBox_x(Copy_enuFifoIndex);


				/* Get The Data */
				Can_GetDataMessaginFifoMailBox_x(Copy_enuFifoIndex,_ArrMessageData);


				if(Address_FilterIndex != NULL){
					*Address_FilterIndex = Can_GetFilterIndexFifox(Copy_enuFifoIndex);
				}

				/* Relase The Message */
				Can_RelaseFIFOxMailBox(Copy_enuFifoIndex);

			}

			else{
				Address_FilterIndex = NULL;
				Loc_enuCanStatusError = CAN_STATUS_RX_FIFO_MAILBOX_EMPTY;
			}
	}

	return Loc_enuCanStatusError;

}

Can_StatusErrorType Can_enuReceiveMessageFifox_MustReceive(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex){
	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;

		if(NULL == Address_Message ){
			Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
		}

		else{
				while( (Can_GetNumberOfPendingMessages_FIFOx(Copy_enuFifoIndex)) == ZERO_VALUE ){
					asm("NOP");
				}

					/* Get DLC of Message */
					Address_Message->can_DLC_FROM_0_TO_8 = Can_GetDLCinRxFifoMailBox_x(Copy_enuFifoIndex);


					/* Get EXID of Message */
					Address_Message->can_extended_id_remaining_18_bit = Can_GetExtendedIDinRxFifoMailBox_x(Copy_enuFifoIndex);


					/* Get IDE of Message */
					Address_Message->can_select_ide_mode = Can_GetIDEinRxFifoMailBox_x(Copy_enuFifoIndex);

					/* Get RTR of Message */
					Address_Message->can_select_rtr_mode = Can_GetRTRinRxFifoMailBox_x(Copy_enuFifoIndex);

					/* Get Standard ID of Message */
					Address_Message->can_standard_id_11_bit = Can_GetStandardIDinRxFifoMailBox_x(Copy_enuFifoIndex);


					/* Get The Data */
					Can_GetDataMessaginFifoMailBox_x(Copy_enuFifoIndex,_ArrMessageData);


					if(Address_FilterIndex != NULL){
						*Address_FilterIndex = Can_GetFilterIndexFifox(Copy_enuFifoIndex);
					}

					/* Relase The Message */
					Can_RelaseFIFOxMailBox(Copy_enuFifoIndex);




		}

		return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuReceiveMessageFifox_MustReceiveWithTimeOut(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,
							Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8* Address_FilterIndex){
	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;
	uint16 Loc_uint16TimeOut = CAN_MAX_TIMEOUT_COUNTER_VALUE;

	if(NULL == Address_Message ){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
	}

	else{
		while(Can_GetNumberOfPendingMessages_FIFOx(Copy_enuFifoIndex) == ZERO_VALUE && Loc_uint16TimeOut != ZERO_VALUE){
			Loc_uint16TimeOut--;

		}
		if(Loc_uint16TimeOut == ZERO_VALUE){
			Loc_enuCanStatusError = CAN_STATUS_RX_FIFO_MAILBOX_EMPTY;
		}
		else{

			/* Get DLC of Message */
			Address_Message->can_DLC_FROM_0_TO_8 = Can_GetDLCinRxFifoMailBox_x(Copy_enuFifoIndex);


			/* Get EXID of Message */
			Address_Message->can_extended_id_remaining_18_bit = Can_GetExtendedIDinRxFifoMailBox_x(Copy_enuFifoIndex);


			/* Get IDE of Message */
			Address_Message->can_select_ide_mode = Can_GetIDEinRxFifoMailBox_x(Copy_enuFifoIndex);

			/* Get RTR of Message */
			Address_Message->can_select_rtr_mode = Can_GetRTRinRxFifoMailBox_x(Copy_enuFifoIndex);

			/* Get Standard ID of Message */
			Address_Message->can_standard_id_11_bit = Can_GetStandardIDinRxFifoMailBox_x(Copy_enuFifoIndex);


			/* Get The Data */
			Can_GetDataMessaginFifoMailBox_x(Copy_enuFifoIndex,_ArrMessageData);


			if(Address_FilterIndex != NULL){
				*Address_FilterIndex = Can_GetFilterIndexFifox(Copy_enuFifoIndex);
			}

			/* Relase The Message */
			Can_RelaseFIFOxMailBox(Copy_enuFifoIndex);
		}
	}

	return Loc_enuCanStatusError;
}

/* Interrupt Part */
Can_StatusErrorType Can_enuEnableRxInterruptFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex){
	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;

	/* Enable Interrupt */
	Can_EnableRxInterruptFifoMailBox_x(Copy_enuFifoIndex);

	return Loc_enuCanStatusError;
}


Can_StatusErrorType Can_enuDisableRxInterruptFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex){
	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;

	/* Enable Interrupt */
	Can_DisableRxInterruptFifoMailBox_x(Copy_enuFifoIndex);

	return Loc_enuCanStatusError;
}

Can_StatusErrorType Can_enuSetCallbackRxFunctionFifox(Can_RxFifoMailBoxIndexType Copy_enuFifoIndex,void (*callback)(Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8 Copy_uint8FilterIndex)){

	Can_StatusErrorType Loc_enuCanStatusError= CAN_STATUS_OK;;

	if( NULL == callback ){
		Loc_enuCanStatusError = CAN_STATUS_NULL_POINTER_ADDRESS;
		}
		else{
			Can_RxInterruptHandler[Copy_enuFifoIndex] =callback;
		}
	return Loc_enuCanStatusError;

}



/**************************** Private Software Interface Implementation **************/

static Can_StatusErrorType enuFiltersInit(void){
	Can_StatusErrorType Loc_enuCanStatusError =CAN_STATUS_OK;

	/* Start Filter Init Mode	 */
	Can_GoToFilterInitMode();

	/* Set Number Of Can1 Filters */
	Can_SetNumberOfCan1Filters(NUMBER_OF_CAN1_FILTERS);

	/* Init All Filters */
	/*
	 * 1- mode
	 * 2- scale
	 * 3- reg1 value
	 * 4- reg2 value
	 * 5- Which Fifo Index
	 */
	Filter_concat(FILTER13_CONFG, FILTER12_CONFG, FILTER11_CONFG, FILTER10_CONFG,
			FILTER9_CONFG, FILTER8_CONFG, FILTER7_CONFG, FILTER6_CONFG, FILTER5_CONFG, FILTER4_CONFG,
			FILTER3_CONFG, FILTER2_CONFG, FILTER1_CONFG, FILTER0_CONFG
						);


	/* Go to Normal Mode */
	Can_GoOutFromFilterInitMode();


	return Loc_enuCanStatusError;
}




void USB_LP_CAN_RX0_IRQHandler(void)
{
	Can_MessageType Loc_ReceivedMessage;
	uint8 Loc_ReceivedDataArr[EIGHT_VALUE];
	uint8 Loc_u8FilterIndex;

	/* Get DLC of Message */
	Loc_ReceivedMessage.can_DLC_FROM_0_TO_8 = Can_GetDLCinRxFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0);


	/* Get EXID of Message */
	Loc_ReceivedMessage.can_extended_id_remaining_18_bit = Can_GetExtendedIDinRxFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0);


	/* Get IDE of Message */
	Loc_ReceivedMessage.can_select_ide_mode = Can_GetIDEinRxFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0);

	/* Get RTR of Message */
	Loc_ReceivedMessage.can_select_rtr_mode = Can_GetRTRinRxFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0);

	/* Get Standard ID of Message */
	Loc_ReceivedMessage.can_standard_id_11_bit = Can_GetStandardIDinRxFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0);


	/* Get The Data */
	Can_GetDataMessaginFifoMailBox_x(CAN_RX_FIFO_MAIL_BOX_INDEX_0,Loc_ReceivedDataArr);

	/* Get Filter Index*/
	Loc_u8FilterIndex = Can_GetFilterIndexFifox(CAN_RX_FIFO_MAIL_BOX_INDEX_0);

	Can_RxInterruptHandler[CAN_RX_FIFO_MAIL_BOX_INDEX_0](&Loc_ReceivedMessage,Loc_ReceivedDataArr,Loc_u8FilterIndex);

	/* Relase/Clear The flag The Message */
	Can_RelaseFIFOxMailBox(CAN_RX_FIFO_MAIL_BOX_INDEX_0);

}
