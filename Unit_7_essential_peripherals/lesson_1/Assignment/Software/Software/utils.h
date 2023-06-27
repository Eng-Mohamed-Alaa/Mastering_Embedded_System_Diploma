
#ifndef UTILS_H_
#define UTILS_H_

#define Set_Bit(reg,bit)	(reg |= 1<<bit)
#define Reset_Bit(reg,bit)	(reg &= ~(1<<bit))
#define Toggle_Bit(reg,bit) (reg ^= 1<<bit)
#define Read_Bit(reg, bit)	((reg>>bit)&1) 

#endif