/**
 ******************************************************************************
 * @file           : RCC.c
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 15, 2023
 ******************************************************************************
 */
#include"../../../Inc/MCAL/RCC/RCC.h"
#define REGISTER_BIT_0  0
#define REGISTER_BIT_1	1
#define REGISTER_BIT_2	2
#define REGISTER_BIT_3	3
#define REGISTER_BIT_4	4
#define REGISTER_BIT_5	5
#define REGISTER_BIT_6	6
#define REGISTER_BIT_7	7
#define REGISTER_BIT_8	8
#define REGISTER_BIT_9	9
#define REGISTER_BIT_10	10
#define REGISTER_BIT_11	11
#define REGISTER_BIT_12	12
#define REGISTER_BIT_13	13
#define REGISTER_BIT_14	14
#define REGISTER_BIT_15	15
#define REGISTER_BIT_16	16
#define REGISTER_BIT_17	17
#define REGISTER_BIT_18	18
#define REGISTER_BIT_19	19
#define REGISTER_BIT_20	20
#define REGISTER_BIT_21	21
#define REGISTER_BIT_22	22
#define REGISTER_BIT_23	23
#define REGISTER_BIT_24	24
#define REGISTER_BIT_25	25
#define REGISTER_BIT_26	26
#define REGISTER_BIT_27	27
#define REGISTER_BIT_28	28
#define REGISTER_BIT_29	29
#define REGISTER_BIT_30	30
#define REGISTER_BIT_31	31
#define REGISTER_BIT_32	32



#define Delay_value 10000

#ifndef EXTERNAL_FREQ
#error"EXTERNAL_FREQ not defined in RCC_CFG.h file "
#endif

// internal clock source freq
#define HSI_RC 8000000

//used in Rcc_enuSelectSysCLk fn
#define HSI_SLECT_MASK 0xFFFFFFFC
#define HSE_SLECT_MASK 0xFFFFFFFD
#define PLL_slect_MASK 0xFFFFFFFE

//used in Rcc_enuGET_SYS_CLOCK fn
#define CLOCK_SLESCT_MASK 0x0C

// this var is aglopal var used to inform al other prephiral with the system freq
volatile float32 STM_SYS_FREQ=1;
volatile uint32 PLL_source=0;
volatile uint32 PLL_OUTPUT=0;





/*
 * @Brief   : select the system clock source & on or off the old clock
 * @options :
 * 	@PARM1:
 * 				RCC_CLK_HSI
 * 				RCC_CLK_HSE
 * 				RCC_CLK_PLL
 *  @PARM2:
 *				RCC_STATE_PRESERVE,
 *				RCC_STATE_NOTPRESERVE
 *
 * */

