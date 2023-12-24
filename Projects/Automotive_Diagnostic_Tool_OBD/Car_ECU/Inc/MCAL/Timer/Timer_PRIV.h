/*
 * Timer_Pivate.h
 *
 *  Created on: Nov 23, 2023
 *      Author: computer store
 */

#ifndef MCAL_TIMER_TIMER_PRIV_H_
#define MCAL_TIMER_TIMER_PRIV_H_


//*******************TIMx_CR1 bits definition******************
#define TIMx_CR1_CEN				(0)
#define TIMx_CR1_UDIS				(1)
#define TIMx_CR1_URS				(2)
#define TIMx_CR1_OPM			    (3)
#define TIMx_CR1_DIR			    (4)
#define TIMx_CR1_CMS			    (5)
#define TIMx_CR1_ARPE			    (7)
#define TIMx_CR1_CKD			    (8)

//*******************TIMx_CCMR1 bits definition******************
#define TIMx_CCMR1_CC1S				(0)
#define TIMx_CCMR1_OC1FE			(2)
#define TIMx_CCMR1_OC1PE			(3)
#define TIMx_CCMR1_OC1M				(4)
#define TIMx_CCMR1_OC1CE			(7)
#define TIMx_CCMR1_CC2S				(8)
#define TIMx_CCMR1_OC2FE			(10)
#define TIMx_CCMR1_OC2PE			(11)
#define TIMx_CCMR1_OC2M				(12)
#define TIMx_CCMR1_OC2CE			(15)

//*******************TIMx_CCMR2 bits definition******************
#define TIMx_CCMR2_CC3S				(0)
#define TIMx_CCMR2_OC3FE			(2)
#define TIMx_CCMR2_OC3PE			(3)
#define TIMx_CCMR2_OC3M				(4)
#define TIMx_CCMR2_OC3CE			(7)
#define TIMx_CCMR2_CC4S				(8)
#define TIMx_CCMR2_OC4FE			(10)
#define TIMx_CCMR2_OC4PE			(11)
#define TIMx_CCMR2_OC4M				(12)
#define TIMx_CCMR2_OC4CE			(15)

//*******************TIMx_CCER bits definition******************
#define TIMx_CCER_CC1E			(0)
#define TIMx_CCER_CC1P			(1)
#define TIMx_CCER_CC2E			(4)
#define TIMx_CCER_CC2P			(5)
#define TIMx_CCER_CC3E			(8)
#define TIMx_CCER_CC3P			(9)
#define TIMx_CCER_CC4E			(12)
#define TIMx_CCER_CC4P			(13)



#endif /* MCAL_TIMER_TIMER_PRIV_H_ */
