
//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103C6_I2C_Driver.h"

//----------------------------------------------------------------
//Generic macros
//----------------------------------------------------------------
#define I2C1_Index 0
#define I2C2_Index 1

//----------------------------------------------------------------
//Generic Global variables
//----------------------------------------------------------------
I2C_Init_Typedef G_I2C_Config[2];

//----------------------------------------------------------------
//APIs Implementation by "MCAL I2C driver"
//----------------------------------------------------------------

void MCAL_I2C_Init(volatile I2C_typedef* I2Cx, I2C_Init_Typedef* I2C_Init_Struct)
{
	uint32_t PCLK1;
	uint16_t Tempreg, FREQ, result;
	//RCC Enable
	if(I2Cx == I2C1)
	{
		G_I2C_Config[I2C1_Index] = *I2C_Init_Struct;
		RCC_I2C1_Clock_Enable();
	}else
	{
		G_I2C_Config[I2C2_Index] = *I2C_Init_Struct;
		RCC_I2C2_Clock_Enable();
	}

	if(I2C_Init_Struct->I2C_Mode == I2C_Mode_I2C)
	{
		// -----------------Init timing-----------------

		//1-The peripheral input clock must be programmed in the I2C_CR2 register Bits 5:0 FREQ[5:0]: Peripheral clock frequency in order to generate correct timings
		//copy I2C_CR2 value to Tempreg
		Tempreg = I2Cx->CR2;

		//clear Tempreg Bits 5:0 FREQ[5:0]: Peripheral clock frequency
		Tempreg &= ~(I2C_CR2_FREQ_Msk);

		//get PCLK1 by RCC driver and calculate FREQ used in I2Cx_CR2
		//PCLK is in MHz need to be mapped to FREQ value (conclusion from SPECS: FREQ = real frequency value in MHZ/1000000)
		PCLK1 = MCAL_RCC_Get_PCLK1_FREQ();
		FREQ =  (uint16_t)(PCLK1/1000000);

		//write the FREQ value to the Tempreg
		Tempreg |= FREQ;

		//write the Tempreg to the I2C_CR2
		I2Cx->CR2 = Tempreg;

		Tempreg = 0;

		//disable the selected I2C peripheral to configure time
		I2Cx->CR1 &= ~(I2C_CR1_PE);

		if(I2C_Init_Struct->I2C_SCLK_Speed == I2C_SCLK_Speed_SM_50K || I2C_Init_Struct->I2C_SCLK_Speed == I2C_SCLK_Speed_SM_100K)
		{
			//2- Configure the clock control registers

			//Bit 15 F/S: I2C master mode selection
			//0: Sm mode I2C (Tempreg = 0 so it's alreqdy setted)
			//1: Fm mode I2C

			//standard mode speed
			//T_high_I2C_CLK = CCR * T_PCLK1
			//T_Low_I2C_CLK = CCR * T_PCLK1
			//T_high_I2C_CLK = T_Low_I2C_CLK = T_I2C_CLK_/2
			//T_I2C_CLK_/2 = CCR * T_PCLK1
			//CCR = T(I2C_CLK)/(2 * T_PCLK1)
			//CCR = F_PCLK1/(2 * F_I2C_CLK)
			result = (uint16_t)(PCLK1/(I2C_Init_Struct->I2C_SCLK_Speed << 1));
			Tempreg |= (0xFFF & result);

			//write Tempreg to I2Cx_CRR
			//don't consider any thing for Bit 14 DUTY: Fm mode duty cycle (FM only)
			I2Cx->CCR = Tempreg;

			//3-Configure the rise time register
			//For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			//If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//therefore the TRISE[5:0] bits must be programmed with 09h.
			//(1000 ns / 125 ns = 8 + 1)
			I2Cx->TRISE = FREQ + 1;
		}else
		{
			//fast mode is not supported
		}

		// -----------------timing is initialized (waiting to enable the I2C peripheral)-----------------

		//4-Program the I2C_CR1 register to enable the peripheral and set remaining configurations
		Tempreg = I2Cx->CR1;
		Tempreg |= (I2C_Init_Struct->General_Call_Address_Detection | I2C_Init_Struct->I2C_ACK_Control | I2C_Init_Struct->I2C_Mode | I2C_Init_Struct->I2C_Stretch_Mode);
		I2Cx->CR1 = Tempreg;

		// -----------------I2Cx OAR1 & I2Cx OAR2 configuration-----------------
		Tempreg = 0;
		if(I2C_Init_Struct->I2C_Slave_Address.Enable_Dual_ADD)
		{
			Tempreg = I2C_OAR2_ENDUAL;
			Tempreg |= I2C_Init_Struct->I2C_Slave_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = Tempreg;
		}
		Tempreg = 0;
		Tempreg |= I2C_Init_Struct->I2C_Slave_Address.Primary_Slave_Address << 1;
		Tempreg |= I2C_Init_Struct->I2C_Slave_Address.I2C_Addressing_Slave_Mode;
		I2Cx->OAR1 = Tempreg;
	}else
	{
		//SMBUS is not supported
	}

	//interrupt mode (Slave mode) --> check callback pionter != NULL
	if(I2C_Init_Struct->P_Slave_Event_CallBack != NULL) //enable slave IRQ state mode
	{
		//Enable IRQ
		I2Cx->CR2 |= (I2C_CR2_ITERREN);
		I2Cx->CR2 |= (I2C_CR2_ITEVTEN);
		I2Cx->CR2 |= (I2C_CR2_ITBUFEN);

		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;

		}else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}
		I2Cx->SR1 = 0;
	}

	//Enable the selected I2C peripheral
	I2Cx->CR1 |= I2C_CR1_PE;
}


