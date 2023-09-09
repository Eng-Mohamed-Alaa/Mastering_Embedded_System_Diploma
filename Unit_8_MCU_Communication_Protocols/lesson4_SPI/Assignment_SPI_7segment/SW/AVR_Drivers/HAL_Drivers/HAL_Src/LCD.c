
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

void LCD_INIT() //DONE
{
	_delay_ms(20);
	//set LCD_Port, LCD_CTRL as output
	LCD_DataDir_PORT |= (0xFF << LCD_DATA_shift); 
	LCD_DataDir_CTRL |= (1 << LCD_RS | 1 << LCD_RW | 1 << LCD_EN);
	
	//RS >>> command register : 0
	//RW >>> Write : 0
	//EN >>> disabled : 0
	LCD_CTRL &= ~(1 << LCD_RS | 1 << LCD_RW | 1 << LCD_EN);
	
	//time delay to wait the LCD after power on 
	_delay_ms(15);
	
	// clear the screen
	LCD_Clear_Screen();
	
	//choose the mode
	#ifdef LCD_EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef LCD_FOUR_BIT_MODE
	/*LCD_WRITE_COMMAND(0x02);
	Sets DDRAM address 0 in
	address counter. Also
	returns display from being
	shifted to original position.
	DDRAM contents remain unchanged*/
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	
}

void LCD_WRITE_COMMAND(unsigned char command) //done
{
	//LCD_Check_Is_Busy();
	
	//RS >>> command register: 0
	//RW >>> write: 0 (set already)
	LCD_CTRL &= ~((1 << LCD_RS) | (1 << LCD_RW));
	
	#ifdef LCD_EIGHT_BIT_MODE
	LCD_PORT = command;
	LCD_kick();
	#endif
	
	#ifdef LCD_FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | ((command & 0xF0)); //send the Higher nibble of the command
	LCD_kick();		
	LCD_PORT = (LCD_PORT & 0x0F) | (command << LCD_DATA_shift); //send the lower nibble of the command
	LCD_kick();

	#endif
}


void LCD_WRITE_CHAR(unsigned char character) //DONE
{
	//LCD_Check_Is_Busy();
	//RS >>> Data register: 1
	//RW >>> write: 0 (set already)
	LCD_CTRL |= (1 << LCD_RS);
	LCD_CTRL &= ~(1 << LCD_RW);
	#ifdef LCD_EIGHT_BIT_MODE
	//LCD_Check_Is_Busy();
	LCD_PORT = character;
	LCD_kick();
	#endif
	
	#ifdef LCD_FOUR_BIT_MODE
	LCD_PORT = (LCD_PORT & 0x0F) | ((character & 0xF0)); //send the Higher nibble
	_delay_ms(1);
	LCD_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << LCD_DATA_shift); //send the lower nibble
	LCD_kick();
	#endif
	_delay_ms(70); //to make writing slow
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

void LCD_Clear_Screen(void) //done
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

static void LCD_kick(void) //done
{
	LCD_CTRL |= (1 << LCD_EN);
	_delay_ms(1); // enable pulse duration
	LCD_CTRL &= ~(1 << LCD_EN);	
	_delay_ms(2); //wait for the LCD execution time
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

