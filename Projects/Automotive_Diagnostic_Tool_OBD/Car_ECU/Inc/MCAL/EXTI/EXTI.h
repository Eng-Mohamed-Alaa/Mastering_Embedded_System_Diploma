/*
 * EXTI.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Mohamed Aburehab
 */

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_


                            /* Lines Definitions */
#define MEXTI_LINE_0                   0
#define MEXTI_LINE_1                   1
#define MEXTI_LINE_2                   2
#define MEXTI_LINE_3                   3
#define MEXTI_LINE_4                   4
#define MEXTI_LINE_5                   5
#define MEXTI_LINE_6                   6
#define MEXTI_LINE_7                   7
#define MEXTI_LINE_8                   8
#define MEXTI_LINE_9                   9
#define MEXTI_LINE_10                  10
#define MEXTI_LINE_11                  11
#define MEXTI_LINE_12                  12
#define MEXTI_LINE_13                  13
#define MEXTI_LINE_14                  14
#define MEXTI_LINE_15                  15

                            /* Modes Definitions */
#define MEXTI_MODE_RISING                   0
#define MEXTI_MODE_FALLING                  1
#define MEXTI_MODE_ON_CHANGE                2

                            /*Functions Prototype */

/**
 * @brief It enables the interrupt of the line that is passed to it
 *
 * @param Copy_u8Line The line number of the interrupt you want to enable.
 */
void MEXTI_voidEnableEXTI(uint8 Copy_u8Line);

/**
 * @brief It disables the interrupt of the line that is passed to it
 *
 * @param Copy_u8Line The line number of the interrupt you want to disable.
 */
void MEXTI_voidDisableEXTI(uint8 Copy_u8Line);

/**
 * @brief This function is used to trigger the interrupt manually by software
 *
 * @param Copy_u8Line The line number of the interrupt you want to trigger the interrupt by software.
 */
void MEXTI_voidSwTrigger(uint8 Copy_u8Line);

/**
 * It sets the interrupt mode for the specified line
 *
 * @param Copy_u8Line The line number of the external interrupt.
 * @param Copy_u8Mode The mode to trigger the interrupt.
 */
void MEXTI_voidSetSignalLatch(uint8 Copy_u8Line,uint8 Copy_u8Mode);

/**
 * It takes a line number and a function pointer, and stores the function pointer in an array of
 * function pointers
 *
 * @param Copy_u8Line The line number of the interrupt.
 * @param Copy_pvoidFunc is a pointer to a function that takes no parameters and returns void.
 */
void MEXTI_voidSetCallBack(uint8 Copy_u8Line, void(*Copy_pvoidFunc)(void));


#endif /* MCAL_EXTI_EXTI_H_ */
