/*
 * STM32F103x6.h
 *
 *  Created on: Jun 7, 2023
 *      Author: Mohamed Alaa
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "stdio.h"
#include "stdint.h"

//----------------------------------------------------------------
//base addresses for memories according to STM32F103x8 SPECs
//----------------------------------------------------------------

#define Flash_Memory_Base 						0x08000000UL
#define System_Memory_Base 						0x1FFFF000UL
#define SRAM_Base 								0x20000000UL

#define Cortex_M3_Internal_Peripherals_Base		0xE0000000UL
#define Peripherals_Base						0x40000000UL

//----------------------------------------------------------------
//base addresses for AHB2 bus peripherals
//----------------------------------------------------------------

#define RCC_Base	0x40021000UL

//----------------------------------------------------------------
//base addresses for ABP2 bus peripherals
//----------------------------------------------------------------

//GPIO A,B ports are fully used in LQFP48 package of STM32F103xx family
#define GPIOA_Base	0x40010800UL
#define GPIOB_Base	0x40010C00UL

//GPIO C,D ports are partially used in LQFP48 package of STM32F103xx family
#define GPIOC_Base	0x40011000UL
#define GPIOD_Base	0x40011400UL

//GPIO E port is not used in LQFP48 package of STM32F103xx family but exist
#define GPIOE_Base	0x40011800UL

//****************************************************************
//Alternative function I/O peripheral (AFIO)

#define AFIO_Base 	0x40010000UL

//****************************************************************
//external interrupt peripheral (EXTI)

#define EXTI_Base 	0x40010400UL

//----------------------------------------------------------------
//Peripherals registers
//----------------------------------------------------------------

//RCC registers

typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_typedef;

//****************************************************************
//GPIO registers

typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_typedef;

//****************************************************************
//AFIO registers

typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;  //offset: 0x14
	volatile uint32_t Reserved; //offset 0x18 doesn't exist
	volatile uint32_t MAPR2; 	//offset 0x1C
}AFIO_typedef;

//****************************************************************
//EXTI registers

typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_typedef;


//----------------------------------------------------------------
//peripheral instants
//----------------------------------------------------------------

//RCC instant

#define RCC ((volatile RCC_typedef *)(RCC_Base))

//****************************************************************
//GPIO instants
#define GPIOA ((volatile GPIO_typedef *)(GPIOA_Base))
#define GPIOB ((volatile GPIO_typedef *)(GPIOB_Base))
#define GPIOC ((volatile GPIO_typedef *)(GPIOC_Base))
#define GPIOD ((volatile GPIO_typedef *)(GPIOD_Base))
#define GPIOE ((volatile GPIO_typedef *)(GPIOE_Base))

//****************************************************************
//AFIO instant

#define AFIO ((volatile AFIO_typedef *)(AFIO_Base))

//****************************************************************
//EXTI instants

#define EXTI ((volatile EXTI_typedef *)(EXTI_Base))

//----------------------------------------------------------------
//6-clock enable macros
//----------------------------------------------------------------

// GPIO clock

#define RCC_GPIOA_Clock_Enable() 	(RCC->APB2ENR |= 1<<2)
#define RCC_GPIOB_Clock_Enable() 	(RCC->APB2ENR |= 1<<3)
#define RCC_GPIOC_Clock_Enable() 	(RCC->APB2ENR |= 1<<4)
#define RCC_GPIOD_Clock_Enable() 	(RCC->APB2ENR |= 1<<5)
#define RCC_GPIOE_Clock_Enable() 	(RCC->APB2ENR |= 1<<6)
#define RCC_GPIOA_Clock_disable()	(RCC->APB2ENR &= ~(1<<2))
#define RCC_GPIOB_Clock_disable()	(RCC->APB2ENR &= ~(1<<3))
#define RCC_GPIOC_Clock_disable()	(RCC->APB2ENR &= ~(1<<4))
#define RCC_GPIOD_Clock_disable()	(RCC->APB2ENR &= ~(1<<5))
#define RCC_GPIOE_Clock_disable()	(RCC->APB2ENR &= ~(1<<6))

//****************************************************************
//AFIO clock

#define RCC_AFIO_Clock_Enable() 	(RCC->APB2ENR |= 1<<0)
#define RCC_AFIO_Clock_disable()	(RCC->APB2ENR &= ~(1<<0))


//****************************************************************
//EXTI clock is always enabled for the the peripheral registers (not controlled to enable/disable)


//----------------------------------------------------------------
//7-Generic macros
//----------------------------------------------------------------

//#define Set_Bit(Address, Bit_no)		(Address |= 1<<Bit_no)
//#define Reset_Bit(Address, Bit_no)		(Address &= ~(1<<Bit_no))
//#define Toggle_Bit(Address, Bit_no)		(Address ^= 1<<Bit_no)
//#define Read_Bit(Address, Bit_no)		((Address>>Bit_no) & 1)


#endif /* INC_STM32F103X6_H_ */
