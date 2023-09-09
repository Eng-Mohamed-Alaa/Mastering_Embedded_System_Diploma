
#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>

#define Set_SEG1(n)		{	PORTA &= (0xF0), PORTA |= n;	}
#define Set_SEG2(n)		{	PORTA &= (0x0F), PORTA |= n << 4;	}

#define MCU_Act_As_Master
//#define MCU_Act_As_Slave

void Seven_Segment_Write(void)
{
	uint8_t data1, data2;
	uint8_t received_data;

#ifdef MCU_Act_As_Master

	data2=0;
	
#endif

#ifdef MCU_Act_As_Slave

	data2 = 5;
	
#endif

	for(; data2 < 10; ++data2)
	{
		received_data = SPI_Send_Receive(data2);
		Set_SEG2(received_data);
		
		for(data1 = 0; data1 < 10; ++data1)
		{
			received_data = SPI_Send_Receive(data1);
			Set_SEG1(received_data);
			_delay_ms(1000);
		}
	}
	
}

int main()
{
	
#ifdef MCU_Act_As_Master
	
	SPI_Master_Init();
	
#endif

#ifdef MCU_Act_As_Slave
	
	SPI_Slave_Init();
		
#endif
	
	//set portA as output to be connected to two 7 segments
	DDRA = 0xFF;
	
	Seven_Segment_Write();
	
	return 0;
}
	
	

	
