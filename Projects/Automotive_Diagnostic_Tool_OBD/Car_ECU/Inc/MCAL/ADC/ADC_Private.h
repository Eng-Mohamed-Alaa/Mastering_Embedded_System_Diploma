/*
 * ADC_Private.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/*========================================= ADC MEMORY MAP =========================================*/

typedef volatile struct
{

  uint32  ADC_SR;
  uint32  ADC_CR1;
  uint32  ADC_CR2;
  uint32  ADC_SMPR1;
  uint32  ADC_SMPR2;
  uint32  ADC_JOFR1;
  uint32  ADC_JOFR2;
  uint32  ADC_JOFR3;
  uint32  ADC_JOFR4;
  uint32  ADC_HTR;
  uint32  ADC_LTR;
  uint32  ADC_SQR1;
  uint32  ADC_SQR2;
  uint32  ADC_SQR3;
  uint32  ADC_JSQR;
  uint32  ADC_JDR1;
  uint32  ADC_JDR2;
  uint32  ADC_JDR3;
  uint32  ADC_JDR4;
  uint32  ADC_DR;
}S_ADC_REGS_t;

#define ADC1_BASE_ADRESS 0x40012400

#define ADC_REGS ((S_ADC_REGS_t*) ADC1_BASE_ADRESS)



/*===================================== ADC_CR1 BITS & ADC_CR2 BITS & ADC_SR BITS =====================================*/
#define ADC_CR1_AWDEN		23		//Analog Watchdog enable bit on regular  channel
#define ADC_CR1_JAWDEN		22		//Analog Watchdog enable bit on injected channel

#define ADC_CR2_TSVREFE		23		//Temperature sensor and VREFINT enable
#define ADC_CR2_SWSTART		22		//ADC START CONVERSION FOR REGULAR CHANNEL
#define ADC_CR2_JSWSTART	21		//ADC START CONVERSION FOR REGULAR CHANNEL
#define ADC_CR2_CONT		1		//Conversion Mode
#define ADC_CR2_ADON		0		//ADC POWER ON BIT

#define ADC_SR_STRT			4		//Start of conversion on regular channel flag
#define ADC_SR_EOC			1		//END of conversion on group channel conversion (regular or injected)


/*===================================== Analog Watchdog mode options Masks =====================*/
#define Enable_Analog_watchdog_for_regular_channels_only							0x00800000
#define Enable_Analog_watchdog_for_injected_channels_only							0x00400000
#define Enable_Analog_watchdog_for_both_regular_and_injected_channels				0x00C00000
#define RESET_Analog_Watchdog_Mode_Selection_Bits									0xFF0FFFFF
#define Disable_Analog_watchdog_for_both_regular_and_injected_channels 				0x00000000

/*==================================== Dual Mode Selection Masks	======================*/
#define RESET_DUAL_MODE_SELECTION_BITS			0xFFF0FFFF
#define DUAL_MODE_INDEPENDENT					0x00000000


/*=================================== Discontinuous mode channel count Masks==================*/
#define RESET_DISCNUM_BITS						0xFFFF1FFF
#define DISCNUM_1_CHANNEL						0x00000000
#define DISCNUM_2_CHANNELS						0x00002000
#define DISCNUM_3_CHANNELS						0x00004000
#define DISCNUM_4_CHANNELS						0x00006000
#define DISCNUM_5_CHANNELS						0x00008000
#define DISCNUM_6_CHANNELS						0x0000A000
#define DISCNUM_7_CHANNELS						0x0000C000
#define DISCNUM_8_CHANNELS						0x0000E000

/*====================================  Analog watchdog channel select bits ====================*/
#define RESET_AWDCH_BITS						0xFFFFFFE0
#define WDT_ADC_analog_Channel0					0x00000000
#define WDT_ADC_analog_Channel1					0x00000001
#define WDT_ADC_analog_Channel2					0x00000002
#define WDT_ADC_analog_Channel3					0x00000003
#define WDT_ADC_analog_Channel4					0x00000004
#define WDT_ADC_analog_Channel5					0x00000005
#define WDT_ADC_analog_Channel6					0x00000006
#define WDT_ADC_analog_Channel7					0x00000007
#define WDT_ADC_analog_Channel8					0x00000008
#define WDT_ADC_analog_Channel9					0x00000009
#define WDT_ADC_analog_Channel10				0x0000000A
#define WDT_ADC_analog_Channel11				0x0000000B
#define WDT_ADC_analog_Channel12				0x0000000C
#define WDT_ADC_analog_Channel13				0x0000000D
#define WDT_ADC_analog_Channel14				0x0000000E
#define WDT_ADC_analog_Channel15				0x0000000F
#define WDT_ADC_analog_Channel16				0x00000010
#define WDT_ADC_analog_Channel17				0x00000011

/*================================================ TEAM A MASKS ===============================================*/
#define ADC_CR1_TEAM_A_MASK					0xFFFFE01F
#define ADC_CR2_TEAM_A_MASK					0xFFE00000





/*=============================================== Internal Temp Sensor Options =======================*/
#define Disable_Internal_Temp_Sensor			0
#define Enable_Internal_Temp_Sensor				1


/*============================================= Conversion Mode Options =================================*/

#define SINGLE_CONVERSION_MODE                       0x00000002
#define Continous_CONVERSION_MODE                    0x00000000



/*==================================== DATA ALIGNMENT OPTIONS ================================*/
#define LEFT_ALIGNMENT							0x00000800
#define RIGHT_ALIGNMENT							0x00000000



/*================================================== Sample Time Masks ==============================================*/
#define Sample_time_1_5_for_all_channels			0x00000000

/*========================================= Peripheral RESET Values =========================*/
#define ADC_CR1_RESET_VALUE						 0x00000000
#define ADC_CR2_RESET_VALUE						 0x00000000
#define ADC_SMPR1_RESET_VALUE					 0x00000000
#define ADC_SMPR2_RESET_VALUE					 0x00000000
#define ADC_JOFRx_RESET_VALUE			     	 0x00000000
#define ADC_HTR_RESET_VALUE						 0x00000FFF
#define ADC_LTR_RESET_VALUE						 0x00000000
#define ADC_SQR1_RESET_VALUE					 0x00000000
#define ADC_SQR2_RESET_VALUE					 0x00000000
#define ADC_SQR3_RESET_VALUE					 0x00000000
#define ADC_JSQR_RESET_VALUE					 0x00000000

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