void MCAL_I2C_Dinit(volatile I2C_typedef* I2Cx)
{

}


void MCAL_I2C_GPIO_Set_Pins(volatile I2C_typedef* I2Cx)
{
	GPIO_Pin_Configuration_t Pin_Config;

	if(I2Cx == I2C1)
	{
		//PB6: I2C1_SCL
		Pin_Config.GPIO_Pin_Number = GPIO_Pin6;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_OD;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);

		//PB7: I2C1_SDA
		Pin_Config.GPIO_Pin_Number = GPIO_Pin7;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_OD;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);

	}else if(I2Cx == I2C2)
	{
		//PB10: I2C2_SCL
		Pin_Config.GPIO_Pin_Number = GPIO_Pin10;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_OD;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);

		//PB11: I2C2_SDA
		Pin_Config.GPIO_Pin_Number = GPIO_Pin11;
		Pin_Config.GPIO_Pin_Mode = GPIO_Mode_AF_OD;
		Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pin_Config);
	}
}

void MCAL_I2C_Master_TX(volatile I2C_typedef* I2Cx, uint16_t Device_Add, uint8_t *Data, uint32_t Data_Length, Stop_Condition Stop, Repeated_Start Start)
{
	uint32_t i;	//counter

	//to do (polling mechanism with timeout)
	//support timeout (configure timer working for specific duration then rise interrupt)
	//timer interrupt() {Flag = 0}
	//so any code exist in while will be (check flag && any polling conditions)

	//1-Generate start condition
	I2C_Generate_Start(I2Cx, Enable_state, Start);

	//2-wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_Get_Status(I2Cx, EV5));

	//3-send address
	I2C_Send_Address(I2Cx, Device_Add, I2C_Direction_TX);

	//4-wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!I2C_Get_Status(I2Cx, EV6));

	//5-check flags: TRA, Busy, MSL, TXE
	while(!I2C_Get_Status(I2Cx, Master_Byte_Transmitting));

	//6-send data and wait for EV8
	//EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	for(i=0; i < Data_Length;++i)
	{
		I2Cx->DR = Data[i];
		while(!I2C_Get_Status(I2Cx, EV8));
	}

	//optional
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition

	//7-send stop condition
	if(Stop == with_stop)
		I2C_Generate_Stop(I2Cx, Enable_state);
}

void MCAL_I2C_Master_RX(volatile I2C_typedef* I2Cx, uint16_t Device_Add, uint8_t *Data, uint32_t Data_Length, Stop_Condition Stop, Repeated_Start Start)
{
	uint32_t index,i;
	index = I2Cx == I2C1 ? I2C1_Index : I2C2_Index;

	//1-Generate start condition
	I2C_Generate_Start(I2Cx, Enable_state, Start);

	//2-wait for EV5
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while(!I2C_Get_Status(I2Cx, EV5));

	//3-send address
	I2C_Send_Address(I2Cx, Device_Add, I2C_Direction_RX);

	//4-wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while(!I2C_Get_Status(I2Cx, EV6));

	I2C_Acknowledge_Config(I2Cx, Enable_state);


	if(Data_Length)
	{
		for(i = 0; i < Data_Length; ++i)
		{
			//5-wait for EV7
			//EV7: RXNE=1, cleared by reading DR register
			while(!I2C_Get_Status(I2Cx, EV7));
			//read data from DR and store it to data buffer
			Data[i] = I2Cx->DR;

		}
		//6-NACK
		I2C_Acknowledge_Config(I2Cx, Disable_state);
	}

	if(Stop == with_stop){
		//7-send stop condition
		I2C_Generate_Stop(I2Cx, Enable_state);
	}

	//re-enable ACK
	if(G_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_Acknowledge_Config(I2Cx, Enable_state);
	}

}

void MCAL_I2C_Slave_TX(volatile I2C_typedef* I2Cx, uint8_t Data)
{
	I2Cx->DR = Data;
}

uint8_t MCAL_I2C_Slave_RX(volatile I2C_typedef* I2Cx)
{
	return (uint8_t)I2Cx->DR;
}


//----------------------------------------------------------------
//Generic APIs
//----------------------------------------------------------------

void I2C_Generate_Start(volatile I2C_typedef* I2Cx, Functional_State New_State,  Repeated_Start Start)
{
	if(Start != repeated_start)
	{
		//check if the Bus is idle
		while(I2C_Get_Status(I2Cx, I2C_Flag_Busy));
	}

	if(New_State == Enable_state)
	{
		//generate a start condition
		I2Cx->CR1 |= I2C_CR1_START;
	}else
	{
		I2Cx->CR1 &= ~I2C_CR1_START;
	}


}


