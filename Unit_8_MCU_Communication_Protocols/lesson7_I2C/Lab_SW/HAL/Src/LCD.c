
//--------------------------------------------------------
//includes
//--------------------------------------------------------
#include <LCD.h>

//--------------------------------------------------------
// static functions prototypes
//--------------------------------------------------------

static void LCD_kick(void);
//static void LCD_Check_Is_Busy(void);

//--------------------------------------------------------
//LCD APIs implementation
//--------------------------------------------------------

void LCD_INIT()
{
	GPIO_Pin_Configuration_t LCD_Pin_Config;

	//set LCD_Port as output, Pin: [7:0]
	LCD_Pin_Config.GPIO_Pin_Number = LCD_D0;
	LCD_Pin_Config.GPIO_Pin_Mode = GPIO_Mode_Output_PP;
	LCD_Pin_Config.GPIO_Pin_Output_Speed = GPIO_Output_Speed_10M;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D1;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D2;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D3;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D4;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D5;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D6;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_D7;
	MCAL_GPIO_Init(LCD_PORT, &LCD_Pin_Config);

	//set LCD_CTRL as output, Pin:[10:8]
	LCD_Pin_Config.GPIO_Pin_Number = LCD_RS;
	MCAL_GPIO_Init(LCD_CTRL, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_RW;
	MCAL_GPIO_Init(LCD_CTRL, &LCD_Pin_Config);

	LCD_Pin_Config.GPIO_Pin_Number = LCD_EN;
	MCAL_GPIO_Init(LCD_CTRL, &LCD_Pin_Config);

	//RS=0 >>> command register
	//RW=0 >>> Write
	//EN=0 >>> disabled
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Reset);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_EN, LCD_Pin_Reset);

	//time delay to wait the LCD after power on
	my_wait(2);
	// clear the screen
	LCD_Clear_Screen();

	//choose the mode
#ifdef LCD_EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
#endif

#ifdef LCD_FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
#endif

	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

void LCD_WRITE_COMMAND(unsigned char command)
{
//LCD_Check_Is_Busy();

#ifdef LCD_EIGHT_BIT_MODE
	MCAL_GPIO_Write_Port(LCD_PORT, command);
	//LCD_Port is the same port of LCD_CTRL so we need to set the LCD_CTRL values after writing over the port
	//RS = 0 >>> command register
	//RW = 0 >>> write
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Reset);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
	LCD_kick();
#endif

#ifdef LCD_FOUR_BIT_MODE
	uint8 nibble;
	nibble= (command & 0xF0); //send the Higher nibble of the command
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Reset);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
	LCD_kick();
	nibble= (command & 0x0F); //send the lower nibble of the command
	MCAL_GPIO_Write_Port(LCD_PORT, nibble << LCD_DATA_shift);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Reset);
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
	LCD_kick();
#endif
}


void LCD_WRITE_CHAR(unsigned char character)
{
	{
	//LCD_Check_Is_Busy();

	#ifdef LCD_EIGHT_BIT_MODE
		MCAL_GPIO_Write_Port(LCD_PORT, character);
		//LCD_Port is the same port of LCD_CTRL so we need to set the LCD_CTRL values after writing over the port
		//RS = 1 >>> Data register
		//RW = 0 >>> write
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Set);
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
		LCD_kick();
	#endif

	#ifdef LCD_FOUR_BIT_MODE
		uint8 nibble;
		nibble= (character & 0xF0); //send the Higher nibble of the command
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Set);
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
		LCD_kick();
		nibble= (character & 0x0F); //send the lower nibble of the command
		MCAL_GPIO_Write_Port(LCD_PORT, nibble << LCD_DATA_shift);
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RS, LCD_Pin_Set);
		MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_RW, LCD_Pin_Reset);
		LCD_kick();
	#endif
	}
	my_wait(1); //to write slowly
}

void LCD_WRITE_STRING(char* string)
{
	uint8_t i, cnt;
	for(i=cnt=0; string[i] > 0; ++i )
	{
		LCD_WRITE_CHAR(string[i]);
		cnt++;
		switch(cnt)
		{

		case 16:
			LCD_GOTO_XY(2,0);
			break;
		case 32:
			LCD_Clear_Screen();
			LCD_GOTO_XY(1,0);
			cnt = 0;
		}
	}
}

void LCD_Clear_Screen(void)
{
	LCD_WRITE_COMMAND(0x01);
}

void LCD_GOTO_XY(unsigned char line, unsigned char position)
{
	if(position >= 0)
	{
		switch(line)
		{
		case 1:
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
			break;
		case 2:
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

//--------------------------------------------------------
// static functions implementation
//--------------------------------------------------------

static void LCD_kick(void)
{
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_EN, LCD_Pin_Set);
	my_wait(100); // enable pulse duration
	MCAL_GPIO_Write_Pin(LCD_CTRL, LCD_EN, LCD_Pin_Reset);
	my_wait(100); //wait for the LCD execution time
}

// static void LCD_Check_Is_Busy(void) //done
// {
// 	//LCD port >>> input
// 	LCD_DataDir_PORT &= ~(0xFF << LCD_DATA_shift);
//
// 	//RS >>> command register: 0
// 	//RW >>> read: 1
// 	LCD_CTRL |= (1 << LCD_RW);
// 	LCD_CTRL &= ~(1 << LCD_RS) ;
// 	LCD_kick();
//
// 	//read as long as the D7 is high
// // 	while((LCD_Port_Input >> 7) & 1)
// // 	{
// // 		LCD_kick();
// // 	}
// //
// 	//LCD port >>> return output
// 	LCD_DataDir_PORT |= (0xFF << LCD_DATA_shift);
// 	LCD_CTRL |= (1 << LCD_RS);
// 	LCD_CTRL &= ~(1 << LCD_RW);
//
// }

