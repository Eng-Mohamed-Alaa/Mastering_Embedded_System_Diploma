#ifndef TIMER0_H_
#define TIMER0_H_

//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "memory_map.h"

//----------------------------------------------------------------------
//user defined data types (structures, enumerations)
//----------------------------------------------------------------------

typedef struct
{
	uint8_t	Clock_Select;			//Bits 2:0 – CS0n: Clock Select [n = 2:0]
									//this parameter is set according to @ref Timer0_Clock_Select
										
	uint8_t	Compare_Output_Mode;	//Bits 5:4 – COM0n: Compare Match Output Mode [n = 1:0]
									//this parameter is set according to @ref Timer0_Compare_Output_Mode
	
	uint8_t	Operation_Mode;			//Bit 6 WGM00 & Bit 3 WGM01 : Waveform Generation Mode
									//this parameter is set according to @ref Timer0_Operation_Mode
	
	uint8_t	Force_Output_Compare;	//Bit 7 – FOC0: Force Output Compare
									//this parameter is set according to @ref Timer0_Force_Output_Compare
									
	uint8_t	Select_Interrupt;		//this parameter is set according to @ref Timer0_Select_Interrupt
	
	void (* PTR_ISR_OVF_CallBack)(void) ;
	void (* PTR_ISR_COMP_CallBack)(void) ;
				
}Timer0_Configurations_t;


//----------------------------------------------------------------------
//reference Macros
//----------------------------------------------------------------------

//@ref Timer0_Clock_Select
#define	Timer0_No_CLK_Source					(uint8_t)(0)
#define	Timer0_Sytem_CLK_divided_by_1			(uint8_t)(1 << CS0n)
#define	Timer0_Sytem_CLK_divided_by_8			(uint8_t)(2 << CS0n)
#define	Timer0_Sytem_CLK_divided_by_64			(uint8_t)(3 << CS0n)
#define	Timer0_Sytem_CLK_divided_by_256			(uint8_t)(4 << CS0n)
#define	Timer0_Sytem_CLK_divided_by_1024		(uint8_t)(5 << CS0n)
#define	Timer0_External_CLK_Pin_T0				(uint8_t)(6 << CS0n)
	

//@ref @ref Timer0_Compare_Output_Mode
#define	Timer0_Disconnect_OC					(uint8_t)(0)				// Normal port operation, OC0 disconnected.
#define	Timer0_Toggle_OC						(uint8_t)(1 << COM0n)		// Toggle OC0 on Compare Match
#define	Timer0_Clear_OC							(uint8_t)(2 << COM0n)		// Clear OC0 on Compare Match
#define	Timer0_Set_OC							(uint8_t)(3 << COM0n)		// Set OC0 on Compare Match


//@ref @ref Timer0_Operation_Mode
#define	Timer0_Normal_Mode						(uint8_t)(0)
#define	Timer0_CTC_Mode							(uint8_t)(1 << WGM01)


//@ref Timer0_Force_Output_Compare
#define	Timer0_Disable_FOC						(uint8_t)(0)
#define Timer0_Enable_FOC						(uint8_t)(1 << WGM01)


//@ref Timer0_Select_Interrupt
#define	Timer0_Interrupt_None					(uint8_t)(0)
#define	Timer0_Interrupt_Overflow				(uint8_t)(1 << TOIE0)
#define	Timer0_Interrupt_Compare_Match			(uint8_t)(1 << OCIE0)
#define	Timer0_Interrupt_All					(uint8_t)(0b11 << TOIE0)	//Compare Match and Overflow Interrupts 



//----------------------------------------------------------------------
//APIs
//----------------------------------------------------------------------

void Timer0_Init(Timer0_Configurations_t* Timer_CFG);
void Timer0_Set_Timer_Reg(uint8_t Ticks);
void Timer0_Set_Output_Compare_Reg(uint8_t Ticks);
void Timer0_Start(void);
void Timer0_Stop(void);
void Timer0_Pause(void);
uint8_t Timer0_Get_Ticks(void);



#endif