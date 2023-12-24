/**
 ******************************************************************************
 * @file           : GPIO.c
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 15, 2023
 ******************************************************************************
 */
#include"../Inc/MCAL/GPIO/GPIO.h"
#define GPIOPA       ((GPIO_t*)(GPIOA_BASE_ADREES))
#define GPIOPB       ((GPIO_t*)(GPIOB_BASE_ADREES))
#define GPIOPC       ((GPIO_t*)(GPIOC_BASE_ADREES))
#define GPIOPD       ((GPIO_t*)(GPIOD_BASE_ADREES))
#define GPIOPE       ((GPIO_t*)(GPIOE_BASE_ADREES))
#define GPIOPF       ((GPIO_t*)(GPIOF_BASE_ADREES))
#define GPIOPG       ((GPIO_t*)(GPIOG_BASE_ADREES))

typedef struct{
	volatile uint32 GPIOx_CRL;
	volatile uint32 GPIOx_CRH;
	volatile uint32 GPIOx_IDR;
	volatile uint32 GPIOx_ODR;
	volatile uint32 GPIOx_BSRR;
	volatile uint32 GPIOx_BRR;
	volatile uint32 GPIOx_LCKR;
} GPIO_t ;

#define CLEAR_1BITMask          (0x00000001)
#define CLEAR_2BITMask          (0x00000003)
#define CLEAR_4BITMask          (0x0000000f)

static GPIO_t* const portARR[]={GPIOPA,GPIOPB,GPIOPC,GPIOPD,GPIOPE,GPIOPF,GPIOPG};

/*
 * @Brief   	: set desired value to specific pin
 * @PARM1	: pin no
 * @PARM2	: port no
 * @PARM3	:
 * 			  Input_Analog
 *			  InputFloating
 *			  Input_pull_up_down
 *			  output_push_pull
 *			  output_Open_drain
 *			  AF_output_Push_pull
 *			  AF_output_Open_drain
 *--------------------------------------------------------------------
 * @parm4	:
 *			  GPIO_INPUT
 *			  GPIO_max_speed_10_MHz
 *			  GPIO_max_speed_2_MHz
 *			  GPIO_max_speed_50_MHz
 *--------------------------------------------------------------------
 * @parm5	:
 *     		          FLOATING
 *     		          pull_UP
 *    		          pull_Down
 *
 * */
GPIO_tenuErrorStatus GPIO_PIN_INIT(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,uint8 mode,GPIO_enuSpeed_t speed,GPIO_enuPULL_cfg_t pull)
{
  GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
  if((0<=Locpin)&&(Locpin<=7))
   {
      //set clock speed or config the pin as input
      (portARR[port]->GPIOx_CRL)=((portARR[port]->GPIOx_CRL)&(~(CLEAR_2BITMask<<(Locpin*4))))|(speed<<(Locpin*4));

      //set the mode configuration if input or output don't care
      (portARR[port]->GPIOx_CRL)=((portARR[port]->GPIOx_CRL)&(~(CLEAR_2BITMask<<(Locpin*4+2))))|(mode<<(Locpin*4+2));
   }
  else if((8<=Locpin)&&(Locpin<=15))
    {
      Locpin-=8;
       //set clock speed or config the pin as input
       (portARR[port]->GPIOx_CRH)=((portARR[port]->GPIOx_CRH)&(~(CLEAR_2BITMask<<(Locpin*4))))|(speed<<(Locpin*4));

       //set the mode configuration if input or output don't care
       (portARR[port]->GPIOx_CRH)=((portARR[port]->GPIOx_CRH)&(~(CLEAR_2BITMask<<(Locpin*4+2))))|(mode<<(Locpin*4+2));
       Locpin+=8;
    }
  else
    {
      Locerrorstatus=Gpio_enuINVALID_PIN;

    }
  if(pull==pull_Down)
    {
      CLR_BIT(portARR[port]->GPIOx_ODR,Locpin);
    }
  else if(pull==pull_UP)
    {
      SET_BIT(portARR[port]->GPIOx_ODR,Locpin);
    }
  else
    {
      Locerrorstatus=Gpio_enuINVALID_Action;

    }
  return Locerrorstatus;

}
/*
 * @Brief   	: set desired value to specific pin
 * @PARM1	: pin no
 * @PARM2	: port no
 * @PARM3	: value
 *
 * */
