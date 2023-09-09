
#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>
#include <I2C.h>

void Lab1(void);
void Lab2(void);

//#define MCU_Act_As_Master
#define MCU_Act_As_Slave

int main()
{
	//Lab1();
	Lab2();
	return 0;
}
	
void Lab1(void)
{
#ifdef MCU_Act_As_Master

	uint8_t ch = 0;
	I2C_Init(0x48);
	while (1)
	{
		_delay_ms(500);
		I2C_Start();
		I2C_Master_TX(0b11010000+0); //Address + Write
		while(TWSR != 0x18);	//address is transmitted and ACK is received
		I2C_Master_TX(ch++);	//data
		while(TWSR != 0x28);	//data is transmitted and ACK is received
		I2C_Stop();
	}
#endif

#ifdef MCU_Act_As_Slave
	
	DDRA = 0xFF;
	I2C_Set_Address(0b11010000);
	while (1)
	{
		PORTA = I2C_Slave_RX(1);
	}
#endif
	
}

void Lab2(void)
{
#ifdef MCU_Act_As_Master

	uint8_t ch = 0;
	DDRA = 0xFF;
	I2C_Init(0x48);
	while (1)
	{
		_delay_ms(500);
		I2C_Start();
		I2C_Master_TX(0b11010000+1); //Address + Reqd
		ch=I2C_Master_RX(0);		//read last byte
		I2C_Stop();
		PORTA = ch;
	}
#endif
	
#ifdef MCU_Act_As_Slave
	 	
	uint8_t ch = 0;
	I2C_Set_Address(0b11010000);
	while (1)
	{
		I2C_Slave_RX(1);
		I2C_Slave_TX(ch++);
	}
#endif
}

	
