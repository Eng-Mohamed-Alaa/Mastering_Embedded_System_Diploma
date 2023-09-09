
//----------------------------------------------------------------
//includes
//----------------------------------------------------------------

#include "STM32F103C6_SPI_Driver.h"


//----------------------------------------------------------------
//Generic macros
//----------------------------------------------------------------

#define SPI1_Index		0
#define SPI2_Index		1

#define SPI_SR_TXE		(uint32_t)(0x2)
#define SPI_SR_RXNE		(uint32_t)(0x1)


//----------------------------------------------------------------
//Generic Global variables
//----------------------------------------------------------------
SPI_Config_t G_SPI_CFG[2];

//----------------------------------------------------------------
//SPI driver static functions
//----------------------------------------------------------------


//----------------------------------------------------------------
//APIs Implementation by "MCAL SPI driver"
//----------------------------------------------------------------

void MCAL_SPI_Init(volatile SPI_typedef* SPIx, SPI_Config_t* SPI_Config)
{
	//Safety for registers
	uint16_t Temp_reg_CR1=0;
	uint16_t Temp_reg_CR2=0;

	//Copy the configuration address and enable SPI clock
	if(SPIx == SPI1)
	{
		G_SPI_CFG[SPI1_Index] = *SPI_Config;
		RCC_SPI1_Clock_Enable();
	}else if(SPIx == SPI2)
	{
		G_SPI_CFG[SPI2_Index] = *SPI_Config;
		RCC_SPI2_Clock_Enable();
	}

	//enable the SPI module
	Temp_reg_CR1 = (1U << 6); //SPIx.CR1 Bit 6 SPE: SPI enable

	//Master or slave
	Temp_reg_CR1 |= SPI_Config->Device_Mode;

	//communication mode
	Temp_reg_CR1 |= SPI_Config->Communication_Mode;

	//Frame_Format
	Temp_reg_CR1 |= SPI_Config->Frame_Format;

	//Data_Size
	Temp_reg_CR1 |= SPI_Config->Data_Size;

	//CLK_Polarity
	Temp_reg_CR1 |= SPI_Config->CLK_Polarity;

	//CLK_Phase
	Temp_reg_CR1 |= SPI_Config->CLK_Phase;

	//NSS
	if(SPI_Config->NSS == SPI_NSS_Hardware_Master_SS_Output_Enable)
	{
		Temp_reg_CR2 |= SPI_Config->NSS;
	}else if(SPI_Config->NSS == SPI_NSS_Hardware_Master_SS_Output_Disable)
	{
		Temp_reg_CR2 &= SPI_Config->NSS;
	}else
	{
		Temp_reg_CR1 |= SPI_Config->NSS;
	}

	//SPI_BAUDRATE_Prescaler
	Temp_reg_CR1 |= SPI_Config->SPI_BAUDRATE_Prescaler;

	//SPI_IRQ_Enable
	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_None)
	{
		Temp_reg_CR2 |= SPI_Config->IRQ_Enable;
		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;

		}else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->SPI_CR1 = Temp_reg_CR1;
	SPIx->SPI_CR2 = Temp_reg_CR2;

}


void MCAL_SPI_Dinit(volatile SPI_typedef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();

	}else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}

}


