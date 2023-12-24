/**
 ******************************************************************************
 * @file           : RCC_PRIV.h
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 15, 2023
 ******************************************************************************
 */

#ifndef MCAL_RCC_RCC_PRIV_H_
#define MCAL_RCC_RCC_PRIV_H_

/*********************** RCC DATA TYPE & reg base adress *********************/
typedef struct
{
  volatile uint32 RCC_CR;          // Control Register
  volatile uint32 RCC_CFGR;        // Configuration Register
  volatile uint32 RCC_CIR;         // Clock Interrupt Register
  volatile uint32 RCC_APB2RSTR;    // APB2 Peripheral Reset Register
  volatile uint32 RCC_APB1RSTR;    // APB1 Peripheral Reset Register
  volatile uint32 RCC_AHBENR;      // AHB Peripheral Clock Enable Register
  volatile uint32 RCC_APB2ENR;     // APB2 Peripheral Clock Enable Register
  volatile uint32 RCC_APB1ENR;     // APB1 Peripheral Clock Enable Register
  volatile uint32 RCC_BDCR;        // Backup Domain Control Register
  volatile uint32 RCC_CSR;         // Control/Status Register
} RCC_TypeDef;
// reg base adreees
#define RCC ((RCC_TypeDef *)(0x40021000))

/****************************** function prototypes section end************************************/

#endif /* MCAL_RCC_RCC_PRIV_H_ */
