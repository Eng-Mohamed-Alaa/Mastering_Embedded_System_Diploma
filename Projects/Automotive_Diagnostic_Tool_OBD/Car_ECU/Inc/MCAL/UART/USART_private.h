/**************************************************************************/
/* Filename						: USART_private.h                                 */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 22, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef UART_USART_PRIVATE_H_
#define UART_USART_PRIVATE_H_



/********************************** Includes *********************************************/

/********************************** Private Function Declartion *********************************************/

static Usart_StatusErrorType Usart_enuSetBaudrate(const Usart_ConfigType* Address_Usart);
static Usart_StatusErrorType Usart_enuEnableRccClock(const Usart_ConfigType* Address_Usart);


/********************************** Macros Declarations *******************************/

#define NUMBER_OF_USART					THREE_VALUE


/********************************** Macros Function Declarations *********************/


#define Usart_SetBaudrateIntPart(_CHANNEL_,_VALUE_)                     ((uartArr[(_CHANNEL_)]->USART_BRR ) = ((uartArr[(_CHANNEL_)]->USART_BRR ) & 0xFFFF000F) | (((_VALUE_)<< FOUR_VALUE ) & 0xFFF0))
#define Usart_SetBaudrateFractionPart(_CHANNEL_,_VALUE_)                     ((uartArr[(_CHANNEL_)]->USART_BRR ) = ((uartArr[(_CHANNEL_)]->USART_BRR ) & 0xFFFFFFF0) | (((_VALUE_)<< ZERO_VALUE ) & 0xF))
#define Usart_SetDataSize(_CHANNEL_,_VALUE_)                 				 WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR1),TWELVE_VALUE, (_VALUE_) )
#define Usart_SetClockPhase(_CHANNEL_,_VALUE_)                 				   WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR2),NINE_VALUE, (_VALUE_) )
#define Usart_SetClockPolarity(_CHANNEL_,_VALUE_)                 		   WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR2),TEN_VALUE, (_VALUE_) )
#define Usart_SetDmaMode(_CHANNEL_,_VALUE_)              			       ((uartArr[(_CHANNEL_)]->USART_CR3 ) = ((uartArr[(_CHANNEL_)]->USART_CR3 ) & 0xFFFFFF3F) | (((_VALUE_)<< SIX_VALUE ) & 0xC0))
#define Usart_SetDuplexMode(_CHANNEL_,_VALUE_)                 			   WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR3),THREE_VALUE, (_VALUE_) )

#define Usart_SelectOversampleMode(_CHANNEL_,_VALUE_)                 	  do{\
																				WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR3),ELEVEN_VALUE, (((_VALUE_)>>ZERO_VALUE) &0x01) ) ;\
																				WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR1),FIFTEEN_VALUE, (((_VALUE_)>>ONE_VALUE) &0x01) ) ;\
																		}while(ZERO_VALUE)

#define Usart_SelectParityBitMode(_CHANNEL_,_VALUE_)              	  ((uartArr[(_CHANNEL_)]->USART_CR1 ) = ((uartArr[(_CHANNEL_)]->USART_CR1 ) & 0xFFFFF9FF) | (((_VALUE_)<< NINE_VALUE ) & 0x600))

#define Usart_SelectStopBits(_CHANNEL_,_VALUE_)              	        ((uartArr[(_CHANNEL_)]->USART_CR2 ) = ((uartArr[(_CHANNEL_)]->USART_CR2 ) & 0xFFFFCFFF) | (((_VALUE_)<< TWELVE_VALUE ) & 3000))

#define Usart_Enable(_CHANNEL_)											SET_BIT((uartArr[(_CHANNEL_)]->USART_CR1),THIRTEEN_VALUE )
#define Usart_EnableTx(_CHANNEL_)										SET_BIT((uartArr[(_CHANNEL_)]->USART_CR1),THREE_VALUE )
#define Usart_EnableRx(_CHANNEL_)										SET_BIT((uartArr[(_CHANNEL_)]->USART_CR1),TWO_VALUE )



