/**************************************************************************/
/* Filename						: NVIC.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 12, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef NVIC_NVIC_H_
#define NVIC_NVIC_H_



/********************************** Includes *********************************************/



/********************************** Macros Declarations *******************************/


/********************************** Macros Function Declarations *********************/


/********************************** Data Type Declarations ****************************/
typedef enum {
NVIC_WWDG,
NVIC_PVD,
NVIC_TAMPER,
NVIC_RTC,
NVIC_FLASH,
NVIC_RCC,
NVIC_EXTI0,
NVIC_EXTI1,
NVIC_EXTI2,
NVIC_EXTI3,
NVIC_EXTI4,
NVIC_DMA1_CHANNEL1,
NVIC_DMA1_CHANNEL2,
NVIC_DMA1_CHANNEL3,
NVIC_DMA1_CHANNEL4,
NVIC_DMA1_CHANNEL5,
NVIC_DMA1_CHANNEL6,
NVIC_DMA1_CHANNEL7,
NVIC_ADC1_2,

NVIC_USB_HP_CAN_TX0,
NVIC_USB_LP_CAN_RX0,
NVIC_CAN1_RX1,
NVIC_CAN1_SCE,

NVIC_EXTI9_5,
NVIC_TIM1_BRK,
NVIC_TIM1_UP,
NVIC_TIM1_TRG_COM,
NVIC_TIM1_CC,
NVIC_TIM2,
NVIC_TIM3,
NVIC_TIM4,
NVIC_I2C1_EV,
NVIC_I2C1_ER,
NVIC_I2C2_EV,
NVIC_I2C2_ER,
NVIC_SPI1,
NVIC_SPI2,
NVIC_USART1,
NVIC_USART2,
NVIC_USART3,
NVIC_EXTI15_10,
NVIC_RTC_Alarm,
NVIC_USBWAKEup,
NVIC_TIM8_BRK,
NVIC_TIM8_UP,
NVIC_TIM8_TRG_COM,
NVIC_TIM8_CC,
NVIC_ADC3,
NVIC_FSMC,
NVIC_SDIO,
NVIC_TIM5 ,
NVIC_SPI3,
NVIC_USART4,
NVIC_USART5,
NVIC_TIM6,
NVIC_TIM7,
NVIC_DMA2_CHANNEL1,
NVIC_DMA2_CHANNEL2,
NVIC_DMA2_CHANNEL3,
NVIC_DMA2_CHANNEL4_5
}Nvic_IndexPeripheralType;


typedef enum{
	NVIC_ACTIVE_FLAG_IS_NOT_ACTIVE,
	NVIC_ACTIVE_FLAG_IS_ACTIVE
}Nvic_ActiveFlagType;

typedef enum {
    NVIC_Select_Group_0,
    NVIC_Select_Group_1,
    NVIC_Select_Group_2,
    NVIC_Select_Group_3,
    NVIC_Select_Group_4,
    NVIC_Select_Group_5,
    NVIC_Select_Group_6,
    NVIC_Select_Group_7,
    NVIC_Select_Group_8,
    NVIC_Select_Group_9,
    NVIC_Select_Group_10,
    NVIC_Select_Group_11,
    NVIC_Select_Group_12,
    NVIC_Select_Group_13,
    NVIC_Select_Group_14,
    NVIC_Select_Group_15
} Nvic_SelectGroupxType;

typedef enum {
    NVIC_Select_Sub_0,
    NVIC_Select_Sub_1,
    NVIC_Select_Sub_2,
    NVIC_Select_Sub_3,
    NVIC_Select_Sub_4,
    NVIC_Select_Sub_5,
    NVIC_Select_Sub_6,
    NVIC_Select_Sub_7,
    NVIC_Select_Sub_8,
    NVIC_Select_Sub_9,
    NVIC_Select_Sub_10,
    NVIC_Select_Sub_11,
    NVIC_Select_Sub_12,
    NVIC_Select_Sub_13,
    NVIC_Select_Sub_14,
    NVIC_Select_Sub_15
} Nvic_SelectSubxType;





typedef enum{
	NVIC_STATUS_FAIL,
	NVIC_STATUS_OK,
	NVIC_STATUS_NULL_POINTER_ADDRESS
}Nvic_ErrorStatusType;

/********************************** Software Interfaces Declarations *******************/

Nvic_ErrorStatusType Nvic_enuEnableInterrupt(Nvic_IndexPeripheralType Copy_NvicIndex);
Nvic_ErrorStatusType Nvic_enuDisableInterrupt(Nvic_IndexPeripheralType Copy_NvicIndex);

Nvic_ErrorStatusType Nvic_enuSetPendingFlag(Nvic_IndexPeripheralType Copy_NvicIndex);
Nvic_ErrorStatusType Nvic_enuClearPendingFlag(Nvic_IndexPeripheralType Copy_NvicIndex);

Nvic_ErrorStatusType Nvic_enuGetActiveFlag(Nvic_IndexPeripheralType Copy_NvicIndex, Nvic_ActiveFlagType* Address_Result);

Nvic_ErrorStatusType Nvic_SetInterruptPriority(Nvic_IndexPeripheralType Copy_NvicIndex,Nvic_SelectGroupxType Copy_enuGroupNumber, Nvic_SelectSubxType Copy_enuSubNumber);





#endif /* NVIC_NVIC_H_ */
