#ifndef PWM0_H_
#define PWM0_H_

//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "memory_map.h"

//----------------------------------------------------------------------
//user defined data types (structures, enumerations)
//----------------------------------------------------------------------

typedef struct
{
	
	uint8_t	Compare_Output_Mode;	//Bits 5:4 – COM0n: Compare Match Output Mode [n = 1:0]
									//this parameter is set according to @ref PWM0_Compare_Output_Mode
	
	uint8_t	Operation_Mode;			//Bit 6 WGM00 & Bit 3 WGM01 : Waveform Generation Mode
									//this parameter is set according to @ref PWM0_Operation_Mode
		
	uint8_t	Select_Interrupt;		//this parameter is set according to @ref PWM0_Select_Interrupt
	
	void (* PTR_ISR_OVF_CallBack)(uint8_t Pulses_Cnt_Status) ;		//Pulses_Cnt_Status parameter is set according to @ref PWM0_Pulses_Cnt_Status
	void (* PTR_ISR_COMP_CallBack)(void) ;
	
}PWM0_Configurations_t;


//----------------------------------------------------------------------
//reference Macros
//----------------------------------------------------------------------

//@ref PWM0_Clock_Select
#define	PWM0_No_CLK_Source					(uint8_t)(0)
#define	PWM0_Sytem_CLK_divided_by_1			(uint8_t)(1 << CS0n)
#define	PWM0_Sytem_CLK_divided_by_8			(uint8_t)(2 << CS0n)
#define	PWM0_Sytem_CLK_divided_by_64		(uint8_t)(3 << CS0n)
#define	PWM0_Sytem_CLK_divided_by_256		(uint8_t)(4 << CS0n)
#define	PWM0_Sytem_CLK_divided_by_1024		(uint8_t)(5 << CS0n)
#define	PWM0_External_CLK_Pin_T0			(uint8_t)(6 << CS0n)


//those values are set based on F_CPU = 8 MHz, timer0_Prescaler = 64, Clear OC0 on Compare Match
//@ref PWM0_T_High
#define	PWM0_T_High_1ms						(uint8_t)(1)		
#define	PWM0_T_High_2ms						(uint8_t)(2)

//same for if we need to define T_low but with Setting OC0 on Compare Match
// those values are set based on F_CPU = 8 MHz, timer0_Prescaler = 64, Set OC0 on Compare Match
// @ref PWM0_T_Low
// #define	PWM0_T_Low_1ms						PWM0_T_High_1ms
// #define	PWM0_T_Low_2ms						PWM0_T_High_2ms

//@ref @ref PWM0_Compare_Output_Mode
#define	PWM0_Disconnect_OC					(uint8_t)(0)				// Normal port operation, OC0 disconnected.
#define	PWM0_Clear_OC						(uint8_t)(2 << COM0n)		// Clear OC0 on Compare Match
#define	PWM0_Set_OC							(uint8_t)(3 << COM0n)		// Set OC0 on Compare Match


//@ref @ref PWM0_Operation_Mode
#define	PWM0_Phase_Correct_Mode				(uint8_t)(1 << WGM00)
#define	PWM0_Fast_Mode						(uint8_t)(1 << WGM01 | 1 << WGM00)


//@ref PWM0_Select_Interrupt
#define	PWM0_Interrupt_None					(uint8_t)(0)
#define	PWM0_Interrupt_Overflow				(uint8_t)(1 << TOIE0)
#define	PWM0_Interrupt_Compare_Match		(uint8_t)(1 << OCIE0)
#define	PWM0_Interrupt_All					(uint8_t)(0b11 << TOIE0)	//Compare Match and Overflow Interrupts

//this macro is used in case number of pulses is undefined 
//and is optional to open PWM0_Interrupt_Overflow
#define N_Pulses_Undefined					(0)


//@ref PWM0_Pulses_Cnt_Status
#define Cnt_Status_Finished					(uint8_t)(0)
#define Cnt_Status_Working					(uint8_t)(1)



//----------------------------------------------------------------------
//APIs
//----------------------------------------------------------------------

void PWM0_Init(PWM0_Configurations_t* Timer_CFG);
void PWM0_Set_Timer_Reg(uint8_t Ticks);
void PWM0_Set_Output_Compare_Reg(uint8_t Ticks);
void PWM0_Start(uint32_t N_Pulses, uint8_t T_High); //if N_Pulses is defined PWM0_Interrupt_Overflow must be open
													//T_High is set according to @ref PWM0_T_High
void PWM0_Reset(void);

#endif