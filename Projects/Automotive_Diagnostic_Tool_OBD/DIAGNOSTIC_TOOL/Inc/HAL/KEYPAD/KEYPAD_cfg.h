
#ifndef KEYPAD_CFG
#define KEYPAD_CFG
//#include "../../MCAL/DIO/include/DIO_private.h"
//#include "../../MCAL/PORT/include/port_private.h"


#define	 KEY_RAW0		GPIO_PIN_0
#define	 KEY_RAW1		GPIO_PIN_1
#define	 KEY_RAW2		GPIO_PIN_9
#define	 KEY_RAW3		GPIO_PIN_10

//#define	 KEY_RAW2		GPIO_PIN_3  GPIO_GPIO_PIN__0
//#define	 KEY_RAW3		GPIO_PIN_4

#define	 KEY_COL0		GPIO_PIN_5
#define	 KEY_COL1		GPIO_PIN_6
#define	 KEY_COL2		GPIO_PIN_7
#define	 KEY_COL3		GPIO_PIN_8



#define	 KEY_COL0_PORT		GPIO_PORT_B
#define	 KEY_COL1_PORT		GPIO_PORT_B
#define	 KEY_COL2_PORT		GPIO_PORT_B
#define	 KEY_COL3_PORT		GPIO_PORT_B

#define	 KEY_RAW0_PORT		GPIO_PORT_B
#define	 KEY_RAW1_PORT		GPIO_PORT_B
#define	 KEY_RAW2_PORT		GPIO_PORT_B
#define	 KEY_RAW3_PORT		GPIO_PORT_B




#define RAW_NUM 4

static uint8 KEYPAD_SYMBOL[16]={1,2,3,0xFF,
							 4,5,6,0xFA,
							 7,8,9,0xFD,
							 4,0,0x0D,0xFB};

							 
							 
#endif 
