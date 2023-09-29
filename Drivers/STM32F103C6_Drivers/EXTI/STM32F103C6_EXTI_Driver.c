
//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103C6_EXTI_Driver.h"



//----------------------------------------------------------------
//Generic macros
//----------------------------------------------------------------


#define AFIO_GPIO_EXTI_Mapping(x)		(	(x == GPIOA) ? 0 :\
											(x == GPIOB) ? 1 :\
											(x == GPIOC) ? 2 : 3	)

//----------------------------------------------------------------
//Generic Global variables
//----------------------------------------------------------------
static void(*GP_IRQ_Callback[16])(void);


//----------------------------------------------------------------
//EXTI driver static functions
//----------------------------------------------------------------

static void NVIC_IRQ_Enable(uint8_t NVIC_IRQ_Number)
{
	if(NVIC_IRQ_Number < 31)
	{ NVIC_ISER0 |= 1<<NVIC_IRQ_Number; }

	else if(NVIC_IRQ_Number > 31 && NVIC_IRQ_Number <64)
	{ NVIC_ISER1 |= 1 << (NVIC_IRQ_Number-32); }
}
static void NVIC_IRQ_Disable(uint8_t NVIC_IRQ_Number)
{
	if(NVIC_IRQ_Number < 31)
	{ NVIC_ICER0 |= 1<<NVIC_IRQ_Number; }

	else if(NVIC_IRQ_Number > 31 && NVIC_IRQ_Number <64)
	{ NVIC_ICER1 |= 1 << (NVIC_IRQ_Number-32); }
}

static void Update_EXTI(EXTI_Pin_Configuration_t* EXTI_Config)
{
	//1-update the GPIO configuration pin as AF input >>> floating input
	GPIO_Pin_Configuration_t Pin_Config;
	Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_Input;
	Pin_Config.GPIO_Pin_Number = EXTI_Config->EXTI_Pin.GPIO_Pin;
	MCAL_GPIO_Init(EXTI_Config->EXTI_Pin.GPIO_Port,&Pin_Config);

	//2-update the AFIO configuration to select which port(A,B,C,D) is connected to the EXTI line
	uint8_t	AFIO_EXTICR_Index = EXTI_Config->EXTI_Pin.EXTI_line_Number / 4;
	uint8_t	AFIO_EXTICR_Config_position = (EXTI_Config->EXTI_Pin.EXTI_line_Number % 4)*4;

	//clear and set the four bits of responsible for mapping the GPIO to the EXTI in
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Config_position);
	AFIO->EXTICR[AFIO_EXTICR_Index] |= (AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_Pin.GPIO_Port) << AFIO_EXTICR_Config_position);

	//3-update the EXTI trigger condition
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
	}else if(EXTI_Config->Trigger_Case == EXTI_Trigger_Rising_and_Falling)
	{
		EXTI->FTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
		EXTI->RTSR |= (1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
	}

	//update the IRQ Handling call back function
	GP_IRQ_Callback[EXTI_Config->EXTI_Pin.EXTI_line_Number] = EXTI_Config->P_IRQ_Callback;

	//Enable/Disable the IRQ Mask in the EXTI and NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= 1 << EXTI_Config->EXTI_Pin.EXTI_line_Number;
		NVIC_IRQ_Enable(EXTI_Config->EXTI_Pin.IVT_IRQ_Number);
	}else
	{
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_Pin.EXTI_line_Number);
		NVIC_IRQ_Disable(EXTI_Config->EXTI_Pin.IVT_IRQ_Number);
	}

}

//----------------------------------------------------------------
//APIs Implementation by "MCAL EXTI driver"
//----------------------------------------------------------------


/*****************************************************************
 * @FN:			MCAL_EXTI_GPIO_Deinit
 * @brief:		Reset the EXTI registers and the NVIC corresponding IRQ mask
 * @param		none
 * @retval:		none
 * @Note:		none
 * */
void MCAL_EXTI_GPIO_Deinit(void)
{
	EXTI->IMR 	=  	0x00000000;
	EXTI->EMR 	=	0x00000000;
	EXTI->RTSR	=  	0x00000000;
	EXTI->FTSR 	=  	0x00000000;
	EXTI->SWIER =  	0x00000000;

	//in the TRM  the Reset value of EXTI_PR is undefined
	//0: No trigger request occurred
	//1: selected trigger request occurred
	//This bit is set when the selected edge event arrives on the external interrupt line. This bit is
	//cleared by writing a ‘1’ into the bit.
	EXTI->PR 	=  	0xFFFFFFFF;

	//Disable the NVIC IRQ mask
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ23_EXTI10_15_Disable;
}


