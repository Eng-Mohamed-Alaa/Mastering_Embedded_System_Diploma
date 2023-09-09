
//Includes
#include "SPI.h"

//SPI APIs implementation
void SPI_Master_Init(void)
{
	//set MOSI,SCK,SS as output pins in portB
	//MISO is set to input by default SPI mode is master mode
	DDRB |= (1 << MOSI | 1 << SCK | 1 << SS);
	
	//set data order to LSB(1)/MSB(0)
	Set_Bit(SPSR, DORD);
	
	//set clock idle state 
	SPI_CLKIdle_Low();
	
	//set data sampling edge 
	SPI_Sample_Laeding();
	
	//set the clock rate (for master only)
	SPI_CLKRate_Fosc_over16();
	 
	//set SPI mode to master
	SPI_Mode_Master();
	
	//enable the SPI
	Set_Bit(SPCR, SPE);
}


void SPI_Slave_Init(void)
{
	//set MISO as output pins in portB
	//MOSI,SCK,SS are set to input by default SPI mode is slave mode
	DDRB |= (1 << MISO);
		
	//set data order to LSB(1)/MSB(0)
	Set_Bit(SPSR, DORD);
		
	//set clock idle state
	SPI_CLKIdle_Low();
		
	//set data sampling edge
	SPI_Sample_Laeding();
		
	//set SPI mode to Slave
	SPI_Mode_Slave();
		
	//enable the SPI
	Set_Bit(SPCR, SPE);
}


//this function works for both SPI master and SPI slave
//the function sends the data from the master to the slave and from the slave to the mater at same time
//after checking data is send from both the master and the slave the received data is read 
//the function parameter is the data to be transmitted and the return is the received data
//we can say that this function exchange the data between master and slave then read it

//note: //calling the function in the master means write data to be send and issue transaction to exchange data then read the received data
		//calling the function in the slave means write data to be send and wait a transaction from the master to exchange data then read the received data
uint8_t SPI_Send_Receive(uint8_t Data)
{
	
	Reset_Bit(PORTB, SS);
	//write data to be send
	SPDR = Data;
	
	//in the master: an exchange data transaction is issued and wait until the transmit is complete from the master (new data received also)
	//in the slave: wait for the exchange data transaction from the master is issued and the transmit is complete from the slave (new data received also)
	while(!Read_Bit(SPSR, SPIF));
	Set_Bit(PORTB, SS);

	//read the new received data
	return SPDR;
}

//when the SPI send data and no data is received
//for connecting MAX7221 chip
void SPI_Send(uint8_t Data)
{
	//write data to be send
	SPDR = Data;
	
	//in the master: an exchange data transaction is issued and wait until the transmit is complete from the master (new data received also)
	//in the slave: wait for the exchange data transaction from the master is issued and the transmit is complete from the slave (new data received also)
	while(!Read_Bit(SPSR, SPIF));
}