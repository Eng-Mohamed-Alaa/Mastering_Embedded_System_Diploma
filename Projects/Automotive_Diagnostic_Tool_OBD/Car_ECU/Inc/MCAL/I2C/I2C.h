/**
 ******************************************************************************
 * @file           : i2c.h
 * @Author:        : Ahmed Radwan
 * @Created on:    : Nov 25, 2023
 ******************************************************************************
 */

#ifndef MCAL_I2C_I2C_H_
#define MCAL_I2C_I2C_H_



/************************************* include section ****************************************/
#include"../../../SERVICES/Standard_Data_Types.h"
#include"../../../SERVICES/Bit_Wise_Operations.h"
#include"../RCC/RCC.h"
#include"../GPIO/GPIO.h"
#include"I2C_PRIV.h"

/************************************* include section end ************************************/

/***************************************** macros section *************************************/


#define I2C      ((I2C_TypeDef*)(I2C_BASE_ADREES))



#define I2C_SWRST_Pos     (15U)
#define I2C_ALERT_Pos     (13U)
#define I2C_PEC_Pos       (12U)
#define I2C_POS_Pos       (11U)
#define I2C_ACK_Pos       (10U)
#define I2C_STOP_Pos      (9U)
#define I2C_START_Pos     (8U)
#define I2C_NOSTRETCH_Pos (7U)
#define I2C_ENGC_Pos      (6U)
#define I2C_ENPEC_Pos     (5U)
#define I2C_ENARP_Pos     (4U)
#define I2C_SMBTYPE_Pos   (3U)
#define I2C_SMBUS_Pos     (1U)
#define I2C_PE_Pos        (0U)

#define I2C_SWRST_Reset     CLR_BIT(I2C->I2C_CR1, I2C_SWRST_Pos)
#define I2C_SWRST_Set       SET_BIT(I2C->I2C_CR1, I2C_SWRST_Pos)

#define I2C_ALERT_High      SET_BIT(I2C->I2C_CR1, I2C_ALERT_Pos)
#define I2C_ALERT_Low       CLR_BIT(I2C->I2C_CR1, I2C_ALERT_Pos)

#define I2C_PEC_Disabled    CLR_BIT(I2C->I2C_CR1, I2C_PEC_Pos)
#define I2C_PEC_Enabled     SET_BIT(I2C->I2C_CR1, I2C_PEC_Pos)

#define I2C_POS_Current     CLR_BIT(I2C->I2C_CR1, I2C_POS_Pos)
#define I2C_POS_Next        SET_BIT(I2C->I2C_CR1, I2C_POS_Pos)

#define I2C_ACK_Disable     CLR_BIT(I2C->I2C_CR1, I2C_ACK_Pos)
#define I2C_ACK_Enable      SET_BIT(I2C->I2C_CR1, I2C_ACK_Pos)

#define I2C_STOP_NoGen      CLR_BIT(I2C->I2C_CR1, I2C_STOP_Pos)
#define I2C_STOP_Generate   SET_BIT(I2C->I2C_CR1, I2C_STOP_Pos)

#define I2C_START_NoGen     CLR_BIT(I2C->I2C_CR1, I2C_START_Pos)
#define I2C_START_Generate  SET_BIT(I2C->I2C_CR1, I2C_START_Pos)

#define I2C_CLOCK_STRETCH_En    CLR_BIT(I2C->I2C_CR1, I2C_NOSTRETCH_Pos)
#define I2C_CLOCK_STRETCH_Dis   SET_BIT(I2C->I2C_CR1, I2C_NOSTRETCH_Pos)

#define I2C_GENERAL_CALL_Disable         CLR_BIT(I2C->I2C_CR1, I2C_ENGC_Pos)
#define I2C_GENERAL_CALL_Enable     SET_BIT(I2C->I2C_CR1, I2C_ENGC_Pos)

#define I2C_ENPEC_Disable   CLR_BIT(I2C->I2C_CR1, I2C_ENPEC_Pos)
#define I2C_ENPEC_Enable    SET_BIT(I2C->I2C_CR1, I2C_ENPEC_Pos)

#define I2C_ENARP_Disable   CLR_BIT(I2C->I2C_CR1, I2C_ENARP_Pos)
#define I2C_ENARP_Enable    SET_BIT(I2C->I2C_CR1, I2C_ENARP_Pos)

#define I2C_SMBTYPE_Device  CLR_BIT(I2C->I2C_CR1, I2C_SMBTYPE_Pos)
#define I2C_SMBTYPE_Host    SET_BIT(I2C->I2C_CR1,I2C_SMBTYPE_Pos)

#define I2C_SMBUS_I2C       CLR_BIT(I2C->I2C_CR1,I2C_SMBUS_Pos)
#define I2C_SMBUS_SMBus     SET_BIT(I2C->I2C_CR1,I2C_SMBUS_Pos)

