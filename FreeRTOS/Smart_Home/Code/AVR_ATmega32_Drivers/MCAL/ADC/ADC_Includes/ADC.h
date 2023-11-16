/*
 * ADC.h
 *
 * Created: 10/23/2023 11:01:31 AM
 *  Author: computer store
 */ 
#ifndef ADC_H_
#define ADC_H_

#include <Services/Std_types.h>

//struct for ADC Configuration
typedef struct
{
	void (*ADC_P_CallBack)(void);
	uint8 ADC_VREF;						//this member is set according to @ADC_VREF macros Reference
	uint8 ADC_Channel_Selection;		//this member is set according to @ADC_Channel_Selection macros Reference
	uint8 ADC_Auto_Trigger_Mode;		//this member is set according to @ADC_Channel_Selection macros Reference
	uint8 ADC_Interrupt_State;			//this member is set according to @ADC_Interrupt_State macros Reference
	uint8 ADC_Prescale;					//this member is set according to @ADC_Freq macros Reference
	uint8 ADC_Trigger_Source;			//this member is set according to @Trigger_Source macros Reference
}ADC_Config_t;


//=============================================================
//this member is set according to @ADC_VREF macros Reference
//=============================================================
#define ADC_VREF_AREF						((uint8)0)
#define ADC_VREF_AVCC						((uint8)1)
#define ADC_VREF_Internal_VREF				((uint8)3)

//=============================================================
//@ADC_Channel_Selection macros Reference
//=============================================================
#define ADC_Channel_ADC0					((uint8)0)
#define ADC_Channel_ADC1					((uint8)1)
#define ADC_Channel_ADC2					((uint8)2)
#define ADC_Channel_ADC3					((uint8)3)
#define ADC_Channel_ADC4					((uint8)4)
#define ADC_Channel_ADC5					((uint8)5)
#define ADC_Channel_ADC6					((uint8)6)
#define ADC_Channel_ADC7					((uint8)7)

//=============================================================
//@ADC_Auto_Trigger_mode
//=============================================================
#define ADC_Auto_Trigger_Disable			((uint8)0)
#define ADC_Auto_Trigger_EN					((uint8)1)

//=============================================================
//@ADC_Interrupt_State macros Reference
//=============================================================
#define ADC_Interrupt_State_Disable			((uint8)0)
#define ADC_Interrupt_State_EN				((uint8)1)



//=============================================================
//@ADC_Prescale macros Reference
//=============================================================
#define ADC_Prescale_2						((uint8)1)
#define ADC_Prescale_4						((uint8)2)
#define ADC_Prescale_8						((uint8)3)
#define ADC_Prescale_16						((uint8)4)
#define ADC_Prescale_32						((uint8)5)
#define ADC_Prescale_64						((uint8)6)
#define ADC_Prescale_128					((uint8)7)


//=============================================================
// @ADC_Trigger_Source macros Reference
//=============================================================
#define ADC_Trigger_Free					((uint8)0)
#define ADC_Trigger_Analog_Comparator		((uint8)1)
#define ADC_Trigger_EXTI0					((uint8)2)
#define Timer_Compare_Match					((uint8)3)
#define Timer0_Overflow						((uint8)4)
#define Timer1_Compare_Match_B				((uint8)5)
#define Timer1_Overflow						((uint8)6)
#define Timer1_Capture_Event				((uint8)7)


//void ADC_Init(void);
void ADC_Disable(void);
void ADC_Read(Puint16 ADC_value, uint8 ADC_Channel_Selection);
void ADC_Set_Config(ADC_Config_t* PS_ADC_Config);
/*void ADC_Start(void);*/

#endif /* ADC_H_ */