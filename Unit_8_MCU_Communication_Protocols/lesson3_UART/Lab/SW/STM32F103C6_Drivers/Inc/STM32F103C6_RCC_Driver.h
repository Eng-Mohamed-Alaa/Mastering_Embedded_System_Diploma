
#ifndef STM32F103C6_EXTI_DRIVER_H_
#define STM32F103C6_EXTI_DRIVER_H_

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103x6.h"
#include "stdint.h"


#define HSE_CLK			(uint32_t) 16000000
#define HSI_RC_CLK		(uint32_t) 8000000

//----------------------------------------------------------------
//APIs supported by "MCAL RCC driver"
//----------------------------------------------------------------

uint32_t MCAL_RCC_Get_SYS_CLK_FREQ(void);
uint32_t MCAL_RCC_Get_HCLK_FREQ(void);
uint32_t MCAL_RCC_Get_PCLK1_FREQ(void);
uint32_t MCAL_RCC_Get_PCLK2_FREQ(void);


#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
