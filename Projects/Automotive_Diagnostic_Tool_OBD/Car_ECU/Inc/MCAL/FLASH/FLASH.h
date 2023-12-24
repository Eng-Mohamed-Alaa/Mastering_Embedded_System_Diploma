/**************************************************************************/
/* Filename						: FLASH.h                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/

#ifndef MCAL_FLASH_FLASH_H_
#define MCAL_FLASH_FLASH_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define FLASH_BASE_ADDRESS			0x08000000
#define FLASH_LAST_ADDRESS			(63*0x400+FLASH_BASE_ADDRESS+0x3FE)


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/



typedef enum{
  	FLASH_STATUS_FAIL,
  	FLASH_STATUS_OK,
  	FLASH_STATUS_NULL_POINTER_ADDRESS
  }Flash_ErrorStatusType;


/********************************** Software Interfaces Declarations *******************/


Flash_ErrorStatusType Flash_enuWriteHalfWordAt_Sync(uint32 Copy_uint32Address,uint16 Copy_uint16Data);
Flash_ErrorStatusType Flash_enuErasePageAt_Sync(uint8 Copy_uint8PageIndexFrom0To63);


#endif /* MCAL_FLASH_FLASH_H_ */
