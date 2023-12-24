/**************************************************************************/
/* Filename						: FLASH_private.h                             */
/* Author  	    				: Muhammad (Ali )Ammar                          */
/* Date 						: Dec 6, 2023	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/

#ifndef MCAL_FLASH_FLASH_PRIVATE_H_
#define MCAL_FLASH_FLASH_PRIVATE_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


typedef volatile struct{
  	uint32 FLASH_ACR;
  	uint32 FLASH_KEYR;
  	uint32 FLASH_OPTKEYR;
  	uint32 FLASH_SR;
  	uint32 FLASH_CR;
  	uint32 FLASH_AR;
  	uint32 RESERVERD;
  	uint32 FLASH_OBR;
  	uint32 FLASH_WRPR;

  }FLASH_Type;


#define FLASH1 	((volatile FLASH_Type*)(0x40022000))

/********************************** Macros Function Declarations *********************/
#define FLASH_LOCK_KEY1				0x45670123
#define FLASH_LOCK_KEY2				0xCDEF89AB

#define Flash_IsFlashOperatingBusy()					(   READ_BIT( (FLASH1->FLASH_SR),ZERO_VALUE )  == ONE_VALUE  )

#define Flash_IsFlashLocked()			    		(   READ_BIT( (FLASH1->FLASH_CR),SEVEN_VALUE )  == ONE_VALUE  )

#define Flash_Lock()							(   SET_BIT( (FLASH1->FLASH_CR),SEVEN_VALUE )   )

#define Flash_Unlock()							do{\
													if(Flash_IsFlashLocked() == ONE_VALUE){ \
													ASSIGN_REG((FLASH1->FLASH_KEYR),(FLASH_LOCK_KEY1)) ;\
													ASSIGN_REG((FLASH1->FLASH_KEYR),(FLASH_LOCK_KEY2)) ;\
													}\
											}while(ZERO_VALUE)

#define Flash_SetEraseModePagex(_INDEX_)				do{\
														(   SET_BIT( (FLASH1->FLASH_CR),ONE_VALUE )  ) ;\
														ASSIGN_REG((FLASH1->FLASH_AR) ,(  (_INDEX_<<TEN_VALUE)+ FLASH_BASE_ADDRESS)  );\
														}while(ZERO_VALUE)

#define Flash_StartErasingAction()					do{\
													while(Flash_IsFlashOperatingBusy() ==ONE_VALUE );\
													(   SET_BIT( (FLASH1->FLASH_CR),SIX_VALUE )  ) ;\
													while(Flash_IsFlashOperatingBusy() ==ONE_VALUE );\
											}while(ZERO_VALUE)


#define Flash_EndOfOperation()				(   SET_BIT( (FLASH1->FLASH_SR),FIVE_VALUE )  )
#define Flash_GetOutOfEraseMode()					(   CLR_BIT( (FLASH1->FLASH_CR),ONE_VALUE )   )

#define Flash_SetFlashWritingMode()						(   SET_BIT( (FLASH1->FLASH_CR),ZERO_VALUE )  )
#define Flash_GetOutOfFlashWritingMode()						(   CLR_BIT( (FLASH1->FLASH_CR),ZERO_VALUE )  )


/********************************** Data Type Declarations ****************************/



/********************************** Software Interfaces Declarations *******************/





#endif /* MCAL_FLASH_FLASH_PRIVATE_H_ */