Flag_Status I2C_Get_Status(volatile I2C_typedef* I2Cx, Status Flag)
{
	volatile uint32_t Temp;
	Flag_Status	Bit_Status = Reset;

	switch(Flag)
	{
	case I2C_Flag_Busy:
	{
		//Bit 1 BUSY: Bus busy
		//0: No communication on the bus
		//1: Communication ongoing on the bus
		//– Set by hardware on detection of SDA or SCL low
		//– cleared by hardware on detection of a Stop condition.
		//It indicates a communication in progress on the bus. This information is still updated when
		//the interface is disabled (PE=0)
		if(I2Cx->SR2 & I2C_SR2_BUSY)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		break;
	}
	case EV5:
	{
		//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//Bit 0 SB: Start bit (Master mode)
		//0: No Start condition
		//1: Start condition generated.
		//– Set when a Start condition generated.
		//– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//hardware when PE=0
		if(I2Cx->SR1 & I2C_SR1_SB)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		break;
	}

	case EV6:
	{
		//Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.
		//Address matched (Slave)
		//0: Address mismatched or not received.
		//1: Received address matched.
		//hardware when PE=0
		if(I2Cx->SR1 & I2C_SR1_ADDR)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		//to clear ADDR field: read SR1 register followed reading SR2
		Temp = I2Cx->SR1;
		break;
	}
	case Master_Byte_Transmitting:
	{
		//check flags: TRA, Busy, MSL, TXE
		Temp = (I2Cx->SR2 << 16) | (I2Cx->SR1 & 0xFFFF);
		if( (Temp & Master_Byte_Transmitting) == Master_Byte_Transmitting)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		break;
	}

	case EV8_1:
	case EV8:
	{
		//		Bit 7 TxE: Data register empty (transmitters)
		//		0: Data register not empty
		//		1: Data register empty
		//		– Set when DR is empty in transmission. TxE is not set during address phase.
		//		– Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0
		if(I2Cx->SR1 & I2C_SR1_TXE)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		break;
	}

	case EV7:
	{
		//Bit 6 RxNE: Data register not empty (receivers)
		//0: Data register empty
		//1: Data register not empty
		//– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//– Cleared by software reading or writing the DR register or by hardware when PE=0.
		if(I2Cx->SR1 & I2C_SR1_RXNE)
			Bit_Status = Set;
		else
			Bit_Status = Reset;
		break;
	}

	}
	return Bit_Status;
}

//supported only 7bit mode
void I2C_Send_Address(volatile I2C_typedef* I2Cx, uint16_t Address, I2C_Direction Direction )
{
	Address = Address << 1;

	if(Direction == I2C_Direction_RX)
	{
		Address |= 1<<0;
	}else
	{
		Address &= ~(1 << 0);
	}

	//send the address
	I2Cx->DR = Address;
}

void I2C_Generate_Stop(volatile I2C_typedef* I2Cx, Functional_State New_State)
{
	if(New_State == Enable_state)
	{
		//generate a stop condition
		I2Cx->CR1 |= I2C_CR1_STOP;
	}else
	{
		//Disable the stop condition
		I2Cx->CR1 &= ~I2C_CR1_STOP;
	}
}

void I2C_Acknowledge_Config(volatile I2C_typedef* I2Cx, Functional_State New_State)
{
	if(New_State == Enable_state)
	{
		I2Cx->CR1 |= I2C_CR1_ACK;
	}else
	{
		I2Cx->CR1 &= ~I2C_CR1_ACK;
	}

}





//----------------------------------------------------------------
//interrupt service routine (to do)
//----------------------------------------------------------------

//we are focus on the interrupt for the I2C in the slave mode but the same can beb made for the I2C in the master mode

//the same interrupt can occur for different reasons so when an interrupt happens we need to define its reason by checking status registers flags to determine the next step

//1- I2Cx_EV_IRQHandler
//-check the interrupt comes from a master or a slave
//-determines the reason for event interrupt by checking related flags
//-call I2C_Send_Slave_State if the interrupt comes from I2C slave and passe the slave state

//2-I2C_Send_Slave_State
//-do a switch condition on the state
//-in each case of the states make sure from some other flags
//-call the ISR_callBack function and pass the state to it (now the APP layer is informed with the state of the I2C and its interrupt)

//3-ISR_callBack
//-take decision by sending/receiving data through MCAL_I2C_Slave_TX/RX  or other decision depending on the state


void I2C1_EV_IRQHandler()       //I2C1 event interrupt
{
}
void I2C1_ER_IRQHandler()       //I2C1 error interrupt
{
}
void I2C2_EV_IRQHandler()       //I2C2 event interrupt
{
}
void I2C2_ER_IRQHandler()       //I2C2 error interrupt
{
}
//belongs to Generic APIs
void I2C_Send_Slave_State(volatile I2C_typedef* I2Cx, Slave_State state)
{
}




