/**************************************************************************/
/* Filename						: USART.h                                 */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 22, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/



#ifndef UART_USART_H_
#define UART_USART_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/

typedef enum{
	USART_SELECT_CHANNEL_1,
	USART_SELECT_CHANNEL_2,
	USART_SELECT_CHANNEL_3
}Usart_SelectChannelType;

typedef enum{

	USART_SELECT_CHARACTER_SIZE_8_BIT,
	USART_SELECT_CHARACTER_SIZE_9_BIT
}Usart_SelectCharacterSizeType;


typedef enum{
	USART_SELECT_ASYNCHRONOUS_MODE,
	USART_SELECT_SYNCHRONOUS_MODE

}Usart_SelectSyncModeType;


typedef enum{
	USART_SELECT_STOP_1_BIT,
	USART_SELECT_STOP_point_5_BIT,
	USART_SELECT_STOP_2_BIT,
	USART_SELECT_STOP_1_point_5_BIT
}Usart_SelectStopBitsType;


typedef enum{
	USART_SELECT_PARITY_DISABLE,
	USART_SELECT_PARITY_EVEN=0b10,
	USART_SELECT_PARITY_ODD=0b11
}Usart_SelectParityBitsType;


typedef enum{
	USART_STATUS_FAIL,
	USART_STATUS_OK,
	USART_STATUS_NULL_POINTER_ADDRESS,
}Usart_StatusErrorType;

typedef enum{

	USART_SELECT_OVERSAMPLE_BY_16_THREE_SAMPLE_METHOD=0b00,
	USART_SELECT_OVERSAMPLE_BY_16_SINGLE_SAMPLE_METHOD=0b01,
	USART_SELECT_OVERSAMPLE_BY_8_THREE_SAMPLE_METHOD=0b10,
	USART_SELECT_OVERSAMPLE_BY_8_SINGLE_SAMPLE_METHOD=0b11
}Usart_SelectOversampleType;

typedef enum{

	USART_SELECT_CLOCK_POLARITY_DONT_CARE_ASYNC_MODE,
	USART_SELECT_CLOCK_POLARITY_LOW=0,
	USART_SELECT_CLOCK_POLARITY_HIGH=1
}Usart_SelectClockPolarityType;


typedef enum{

	USART_SELECT_CLOCK_PHASE_DONT_CARE_ASYNC_MODE,
	USART_SELECT_CLOCK_PHASE_READ_OR_CAPUTRE_FIRST=0,
	USART_SELECT_CLOCK_PHASE_WRITE_FIRST=1
}Usart_SelectClockPhaseType;

typedef enum{

	USART_SELECT_DMA_TX_DISABLE_DMA_RX_DISABLE=0b00,
	USART_SELECT_DMA_TX_DISABLE_DMA_RX_ENABLE=0b01,
	USART_SELECT_DMA_TX_ENABLE_DMA_RX_DISABLE=0b10,
	USART_SELECT_DMA_TX_ENABLE_DMA_RX_ENABLE=0b11
}Usart_SelectDmaEnableType;


typedef enum{
	USART_SELECT_FULL_DUPLEX,
	USART_SELECT_HALF_DUPLEX_SINGLE_WIRE

}Usart_SelectFullDuplexHalfDuplexModeType;


typedef struct{
	Usart_SelectChannelType select_channel_number;
	Usart_SelectCharacterSizeType select_character_size;
	Usart_SelectSyncModeType select_sync_mode;
	Usart_SelectStopBitsType select_stop_bits;
	Usart_SelectParityBitsType select_parity_bits;
	Usart_SelectOversampleType select_oversample;
	Usart_SelectClockPolarityType select_clock_polarity;
	Usart_SelectClockPhaseType select_clock_phase;
	Usart_SelectDmaEnableType select_dma_tx_enable_rx_enable;
	Usart_SelectFullDuplexHalfDuplexModeType select_full_duplex_half_duplex;
	uint64 						baude_rate;

}Usart_ConfigType;

/********************************** Software Interfaces Declarations *******************/


Usart_StatusErrorType Usart_enuInit(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuDeInit(const Usart_ConfigType* Address_Usart);




Usart_StatusErrorType Usart_enuTransmitCharBlocking(const Usart_ConfigType* Address_Usart, uint16 Copy_uint16Data);
Usart_StatusErrorType Usart_enuTransmitStringBlocking(const Usart_ConfigType* Address_Usart, uint8* Address_Data);
Usart_StatusErrorType Usart_enuTransmitNumberOfChar(const Usart_ConfigType* Address_Usart, uint8* Address_Data,uint8 Copy_uint8NumberBytes);
Usart_StatusErrorType Usart_enuReceiveCharBlocking(const Usart_ConfigType* Address_Usart, uint16* Address_Data);
Usart_StatusErrorType Usart_enuReceiveStringBlocking(const Usart_ConfigType* Address_Usart, uint8* Address_Data);

Usart_StatusErrorType Usart_enuSetBreakFrame(const Usart_ConfigType* Address_Usart);


/////////////////////////////// Interrupt Part ////////////////////////////////////////////

/*
 * Look At Page 1006
 */
Usart_StatusErrorType Usart_enuEnableRxInterrupt(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuDisableRxInterrupt(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuSetCallbackRxFunction(const Usart_ConfigType* Address_Usart,void (*callback)(uint16 Copy_uint16Result));


Usart_StatusErrorType Usart_enuEnableTxCompleteInterrupt(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuDisableTxCompleteInterrupt(const Usart_ConfigType* Address_Usart);
Usart_StatusErrorType Usart_enuSetCallbackTxCompleteFunction(const Usart_ConfigType* Address_Usart,void (*callback)(void));




/*
 * Interrupt Part
 */




#endif /* UART_USART_H_ */
