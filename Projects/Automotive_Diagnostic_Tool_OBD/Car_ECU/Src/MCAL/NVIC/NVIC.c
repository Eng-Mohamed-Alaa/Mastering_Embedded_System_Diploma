/**************************************************************************/
/* Filename						: NVIC.c                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 12, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/





/********************************** Includes *********************************************/


#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"


#include "../../../Inc/MCAL/SCB/SCB.h"


#include "../../../Inc/MCAL/NVIC/NVIC_private.h"
#include "../../../Inc/MCAL/NVIC/NVIC.h"

/********************************** Private declaration **********************************/



/********************************** Data Type Declarations ****************************/

extern Scb_SelectGroupPriorityAndSubPriorityType Global_GroupPrioritySelection;

/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/




/******************************* Software Interfaces Implementation *******************/

Nvic_ErrorStatusType Nvic_enuEnableInterrupt(Nvic_IndexPeripheralType Copy_NvicIndex){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;
	uint8 Loc_uint8RegNumber = Copy_NvicIndex/THIRTYTWO_VALUE;
	uint8 Loc_uint8BitNumber = Copy_NvicIndex%THIRTYTWO_VALUE;

	SET_BIT(*GlobalStatic_NvicIsrEnableArr[Loc_uint8RegNumber], Loc_uint8BitNumber);


	return Loc_NvicErrorStatus;
}
Nvic_ErrorStatusType Nvic_enuDisableInterrupt(Nvic_IndexPeripheralType Copy_NvicIndex){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;
	uint8 Loc_uint8RegNumber = Copy_NvicIndex/THIRTYTWO_VALUE;
	uint8 Loc_uint8BitNumber = Copy_NvicIndex%THIRTYTWO_VALUE;

	SET_BIT(*GlobalStatic_NvicIsrDisableArr[Loc_uint8RegNumber], Loc_uint8BitNumber);

	return Loc_NvicErrorStatus;
}


Nvic_ErrorStatusType Nvic_enuSetPendingFlag(Nvic_IndexPeripheralType Copy_NvicIndex){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;

	uint8 Loc_uint8RegNumber = Copy_NvicIndex/THIRTYTWO_VALUE;
	uint8 Loc_uint8BitNumber = Copy_NvicIndex%THIRTYTWO_VALUE;

	SET_BIT(*GlobalStatic_NvicPendingFlagSetArr[Loc_uint8RegNumber], Loc_uint8BitNumber);


	return Loc_NvicErrorStatus;
}

Nvic_ErrorStatusType Nvic_enuClearPendingFlag(Nvic_IndexPeripheralType Copy_NvicIndex){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;

	uint8 Loc_uint8RegNumber = Copy_NvicIndex/THIRTYTWO_VALUE;
	uint8 Loc_uint8BitNumber = Copy_NvicIndex%THIRTYTWO_VALUE;

	SET_BIT(*GlobalStatic_NvicPendingFlagClearArr[Loc_uint8RegNumber], Loc_uint8BitNumber);


	return Loc_NvicErrorStatus;
}


Nvic_ErrorStatusType Nvic_enuGetActiveFlag(Nvic_IndexPeripheralType Copy_NvicIndex, Nvic_ActiveFlagType* Address_Result){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;
	uint8 Loc_uint8RegNumber;
	uint8 Loc_uint8BitNumber;


	if(NULL == Address_Result){
		Loc_NvicErrorStatus = NVIC_STATUS_NULL_POINTER_ADDRESS;
	}
	else{
		 Loc_uint8RegNumber = Copy_NvicIndex/THIRTYTWO_VALUE;
		 Loc_uint8BitNumber = Copy_NvicIndex%THIRTYTWO_VALUE;
		*Address_Result =  (Nvic_ActiveFlagType) READ_BIT(*GlobalStatic_NvicActiveFlagArr[Loc_uint8RegNumber], Loc_uint8BitNumber);
	}

	return Loc_NvicErrorStatus;
}

Nvic_ErrorStatusType Nvic_SetInterruptPriority(Nvic_IndexPeripheralType Copy_NvicIndex,Nvic_SelectGroupxType Copy_enuGroupNumber,
																Nvic_SelectSubxType Copy_enuSubNumber){
	Nvic_ErrorStatusType Loc_NvicErrorStatus = NVIC_STATUS_OK;
	uint8 Loc_uint8PriorityResult= ZERO_VALUE;

	switch(Global_GroupPrioritySelection){

	case SCB_SELECT_GROUP_PRIORITY_16_AND_SUB_PRIORITY_ZERO :
		Loc_uint8PriorityResult = Copy_enuGroupNumber;
		break;

	case SCB_SELECT_GROUP_PRIORITY_4_AND_SUB_PRIORITY_4:
		Loc_uint8PriorityResult = ((Copy_enuGroupNumber & 0b11) <<TWO_VALUE) | ((Copy_enuSubNumber & 0b11) <<ZERO_VALUE);
		break;
	case SCB_SELECT_GROUP_PRIORITY_2_AND_SUB_PRIORITY_8:
		Loc_uint8PriorityResult = ((Copy_enuGroupNumber & 0b1) <<ONE_VALUE) | ((Copy_enuSubNumber & 0b111) <<ZERO_VALUE);
		break;

	case SCB_SELECT_GROUP_PRIORITY_ZERO_AND_SUB_PRIORITY_16:
		Loc_uint8PriorityResult = Copy_enuSubNumber;
		break;

	default :
		Loc_NvicErrorStatus = NVIC_STATUS_FAIL;
	}


	NVIC_IPR[Copy_NvicIndex] = Loc_uint8PriorityResult<<FOUR_VALUE; // first 4 bits reserved


	return Loc_NvicErrorStatus;
}





/**************************** Private Software Interface Implementation **************/

