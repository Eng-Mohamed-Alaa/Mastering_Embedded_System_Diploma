/**************************************************************************/
/* Filename						: FEE.h                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/

#ifndef HAL_FEE_FEE_H_
#define HAL_FEE_FEE_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum{
  	FEE_STATUS_FAIL,
  	FEE_STATUS_OK,
  	FEE_STATUS_NULL_POINTER_ADDRESS
  }Fee_ErrorStatusType;


/********************************** Software Interfaces Declarations *******************/


 Fee_ErrorStatusType Fee_enuWriteHalfWordAt_Sync(uint32 Copy_uint32Address,uint16 Copy_uint16Data);


#endif /* HAL_FEE_FEE_H_ */