Rcc_tenuErrorStatus Rcc_enuSelectSysCLk(uint8 Copy_uint8SysClk , RCC_enuOLD_CLOCK_STATE_t Copy_enuOldSysClk)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    uint32 loc_counter=Delay_value;// used to get out from checking the flag in the simulation
    uint32 old_clock=((RCC->RCC_CFGR)&0x03);// get the old system clock
    switch (Copy_uint8SysClk)
    {
    case RCC_CLK_HSI:
        SET_BIT(RCC->RCC_CR,REGISTER_BIT_0);
        // wait untill clock source be ready
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_1)))
        {
           if(loc_counter==0)
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR&=HSI_SLECT_MASK;
        STM_SYS_FREQ*= HSI_RC;
        break;
    case RCC_CLK_HSE:
        SET_BIT(RCC->RCC_CR,REGISTER_BIT_16);
         // wait untill clock source be ready
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_17)))
        {
           if(loc_counter==0)
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR=((RCC->RCC_CFGR)&HSI_SLECT_MASK)|RCC_CLK_HSE;
        STM_SYS_FREQ*= EXTERNAL_FREQ;
        break;
    case RCC_CLK_PLL:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_24);
        while(!(GET_BIT(RCC->RCC_CR,REGISTER_BIT_25)))
        {
           if(loc_counter==0)
           {
            break;
           }
           loc_counter--;
        }
        // switch to the desired clock
        RCC->RCC_CFGR=((RCC->RCC_CFGR)&HSI_SLECT_MASK)|RCC_CLK_PLL;
        STM_SYS_FREQ*=PLL_OUTPUT;
        break;
    default:
        Locerrorstatus=RCC_enuUnLogicActionError;
        break;
    }
    if(Copy_enuOldSysClk==RCC_STATE_NOTPRESERVE)
    {
      switch(old_clock)
      {
        case RCC_CLK_HSI:
           CLR_BIT(RCC->RCC_CR,REGISTER_BIT_0);
           break;
        case RCC_CLK_HSE:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        case RCC_CLK_PLL:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_26);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
     }
    }

    return Locerrorstatus;
}

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
Rcc_tenuErrorStatus Rcc_enuControlCLk(uint8 Copy_uint8ControlHSI  ,uint8 Copy_uint8ControlHSE ,uint8 Copy_uint8ControlPLL)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_uint8ControlHSI)
    {
        case RCC_CNTROL_HSION:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_0);
            break;
        case RCC_CNTROL_HSIOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_0);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
    }
    switch(Copy_uint8ControlHSE)
    {
        case RCC_CNTROL_HSEON:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        case RCC_CNTROL_HSEOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_16);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
    }
    switch(Copy_uint8ControlPLL)
    {
        case RCC_CNTROL_PLLON:
            SET_BIT(RCC->RCC_CR,REGISTER_BIT_24);
            break;
        case RCC_CNTROL_PLLOFF:
            CLR_BIT(RCC->RCC_CR,REGISTER_BIT_24);
            break;
        default:
            Locerrorstatus=RCC_enuUnLogicActionError;
            break;
    }
    return Locerrorstatus;
}

/*
 * @Brief   : check the status of the desired clock source if it ready or not
 * @options :
 * 	@PARM1:
 * 				RCC_CLK_HSI
 * 				RCC_CLK_HSE
 * 				RCC_CLK_PLL
 *  	@PARM2: pointer to uint8 variable receive the status in it
 *
 * */
Rcc_tenuErrorStatus Rcc_enuCheckCLk(uint8 Copy_uint8CLk, Puint8 Add_puint8RdyStatus)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if (NULL==Add_puint8RdyStatus)
    {
        Locerrorstatus=RCC_enuNullPointerError;
    }
    else
    {
     switch(Copy_uint8CLk)
      {
        case RCC_CLK_HSI:
            *Add_puint8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_1);
           break;
        case RCC_CLK_HSE:
            *Add_puint8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_17);
            break;
        case RCC_CLK_PLL:
           *Add_puint8RdyStatus=GET_BIT(RCC->RCC_CR,REGISTER_BIT_25);
            break;
        default:
             Locerrorstatus=RCC_enuUnLogicActionError;
            break;
      }
    }
    return Locerrorstatus;
}

/*
 * @Brief   : get the system clock source
 * @PARM:pointer to uint8 variable receive the source in it
 *
 * */
Rcc_tenuErrorStatus Rcc_enuGET_SYS_CLOCK(Puint8 ADD_puint8SYSclocK)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    if (NULL==ADD_puint8SYSclocK)
    {
        Locerrorstatus=RCC_enuNullPointerError;
    }
    else
    {
        *ADD_puint8SYSclocK=((RCC->RCC_CFGR)&CLOCK_SLESCT_MASK)>>2;// get the old system clock
    }

    return Locerrorstatus;
}

