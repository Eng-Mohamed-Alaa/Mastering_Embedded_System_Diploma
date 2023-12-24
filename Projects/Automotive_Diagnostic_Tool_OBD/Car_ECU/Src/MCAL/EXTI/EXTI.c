/*
 * EXTI.c
 *
 *  Created on: Dec 6, 2023
 *      Author: Mohamed Aburehab
 */

/*================ Services Includes =====================*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"
#include "../SERVICES/Bit_Wise_Operations.h"
/*================ MCAL Includes =========================*/

#include "../INC/MCAL/EXTI/EXTI_CFG.h"
#include "../INC/MCAL/EXTI/EXTI.h"
#include "../INC/MCAL/EXTI/EXTI_PRIVATE.h"


/* An array of pointers to functions. */
static void(*CallBackFuncArr[16])(void) = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};


/**
 * @brief It enables the interrupt of the line that is passed to it
 *
 * @param Copy_u8Line The line number of the interrupt you want to enable.
 */
void MEXTI_voidEnableEXTI(uint8 Copy_u8Line){
    SET_BIT(EXTI->IMR, Copy_u8Line);
}

/**
 * @brief It disables the interrupt of the line that is passed to it
 *
 * @param Copy_u8Line The line number of the interrupt you want to disable.
 */
void MEXTI_voidDisableEXTI(uint8 Copy_u8Line){
    CLR_BIT(EXTI->IMR, Copy_u8Line);
}

/**
 * @brief This function is used to trigger the interrupt manually by software
 *
 * @param Copy_u8Line The line number of the interrupt you want to trigger the interrupt by software.
 */
void MEXTI_voidSwTrigger(uint8 Copy_u8Line){
    SET_BIT(EXTI->SWIER, Copy_u8Line);
}

/**
 * It sets the interrupt mode for the specified line
 *
 * @param Copy_u8Line The line number of the external interrupt.
 * @param Copy_u8Mode The mode to trigger the interrupt.
 */
void MEXTI_voidSetSignalLatch(uint8 Copy_u8Line,uint8 Copy_u8Mode){
    switch (Copy_u8Mode)
    {
    case MEXTI_MODE_RISING:
        SET_BIT(EXTI->RTSR, Copy_u8Line);
        break;
    case MEXTI_MODE_FALLING:
        SET_BIT(EXTI->FTSR, Copy_u8Line);
        break;
    case MEXTI_MODE_ON_CHANGE:
        SET_BIT(EXTI->RTSR, Copy_u8Line);
        SET_BIT(EXTI->FTSR, Copy_u8Line);
        break;

    }
}

/**
 * It takes a line number and a function pointer, and stores the function pointer in an array of
 * function pointers
 *
 * @param Copy_u8Line The line number of the interrupt.
 * @param Copy_pvoidFunc is a pointer to a function that takes no parameters and returns void.
 */
void MEXTI_voidSetCallBack(uint8 Copy_u8Line, void(*Copy_pvoidFunc)(void)){
    CallBackFuncArr[Copy_u8Line] = Copy_pvoidFunc;
}

void EXTI0_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_0]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 0. */
                CallBackFuncArr[MEXTI_LINE_0]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_0);
        }
}
void EXTI1_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_1]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 1. */
                CallBackFuncArr[MEXTI_LINE_1]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_1);
        }
}
void EXTI2_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_2]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 2. */
                CallBackFuncArr[MEXTI_LINE_2]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_2);
        }
}
void EXTI3_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_3]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 3. */
                CallBackFuncArr[MEXTI_LINE_3]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_3);
        }
}
void EXTI4_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_4]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 4. */
                CallBackFuncArr[MEXTI_LINE_4]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_4);
        }
}
void EXTI5_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_5]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 5. */
                CallBackFuncArr[MEXTI_LINE_5]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_5);
        }
}
void EXTI6_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_6]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 6. */
                CallBackFuncArr[MEXTI_LINE_6]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_6);
        }
}
void EXTI7_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_7]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 7. */
                CallBackFuncArr[MEXTI_LINE_7]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_7);
        }
}
void EXTI8_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_8]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 8. */
                CallBackFuncArr[MEXTI_LINE_8]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_8);
        }
}
void EXTI9_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_9]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 9. */
                CallBackFuncArr[MEXTI_LINE_9]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_9);
        }
}
void EXTI10_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_10]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 10. */
                CallBackFuncArr[MEXTI_LINE_10]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_10);
        }
}
void EXTI11_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_11]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 11. */
                CallBackFuncArr[MEXTI_LINE_11]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_11);
        }
}
void EXTI12_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_12]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 12. */
                CallBackFuncArr[MEXTI_LINE_12]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_12);
        }
}
void EXTI13_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_13]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 13. */
                CallBackFuncArr[MEXTI_LINE_13]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_13);
        }
}
void EXTI14_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_14]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 14. */
                CallBackFuncArr[MEXTI_LINE_14]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_14);
        }
}
void EXTI15_IRQHandler(void)
{
    /* Checking if the function pointer is not null, if it is not null it will call
    the function and clear the pending Flag. */
    if((CallBackFuncArr[MEXTI_LINE_15]!=NULL) )
    {
        /* Calling the call back function that is stored in the array at index 15. */
                CallBackFuncArr[MEXTI_LINE_15]();
        /* Clearing the pending flag of the interrupt. */
                SET_BIT(EXTI->PR,MEXTI_LINE_15);
        }
}
