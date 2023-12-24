/*
 * EXTI_PRIVATE.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Mohamed Aburehab
 */

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

                            /* Register Definitions */
typedef struct
{
    volatile uint32 IMR;   /* Interrupt mask register */
    volatile uint32 EMR;   /* Event mask register */
    volatile uint32 RTSR;  /* Rising trigger selection register */
    volatile uint32 FTSR;  /* Falling trigger selection register  */
    volatile uint32 SWIER; /* Software interrupt event register */
    volatile uint32 PR;    /* Pending register */
}EXTI_t;

#define EXTI        ((volatile EXTI_t*) 0x40010400)

/*EXTI Intial states*/
#define EXTI_DISABLE        0
#define EXTI_ENABLE         1


#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
