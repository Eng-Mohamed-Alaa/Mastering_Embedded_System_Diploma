/***************************************************************/
/* Author    : Mahmoud Korayem                                    */
/* Version   : V01                                             */
/* Date      : 24 NOV 2022                                     */
/***************************************************************/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../Inc/MCAL/GPIO/GPIO.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"
#include "../Inc/HAL/TFT/TFT_private.h"
#include "../Inc/HAL/TFT/TFT_config.h"
#include "../Inc/HAL/TFT/TFT_interface.h"
#include "../Inc/HAL/TFT/fonts.h"
#include "OS_Rupper/OS_Rupper.h"

uint16 _width=128;       ///< Display width as modified by current rotation
uint16 _height=160;      ///< Display height as modified by current rotation
uint16  cursor_x;     ///< x location to start print()ing text
uint16 cursor_y;     ///< y location to start print()ing text
uint8 rotation;     ///< Display rotation (0 thru 3)
uint8 _colstart;   ///< Some displays need this changed to offset
uint8 _rowstart;       ///< Some displays need this changed to offset
uint8 _xstart;
uint8 _ystart;

void HTFT_voidInitialize (void)
{
	GPIO_Port_Enable_clock(GPIO_PORT_A);
	/* Reset Pulse */
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_HIGH);
	OS_vTaskDelay(1);
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_LOW);
	OS_vTaskDelay(1);
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_HIGH);
	OS_vTaskDelay(1);
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_LOW);
	OS_vTaskDelay(100);
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_HIGH);
	OS_vTaskDelay(120);
	
	/* Sleep Out Command */
	voidWriteCommand(0x11);
	
	/* Wait 150 ms */
	OS_vTaskDelay(150);
	
	/* Color Mode Command */
	voidWriteCommand(0x3A);
	voidWriteData (0x05); /*RGB565 is the parameter for COlor Mode Command */
	
	/* Display On Command */
	voidWriteCommand(0x29);
}

TFT_SPI_CONFIG(void)
{
Rcc_enuControl_APB2_Peripheral(RCC_APB2_Periph_SPI1,RCC_Periph_ENABLE);
GPIO_PIN_INIT(GPIO_PIN_1 ,GPIO_PORT_A,output_push_pull,GPIO_max_speed_2_MHz,pull_UP); 	   //A0
GPIO_PIN_INIT(GPIO_PIN_2 ,GPIO_PORT_A,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);	  //RST
GPIO_PIN_INIT(GPIO_PIN_5 ,GPIO_PORT_A,AF_output_Push_pull,GPIO_max_speed_10_MHz,pull_UP);	  //CLK
GPIO_PIN_INIT(GPIO_PIN_7 ,GPIO_PORT_A,AF_output_Push_pull,GPIO_max_speed_10_MHz,pull_UP);	  //MOSI

/* SPI Init */
MSPI1_voidInit();
}


void HTFT_voidDisplayImage (const uint16* Copy_Image)
{
	uint16 counter;
	uint8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	
	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_Image[counter] >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_Image[counter] & 0x00ff;
		voidWriteData(Data);
	}


}
void HTFT_voidFillColor (uint16 Copy_uint16Color)
{
	uint16 counter;
	uint8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< 20480;counter++)
	{
		Data = Copy_uint16Color >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_uint16Color & 0x00ff;
		voidWriteData(Data);
	}
}
void HTFT_voidDrawRect(uint8 x1 ,uint8 x2 ,uint8 y1 ,uint8 y2 ,uint16 Copy_uint16Color)
{
	uint16 size =(x2-x1) * (y2-y1);
	uint16 counter;
	uint8 Data;

	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(x1);
	voidWriteData(0);
	voidWriteData(x2);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(y1);
	voidWriteData(0);
	voidWriteData(y2);

	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);

	for(counter = 0; counter< size ;counter++)
	{
		Data = Copy_uint16Color >> 8;

		/* Write the high byte */
		voidWriteData(Data);
		/* Write the low byte */
		Data = Copy_uint16Color & 0x00ff;
		voidWriteData(Data);
	}
}
void voidWriteCommand(uint8 Copy_uint8Command)
{
	uint8 Local_uint8Temp; /* this var has no effect as MISO pin not connected */
	
	/* Set A0 Pin to Low */
	GPIO_set_PIN_value(TFT_A0_PIN,GPIO_LOGIC_LOW);
	
	/* Send Command over SPI */
	MSPI1_voidSendReceiveSynch(Copy_uint8Command,&Local_uint8Temp);
	
}

