/*
 * HC_05.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Mahmoud Tariq
 */
/*================ Services Includes =======================*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"
#include "../SERVICES/Bit_Wise_Operations.h"
/*================ MCAL Includes ===========================*/
#include "../INC/MCAL/GPIO/GPIO.h"
#include "../INC/MCAL/UART/USART.h"
/*==================HAL Includes ===========================*/
#include"../INC/HAL/HC_05/HC_05.h"



uint16 HC05_u8Recieve(void)
{	static uint8 Entry_here = 0;
	uint16 Return_val = 0;
	static Usart_ConfigType Usart1;

	if(Entry_here == 0)
	{
		Entry_here++;
	}
	if(Entry_here == 1)
	{
		/*UART Initializations*/
		Usart1 = (Usart_ConfigType){

						.baude_rate = 9600,
						.select_channel_number = USART_SELECT_CHANNEL_1,
						.select_character_size = USART_SELECT_CHARACTER_SIZE_8_BIT,
						.select_clock_phase = USART_SELECT_CLOCK_PHASE_DONT_CARE_ASYNC_MODE,
						.select_clock_polarity = USART_SELECT_CLOCK_POLARITY_DONT_CARE_ASYNC_MODE,
						.select_dma_tx_enable_rx_enable = USART_SELECT_DMA_TX_DISABLE_DMA_RX_DISABLE,
						.select_full_duplex_half_duplex = USART_SELECT_FULL_DUPLEX,
						.select_oversample = USART_SELECT_OVERSAMPLE_BY_16_THREE_SAMPLE_METHOD,
						.select_parity_bits = USART_SELECT_PARITY_DISABLE,
						.select_stop_bits = USART_SELECT_STOP_1_BIT,
						.select_sync_mode = USART_SELECT_ASYNCHRONOUS_MODE
				};

				/* USART TX PA9 */
				GPIO_PIN_INIT(GPIO_PIN_9,GPIO_PORT_A,AF_output_Push_pull,GPIO_max_speed_2_MHz,pull_UP);

				/* USART RX PA10*/
				GPIO_PIN_INIT(GPIO_PIN_10,GPIO_PORT_A,InputFloating,GPIO_INPUT,FLOATING);
				Usart_enuInit(&Usart1);
				Entry_here = 2;

	}

	else
	{

		Usart_enuReceiveCharBlocking(&Usart1, &Return_val);

	}
	return Return_val;
}
