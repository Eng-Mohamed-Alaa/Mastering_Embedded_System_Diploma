/***************************************************************/
/* Author    : Mahmoud Korayem                                 */
/* Version   : V01                                             */
/* Date      : 24 NOV 2022                                     */
/***************************************************************/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../Inc/MCAL/GPIO/GPIO.h"
//#include "GPIO.h"

#include "../Inc/MCAL/SPI/SPI_config.h"
#include "../Inc/MCAL/SPI/SPI_private.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"

void (*CallBack)(uint8);

void MSPI1_voidInit(void)
{
	MSPI1->CR1 = 0x0347;
}

void MSPI1_voidSendReceiveSynch(uint8 Copy_uint8DataToTransmit, uint8 *Copy_DataToReceive)
{
	/* Clear For Slave Select Pin */
	GPIO_set_PIN_value(MSPI1_SLAVE_PIN,GPIO_LOGIC_LOW);
	
	/* Send Data */
	MSPI1 -> DR = Copy_uint8DataToTransmit;
	
	/* Wait Busy Flag to finish */
																																				while (GET_BIT(MSPI1 -> SR, 7) == 1);

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI1 -> DR;
	
	/* Set Salve Select Pin */
	GPIO_set_PIN_value(MSPI1_SLAVE_PIN,GPIO_LOGIC_HIGH);
}

