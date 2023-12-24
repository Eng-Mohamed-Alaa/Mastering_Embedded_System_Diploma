/**************************************************************************/
/* Filename						: MAGIC_NUMBERS.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: 21 Oct 2023  	           	 	      	 */
/* Version 	 					: V01                                     */
/* MicroController  			: AVR 								  	  */
/**************************************************************************/



#ifndef SERIVICES_INCLUDE_MAGIC_NUMBERS_H_
#define SERIVICES_INCLUDE_MAGIC_NUMBERS_H_

/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/

#define ZERO_VALUE			0
#define ONE_VALUE			1
#define TWO_VALUE			2
#define THREE_VALUE			3
#define FOUR_VALUE			4
#define FIVE_VALUE			5
#define SIX_VALUE			6
#define SEVEN_VALUE			7
#define EIGHT_VALUE			8
#define NINE_VALUE			9
#define TEN_VALUE			10
#define ELEVEN_VALUE		11
#define TWELVE_VALUE		12
#define THIRTEEN_VALUE		13
#define FOURTEEN_VALUE		14
#define FIFTEEN_VALUE		15
#define SIXTEEN_VALUE		16
#define SEVENTEEN_VALUE		17
#define EIGHTEEN_VALUE		18
#define NINETEEN_VALUE		19
#define TWENTY_VALUE		20
#define TWENTYONE_VALUE		21
#define TWENTYTWO_VALUE		22
#define TWENTYTHREE_VALUE	23
#define TWENTYFOUR_VALUE	24
#define TWENTYFIVE_VALUE	25
#define TWENTYSIX_VALUE		26
#define TWENTYSEVEN_VALUE	27
#define TWENTYEIGHT_VALUE	28
#define TWENTYNINE_VALUE	29
#define THIRTY_VALUE		30
#define THIRTYONE_VALUE		31
#define THIRTYTWO_VALUE		32


#define KEYPAD_DELAY_HW			102
#define KEYPAD_DELAY_PROTUS		389


#define KEYPAD_DELAY		KEYPAD_DELAY_PROTUS


#define LCD_CLEAR_DELAY				4
#define LCD_DISPLAY_DELAY			20


typedef enum{
	STD_FALSE,
	STD_TRUE
}Std_True_or_FalseType;

typedef enum{
	STD_LOW,
	STD_HIGH
}Std_HIGH_or_LowType;


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/




/********************************** Software Interfaces Declarations *******************/


#endif /* SERIVICES_INCLUDE_MAGIC_NUMBERS_H_ */