#define I2C_PE_Disable      CLR_BIT(I2C->I2C_CR1,I2C_PE_Pos)
#define I2C_PE_Enable       SET_BIT(I2C->I2C_CR1,I2C_PE_Pos)

//////////////////////////////////////////////////

#define I2C_LAST_Pos      (12U)
#define I2C_DMAEN_Pos     (11U)
#define I2C_ITBUFEN_Pos   (10U)
#define I2C_ITEVTEN_Pos   (9U)
#define I2C_ITERREN_Pos   (8U)
#define I2C_FREQ_MASK     (0xFFE0)


#define I2C_LAST_Last     	SET_BIT(I2C->I2C_CR2, I2C_LAST_Pos)
#define I2C_LAST_NotLast  	CLR_BIT(I2C->I2C_CR2, I2C_LAST_Pos)

#define I2C_DMAEN_Enable  	SET_BIT(I2C->I2C_CR2, I2C_DMAEN_Pos)
#define I2C_DMAEN_Disable 	CLR_BIT(I2C->I2C_CR2, I2C_DMAEN_Pos)

#define I2C_ITBUFEN_Enable  	SET_BIT(I2C->I2C_CR2, I2C_ITBUFEN_Pos)
#define I2C_ITBUFEN_Disable 	CLR_BIT(I2C->I2C_CR2, I2C_ITBUFEN_Pos)

#define I2C_ITEVTEN_Enable  	SET_BIT(I2C->I2C_CR2, I2C_ITEVTEN_Pos)
#define I2C_ITEVTEN_Disable	CLR_BIT(I2C->I2C_CR2, I2C_ITEVTEN_Pos)

#define I2C_ITERREN_Enable  	SET_BIT(I2C->I2C_CR2, I2C_ITERREN_Pos)
#define I2C_ITERREN_Disable 	CLR_BIT(I2C->I2C_CR2, I2C_ITERREN_Pos)

#define I2C_ASSIGN_FREQ(freq) 	(I2C->I2C_CR2=(((I2C->I2C_CR2)&I2C_FREQ_MASK)|freq))

#define ADRESS_MODE_7_BIT_SET()     do{CLR_BIT(I2C->I2C_OAR1, 15);\
				       SET_BIT(I2C->I2C_OAR1, 14);\
					      }while(0);
#define ADRESS_MODE_11_BIT_SET      do{SET_BIT(I2C->I2C_OAR1, 15);\
				       SET_BIT(I2C->I2C_OAR1, 14);\
					      }while(0);


#define I2C_FAST_MODE_SLECT 		 SET_BIT(I2C->I2C_CCR,15)
#define I2C_STANDARD_MODE_SLECT 	 CLR_BIT(I2C->I2C_CCR,15)

#define I2C_SET_DUTY_16_9 		 SET_BIT(I2C->I2C_CCR,14)
#define I2C_SET_DUTY_2 	                 CLR_BIT(I2C->I2C_CCR,14)

#define I2C_GET_START_STATUS 	         GET_BIT(I2C->I2C_SR1,0)

#define I2C_GET_ADRESS_STATUS 	         GET_BIT(I2C->I2C_SR1,1)

#define I2C_GET_BYTE_TRANS_STATUS 	 GET_BIT(I2C->I2C_SR1,2)

#define I2C_GET_10BIT_ADRESS_STATUS 	 GET_BIT(I2C->I2C_SR1,3)

#define I2C_GET_STOP_STATUS 	         GET_BIT(I2C->I2C_SR1,4)

#define I2C_GET_RX_DATA_REG_STATUS 	         GET_BIT(I2C->I2C_SR1,6)

#define I2C_GET_TX_DATA_REG_STATUS 	         GET_BIT(I2C->I2C_SR1,7)

#define I2C_GET_MASTER_SLAVE_STATUS 	         GET_BIT(I2C->I2C_SR2,0)
#define I2C_GET_BUS_STATUS 	                 GET_BIT(I2C->I2C_SR2,1)
#define I2C_GET_TRANS_RECIV_STATUS 	         GET_BIT(I2C->I2C_SR2,2)

#define CLEAR_AF_FLAG                          (I2C->I2C_SR1=0xFFFFFBFF)







/*********************************** macros section end ***************************************/


/*********************************** user defined data types section **************************/
typedef struct
{
  volatile uint32 I2C_CR1;
  volatile uint32 I2C_CR2;
  volatile uint32 I2C_OAR1;
  volatile uint32 I2C_OAR2;
  volatile uint32 I2C_DR;
  volatile uint32 I2C_SR1;
  volatile uint32 I2C_SR2;
  volatile uint32 I2C_CCR;
  volatile uint32 I2C_TRISE;
} I2C_TypeDef;