/*
* @Brief   : set the prescaler for AHB bus and update the
* @options :
*			  RCC_AHB_NOTDIV
*            RCC_AHB_DIV2
*            RCC_AHB_DIV4
*            RCC_AHB_DIV8
*            RCC_AHB_DIV16
*            RCC_AHB_DIV64
*            RCC_AHB_DIV128
*            RCC_AHB_DIV256
*            RCC_AHB_DIV512
*
* */
Rcc_tenuErrorStatus Rcc_enuCfg_AHB_BusPrescalers(uint32 Copy_uint32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_uint32Prescaler)
    {
        case RCC_AHB_NOTDIV:
            (RCC->RCC_CFGR)&=RCC_AHB_NOTDIV;
            break;
         case RCC_AHB_DIV2:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV2_DEVIDER;//update system freq variable
            break;
         case RCC_AHB_DIV4:
           (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV4_DEVIDER;//update system freq variable
            break;
         case RCC_AHB_DIV8:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV8_DEVIDER;//update system freq variable
            break;
         case RCC_AHB_DIV16:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV16_DEVIDER;//update system freq variable
            break;
        case RCC_AHB_DIV64:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV64_DEVIDER;//update system freq variable
            break;
        case RCC_AHB_DIV128:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV128_DEVIDER;//update system freq variable
            break;
        case RCC_AHB_DIV256:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV256_DEVIDER;//update system freq variable
            break;
        case RCC_AHB_DIV512:
	    (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_AHB_NOTDIV)|Copy_uint32Prescaler;
            STM_SYS_FREQ/=RCC_AHB_DIV512_DEVIDER;//update system freq variable
            break;
         default:
            Locerrorstatus=Rcc_enuWrongAHB_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : set the prescaler for APB1 bus and update the
* @options :
*			 RCC_APB1_NOTDIV
*            RCC_APB1_DIV2
*            RCC_APB1_DIV4
*            RCC_APB1_DIV8
*            RCC_APB1_DIV16
* */
Rcc_tenuErrorStatus Rcc_enuCfg_APB1_BusPrescalers(uint32 Copy_uint32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_uint32Prescaler)
    {
        case RCC_APB1_NOTDIV:
          (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_APB1_NOTDIV);
	  break;
        case RCC_APB1_DIV2:
        case RCC_APB1_DIV4:
        case RCC_APB1_DIV8:
        case RCC_APB1_DIV16:
            (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_APB1_NOTDIV)|Copy_uint32Prescaler;
            break;
        default:
            Locerrorstatus=Rcc_enuWrongAPB1_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : set the prescaler for APB2 bus and update the
* @options :
*			 RCC_APB2_NOTDIV
*            RCC_APB2_DIV2
*            RCC_APB2_DIV4
*            RCC_APB2_DIV8
*            RCC_APB2_DIV16
*
* */
Rcc_tenuErrorStatus Rcc_enuCfg_APB2_BusPrescalers(uint32 Copy_uint32Prescaler)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Copy_uint32Prescaler)
    {
         case RCC_APB2_NOTDIV:
           (RCC->RCC_CFGR)=(RCC->RCC_CFGR)&RCC_APB2_NOTDIV;
           break;
         case RCC_APB2_DIV2:
         case RCC_APB2_DIV4:
         case RCC_APB2_DIV8:
         case RCC_APB2_DIV16:
           (RCC->RCC_CFGR)=(((RCC->RCC_CFGR)&RCC_APB2_NOTDIV)|Copy_uint32Prescaler);
           break;
         default:
            //in valid input
            Locerrorstatus=Rcc_enuWrongAPB2_PrescalerError;
            break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : set the prescaler for ADC clock source
* @options :
*				 RCC_ADC_PRESCALER_DIV_2
*				 RCC_ADC_PRESCALER_DIV_4
*				 RCC_ADC_PRESCALER_DIV_8
*				 RCC_ADC_PRESCALER_DIV_16
*
* */
Rcc_tenuErrorStatus Rcc_enuCfg_ADC_ClockSrc_Prescalers(uint32 Copy_uint32Prescaler)
{
  Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
      switch(Copy_uint32Prescaler)
      {
           case RCC_ADC_PRESCALER_DIV_2:
             (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_ADC_PRESCALER_DIV_2);
             break;
           case RCC_ADC_PRESCALER_DIV_4:
           case RCC_ADC_PRESCALER_DIV_8:
           case RCC_ADC_PRESCALER_DIV_16:
             (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&RCC_ADC_PRESCALER_DIV_2)|Copy_uint32Prescaler;
             break;
           default:
              //in valid input
              Locerrorstatus=Rcc_enuWrongADC_PrescalerError;
              break;
      }
      return Locerrorstatus;
}

/*
* @Brief   : config the pll clock source
* @Note    : using of this fn will case disable PLL in first then re enable it  PLL first then open it again
*            this fn will execute if only the PLL did not the system clock source yet
*@Parm1    :
*		 		  RCC_PLL_SRC_HSI_DIV_2
*		 		  RCC_PLL_SRC_HSE
*--------------------------------------------------
*@Parm2    :
*				  RCC_PLL_INPUT_CLOCK_X_2_MASK
*				  RCC_PLL_INPUT_CLOCK_X_3_MASK
*				  RCC_PLL_INPUT_CLOCK_X_4_MASK
*				  RCC_PLL_INPUT_CLOCK_X_5_MASK
*				  RCC_PLL_INPUT_CLOCK_X_6_MASK
*				  RCC_PLL_INPUT_CLOCK_X_7_MASK
*				  RCC_PLL_INPUT_CLOCK_X_8_MASK
*				  RCC_PLL_INPUT_CLOCK_X_9_MASK
*				  RCC_PLL_INPUT_CLOCK_X_10_MASK
*				  RCC_PLL_INPUT_CLOCK_X_11_MASK
*				  RCC_PLL_INPUT_CLOCK_X_12_MASK
*				  RCC_PLL_INPUT_CLOCK_X_13_MASK
*				  RCC_PLL_INPUT_CLOCK_X_14_MASK
*				  RCC_PLL_INPUT_CLOCK_X_15_MASK
*				  RCC_PLL_INPUT_CLOCK_X_16_MASK
*---------------------------------------------------------
*@Parm3    :
*                 RCC_PLL_HSE_NO_DIV,
*		  		  RCC_PLL_HSE_DIV_2
*---------------------------------------------------------
*/

Rcc_tenuErrorStatus Rcc_enuCfg_PLL_CFG(RCC_PLL_CLOCK_Source_t Copy_enuPLLsrc,uint32 Copy_uint32PLLmul,RCC_PLL_SRC_HSE_DIV_t Copy_enuPLL_HSEdiv)
{
  Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
  if(((RCC->RCC_CFGR)&0x03)==RCC_CLK_PLL)
   {
      Locerrorstatus=RCC_enuPll_IS_sys_clk_src_Error;
   }
  else
    {
      // disable PLL
      CLR_BIT(RCC->RCC_CR,REGISTER_BIT_24);

      if(Copy_enuPLLsrc==RCC_PLL_SRC_HSI_DIV_2)
	{
	  CLR_BIT(RCC->RCC_CFGR,REGISTER_BIT_16);
	  PLL_source=HSI_RC/2;

	}
      else if (Copy_enuPLLsrc==RCC_PLL_SRC_HSE)
	{
	  SET_BIT(RCC->RCC_CFGR,REGISTER_BIT_16);
	  PLL_source=EXTERNAL_FREQ;
	}
      else
	{
	  Locerrorstatus=RCC_enuInvalid_ScrPll_Error;
	}
      if(Copy_enuPLL_HSEdiv==RCC_PLL_HSE_NO_DIV)
	{
	  CLR_BIT(RCC->RCC_CFGR,REGISTER_BIT_17);
	}
      else if(Copy_enuPLL_HSEdiv==RCC_PLL_HSE_DIV_2)
	{
	  SET_BIT(RCC->RCC_CFGR,REGISTER_BIT_17);
	  PLL_source=EXTERNAL_FREQ/2;
	}
      else
	{
	  Locerrorstatus=RCC_enuInvalid_ScrPll_Error;
	}
      //set the multiplier
      RCC->RCC_CFGR=((RCC->RCC_CFGR)&RCC_PLL_MUL_MASK)|Copy_uint32PLLmul;
      PLL_OUTPUT =PLL_source*((Copy_uint32PLLmul>>18)+2);
      // enable PLL
      SET_BIT(RCC->RCC_CR,REGISTER_BIT_24);

    }
  return Locerrorstatus;
}

/*
* @Brief   : enable or disable Peripheral on AHB bus
*/
Rcc_tenuErrorStatus Rcc_enuControl_AHB_Peripheral(RCC_AHBPeriph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
        Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
        uint32 bitMASK=0;
        switch (Peripheral)
         {
            case RCC_AHB_Periph_DMA1:
            case RCC_AHB_Periph_DMA2:
            case RCC_AHB_Periph_SRAM:
            case RCC_AHB_Periph_FLITF:
            case RCC_AHB_Periph_CRC:
            case RCC_AHB_Periph_FSMC:
            case RCC_AHB_Periph_SDIO:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHBENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_AHBENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError;
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAHB_WRONG_PERIPHERAL;
                break;
    }
    return Locerrorstatus;
}


/*
* @Brief   : enable  or disable Peripheral on APB1 bus
*/
Rcc_tenuErrorStatus Rcc_enuControl_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    uint32 bitMASK=0;
        switch (Peripheral)
         {
		case RCC_APB1_Periph_TIM2  :
		case RCC_APB1_Periph_TIM3  :
		case RCC_APB1_Periph_TIM4  :
		case RCC_APB1_Periph_TIM5  :
		case RCC_APB1_Periph_TIM6  :
		case RCC_APB1_Periph_TIM7  :
		case RCC_APB1_Periph_TIM12 :
		case RCC_APB1_Periph_TIM13 :
		case RCC_APB1_Periph_TIM14 :
		case RCC_APB1_Periph_WWDG  :
		case RCC_APB1_Periph_SPI2  :
		case RCC_APB1_Periph_SPI3  :
		case RCC_APB1_Periph_USART2:
		case RCC_APB1_Periph_USART3:
		case RCC_APB1_Periph_UART4 :
		case RCC_APB1_Periph_UART5 :
		case RCC_APB1_Periph_I2C1  :
		case RCC_APB1_Periph_I2C2  :
		case RCC_APB1_Periph_USB   :
		case RCC_APB1_Periph_CAN   :
		case RCC_APB1_Periph_BKP   :
		case RCC_APB1_Periph_PWR   :
		case RCC_APB1_Periph_DAC   :
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1ENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB1ENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError;
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB1_WRONG_PERIPHERAL;
                break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : enable or disable Peripheral on APB2 bus
*/
Rcc_tenuErrorStatus Rcc_enuControl_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral,RCC_Periph_CFG_TypeDef action)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    uint32 bitMASK=0;
    switch (Peripheral)
    {
        case AFIORST:
        case RCC_APB2_Periph_IOPA:
	case RCC_APB2_Periph_IOPB:
	case RCC_APB2_Periph_IOPC:
	case RCC_APB2_Periph_IOPD:
	case RCC_APB2_Periph_IOPE:
	case RCC_APB2_Periph_IOPF:
	case RCC_APB2_Periph_IOPG:
	case RCC_APB2_Periph_ADC1:
	case RCC_APB2_Periph_ADC2:
	case RCC_APB2_Periph_TIM1:
	case RCC_APB2_Periph_SPI1:
	case RCC_APB2_Periph_TIM8:
	case RCC_APB2_Periph_USART1:
	case RCC_APB2_Periph_ADC3:
	case RCC_APB2_Periph_TIM9:
	case RCC_APB2_Periph_TIM10:
	case RCC_APB2_Periph_TIM11:
                // Valid peripheral, proceed with enabling or disabling
                if(action==RCC_Periph_ENABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2ENR|=bitMASK;
                }
                else if(action==RCC_Periph_DISABLE)
                {
                    bitMASK=1<<Peripheral;
                    RCC->RCC_APB2ENR&=~bitMASK;
                }
                else
                {
                    Locerrorstatus=RCC_enuUnLogicActionError;
                }

                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB2_WRONG_PERIPHERAL;
                break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : reset Peripheral on APB1 bus
*/
Rcc_tenuErrorStatus Rcc_enuReset_APB1_Peripheral(RCC_APB1Periph_TypeDef Peripheral)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    uint32 bitMASK=0;
        switch (Peripheral)
         {
		case RCC_APB1_Periph_TIM2  :
		case RCC_APB1_Periph_TIM3  :
		case RCC_APB1_Periph_TIM4  :
		case RCC_APB1_Periph_TIM5  :
		case RCC_APB1_Periph_TIM6  :
		case RCC_APB1_Periph_TIM7  :
		case RCC_APB1_Periph_TIM12 :
		case RCC_APB1_Periph_TIM13 :
		case RCC_APB1_Periph_TIM14 :
		case RCC_APB1_Periph_WWDG  :
		case RCC_APB1_Periph_SPI2  :
		case RCC_APB1_Periph_SPI3  :
		case RCC_APB1_Periph_USART2:
		case RCC_APB1_Periph_USART3:
		case RCC_APB1_Periph_UART4 :
		case RCC_APB1_Periph_UART5 :
		case RCC_APB1_Periph_I2C1  :
		case RCC_APB1_Periph_I2C2  :
		case RCC_APB1_Periph_USB   :
		case RCC_APB1_Periph_CAN   :
		case RCC_APB1_Periph_BKP   :
		case RCC_APB1_Periph_PWR   :
		case RCC_APB1_Periph_DAC   :
                // Valid peripheral, proceed with enabling or disabling
                bitMASK=1<<Peripheral;
                RCC->RCC_APB1RSTR|=bitMASK;
                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB1_WRONG_PERIPHERAL;
                break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : reset Peripheral on APB2 bus
*/
Rcc_tenuErrorStatus Rcc_enuReset_APB2_Peripheral(RCC_APB2Periph_TypeDef Peripheral)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    uint32 bitMASK=0;
    switch (Peripheral)
    {
		case AFIORST:
		case RCC_APB2_Periph_IOPA:
		case RCC_APB2_Periph_IOPB:
		case RCC_APB2_Periph_IOPC:
		case RCC_APB2_Periph_IOPD:
		case RCC_APB2_Periph_IOPE:
		case RCC_APB2_Periph_IOPF:
		case RCC_APB2_Periph_IOPG:
		case RCC_APB2_Periph_ADC1:
		case RCC_APB2_Periph_ADC2:
		case RCC_APB2_Periph_TIM1:
		case RCC_APB2_Periph_SPI1:
		case RCC_APB2_Periph_TIM8:
		case RCC_APB2_Periph_USART1:
		case RCC_APB2_Periph_ADC3:
		case RCC_APB2_Periph_TIM9:
		case RCC_APB2_Periph_TIM10:
		case RCC_APB2_Periph_TIM11:
                // Valid peripheral, proceed with enabling or disabling
                bitMASK=1<<Peripheral;
                RCC->RCC_APB2RSTR|=bitMASK;
                break;
            default:
                // Invalid peripheral
                Locerrorstatus=Rcc_enuWrongAPB2_WRONG_PERIPHERAL;
                break;
    }
    return Locerrorstatus;
}

/*
* @Brief   : chose the mco clock source
* @options :
* 		MCO_NO_CLOCK
*		MCO_CLK_SOURCE_HSI
*		MCO_CLK_SOURCE_HSE
*		MCO_CLK_SOURCE_PLL_DIV_2
*/
Rcc_tenuErrorStatus Rcc_enuMCO_CLOCK_slector(uint32 Source)
{
    Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
    switch(Source)
    {
        case MCO_NO_CLOCK:
          (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&MCO_NO_CLOCK);
          break;
        case MCO_CLK_SOURCE_SYSCLK:
        case MCO_CLK_SOURCE_HSI:
        case MCO_CLK_SOURCE_HSE:
        case MCO_CLK_SOURCE_PLL_DIV_2:
        // clear the  two bits respnsibol of slecting the clock source then config them to chose the desired source
        (RCC->RCC_CFGR)=((RCC->RCC_CFGR)&MCO_NO_CLOCK)|Source;
        break;
        default:
            // Invalid source
            Locerrorstatus=RCC_enuWrongMCOSourceError;
            break;
    }

    return Locerrorstatus;
}

/*
* @Brief   : chose the USB clock source
* @options :
* 		RCC_USB_SRC_PLL_DIVIDED
*		RCC_USB_SRC_PLL
*/
Rcc_tenuErrorStatus Rcc_enuCfg_USB_ClockSrc_Prescalers(RCC_USB_CLK_SRC_TypeDef Source)
{
  Rcc_tenuErrorStatus Locerrorstatus=Rcc_enuOk;
  switch(Source)
  {
    case RCC_USB_SRC_PLL_DIVIDED:
      CLR_BIT(RCC->RCC_CR,REGISTER_BIT_22);
      break;
    case RCC_USB_SRC_PLL:
      SET_BIT(RCC->RCC_CR,REGISTER_BIT_22);
      break;
    default:
      Locerrorstatus=RCC_enuWrongUSBSourceError;
      break;
  }
  return Locerrorstatus;
}
