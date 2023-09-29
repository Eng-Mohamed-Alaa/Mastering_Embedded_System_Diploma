#ifndef ADC_H_
#define ADC_H_

//----------------------------------------------------------------------
//includes
//----------------------------------------------------------------------
#include "memory_map.h"


//----------------------------------------------------------------------
//Configuration macros
//----------------------------------------------------------------------
#define ADC_AVCC			5000	//voltage in mv
#define ADC_Resoultion		10		//number of bits in ADC register 


//----------------------------------------------------------------------
//user defined data types (structures)
//----------------------------------------------------------------------

typedef struct
{
	uint8_t Left_Adjust_Result;			//this parameter is set according to @ref ADC_Left_Adjust_Result
	uint8_t Voltage_Reference_SRC;		//this parameter is set according to @ref ADC_Voltage_Reference_SRC
	uint8_t Prescaler;					//this parameter is set according to @ref ADC_Prescaler
	uint8_t Interrupt_Status;			//this parameter is set according to @ref ADC_Interrupt_Status
	uint8_t Auto_Trigger_Source;		//this parameter is set according to @ref ADC_Auto_Trigger_Source

}ADC_Configurations_t;


//----------------------------------------------------------------------
//reference Macros
//----------------------------------------------------------------------

// @ref ADC_Left_Adjust_Result
#define ADC_Left_Adjust_Result_Disable			(uint8_t)(0)			
#define ADC_Left_Adjust_Result_Enable			(uint8_t)(1 << ADLAR)


// @ref ADC_Voltage_Reference_SRC
#define ADC_V_Ref_External						(uint8_t)(0)
#define ADC_V_Ref_Avcc							(uint8_t)(1 << REFSn)
#define ADC_V_Ref_3v							(uint8_t)(3 << REFSn)


// @ref ADC_Prescaler
#define ADC_Sytem_CLK_divided_by_2				(uint8_t)(1 << ADPSn)
#define ADC_Sytem_CLK_divided_by_4				(uint8_t)(2 << ADPSn)
#define ADC_Sytem_CLK_divided_by_8				(uint8_t)(3 << ADPSn)
#define ADC_Sytem_CLK_divided_by_16				(uint8_t)(4 << ADPSn)
#define ADC_Sytem_CLK_divided_by_32				(uint8_t)(5 << ADPSn)
#define ADC_Sytem_CLK_divided_by_64				(uint8_t)(6 << ADPSn)
#define ADC_Sytem_CLK_divided_by_128			(uint8_t)(7 << ADPSn)


// @ref ADC_Interrupt_Status
#define ADC_Interrupt_Disable					(uint8_t)(0)
#define ADC_Interrupt_Enable					(uint8_t)(1 << ADIE)


// @ref ADC_Auto_Trigger_Source
#define ADC_Auto_Trigger_None									(uint8_t)(0xFF)
#define ADC_Auto_Trigger_Free_Running_mode						(uint8_t)(0 << ADTSn)
#define ADC_Auto_Trigger_Comparator								(uint8_t)(1 << ADTSn)
#define ADC_Auto_Trigger_External_Interrupt_Request0			(uint8_t)(2 << ADTSn)
#define ADC_Auto_Trigger_Counter0_Compare_Match					(uint8_t)(3 << ADTSn)
#define ADC_Auto_Trigger_Counter0_Overflow						(uint8_t)(4 << ADTSn)
#define ADC_Auto_Trigger_Counter1_Compare_MatchB				(uint8_t)(5 << ADTSn)
#define ADC_Auto_Trigger_Counter1_Overflow						(uint8_t)(6 << ADTSn)
#define ADC_Auto_Trigger_Counter1_Capture_Event					(uint8_t)(7 << ADTSn)


// @ref ADC_Channel --> single ended input
#define ADC0		(uint8_t)(0)
#define ADC1		(uint8_t)(1 << MUXn)
#define ADC2		(uint8_t)(2 << MUXn)
#define ADC3		(uint8_t)(3 << MUXn)
#define ADC4		(uint8_t)(4 << MUXn)
#define ADC5		(uint8_t)(5 << MUXn)
#define ADC6		(uint8_t)(6 << MUXn)
#define ADC7		(uint8_t)(7 << MUXn)


//----------------------------------------------------------------------
//APIs
//----------------------------------------------------------------------
void ADC_Init(ADC_Configurations_t* ADC_CFG);
uint16_t ADC_Read_Single_Conversion(uint8_t ADC_Channel);		//ADC_Channel is set according to @ref ADC_Channel







#endif