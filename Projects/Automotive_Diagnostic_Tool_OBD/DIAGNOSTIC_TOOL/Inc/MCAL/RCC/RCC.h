/**
 ******************************************************************************
 * @file           : RCC.h
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 15, 2023
 ******************************************************************************
 */

#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_



/************************************* include section ****************************************/
#include"../../../SERVICES/Standard_Data_Types.h"
#include"../../../SERVICES/Bit_Wise_Operations.h"
#include "RCC_CFG.h"
#include"RCC_PRIV.h"

/************************************* include section end ************************************/

/***************************************** macros section *************************************/


/* SYSCLK OPTIONS AND INPUT PARAMETERS FOR Rcc_enuSelectSysCLk */

#define RCC_CLK_HSI 	0x00000000		//ALSO USED IN Rcc_enuCheckCLk
#define RCC_CLK_HSE 	0x00000001		//ALSO USED IN Rcc_enuCheckCLk
#define RCC_CLK_PLL 	0x00000002		//ALSO USED IN Rcc_enuCheckCLk


/*CONTROL EACH CLK BY SELECTING THREE FROM THOSE INPUT PARAMETERS FOR Rcc_enuControlCLk*/
#define RCC_CNTROL_HSION 	3
#define RCC_CNTROL_HSIOFF	4
#define RCC_CNTROL_HSEON	5
#define RCC_CNTROL_HSEOFF	6
#define RCC_CNTROL_PLLON	7
#define RCC_CNTROL_PLLOFF	8
///////////////////////////////////////////////////////////////////////////////////////

//////VALUES OF THE CREATED VALUE FOR CHECKING READY OR NOT IN  Rcc_enuCheckCLk/////////
#define RCC_STATE_NOTREADY  	0
#define RCC_STATE_READY  	1


///////////////////////INPUTS FOR Rcc_enuCfgBusPrescalers///////////////////////////////////


/*PPRE2 OPTIONS and masks*/
#define RCC_APB2_NOTDIV  0xFFFFC7FF
#define RCC_APB2_DIV2    0x2000
#define RCC_APB2_DIV4    0x2800
#define RCC_APB2_DIV8    0x3000
#define RCC_APB2_DIV16   0x3800

/*PPRE1 OPTIONS and masks*/
#define RCC_APB1_NOTDIV  0xFFFFF8FF
#define RCC_APB1_DIV2    0x400
#define RCC_APB1_DIV4    0x500
#define RCC_APB1_DIV8    0x600
#define RCC_APB1_DIV16   0x700

/*HPRE OPTIONS and masks*/
#define RCC_AHB_NOTDIV  0xFFFFFF0F
#define RCC_AHB_DIV2    0x80
#define RCC_AHB_DIV4    0x90
#define RCC_AHB_DIV8    0xA0
#define RCC_AHB_DIV16   0xB0
#define RCC_AHB_DIV64   0xC0
#define RCC_AHB_DIV128  0xD0
#define RCC_AHB_DIV256  0xE0
#define RCC_AHB_DIV512  0xF0

#define RCC_AHB_NOTDIV_DEVIDER      1
#define RCC_AHB_DIV2_DEVIDER        2
#define RCC_AHB_DIV4_DEVIDER        4
#define RCC_AHB_DIV8_DEVIDER        8
#define RCC_AHB_DIV16_DEVIDER       16
#define RCC_AHB_DIV64_DEVIDER       64
#define RCC_AHB_DIV128_DEVIDER      128
#define RCC_AHB_DIV256_DEVIDER      256
#define RCC_AHB_DIV512_DEVIDER      512

//adc Prescalers options and masks masks
#define RCC_ADC_PRESCALER_DIV_2  	 0xFFFF3FFF
#define RCC_ADC_PRESCALER_DIV_4	 	 0x4000
#define RCC_ADC_PRESCALER_DIV_8		 0x8000
#define RCC_ADC_PRESCALER_DIV_16	 0xc000

#define RCC_PLL_MUL_MASK                 0xFFC3FFFF

#define RCC_PLL_INPUT_CLOCK_X_2_MASK   (0x00000000U)
#define RCC_PLL_INPUT_CLOCK_X_3_MASK   (0x00040000U)
#define RCC_PLL_INPUT_CLOCK_X_4_MASK   (0x00080000U)
#define RCC_PLL_INPUT_CLOCK_X_5_MASK   (0x000C0000U)
#define RCC_PLL_INPUT_CLOCK_X_6_MASK   (0x00100000U)
#define RCC_PLL_INPUT_CLOCK_X_7_MASK   (0x00140000U)
#define RCC_PLL_INPUT_CLOCK_X_8_MASK   (0x00180000U)
#define RCC_PLL_INPUT_CLOCK_X_9_MASK   (0x001C0000U)
#define RCC_PLL_INPUT_CLOCK_X_10_MASK  (0x00200000U)
#define RCC_PLL_INPUT_CLOCK_X_11_MASK  (0x00240000U)
#define RCC_PLL_INPUT_CLOCK_X_12_MASK  (0x00280000U)
#define RCC_PLL_INPUT_CLOCK_X_13_MASK  (0x002C0000U)
#define RCC_PLL_INPUT_CLOCK_X_14_MASK  (0x00300000U)
#define RCC_PLL_INPUT_CLOCK_X_15_MASK  (0x00340000U)
#define RCC_PLL_INPUT_CLOCK_X_16_MASK  (0x00380000U)


