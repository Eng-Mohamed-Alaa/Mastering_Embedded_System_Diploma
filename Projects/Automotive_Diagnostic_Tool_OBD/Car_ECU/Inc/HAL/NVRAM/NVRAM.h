/**************************************************************************/
/* Filename						: NVRAM.h                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/

#ifndef HAL_NVRAM_NVRAM_H_
#define HAL_NVRAM_NVRAM_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/


typedef enum{
  	NVRAM_STATUS_FAIL,
	NVRAM_STATUS_OK,
	NVRAM_STATUS_NULL_POINTER_ADDRESS
  }Nvram_ErrorStatusType;


/********************************** Software Interfaces Declarations *******************/


  Nvram_ErrorStatusType Nvram_EnableFeature(uint32 Copy_uint32Address);
  Nvram_ErrorStatusType Nvram_DisableFeature(uint32 Copy_uint32Address);




#endif /* HAL_NVRAM_NVRAM_H_ */
