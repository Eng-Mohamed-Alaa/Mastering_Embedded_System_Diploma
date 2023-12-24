/**************************************************************************/
/* Filename						: SCB_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 12, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef SCB_SCB_PRIVATE_H_
#define SCB_SCB_PRIVATE_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define SCB_ACTLR		(*(volatile uint32*)(0xE000E008 ))
#define SCB_CPUID		(*(volatile uint32*)(0xE000ED00 ))
#define SCB_ICSR		(*(volatile uint32*)(0xE000ED04))
#define SCB_VTOR		(*(volatile uint32*)(0xE000ED08 ))
#define SCB_AIRCR		(*(volatile uint32*)(0xE000ED0C ))
#define SCB_SCR			(*(volatile uint32*)(0xE000ED10 ))
#define SCB_CCR			(*(volatile uint32*)(0xE000ED14 ))
#define SCB_SHPR1		(*(volatile uint32*)(0xE000ED18 ))
#define SCB_SHPR2		(*(volatile uint32*)(0xE000ED1C ))
#define SCB_SHPR3		(*(volatile uint32*)(0xE000ED20 ))
#define SCB_SHCSR		(*(volatile uint32*)(0xE000ED24 ))
#define SCB_CFSR		(*(volatile uint32*)(0xE000ED28 ))
#define SCB_MMSR		(*(volatile uint32*)(0xE000ED28 ))
#define SCB_BFSR		(*(volatile uint32*)(0xE000ED29 ))
#define SCB_USFR		(*(volatile uint32*)(0xE000ED2A ))
#define SCB_HFSR		(*(volatile uint32*)(0xE000ED2C ))
#define SCB_MMAR		(*(volatile uint32*)(0xE000ED34 ))
#define SCB_BFAR		(*(volatile uint32*)(0xE000ED38 ))
#define SCB_AFSR		(*(volatile uint32*)(0xE000ED3C ))


#define SCB_AIRCR_VECTKEY			0x5FA



/********************************** Macros Function Declarations *********************/


#define Scb_SetGroupPrioirty(_VALUE_)				(SCB_AIRCR) = ( (SCB_AIRCR_VECTKEY<<SIXTEEN_VALUE) | ( (_VALUE_<<EIGHT_VALUE) & 0x700))

/********************************** Data Type Declarations ****************************/



/********************************** Software Interfaces Declarations *******************/



#endif /* SCB_SCB_PRIVATE_H_ */
