/*
 * lm35.h
 *
 *  Created on: Nov 27, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef HAL_LM35_LM35_H_
#define HAL_LM35_LM35_H_

void lm35_VidInit(void);
uint16 lm35_u16Read(uint8 copy_u8ADC_Channel,Puint16 add_pu16_lm35_val);

#endif /* HAL_LM35_LM35_H_ */
