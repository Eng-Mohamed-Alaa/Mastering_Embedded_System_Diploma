/**************************************************************************/
/* Filename						: NVRAM.c                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/





/********************************** Includes *********************************************/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../../../Inc/MCAL/FLASH/FLASH.h"
#include "../../../Inc/HAL/FEE/FEE.h"
#include "../../../Inc/HAL/NVRAM/NVRAM.h"


/********************************** Private declaration **********************************/



/********************************** Data Type Declarations ****************************/


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/

/********************************** Software Interfaces  Implementation*******************/


  Nvram_ErrorStatusType Nvram_EnableFeature(uint32 Copy_uint32Address){
	  Nvram_ErrorStatusType Loc_NvramErrorStatus = NVRAM_STATUS_OK;

	  Fee_enuWriteHalfWordAt_Sync(Copy_uint32Address, ONE_VALUE);

	  return Loc_NvramErrorStatus;
  }
  Nvram_ErrorStatusType Nvram_DisableFeature(uint32 Copy_uint32Address){
	  Nvram_ErrorStatusType Loc_NvramErrorStatus = NVRAM_STATUS_OK;

	  Fee_enuWriteHalfWordAt_Sync(Copy_uint32Address, ZERO_VALUE);

	  return Loc_NvramErrorStatus;
  }



/**************************** Private Software Interface Implementation **************/