typedef enum
{
  HAL_I2C_STATE_RESET             = 0x00U,   /*!< Peripheral is not yet Initialized         */
  HAL_I2C_STATE_READY             = 0x20U,   /*!< Peripheral Initialized and ready for use  */
  HAL_I2C_STATE_BUSY              = 0x24U,   /*!< An internal process is ongoing            */
  HAL_I2C_STATE_BUSY_TX           = 0x21U,   /*!< Data Transmission process is ongoing      */
  HAL_I2C_STATE_BUSY_RX           = 0x22U,   /*!< Data Reception process is ongoing         */
  HAL_I2C_STATE_LISTEN            = 0x28U,   /*!< Address Listen Mode is ongoing            */
  HAL_I2C_STATE_BUSY_TX_LISTEN    = 0x29U,   /*!< Address Listen Mode and Data Transmission
                                                 process is ongoing                         */
  HAL_I2C_STATE_BUSY_RX_LISTEN    = 0x2AU,   /*!< Address Listen Mode and Data Reception
                                                 process is ongoing                         */
  HAL_I2C_STATE_ABORT             = 0x60U,   /*!< Abort user request ongoing                */
  HAL_I2C_STATE_TIMEOUT           = 0xA0U,   /*!< Timeout state                             */
  HAL_I2C_STATE_ERROR             = 0xE0U    /*!< Error                                     */

} HAL_I2C_StateTypeDef;

typedef enum
{
  I2C_STANDARD_MODE,
  I2C_FAST_MODE
}I2C_mode_CFG_t;

typedef enum
{
  I2C_ADDRESSINGMODE_7BIT,
  I2C_ADDRESSINGMODE_10BIT
}I2C_ADRESS_CFG_t;
typedef enum
{
  I2C_GENERALCALL_DISABLE,
  I2C_GENERALCALL_ENABLE
}I2C_GENERAL_CALL_CFG_t;
typedef enum
{
  I2C_CLOCK_STRETCH_DISABLE,
  I2C_CLOCK_STRETCH_ENABLE
}I2C_CLOCK_STRETCH_CFG_t;
typedef enum
{
  I2C_DUTYCYCLE_2,
  I2C_DUTYCYCLE_16_9
}I2C_enuDUTYCYCLE_CFG_t;
typedef enum
{
  I2C_enuINTERRUPT_DISABLE,
  I2C_enuINTERRUPT_ENABLE
} I2C_enuINTERRUPT_CFG_t;




typedef struct
{
  uint32 ClockSpeed;     		  /*!< Specifies the clock frequency.
					  This parameter must be set to a value lower than 400kHz */

  uint32 AHB_BUS_SPEED;

  I2C_enuDUTYCYCLE_CFG_t DutyCycle;        		/*!< Specifies the I2C fast mode duty cycle.*/

  I2C_mode_CFG_t I2C_MODE;

  uint32 OwnAddress1;      		/* !< Specifies the first device own address.
					 This parameter can be a 7-bit or 10-bit address. */

  I2C_ADRESS_CFG_t AddressingMode;   	/*!< Specifies if 7-bit or 10-bit addressing mode is selected.*/


  I2C_GENERAL_CALL_CFG_t GeneralCallMode;  	/*!< Specifies if general call mode is selected.*/

  I2C_CLOCK_STRETCH_CFG_t StretchMode;     	 /*!< Specifies if nostretch mode is selected.*/

  I2C_enuINTERRUPT_CFG_t Event_interrupt;

  I2C_enuINTERRUPT_CFG_t Error_interrupt;

} I2C_Init_t;

typedef enum
{
  I2C_enuOK,
  I2C_enuERROR
} I2C_tenuErrorStatus;



/*********************************** user defined data types section end **************************/



/****************************** function prototypes section****************************************/

I2C_tenuErrorStatus I2C_INIT(I2C_Init_t*Local_ptrI2C);
I2C_tenuErrorStatus I2C_master_tx_with_ACK_no_byte(uint8 adress,uint8* data,uint8 size);
I2C_tenuErrorStatus I2C_master_rx_with_ACK_no_byte(uint8 adress,uint8* data,uint8 size);
void I2C_SEND_ADRESS_WRITE(uint8 adress);
void I2C_SEND_ADRESS_READ_WITH_ACK(uint8 adress);
void I2C_SEND_ADRESS_READ_NO_ACK(uint8 ADRESS);
void I2C_WRITE_Byte(uint8 data);
void I2C_READ_Byte(uint8* data);
void I2C_send_start_cond(void);
void I2C_send_stop(void);

/****************************** function prototypes section end************************************/

#endif /* MCAL_I2C_I2C_H_ */