void voidWriteData   (uint8 Copy_uint8Data)
{
	uint8 Local_uint8Temp;
	
	/* Set A0 Pin to High */
	GPIO_set_PIN_value(TFT_A0_PIN,GPIO_LOGIC_HIGH);
	
	/* Send data over SPI */
	MSPI1_voidSendReceiveSynch(Copy_uint8Data,&Local_uint8Temp);	
}
void ST7735_Reset(void)
{
	/* Reset Pulse */
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_LOW);
	MSTK_voidSetBusyWait(100);
	GPIO_set_PIN_value(TFT_RST_PIN,GPIO_LOGIC_HIGH);
}

void ST7735_SetAddressWindow(uint8 x0, uint8 y0, uint8 x1, uint8 y1)
{
	/* Set X Address */
	// sending Start poin 00 (16bit) and Ending POint in X is 0/159 (16 bit ) sending byte by byte
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(x0);
	voidWriteData(0);
	voidWriteData(x1);

	/* Set Y Address */
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(y0);
	voidWriteData(0);
	voidWriteData(y1);
	/* RAM Write all coming date show it on screen */
	voidWriteCommand(0x2C);
}
void ST7735_WriteChar(uint16 x, uint16 y, char ch, FontDef font, uint16 color, uint16 bgcolor) {
    uint32 i, b, j;

    ST7735_SetAddressWindow(x, y, x+font.width-1, y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                uint8 data[] = { color >> 8, color & 0xFF };
                for(uint8 i=0;i<sizeof(data);i++)
                {
                	voidWriteData(data[i]);
                }
               // ST7735_WriteData(data, sizeof(data));
            } else {
                uint8 data[] = { bgcolor >> 8, bgcolor & 0xFF };
                for(uint8 i=0;i<sizeof(data);i++)
                {
                	voidWriteData(data[i]);
                }
                //ST7735_WriteData(data, sizeof(data));
            }
        }
    }
}

void ST7735_WriteString(uint16 x, uint16 y, const char* str, FontDef font, uint16 color, uint16 bgcolor) {
    while(*str) {
        if(x + font.width >= _width) {
            x = 0;
            y += font.height;
            if(y + font.height >= _height) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        ST7735_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

}

void drawPixel(uint16 x, uint16 y, uint16 color) {
    if((x >= _width) || (y >= _height))
        return;
    ST7735_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[] = { color >> 8, color & 0xFF };
    for(uint8 i=0;i<sizeof(data);i++)
    {
    	voidWriteData(data[i]);
    }
}

void writePixel(uint16 x, uint16 y, uint16 color)
{
    drawPixel(x, y, color);
}

void writeLine(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color)
{
    uint16 steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    uint16 dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    uint16 err = dx / 2;
    uint16 ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            writePixel(y0, x0, color);
        } else {
            writePixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void  drawFastVLine(uint16 x, uint16 y, uint16 h, uint16 color)
{
	writeLine(x, y, x, y + h - 1, color);
}
void  drawFastHLine(uint16 x, uint16 y, uint16 w, uint16 color)
{
	writeLine(x, y, x + w - 1, y, color);
}
void drawRect(uint16 x, uint16 y, uint16 w, uint16 h, uint16 color)
{
    drawFastHLine(x, y, w, color);
    drawFastHLine(x, y+h-1, w, color);
    drawFastVLine(x, y, h, color);
    drawFastVLine(x+w-1, y, h, color);
}

void ST7735_SetRotation(uint8_t m)
{

  uint8_t madctl = 0;

  rotation = m % 4; // can't be higher than 3

  switch (rotation)
  {
  case 0:
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MY | ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
      _xstart = _colstart;
      _ystart = _rowstart;
    break;
  case 1:
      madctl = ST7735_MADCTL_MY | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
    break;
  case 2:
      madctl = ST7735_MADCTL_RGB;
      _height = ST7735_HEIGHT;
      _width = ST7735_WIDTH;
    _xstart = _colstart;
    _ystart = _rowstart;
    break;
  case 3:
      madctl = ST7735_MADCTL_MX | ST7735_MADCTL_MV | ST7735_MADCTL_RGB;
      _width = ST7735_HEIGHT;
      _height = ST7735_WIDTH;
    _ystart = _colstart;
    _xstart = _rowstart;
    break;
  }
  voidWriteCommand(0x36);//ST7735_MADCTL
//  ST7735_WriteData(&madctl,1);
	voidWriteData(madctl);

}