void MCAL_SPI_GPIO_Set_Pins(volatile SPI_typedef* SPIx)
{
	GPIO_Pin_Configuration_t Pin_CFG;
	if(SPIx == SPI1)
	{
		//PA4: SPI1_NSS
		//PA5: SPI1_SCK
		//PA6: SPI1_MISO
		//PA7: SPI1_MOSI

		//Master
		if(G_SPI_CFG[SPI1_Index].Device_Mode == SPI_Device_Mode_Master)
		{
			//PA4: SPI1_NSS
			switch ((uint32_t)G_SPI_CFG[SPI1_Index].NSS)
			{
			case SPI_NSS_Hardware_Master_SS_Output_Disable:
				// Hardware master/slave >>> Input floating
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin4;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
				MCAL_GPIO_Init(GPIOA, &Pin_CFG);
				break;

			case SPI_NSS_Hardware_Master_SS_Output_Enable:
				//Hardware master/NSS output enabled >>> Alternate function push-pull
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin4;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
				Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
				MCAL_GPIO_Init(GPIOA, &Pin_CFG);
				break;
			}


			//PA5: SPI1_SCK
			//Master Alternate function push-pull
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin5;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);


			//PA6: SPI1_MISO
			//Full duplex / master Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin6;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);

			//PA7: SPI1_MOSI
			//Full duplex / master Alternate function push-pull
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin7;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);
		}

		//slave
		else
		{
			//PA4: SPI1_NSS
			if(G_SPI_CFG[SPI1_Index].NSS == SPI_NSS_Hardware_Slave)
			{
				//Hardware master /slave Input floating
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin4;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
				MCAL_GPIO_Init(GPIOA, &Pin_CFG);
			}

			//PA5: SPI1_SCK
			//Slave Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin5;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);


			//PA6: SPI1_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			//Full duplex / slave (multi-slave) Alternate function open drain
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin6;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);


			//PA7: SPI1_MOSI
			//Full duplex / slave Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin7;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOA, &Pin_CFG);

		}



	}


	else if(SPIx == SPI2)
	{
		//	PB12: SPI2_NSS
		//	PB13: SPI2_SCK
		//	PB14 SPI2_MISO
		//	PB15: SPI2_MOSI

		//Master
		if(G_SPI_CFG[SPI2_Index].Device_Mode == SPI_Device_Mode_Master)
		{
			//PB12: SPI1_NSS
			switch ((uint32_t)G_SPI_CFG[SPI2_Index].NSS)
			{
			case SPI_NSS_Hardware_Master_SS_Output_Disable:
				// Hardware master/slave >>> Input floating
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin12;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
				MCAL_GPIO_Init(GPIOB, &Pin_CFG);
				break;

			case SPI_NSS_Hardware_Master_SS_Output_Enable:
				//Hardware master/NSS output enabled >>> Alternate function push-pull
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin12;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
				Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
				MCAL_GPIO_Init(GPIOB, &Pin_CFG);
				break;
			}


			//PB13: SPI1_SCK
			//Master Alternate function push-pull
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin13;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);


			//PB14: SPI1_MISO
			//Full duplex / master Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin14;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);

			//PB15: SPI1_MOSI
			//Full duplex / master Alternate function push-pull
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin15;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);
		}

		//slave
		else
		{
			//PB12: SPI1_NSS
			if(G_SPI_CFG[SPI2_Index].NSS == SPI_NSS_Hardware_Slave)
			{
				//Hardware master /slave Input floating
				Pin_CFG.GPIO_Pin_Number = GPIO_Pin12;
				Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
				MCAL_GPIO_Init(GPIOB, &Pin_CFG);
			}

			//PB13: SPI1_SCK
			//Slave Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin13;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);


			//PB14: SPI1_MISO
			//Full duplex / slave (point to point) Alternate function push-pull
			//Full duplex / slave (multi-slave) Alternate function open drain
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin14;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_AF_PP;
			Pin_CFG.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);


			//PB15: SPI1_MOSI
			//Full duplex / slave Input floating
			Pin_CFG.GPIO_Pin_Number = GPIO_Pin15;
			Pin_CFG.GPIO_Pin_Mode = GPIO_Mode_Input_FLO;
			MCAL_GPIO_Init(GPIOB, &Pin_CFG);
		}
	}
}

void MCAL_SPI_Send_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_Enable)
		while(!(SPIx->SPI_SR & SPI_SR_TXE));

	SPIx->SPI_DR = *P_TX_Buffer;

}


void MCAL_SPI_Receive_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_Enable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*P_TX_Buffer = SPIx->SPI_DR;
}


void MCAL_SPI_TX_RX_Data(volatile SPI_typedef* SPIx, uint16_t* P_TX_Buffer, enum SPI_Polling_Mechanism Polling_En)
{
	if(Polling_En == Polling_Enable)
		while(!(SPIx->SPI_SR & SPI_SR_TXE));

	SPIx->SPI_DR = *P_TX_Buffer;

	if(Polling_En == Polling_Enable)
		while(!(SPIx->SPI_SR & SPI_SR_RXNE));

	*P_TX_Buffer = SPIx->SPI_DR;
}


//----------------------------------------------------------------
//IRQ
//----------------------------------------------------------------
void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE  = ((SPI1->SPI_SR & 1<<1) >> 1);
	irq_src.RXNE = ((SPI1->SPI_SR & 1<<0) >> 0);
	irq_src.ERRI = ((SPI1->SPI_SR & 1<<4) >> 4);

	G_SPI_CFG[SPI1_Index].P_IRQ_CallBack(irq_src);
}

void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_src;

	irq_src.TXE  = ((SPI2->SPI_SR & 1<<1) >> 1);
	irq_src.RXNE = ((SPI2->SPI_SR & 1<<0) >> 0);
	irq_src.ERRI = ((SPI2->SPI_SR & 1<<4) >> 4);

	G_SPI_CFG[SPI2_Index].P_IRQ_CallBack(irq_src);

}

//ISR
//any flag that can generate an interrupt is cleared by the hardware when the interrupt is acknowledged in the NVIC by the processor
//if the flag is not enabled as interrupt it can be cleared reading from or writing to certain register or by another method according to the SPECS

