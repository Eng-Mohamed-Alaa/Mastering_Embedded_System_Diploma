/**************************************************************************/
/* Filename						: FLASH.c                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../../../Inc/MCAL/RCC/RCC.h"


#include "../../../Inc/MCAL/FLASH/FLASH.h"
#include "../../../Inc/MCAL/FLASH/FLASH_private.h"





/********************************** Private declaration **********************************/



/********************************** Data Type Declarations ****************************/


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/




/******************************* Software Interfaces Implementation *******************/


Flash_ErrorStatusType Flash_enuWriteHalfWordAt_Sync(uint32 Copy_uint32Address,uint16 Copy_uint16Data){
	Flash_ErrorStatusType Loc_enuFlashErrorStatus = FLASH_STATUS_OK;

		if(Copy_uint32Address>FLASH_LAST_ADDRESS || Copy_uint32Address<FLASH_BASE_ADDRESS){
			Loc_enuFlashErrorStatus = FLASH_STATUS_FAIL;
		}
		else{
			/* wait busy flag */
			while(Flash_IsFlashOperatingBusy() == ONE_VALUE);

			/* Flash Unlcok */
			Flash_Unlock();

			/* Enter Write Mode */
			Flash_SetFlashWritingMode();

			/* start writing */
			*((volatile uint16*)(Copy_uint32Address))=Copy_uint16Data;

			/* wait busy flag */
			while(Flash_IsFlashOperatingBusy() == ONE_VALUE);

			/* End of operation */
			Flash_EndOfOperation();

			/* Get Out of Writing mode Mode */
			Flash_GetOutOfFlashWritingMode();


			/* Flash Lock */
			Flash_Lock();
		}



		return Loc_enuFlashErrorStatus;
}



Flash_ErrorStatusType Flash_enuErasePageAt_Sync(uint8 Copy_uint8PageIndexFrom0To63){
	Flash_ErrorStatusType Loc_enuFlashErrorStatus = FLASH_STATUS_OK;

	if(Copy_uint8PageIndexFrom0To63>63){
		Loc_enuFlashErrorStatus = FLASH_STATUS_FAIL;
	}
	else{
		/* wait busy flag */
		while(Flash_IsFlashOperatingBusy() == ONE_VALUE);

		/* Flash Unlcok */
		Flash_Unlock();

		/* Select Page Operation Mode */
		Flash_SetEraseModePagex(Copy_uint8PageIndexFrom0To63);

		/* Start Erasing Sync */
		Flash_StartErasingAction();

		/* End of operation */
		Flash_EndOfOperation();

		/* Get Out of Erase Mode */
		Flash_GetOutOfEraseMode();


		/* Flash Lock */
		Flash_Lock();
	}



	return Loc_enuFlashErrorStatus;
}


/**************************** Private Software Interface Implementation **************/
