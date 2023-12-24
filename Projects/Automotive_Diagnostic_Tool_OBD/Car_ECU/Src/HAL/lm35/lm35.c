/*
 * lm35.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Mahmoud Tariq
 */


/*================ Services Includes =======================*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"
#include "../SERVICES/Bit_Wise_Operations.h"
/*================ MCAL Includes ===========================*/
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/ADC/ADC.h"
/*==================HAL Includes ===========================*/
#include "HAL/lm35/LM35.h"

void lm35_VidInit(void)
{
	ADC_vidInit();
}
uint16 lm35_u16Read(uint8 copy_u8ADC_Channel,Puint16 add_pu16_lm35_val)
{
	ADC_enu_Read_Regular_Channel(add_pu16_lm35_val);
	return (uint16)( ((uint32) ((*add_pu16_lm35_val)*150)) /4096);

}

