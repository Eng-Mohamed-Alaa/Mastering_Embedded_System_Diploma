/*
 * ADC_CONFIG.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


/*================ Analog Watchdog options ====================
 * 1-Enable_Analog_watchdog_for_regular_channels_only
 * 2-Enable_Analog_watchdog_for_injected_channels_only
 * 3-Enable_Analog_watchdog_for_both_regular_and_injected_channels
 * 4-Disable_Analog_watchdog_for_both_regular_and_injected_channels
 */
#define Analog_Watchdog_Mode	Disable_Analog_watchdog_for_both_regular_and_injected_channels


/*================= DUAL MODE OPTIONS ========================
 * 1-DUAL_MODE_INDEPENDENT
 */
#define ADC_DUAL_MODE		DUAL_MODE_INDEPENDENT


/*=================================== Discontinuous mode channel count OPTIONS =========================
 *1-DISCNUM_1_CHANNEL
 *2-DISCNUM_2_CHANNELS
 *3-DISCNUM_3_CHANNELS
 *4-DISCNUM_4_CHANNELS
 *5-DISCNUM_5_CHANNELS
 *6-DISCNUM_6_CHANNELS
 *7-DISCNUM_7_CHANNELS
 *8-DISCNUM_8_CHANNELS
 */
#define DISCNUM_MODE 		DISCNUM_1_CHANNEL

/*====================================  Analog watchdog channel select bits ===========================
 * 1-WDT_ADC_analog_Channel0
 * 2-WDT_ADC_analog_Channel2
 * 3-WDT_ADC_analog_Channel3
 * 4-WDT_ADC_analog_Channel4
 * 5-WDT_ADC_analog_Channel5
 * 6-WDT_ADC_analog_Channel6
 * 7-WDT_ADC_analog_Channel7
 * 8-WDT_ADC_analog_Channel8
 * 9-WDT_ADC_analog_Channel9
 * 10-WDT_ADC_analog_Channel10
 * 11-WDT_ADC_analog_Channel11
 * 12-WDT_ADC_analog_Channel12
 * 13-WDT_ADC_analog_Channel13
 * 14-WDT_ADC_analog_Channel14
 * 15-WDT_ADC_analog_Channel15
 * 16-WDT_ADC_analog_Channel16
 * 17-WDT_ADC_analog_Channel17
 */

#define AWDCH_Mask 		WDT_ADC_analog_Channel5

/*============================================ DATA ALIGNMENT OPTIONS ====================================
 * 1-LEFT_ALIGNMENT
 * 2-RIGHT_ALIGNMENT
 */

#define DATA_ALIGNMENT_MODE   RIGHT_ALIGNMENT

/*=========================================== Internal Temp Sensor Options ===============================
 * 1-Enable_Internal_Temp_Sensor
 * 2-Disable_Internal_Temp_Sensor
 */
#define ADC_Internal_Temp_Sensor		Enable_Internal_Temp_Sensor
/*=========================================== Conversion Mode Options ====================================
 * 1-SINGLE_CONVERSION_MODE
 * 2-Continous_CONVERSION_MODE
 */
#define ADC_Conversion_Mode			SINGLE_CONVERSION_MODE

/*============================================ Setting Regular Channels Priority ==========================
 * 		// Priority 1 is the highest priority//
 */
#define	ADC_Regular_Priority_1		ADC_Channel_0
#define ADC_Regular_Priority_2		ADC_Channel_4
#define ADC_Regular_Priority_3		ADC_Channel_3
#define ADC_Regular_Priority_4		ADC_Channel_2
#define ADC_Regular_Priority_5		ADC_Channel_1
#define ADC_Regular_Priority_6		ADC_Channel_5

#endif /* MCAL_ADC_ADC_CONFIG_H_ */
