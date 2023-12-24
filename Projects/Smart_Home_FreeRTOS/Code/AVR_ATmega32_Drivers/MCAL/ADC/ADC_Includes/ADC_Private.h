/*
 * ADC_Private.h
 *
 * Created: 10/23/2023 11:02:01 AM
 *  Author: computer store
 */ 
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX			(*(volatile Puint8)0x27)
#define ADCSRA			(*(volatile Puint8)0x26)
#define ADCL			(*(volatile Puint8)0x24)
#define ADCH			(*(volatile Puint8)0x25)
#define SFIOR			(*(volatile Puint8)0x50)



//ADMUX bits
#define	REFSn			6
#define	MUXn			0

//ADCSRA bits
#define	ADEN			7
#define	ADSC			6
#define	ADATE			5
#define	ADIE			3
#define	ADPSn			0

//SFIOR bits
#define ADTSn			5



#endif /* ADC_PRIVATE_H_ */