//mco clock source slection
#define  MCO_NO_CLOCK              0xF8FFFFFF
#define  MCO_CLK_SOURCE_SYSCLK     0x4000000
#define  MCO_CLK_SOURCE_HSI        0X5000000
#define  MCO_CLK_SOURCE_HSE        0x6000000
#define  MCO_CLK_SOURCE_PLL_DIV_2  0x7000000

/*********************************** macros section end ***************************************/


/*********************************** user defined data types section **************************/


/* ERROR STATUS ENUM */
typedef enum
{
	Rcc_enuOk,
	Rcc_enuTimeOutError,
	RCC_enuUnLogicActionError,
	RCC_enuNullPointerError,
	RCC_enuInvalid_ScrPll_Error,
	RCC_enuPll_IS_sys_clk_src_Error,
	Rcc_enuWrongAHB_PrescalerError,
	Rcc_enuWrongAPB1_PrescalerError,
	Rcc_enuWrongAPB2_PrescalerError,
	Rcc_enuWrongAHB_WRONG_PERIPHERAL,
	Rcc_enuWrongAPB1_WRONG_PERIPHERAL,
	Rcc_enuWrongAPB2_WRONG_PERIPHERAL,
	Rcc_enuWrongADC_PrescalerError,
	RCC_enuWrongMCOSourceError,
	RCC_enuWrongUSBSourceError
} Rcc_tenuErrorStatus;

//chose if you need the old clock to stay enable or disabled
typedef enum {
 RCC_STATE_PRESERVE,
 RCC_STATE_NOTPRESERVE
}RCC_enuOLD_CLOCK_STATE_t;

typedef enum {
 RCC_PLL_SRC_HSI_DIV_2,
 RCC_PLL_SRC_HSE
}RCC_PLL_CLOCK_Source_t;

typedef enum {
 RCC_PLL_HSE_NO_DIV,
 RCC_PLL_HSE_DIV_2
}RCC_PLL_SRC_HSE_DIV_t;

typedef enum {
    RCC_Periph_DISABLE,
    RCC_Periph_ENABLE,
} RCC_Periph_CFG_TypeDef;

typedef enum {
    RCC_USB_SRC_PLL_DIVIDED,
    RCC_USB_SRC_PLL,
} RCC_USB_CLK_SRC_TypeDef;

typedef enum {
  RCC_AHB_Periph_DMA1=0, //DMA1 clock
  RCC_AHB_Periph_DMA2=1, //DMA2 clocK
  RCC_AHB_Periph_SRAM=2, //SRAM interface clock
//3   Reserved
  RCC_AHB_Periph_FLITF=4, //FLITF clock
//5   Reserved
  RCC_AHB_Periph_CRC=6, //CRC clock
  // 7  Reserved
  RCC_AHB_Periph_FSMC=8, //FSMC clock
// 9  Reserved, must be kept at reset value
   RCC_AHB_Periph_SDIO=10, //SDIO clock
// 11-31   Reserved
} RCC_AHBPeriph_TypeDef;

typedef enum {
  RCC_APB1_Periph_TIM2   = 0,   // TIM2 timer clock
  RCC_APB1_Periph_TIM3   = 1,   // TIM3 timer clock
  RCC_APB1_Periph_TIM4   = 2,   // TIM4 timer clock
  RCC_APB1_Periph_TIM5   = 3,   // TIM5 timer clock
  RCC_APB1_Periph_TIM6   = 4,   // TIM6 timer clock
  RCC_APB1_Periph_TIM7   = 5,   // TIM7 timer clock
  RCC_APB1_Periph_TIM12  = 6,   // TIM12 timer clock
  RCC_APB1_Periph_TIM13  = 7,   // TIM13 timer clock
  RCC_APB1_Periph_TIM14  = 8,   // TIM14 timer clock
  //10-9 reserved
  RCC_APB1_Periph_WWDG  = 11,  // Window watchdog clock
  RCC_APB1_Periph_SPI2  = 14,  // SPI2 clock
  RCC_APB1_Periph_SPI3  = 15,  // SPI3 clock
  //16 reserved
  RCC_APB1_Periph_USART2 = 17,  // USART2 clock
  RCC_APB1_Periph_USART3 = 18,  // USART3 clock
  RCC_APB1_Periph_UART4  = 19,  // USART4 clock
  RCC_APB1_Periph_UART5  = 20,  // USART5 clock
  RCC_APB1_Periph_I2C1   = 21,  // I2C1 clock
  RCC_APB1_Periph_I2C2   = 22,  // I2C2 clock
  RCC_APB1_Periph_USB    = 23,  // USB clock
  //24 Reserved, must be kept at reset value
  RCC_APB1_Periph_CAN    = 25,  // CAN clock
  // 26  Reserved, must be kept at reset value
  RCC_APB1_Periph_BKP   = 27,  // Backup interface clock
  RCC_APB1_Periph_PWR   = 28,  // Power interface clock
  RCC_APB1_Periph_DAC   = 29   // DAC interface clock
} RCC_APB1Periph_TypeDef;