#define Usart_Disable(_CHANNEL_)										CLR_BIT((uartArr[(_CHANNEL_)]->USART_CR1),THIRTEEN_VALUE)
#define Usart_DisableTx(_CHANNEL_)										CLR_BIT((uartArr[(_CHANNEL_)]->USART_CR2),THREE_VALUE)
#define Usart_DisableRx(_CHANNEL_)										CLR_BIT((uartArr[(_CHANNEL_)]->USART_CR2),TWO_VALUE)


#define Usart_SetClkInSyncMode(_CHANNEL_,_VALUE_)                 	    WRITE_BIT((uartArr[(_CHANNEL_)]->USART_CR2),ELEVEN_VALUE, (_VALUE_) )


#define Usart_SendBreakFrame(_CHANNEL_)									SET_BIT((uartArr[(_CHANNEL_)]->USART_CR1),ZERO_VALUE )



#define Usart_SetDataReg(_CHANNEL_,_VALUE_)								ASSIGN_REG((uartArr[(_CHANNEL_)]->USART_DR) , (_VALUE_)  )
#define Usart_GetDataReg(_CHANNEL_)						        		(uartArr[(_CHANNEL_)]->USART_DR)


#define Usart_IsTransmitDataRegisterEmpty(_CHANNEL_)				 (READ_BIT( (uartArr[(_CHANNEL_)]->USART_SR),SEVEN_VALUE) == ONE_VALUE )
#define Usart_IsReceiveDataRegisterEmpty(_CHANNEL_)				    (READ_BIT( (uartArr[(_CHANNEL_)]->USART_SR),FIVE_VALUE) == ZERO_VALUE )

/// Interrupt PArt

#define Usart_GetTxCompleteFlag(_CHANNEL_)								 (READ_BIT( (uartArr[(_CHANNEL_)]->USART_SR),SIX_VALUE) )
#define Usart_ClearTxCompleteFlag(_CHANNEL_)							 (CLR_BIT( (uartArr[(_CHANNEL_)]->USART_SR),SIX_VALUE) )

#define Usart_GetRxCompleteFlag(_CHANNEL_)								 (READ_BIT( (uartArr[(_CHANNEL_)]->USART_SR),FIVE_VALUE) )
#define Usart_ClearRxCompleteFlag(_CHANNEL_)							 (CLR_BIT( (uartArr[(_CHANNEL_)]->USART_SR),FIVE_VALUE) )

#define Usart_EnableTxCompleteInterrupt(_CHANNEL_)						(SET_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),SIX_VALUE) )
#define Usart_DisableTxCompleteInterrupt(_CHANNEL_)						(CLR_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),SIX_VALUE) )
#define Usart_IsTxCompleteInterruptEnabled(_CHANNEL_)					(READ_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),SIX_VALUE) )


#define Usart_EnableRxCompleteInterrupt(_CHANNEL_)						(SET_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),FIVE_VALUE) )
#define Usart_DisableRxCompleteInterrupt(_CHANNEL_)						(CLR_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),FIVE_VALUE) )
#define Usart_IsRxCompleteInterruptEnabled(_CHANNEL_)					(READ_BIT( (uartArr[(_CHANNEL_)]->USART_CR1),FIVE_VALUE) )




/********************************** Data Type Declarations ****************************/

//extern uint64 Global_uint64ABP1Freq;
//extern uint64 Global_uint64ABP2Freq;

typedef volatile struct{
  	uint32 USART_SR;
  	uint32 USART_DR;
  	uint32 USART_BRR;
  	uint32 USART_CR1;
  	uint32 USART_CR2;
  	uint32 USART_CR3;
  	uint32 USART_GPTR;
  }USARTx_Type;

#define USART1 	((volatile USARTx_Type*)(0x40013800))
#define USART2 	((volatile USARTx_Type*)(0x40004400))
#define USART3 	((volatile USARTx_Type*)(0x40004800))




