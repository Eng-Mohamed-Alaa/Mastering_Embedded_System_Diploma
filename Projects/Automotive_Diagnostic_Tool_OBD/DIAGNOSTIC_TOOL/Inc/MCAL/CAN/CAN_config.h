/**************************************************************************/
/* Filename						: CAN_config.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 15, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef CAN_CAN_CONFIG_H_
#define CAN_CAN_CONFIG_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

/*
 * From 1 To 28
 */
#define NUMBER_OF_CAN1_FILTERS				28


/*	             _ARGU_1       	         	 | 		    _ARGU_2 	   ||       _ARGU_3 			|| _ARGU_4   || 				 ||
 * 		     							     | 	    			       || 	    				    || 		     ||	 	             ||
 * 			 	FILTER_ON					 |   	 MASK_MODE         ||     SCALE_16BIT_DUAL		|| FIFO_0    ||    REG1 Value    ||		REG2 Value
 * 			  	FILTER_OFF					 | 		ID_LIST_MODE       ||     SCALE_32BIT_SINGLE    || FIFO_1  	 ||			         ||
 * 				                    		 |    					   ||     						||	 	     ||	    	         ||
 */


/*
 * 	STD     , EXID   , IDE  , RTR,  0             (ID_LIST_MODE)
 * 	11bits  , 18bit  , 1bit ,1bit , 1bit
 *
 * 	-----------------------------------------------------------------
 * 	STD     , RTR,  IDE,   EXID[17:15]				 (MASK_MODE)
 * 	11bits  , 1bit, 1bit,  3bit
 */
#define FILTER0_CONFG					FILTER_ON, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x20000000, 0x20000000
#define FILTER1_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER2_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER3_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER4_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER5_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER6_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER7_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER8_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER9_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER10_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER11_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER12_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000
#define FILTER13_CONFG					FILTER_OFF, ID_LIST_MODE, SCALE_32BIT_SINGLE, FIFO_0, 0x00000000, 0x00000000



/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/



/********************************** Software Interfaces Declarations *******************/



#endif /* CAN_CAN_CONFIG_H_ */
