/**
 ******************************************************************************
 * @file           : i2c.c
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 25, 2023
 ******************************************************************************
 */

#include"../../../Inc/MCAL/I2C/I2C.h"


  static void I2C_set_clock(I2C_Init_t*Local_ptrI2C);
  static void I2C_set_adress(I2C_Init_t*Local_ptrI2C);
  static void I2C_clock_stretch(I2C_Init_t*Local_ptrI2C);
  static void I2C_interrupt_cfg(I2C_Init_t*Local_ptrI2C);
  static void I2C_general_call_cfg(I2C_Init_t*Local_ptrI2C);
  static void clear_addr_flag(void);
  static void clear_stop_flag(void);
  static void clear_AF_flag(void);




  I2C_tenuErrorStatus I2C_INIT(I2C_Init_t*Local_ptrI2C)
  {
    I2C_tenuErrorStatus Locerrorstatus=I2C_enuOK;
    if(NULL==Local_ptrI2C)
      {
        Locerrorstatus=I2C_enuERROR;
      }
    else
      {

        //pins cfg
        GPIO_Port_Enable_clock(GPIO_PORT_B);
        GPIO_PIN_INIT(GPIO_PIN_6,GPIO_PORT_B,AF_output_Open_drain,GPIO_max_speed_50_MHz,FLOATING);
        GPIO_PIN_INIT(GPIO_PIN_7,GPIO_PORT_B,AF_output_Open_drain,GPIO_max_speed_50_MHz,FLOATING);

        //enable peripheral clock
        Rcc_enuControl_APB1_Peripheral(RCC_APB1_Periph_I2C1, RCC_Periph_ENABLE);

        //reset peripheral
        I2C_SWRST_Set;
        I2C_SWRST_Reset;

        //clock cfg
        I2C_ASSIGN_FREQ(Local_ptrI2C->AHB_BUS_SPEED);
        I2C_PE_Disable;
        I2C_set_clock(Local_ptrI2C);
        I2C_clock_stretch(Local_ptrI2C);




        I2C_general_call_cfg(Local_ptrI2C);
        I2C_set_adress(Local_ptrI2C);
        I2C_interrupt_cfg(Local_ptrI2C);

        I2C_PE_Enable;
      }
    return Locerrorstatus ;
  }


I2C_tenuErrorStatus I2C_master_tx_with_ACK_no_byte(uint8 adress,uint8* data,uint8 size)
{
  I2C_tenuErrorStatus Locerrorstatus=I2C_enuOK;

  Locerrorstatus=I2C_enuOK;
  I2C_POS_Current;
  //check if the bus is Ideal
  I2C_send_start_cond();
  I2C_SEND_ADRESS_WRITE(adress);
  //I2C_ACK_Enable;
  if(size)
    {
      for(uint8 counter=0;counter<size;counter++)
	{
	  I2C_WRITE_Byte(*(data+counter));
	}
    }
  else
    {
      Locerrorstatus=I2C_enuERROR;
    }

  //while(!(I2C_GET_TX_DATA_REG_STATUS&I2C_GET_MASTER_SLAVE_STATUS&I2C_GET_BUS_STATUS&I2C_GET_TRANS_RECIV_STATUS));

  I2C_send_stop();

  return Locerrorstatus ;

}

