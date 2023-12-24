/**************************************************************************/
/* Filename						: FEE.c                             */
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

/********************************** Private declaration **********************************/



/********************************** Data Type Declarations ****************************/


/********************************** Macros Declarations *******************************/

/********************************** Macros Function Declarations *********************/




/******************************* Software Interfaces Implementation *******************/
 Fee_ErrorStatusType Fee_enuWriteHalfWordAt_Sync(uint32 Copy_uint32Address,uint16 Copy_uint16Data){
	 Fee_ErrorStatusType Loc_enuFeeErrorStatus = FEE_STATUS_OK;
	 uint8 Loc_u8PageIndex;
	 uint32 Loc_u32PageStartAddress;
	 uint32 Loc_u32PageStartAddressTemp;
	 uint16 Loc_u16Buffer[512];
	 uint8 Loc_u8DataIndex ;
	 uint16 Loc_u16Counter ;
	 short int y;
			if(Copy_uint32Address>FLASH_LAST_ADDRESS || Copy_uint32Address<FLASH_BASE_ADDRESS){
				Loc_enuFeeErrorStatus = FEE_STATUS_FAIL;
			}
			else{

				/******** I think Interrupt Should be Disabled Here ***************/

				Loc_u8PageIndex = (Copy_uint32Address-FLASH_BASE_ADDRESS)/0x400;
				Loc_u32PageStartAddress = Loc_u8PageIndex*0x400+FLASH_BASE_ADDRESS;
				Loc_u32PageStartAddressTemp = Loc_u32PageStartAddress;
				Loc_u8DataIndex = (Copy_uint32Address-Loc_u32PageStartAddress)>>ONE_VALUE;

				/* Copy Data First */
				for(Loc_u16Counter = ZERO_VALUE;Loc_u16Counter<512;Loc_u16Counter++){

					Loc_u16Buffer[Loc_u16Counter]= *((uint16*)(Loc_u32PageStartAddressTemp));
					Loc_u32PageStartAddressTemp+=TWO_VALUE;
				}

				/* Erase Page */
				Flash_enuErasePageAt_Sync(Loc_u8PageIndex);


				/* Write New Data */
				Loc_u16Buffer[Loc_u8DataIndex]=Copy_uint16Data;
				for(Loc_u16Counter = ZERO_VALUE;Loc_u16Counter<512;Loc_u16Counter++){

					Flash_enuWriteHalfWordAt_Sync(Loc_u32PageStartAddress, Loc_u16Buffer[Loc_u16Counter]);
					Loc_u32PageStartAddress+=TWO_VALUE;
				}
				 y = *((uint16*)Copy_uint32Address);

			}



			return Loc_enuFeeErrorStatus;
 }


/**************************** Private Software Interface Implementation **************/
