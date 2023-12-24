
#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

#include "fonts.h"
void HTFT_voidInitialize   (void);
void TFT_SPI_CONFIG(void);
void HTFT_voidDisplayImage (const uint16* Copy_Image);
void HTFT_voidFillColor (uint16 Copy_uint16Color);
void HTFT_voidDrawRect(uint8 x1 ,uint8 x2 ,uint8 y1 ,uint8 y2 ,uint16 Copy_uint16Color);
void ST7735_WriteChar(uint16 x, uint16 y, char ch, FontDef font, uint16 color, uint16 bgcolor);
void ST7735_WriteString(uint16 x, uint16 y, const char* str, FontDef font, uint16 color, uint16 bgcolor);
void ST7735_Reset(void);
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

//#define _width 128
//#define _height 160

#define ST7735_WIDTH  128
#define ST7735_HEIGHT 160

#define DELAY 0x80

#define ST7735_MADCTL_MY  0x80
#define ST7735_MADCTL_MX  0x40
#define ST7735_MADCTL_MV  0x20
#define ST7735_MADCTL_ML  0x10
#define ST7735_MADCTL_RGB 0x00
#define ST7735_MADCTL_BGR 0x08
#define ST7735_MADCTL_MH  0x04


#define ST7735_INVOFF  0x20
#define ST7735_INVON   0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_RAMRD   0x2E

#define _swap_int16_t(a, b)                                                    \
  {                                                                            \
    uint16 t = a;                                                             \
    a = b;                                                                     \
    b = t;                                                                     \
  }

void drawPixel(uint16 x, uint16 y, uint16 color);
void writePixel(uint16 x, uint16 y, uint16 color);
void writeLine(uint16 x0, uint16 y0, uint16 x1, uint16 y1, uint16 color);
void  drawFastVLine(uint16 x, uint16 y, uint16 h, uint16 color);
void  drawFastHLine(uint16 x, uint16 y, uint16 w, uint16 color);
void drawRect(uint16 x, uint16 y, uint16 w, uint16 h, uint16 color);
void ST7735_SetRotation(uint8_t m);
void voidWriteCommand(uint8 Copy_uint8Command);
#endif