/*****************************************************************
 * @FN:			MCAL_EXTI_GPIO_Init
 * @brief:		this is used to set specific pin in the GPIO as specific external interrupt, specify the trigger condition, the IRQ call back function, and enable/disable the IRQ mask in the EXTI and the NVIC
 * @param		EXTI_Config must be set by @ref EXTI_Define, @ref EXTI_Trigger_Define, @ref EXTI_IRQ_EN_Define
 * @retval:		none
 * @Note:		STM32F103c6 has GPIO A,B,C,D,E modules
 * 				but LQFP48 package has A,B and part of C,D as exported pins
 * 				it's mandatory to enable the corresponding GPIO, AFIO clocks
 * */
void MCAL_EXTI_GPIO_Init(EXTI_Pin_Configuration_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


/*****************************************************************
 * @FN:			MCAL_EXTI_GPIO_Update
 * @brief:		this is used to update the configuration of a seted pin in the GPIO as specific external interrupt, the trigger condition, the IRQ call back function, and enable/disable the IRQ mask in the EXTI and the NVIC
 * @param		EXTI_Config must be set by @ref EXTI_Define, @ref EXTI_Trigger_Define, @ref EXTI_IRQ_EN_Define
 * @retval:		none
 * @Note:		STM32F103c6 has GPIO A,B,C,D,E modules
 * 				but LQFP48 package has A,B and part of C,D as exported pins
 * 				it's mandatory to enable the corresponding GPIO, AFIO clocks
 * */
void MCAL_EXTI_GPIO_Update(EXTI_Pin_Configuration_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


//----------------------------------------------------------------
//EXTI ISR functions
//----------------------------------------------------------------

void EXTI0_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	EXTI->PR |= 1<<0;

	//go to the call back function in APP layer
	GP_IRQ_Callback[0]();
}

void EXTI1_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	EXTI->PR |= 1<<1;

	//go to the call back function in APP layer
	GP_IRQ_Callback[1]();
}

void EXTI2_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	EXTI->PR |= 1<<2;

	//go to the call back function in APP layer
	GP_IRQ_Callback[2]();
}

void EXTI3_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	EXTI->PR |= 1<<3;

	//go to the call back function in APP layer
	GP_IRQ_Callback[3]();
}

void EXTI4_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	EXTI->PR |= 1<<4;

	//go to the call back function in APP layer
	GP_IRQ_Callback[4]();
}

void EXTI9_5_IRQHandler(void)
{
	//clear the interrupt from the EXTI module
	//go to the call back function in APP layer
	if(EXTI->PR & (1<<5) ) {	EXTI->PR |= 1<<5 ;GP_IRQ_Callback[5]();		}
	if(EXTI->PR & (1<<6) ) {	EXTI->PR |= 1<<6 ;GP_IRQ_Callback[6](); 	}
	if(EXTI->PR & (1<<7) ) {	EXTI->PR |= 1<<7 ;GP_IRQ_Callback[7](); 	}
	if(EXTI->PR & (1<<8) ) { 	EXTI->PR |= 1<<8 ;GP_IRQ_Callback[8](); 	}
	if(EXTI->PR & (1<<9) ) { 	EXTI->PR |= 1<<9 ;GP_IRQ_Callback[9](); 	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & (1<<10) )	{ 	EXTI->PR |= 1<<10 ;GP_IRQ_Callback[10]();	}
	if(EXTI->PR & (1<<11) ) { 	EXTI->PR |= 1<<11 ;GP_IRQ_Callback[11]();	}
	if(EXTI->PR & (1<<12) ) {	EXTI->PR |= 1<<12 ;GP_IRQ_Callback[12](); 	}
	if(EXTI->PR & (1<<13) ) {	EXTI->PR |= 1<<13 ;GP_IRQ_Callback[13](); 	}
	if(EXTI->PR & (1<<14) ) { 	EXTI->PR |= 1<<14 ;GP_IRQ_Callback[14](); 	}
	if(EXTI->PR & (1<<15) ) { 	EXTI->PR |= 1<<15 ;GP_IRQ_Callback[15](); 	}
}



