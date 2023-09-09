
//----------------------------------------------------------------
//includes
//----------------------------------------------------------------
#include "STM32F103C6_RCC_Driver.h"


//----------------------------------------------------------------
//Generic macros
//----------------------------------------------------------------


//----------------------------------------------------------------
//Generic Global variables
//----------------------------------------------------------------


//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
//Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
//PPRE2 bits have the same values as PPRE1 bits but with different index so same array can be used as a table for PPRE2

const uint8_t APB_Prescaler_Table[8U] = {0,0,0,0,1,2,3,4}; //this table is used with shift right (>>) so 0 divide by 1 and 3 divide by 8, ....

//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512

const uint8_t AHB_Prescaler_Table[16U] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8}; //this table is used with shift right (>>) so 0 means to divide by 1 and 3 means to divide by 8, ....

//----------------------------------------------------------------
//RCC driver static functions
//----------------------------------------------------------------


//----------------------------------------------------------------
//APIs Implementation by "MCAL RCC driver"
//----------------------------------------------------------------

uint32_t MCAL_RCC_Get_SYSCLK_FREQ(void)
{
//	Bits 3:2 SWS[1:0]: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: Not applicable
	switch( (RCC->CFGR >> 2) & 0b11 )
	{
	case 0:
		return HSI_RC_CLK;

	case 1:
		//HSE to do: need to be calculated and user should specify it in the macro
			return HSE_CLK;

	case 2:
		//PLLCLK to do: need to be calculated by PLLSRC, PLLMUL, ....
			return 16000000U;
	}
}

uint32_t MCAL_RCC_Get_HCLK_FREQ(void)
{
	return (MCAL_RCC_Get_SYSCLK_FREQ() >> AHB_Prescaler_Table[ (RCC->CFGR >> 4) & 0xF ] );
}

uint32_t MCAL_RCC_Get_PCLK1_FREQ(void)
{
	return (MCAL_RCC_Get_HCLK_FREQ() >> APB_Prescaler_Table[ (RCC->CFGR >> 8) & 0b111 ] );
}

uint32_t MCAL_RCC_Get_PCLK2_FREQ(void)
{
	//Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	return (MCAL_RCC_Get_HCLK_FREQ() >> APB_Prescaler_Table[(RCC->CFGR >> 11) & 0b111]);
}