static volatile USARTx_Type* uartArr[] = {USART1,USART2,USART3};

/********************************** Software Interfaces Declarations *******************/
static Usart_StatusErrorType Usart_enuSetBaudrate(const Usart_ConfigType* Address_Usart){
	Usart_StatusErrorType Loc_UsartStatusError = USART_STATUS_OK;
	float64 Loc_float64Brr ;
	uint64 Loc_uint64Fraction ;
	uint64 Loc_uint64IntPart ;
	uint8 Loc_uint8OverRun;
	if(Address_Usart == NULL){
		Loc_UsartStatusError = USART_STATUS_NULL_POINTER_ADDRESS;
	}
	else if(Address_Usart->select_sync_mode == USART_SELECT_ASYNCHRONOUS_MODE){
		Loc_uint8OverRun = Address_Usart->select_oversample & 0b10;

		switch(Address_Usart->select_channel_number){

		case USART_SELECT_CHANNEL_1:

//			Loc_float64Brr = (float64)Global_uint64ABP2Freq/(Address_Usart->baude_rate)/(8*(2-Loc_uint8OverRun));
			Loc_float64Brr = (float64)8000000/(Address_Usart->baude_rate)/(8*(2-Loc_uint8OverRun));

			Loc_uint64IntPart = (uint64)Loc_float64Brr;
			Loc_uint64Fraction =(Loc_float64Brr-Loc_uint64IntPart)*16+0.5;
			if(Loc_uint64Fraction ==16){
				Loc_uint64Fraction = 0;
				Loc_uint64IntPart++;
			}
			Usart_SetBaudrateIntPart(Address_Usart->select_channel_number,Loc_uint64IntPart);
			Usart_SetBaudrateFractionPart(Address_Usart->select_channel_number,Loc_uint64Fraction);

			break;



		case USART_SELECT_CHANNEL_2:
		case USART_SELECT_CHANNEL_3:


			Loc_float64Brr = (float64)8000000/(Address_Usart->baude_rate)/(8*(2-Loc_uint8OverRun));
			Loc_uint64IntPart = (uint64)Loc_float64Brr;
			Loc_uint64Fraction =(Loc_float64Brr-Loc_uint64IntPart)*16+0.5;
			if(Loc_uint64Fraction ==16){
				Loc_uint64Fraction = 0;
				Loc_uint64IntPart++;
			}
			Usart_SetBaudrateIntPart(Address_Usart->select_channel_number,Loc_uint64IntPart);
			Usart_SetBaudrateFractionPart(Address_Usart->select_channel_number,Loc_uint64IntPart);

			break;


		default :
			Loc_UsartStatusError = USART_STATUS_FAIL;




		}
	}
	else{
		/* Sync Mode */
		Loc_UsartStatusError = USART_STATUS_FAIL;
	}
	return Loc_UsartStatusError;

}


static Usart_StatusErrorType Usart_enuEnableRccClock(const Usart_ConfigType* Address_Usart){
	Usart_StatusErrorType Loc_UsartStatusError = USART_STATUS_OK;

		if(Address_Usart == NULL){
			Loc_UsartStatusError = USART_STATUS_NULL_POINTER_ADDRESS;
		}
		else {
			switch(Address_Usart->select_channel_number){
			case USART_SELECT_CHANNEL_1:
				Rcc_enuControl_APB2_Peripheral(RCC_APB2_Periph_USART1,RCC_Periph_ENABLE);
				break;


			case USART_SELECT_CHANNEL_2:
				Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_USART2,RCC_Periph_ENABLE);
				break;

			case USART_SELECT_CHANNEL_3:
				Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_USART3,RCC_Periph_ENABLE);
				break;


			default :
					Loc_UsartStatusError = USART_STATUS_FAIL;

			}
		}

		return Loc_UsartStatusError;

}


#endif /* UART_USART_PRIVATE_H_ */