GPIO_tenuErrorStatus GPIO_set_PIN_value(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,GPIO_enuLogic_t action)
{
  GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
  if(action==GPIO_LOGIC_LOW)
    {
      CLR_BIT((portARR[port]->GPIOx_ODR),Locpin);
    }
  else if(action==GPIO_LOGIC_HIGH)
    {
      SET_BIT((portARR[port]->GPIOx_ODR),Locpin);
    }
  else
    {
      Locerrorstatus=Gpio_enuINVALID_Action;

    }
  return Locerrorstatus;
}
/*
 * @Brief   	: toggle pin
 * @PARM1   	: pin no
 * @PARM2   	: port no
 *
 * */
void GPIO_togle_PIN(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port)
{
  TGL_BIT(portARR[port]->GPIOx_ODR,Locpin);
}

void Atomic_bit_set(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port)
{
  SET_BIT((portARR[port]->GPIOx_BSRR),Locpin);
}
void Atomic_bit_reset(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port)
{
  SET_BIT((portARR[port]->GPIOx_BSRR),(Locpin+16));
}

/*
 * @Brief   	: get specific pin value
 * @PARM1	: pin no
 * @PARM2	: port no
 * @PARM3	: pointer to receive the pin value
 *
 * */
GPIO_tenuErrorStatus GPIO_get_PIN_value(GPIO_enuPIN_NO_t Locpin,GPIO_enuPORT_NO_t port,uint8* Locpuint8value)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
    uint16 localuint16_temp=0;
    if(NULL==Locpuint8value)
    {
        Locerrorstatus=Gpio_enuNULL_PTR;
    }
    else
    {
	localuint16_temp=portARR[port]->GPIOx_IDR;
        *Locpuint8value=(localuint16_temp&(1<<(Locpin)))>>(Locpin);
    }
    return Locerrorstatus;
}
/*
 * @Brief   	: enable clock for gpio port
 * @PARM1	: port no
 *
 * */
GPIO_tenuErrorStatus GPIO_Port_Enable_clock(GPIO_enuPORT_NO_t port)
{
  GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
  switch(port)
  {
    case GPIO_PORT_A:
    case GPIO_PORT_B:
    case GPIO_PORT_C:
    case GPIO_PORT_D:
    case GPIO_PORT_E:
    case GPIO_PORT_F:
    case GPIO_PORT_G:
      //+2 used because in RCC_APB2ENR ports bits started from 2
      //@ref: RCC_APB2Periph_TypeDef in RCC.h file
      Rcc_enuControl_APB2_Peripheral(((RCC_APB2Periph_TypeDef)(port+2)),RCC_Periph_ENABLE);
      break;
    default:
      Locerrorstatus=Gpio_enuINVALID_PORT;
      break;
  }
  return Locerrorstatus;

}
/*
 * @Brief   	: reset clock for gpio port
 * @PARM1	: port no
 *
 * */
GPIO_tenuErrorStatus GPIO_Port_Reset_clock(GPIO_enuPORT_NO_t port)
{
    GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
  switch(port)
  {
    case GPIO_PORT_A:
    case GPIO_PORT_B:
    case GPIO_PORT_C:
    case GPIO_PORT_D:
    case GPIO_PORT_E:
    case GPIO_PORT_F:
    case GPIO_PORT_G:
      //+2 used because in RCC_APB2ENR ports bits started from 2
      //@ref: RCC_APB2Periph_TypeDef in RCC.h file
      Rcc_enuReset_APB2_Peripheral((RCC_APB2Periph_TypeDef)(port+2));
      break;
    default:
      Locerrorstatus=Gpio_enuINVALID_PORT;
      break;
   }
  return Locerrorstatus;

}
/*
 * @Brief   	: disable clock for gpio port
 * @PARM1	: port no
 *
 * */
GPIO_tenuErrorStatus GPIO_Port_Disable_clock(GPIO_enuPORT_NO_t port)
{
  GPIO_tenuErrorStatus Locerrorstatus=Gpio_enuOk;
  switch(port)
  {
    case GPIO_PORT_A:
    case GPIO_PORT_B:
    case GPIO_PORT_C:
    case GPIO_PORT_D:
    case GPIO_PORT_E:
    case GPIO_PORT_F:
    case GPIO_PORT_G:
      //+2 used because in RCC_APB2ENR ports bits started from 2
      //@ref: RCC_APB2Periph_TypeDef in RCC.h file
      Rcc_enuControl_APB2_Peripheral(((RCC_APB2Periph_TypeDef)(port+2)),RCC_Periph_DISABLE);
      break;
    default:
      Locerrorstatus=Gpio_enuINVALID_PORT;
      break;
  }
  return Locerrorstatus;
}



