/**
 ******************************************************************************
 * @file           : GPIO.h
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 15, 2023
 ******************************************************************************
 */

#ifndef MCAL_GPIO_GPIO_H_
#define MCAL_GPIO_GPIO_H_



/************************************* include section ****************************************/
#include"../../../SERVICES/Standard_Data_Types.h"
#include"../../../SERVICES/Bit_Wise_Operations.h"
#include"../RCC/RCC.h"
#include"GPIO_PRIV.h"

/************************************* include section end ************************************/

/***************************************** macros section *************************************/


/***************** pin modes ********************************/
#define  Input_Analog 		0x00
#define  InputFloating		0x01
#define  Input_pull_up_down	0x02

#define  output_push_pull	0x00
#define  output_Open_drain	0x01
#define  AF_output_Push_pull	0x02
#define  AF_output_Open_drain 	0x03

/*********************************** macros section end ***************************************/


/*********************************** user defined data types section **************************/


typedef enum {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15
}GPIO_enuPIN_NO_t;

typedef enum {
     GPIO_PORT_A,
     GPIO_PORT_B,
     GPIO_PORT_C,
     GPIO_PORT_D,
     GPIO_PORT_E,
     GPIO_PORT_F,
     GPIO_PORT_G
}GPIO_enuPORT_NO_t;

typedef enum {
    FLOATING,
    pull_UP,
    pull_Down
}GPIO_enuPULL_cfg_t ;

typedef enum {
  GPIO_INPUT,
  GPIO_max_speed_10_MHz,
  GPIO_max_speed_2_MHz,
  GPIO_max_speed_50_MHz
}GPIO_enuSpeed_t;


typedef enum {
   GPIO_LOGIC_LOW,
   GPIO_LOGIC_HIGH
}GPIO_enuLogic_t;


typedef enum{
     Gpio_enuOk,
     Gpio_enuNULL_PTR,
     Gpio_enuINVALID_LOGIC,
     Gpio_enuINVALID_PORT,
     Gpio_enuINVALID_PIN,
     Gpio_enuINVALID_Action
} GPIO_tenuErrorStatus;

/*********************************** user defined data types section end **************************/



/****************************** function prototypes section****************************************/
GPIO_tenuErrorStatus GPIO_PIN_INIT(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,uint8 mode,GPIO_enuSpeed_t speed,GPIO_enuPULL_cfg_t pull);
GPIO_tenuErrorStatus GPIO_set_PIN_value(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,GPIO_enuLogic_t action);
void GPIO_togle_PIN(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port);
void Atomic_bit_reset(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port);
void Atomic_bit_set(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port);
GPIO_tenuErrorStatus GPIO_get_PIN_value(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,uint8* Locpuint8value);
GPIO_tenuErrorStatus GPIO_Port_Enable_clock(GPIO_enuPORT_NO_t port);
GPIO_tenuErrorStatus GPIO_Port_Disable_clock(GPIO_enuPORT_NO_t port);
GPIO_tenuErrorStatus GPIO_Port_Reset_clock(GPIO_enuPORT_NO_t port);

/****************************** function prototypes section end************************************/

#endif /* MCAL_GPIO_GPIO_H_ */
