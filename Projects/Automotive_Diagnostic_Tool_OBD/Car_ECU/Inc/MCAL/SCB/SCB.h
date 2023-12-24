/**************************************************************************/
/* Filename						: SCB.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 12, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef SCB_SCB_H_
#define SCB_SCB_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum{
	SCB_SELECT_GROUP_PRIORITY_16_AND_SUB_PRIORITY_ZERO,
	SCB_SELECT_GROUP_PRIORITY_4_AND_SUB_PRIORITY_4= 0b100,
	SCB_SELECT_GROUP_PRIORITY_2_AND_SUB_PRIORITY_8=0b110,
	SCB_SELECT_GROUP_PRIORITY_ZERO_AND_SUB_PRIORITY_16=0b111
}Scb_SelectGroupPriorityAndSubPriorityType;



typedef enum{
	SCB_STATUS_FAIL,
	SCB_STATUS_OK,
	SCB_STATUS_NULL_POINTER_ADDRESS
}SCB_ErrorStatusType;

/********************************** Software Interfaces Declarations *******************/
SCB_ErrorStatusType Scb_enuSetGroupPrioirty(Scb_SelectGroupPriorityAndSubPriorityType Copy_enuSelectGroupPriority);


#endif /* SCB_SCB_H_ */