I2C_tenuErrorStatus I2C_master_rx_with_ACK_no_byte(uint8 adress,uint8* data,uint8 size)
{
  I2C_tenuErrorStatus Locerrorstatus=I2C_enuOK;

    Locerrorstatus=I2C_enuOK;
    I2C_POS_Current;
    //check if the bus is Ideal
    I2C_send_start_cond();

    I2C_SEND_ADRESS_READ_WITH_ACK(adress);
    if(size)
      {
	uint8 counter=0;
	while(size)
	  {
	      if(size==1)
		{
		  I2C_ACK_Disable;
		}
	      //wait until recive done
	      while(!I2C_GET_RX_DATA_REG_STATUS);
	      *(data+counter)=I2C->I2C_DR;
	      counter++;
	      size--;
	  }

      }
    else
     {
	Locerrorstatus=I2C_enuERROR;
      }
    // end communication with the stop bit
    I2C_STOP_Generate;
    //re enable ack
    I2C_ACK_Enable;
    return Locerrorstatus;

}
void I2C_SEND_ADRESS_WRITE(uint8 adress)
{
  I2C_ACK_Enable;
  adress=adress<<1;
  I2C->I2C_DR=adress;
  //wait until  ADDR
  while ( ! I2C_GET_ADRESS_STATUS );
  clear_addr_flag();

}
void I2C_SEND_ADRESS_READ_WITH_ACK(uint8 adress)
{

  adress=(adress<<1)|1;
  I2C->I2C_DR=adress;
  //wait until  ADDR
  while ( ! I2C_GET_ADRESS_STATUS );
  clear_addr_flag();
  //I2C_ACK_Enable;
}
void I2C_SEND_ADRESS_READ_NO_ACK(uint8 adress)
{
  I2C_ACK_Disable;
  adress=(adress<<1)|1;
  I2C->I2C_DR=adress;
  //wait until  ADDR
  while ( ! I2C_GET_ADRESS_STATUS );
  clear_addr_flag();
}
void I2C_WRITE_Byte(uint8 data)
{
  while(!(I2C_GET_TX_DATA_REG_STATUS));
  I2C->I2C_DR=data;

}
void I2C_READ_Byte(uint8* data)
{
  while(!(I2C_GET_RX_DATA_REG_STATUS));
  *data=I2C->I2C_DR;

}
void I2C_send_start_cond(void)
{
  while(I2C_GET_BUS_STATUS);
  I2C_START_Generate;
  //wait until  SB
  while( ! I2C_GET_START_STATUS );
}
void I2C_send_stop(void)
{
  // wait until BTF
  while ( ! I2C_GET_BYTE_TRANS_STATUS );
  I2C_STOP_Generate;
}
static void I2C_set_clock(I2C_Init_t*Local_ptrI2C)
{

  I2C->I2C_CCR |= ( Local_ptrI2C->AHB_BUS_SPEED * 1000000) / (Local_ptrI2C->ClockSpeed << 1);
  I2C->I2C_TRISE=0x09;
  if(Local_ptrI2C->I2C_MODE==I2C_STANDARD_MODE)
    {
      I2C_STANDARD_MODE_SLECT;
    }
  else
    {
      I2C_FAST_MODE_SLECT;
    }

  if(Local_ptrI2C->DutyCycle==I2C_DUTYCYCLE_2)
    {
      I2C_SET_DUTY_2;
    }
  else
    {
      I2C_SET_DUTY_16_9;
    }

}
static void I2C_set_adress(I2C_Init_t*Local_ptrI2C)

{

  if(I2C_ADDRESSINGMODE_7BIT==Local_ptrI2C->AddressingMode)
    {
      I2C->I2C_OAR1=(Local_ptrI2C->OwnAddress1);
      ADRESS_MODE_7_BIT_SET();
    }
  else
    {

      I2C->I2C_OAR1=Local_ptrI2C->OwnAddress1;
      ADRESS_MODE_11_BIT_SET;
    }

}
static void I2C_clock_stretch(I2C_Init_t*Local_ptrI2C)
{
  if(I2C_CLOCK_STRETCH_DISABLE==Local_ptrI2C->StretchMode)
    {
      I2C_CLOCK_STRETCH_Dis;

    }
  else
    {
      I2C_CLOCK_STRETCH_En;
    }
}
static void I2C_interrupt_cfg(I2C_Init_t*Local_ptrI2C)
{
  if(I2C_enuINTERRUPT_DISABLE==Local_ptrI2C->Error_interrupt)
    {
      I2C_ITERREN_Disable;
    }
  else
    {
      I2C_ITERREN_Enable;
    }
  if(I2C_enuINTERRUPT_DISABLE==Local_ptrI2C->Event_interrupt)
    {
      I2C_ITEVTEN_Disable;
    }
  else
    {
      I2C_ITEVTEN_Enable;
    }
}
static void I2C_general_call_cfg(I2C_Init_t*Local_ptrI2C)
{
  if(I2C_GENERALCALL_ENABLE==Local_ptrI2C->GeneralCallMode)
    {
      I2C_GENERAL_CALL_Enable;
    }
  else
    {
      I2C_GENERAL_CALL_Disable;
    }
}

static void clear_addr_flag(void)
{
  uint16 temp;

  temp = I2C->I2C_SR1;
  temp = I2C->I2C_SR2;

}

static void clear_stop_flag(void)
{
  uint16 temp;

  temp = I2C->I2C_SR1;
  temp = I2C->I2C_SR2;

SET_BIT(I2C->I2C_SR2, 4);
}
static void clear_AF_flag(void)
{
  /********************/
  I2C_STOP_Generate;
  CLEAR_AF_FLAG;

}