typedef enum {
    AFIORST  = 0,   // Alternate function IO reset
    // Bit 1: Reserved, must be kept at reset value
    RCC_APB2_Periph_IOPA = 2,   // IO port A reset
    RCC_APB2_Periph_IOPB = 3,   // IO port B reset
    RCC_APB2_Periph_IOPC = 4,   // IO port C reset
    RCC_APB2_Periph_IOPD = 5,   // IO port D reset
    RCC_APB2_Periph_IOPE = 6,   // IO port E reset
    RCC_APB2_Periph_IOPF = 7,   // IO port F reset
    RCC_APB2_Periph_IOPG = 8,   // IO port G reset
    RCC_APB2_Periph_ADC1 = 9,   // ADC 1 interface reset
    RCC_APB2_Periph_ADC2 = 10,  // ADC 2 interface reset
    RCC_APB2_Periph_TIM1 = 11,  // TIM1 timer reset
    RCC_APB2_Periph_SPI1 = 12,  // SPI1 reset
    RCC_APB2_Periph_TIM8 = 13,  // TIM8 timer reset
    RCC_APB2_Periph_USART1 = 14, // USART1 reset
    RCC_APB2_Periph_ADC3  = 15,  // ADC3 interface reset
    // Bits 18-16: Reserved, always read as 0
    RCC_APB2_Periph_TIM9  = 19,  // TIM9 timer reset
    RCC_APB2_Periph_TIM10 = 20,  // TIM10 timer reset
    RCC_APB2_Periph_TIM11 = 21   // TIM11 timer reset
} RCC_APB2Periph_TypeDef;


/*********************************** user defined data types section end **************************/



/****************************** function prototypes section****************************************/


/*
 * @Brief   : select the system clock source & on or off the old clock
 * @options :
 * 	@PARM1:
 * 				RCC_CLK_HSI
 * 				RCC_CLK_HSE
 * 				RCC_CLK_PLL
 *      @PARM2:
 *				RCC_STATE_PRESERVE,
 *				RCC_STATE_NOTPRESERVE
 *
 * */

Rcc_tenuErrorStatus Rcc_enuSelectSysCLk(uint8 Copy_uint8SysClk , RCC_enuOLD_CLOCK_STATE_t Copy_enuOldSysClk) ;

/*
 * @Brief   : on / off the clock sources
 * @options :
 *
 * 	 @PARM1:
 *      	RCC_CNTROL_HSION
 *		RCC_CNTROL_HSIOFF
 * 	 @PARM2:
 * 		RCC_CNTROL_HSEON
 * 		RCC_CNTROL_HSEOFF
 * 	 @PARM3:
 *	    	RCC_CNTROL_PLLON
 *		RCC_CNTROL_PLLOFF
 *
 * */

Rcc_tenuErrorStatus Rcc_enuControlCLk(uint8 Copy_uint8ControlHSI  ,uint8 Copy_uint8ControlHSE ,uint8 Copy_uint8ControlPLL) ;

Rcc_tenuErrorStatus Rcc_enuCheckCLk(uint8 Copy_uint8CLk, Puint8 Add_puint8RdyStatus) ;

Rcc_tenuErrorStatus Rcc_enuCfg_PLL_CFG(RCC_PLL_CLOCK_Source_t Copy_enuPLLsrc,uint32 Copy_u32PLLmul,RCC_PLL_SRC_HSE_DIV_t Copy_enuPLL_HSEdiv);

Rcc_tenuErrorStatus Rcc_enuGET_SYS_CLOCK(Puint8 ADD_puint8SYSclocK);

/*******************************config buss prescaller*************************/
Rcc_tenuErrorStatus Rcc_enuCfg_AHB_BusPrescalers(uint32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_APB1_BusPrescalers(uint32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_APB2_BusPrescalers(uint32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_ADC_ClockSrc_Prescalers(uint32 Copy_u32Prescaler);

Rcc_tenuErrorStatus Rcc_enuCfg_USB_ClockSrc_Prescalers(RCC_USB_CLK_SRC_TypeDef Source);

/** enable OR disabled clock for the input Peripheral depending on action parameter**/

Rcc_tenuErrorStatus Rcc_enuControl_AHB_Peripheral(RCC_AHBPeriph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);

Rcc_tenuErrorStatus Rcc_enuControl_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);
Rcc_tenuErrorStatus Rcc_enuControl_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action);

Rcc_tenuErrorStatus Rcc_enuReset_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral);
Rcc_tenuErrorStatus Rcc_enuReset_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral);

Rcc_tenuErrorStatus Rcc_enuMCO_CLOCK_slector(uint32 Source);


/****************************** function prototypes section end************************************/

#endif /* MCAL_RCC_RCC_H_ */
