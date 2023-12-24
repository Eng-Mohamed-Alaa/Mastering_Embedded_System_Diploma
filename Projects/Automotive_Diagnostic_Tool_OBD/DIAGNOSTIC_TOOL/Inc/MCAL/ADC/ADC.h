/*
 * ADC.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef MCAL_ADC_ADC_H_
#define MCAL_ADC_ADC_H_

#define ADC_Channel_0  				GPIO_PIN_0
#define ADC_Channel_1  				GPIO_PIN_1
#define ADC_Channel_2  				GPIO_PIN_2
#define ADC_Channel_3  				GPIO_PIN_3
#define ADC_Channel_4  				GPIO_PIN_4
#define ADC_Channel_5  				GPIO_PIN_5
#define ADC_Channel_6  				GPIO_PIN_6
#define ADC_Channel_7  				GPIO_PIN_7
#define ADC_Channel_8  				GPIO_PIN_8
#define ADC_Channel_9  				GPIO_PIN_9
#define ADC_Channel_10  			10
#define ADC_Channel_11  			11
#define ADC_Channel_12  			12
#define ADC_Channel_13  			13
#define ADC_Channel_14  			14
#define ADC_Channel_15  			15
#define ADC_Channel_16  			16
#define ADC_Channel_17  			17



/*=============================================== Peripheral Error Status ENUM ==============================================*/
typedef enum
{
  ADC_STATUS_FAILED,
  ADC_STATUS_OK,
  ADC_NULL_PTR_ERROR,
  ADC_CHANNEL_NO_ERROR,
  ADC_TIME_OUT_ERROR

}enu_ADC_Error_Status;


/*=============================================== FUNCTIONS Prototypes ======================================================*/
void ADC_vidInit(void);
enu_ADC_Error_Status ADC_enu_Read_Regular_Channel(Puint16 add_pu16Value);
void ADC_vidDeInit(void);

#endif /* MCAL_ADC_ADC_H_ */
