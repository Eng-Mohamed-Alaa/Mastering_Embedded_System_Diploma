/**************************************************************************/
/* Filename						: SCB.c                            */
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
#include "../../../Inc/MCAL/SCB/SCB_private.h"


/**********************************  declaration **********************************/

/* it's used for NVIC Driver */
Scb_SelectGroupPriorityAndSubPriorityType Global_GroupPrioritySelection;

/********************************** Data Type Declarations ****************************/


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/




/******************************* Software Interfaces Implementation *******************/
SCB_ErrorStatusType Scb_enuSetGroupPrioirty(Scb_SelectGroupPriorityAndSubPriorityType Copy_enuSelectGroupPriority){

	SCB_ErrorStatusType Loc_enuScbErrorStatus = SCB_STATUS_OK;

	Scb_SetGroupPrioirty(Copy_enuSelectGroupPriority);

	/* it's used for NVIC Driver */
	Global_GroupPrioritySelection =Copy_enuSelectGroupPriority;
	return Loc_enuScbErrorStatus;
}


/**************************** Private Software Interface Implementation **************/

