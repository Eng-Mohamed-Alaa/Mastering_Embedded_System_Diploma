

#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../Inc/MCAL/UART/USART.h"
#include "../Inc/HAL/TFT/fonts.h"
#include "../Inc/HAL/TFT/TFT_interface.h"

#include "screens.h"


void SCREEN_securityLevel1POS(uint8 Copy_u8level){

	switch(Copy_u8level){
	case 1 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZGF    \n\n\n        Security Level 1 approved\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 1", Font_7x10, GREEN,BLACK);
		ST7735_WriteString(40, 25, "approved", Font_7x10, GREEN,BLACK);
		break;
	case 2 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZGF    \n\n\n        Security Level 2 approved\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 2", Font_7x10, GREEN,BLACK);
		ST7735_WriteString(40, 25, "approved", Font_7x10, GREEN,BLACK);
		break;
	case 3 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZGF    \n\n\n        Security Level 3 approved\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 3", Font_7x10, GREEN,BLACK);
		ST7735_WriteString(40, 25, "approved", Font_7x10, GREEN,BLACK);
		break;
	case 4 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZG    \n\n\n        Feature Enabled Successfully\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Feature Enabled", Font_7x10, GREEN,BLACK);
		ST7735_WriteString(20, 25, "Successfully", Font_7x10, GREEN,BLACK);
		break;
	case 5 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZG    \n\n\n        Feature Disabled Successfully\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Feature Disabled", Font_7x10, GREEN,BLACK);
		ST7735_WriteString(20, 25, "Successfully", Font_7x10, GREEN,BLACK);
		break;
	}

}

void SCREEN_securityLevel1NEG(uint8 Copy_u8level){


	switch(Copy_u8level){
	case 1 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Security Level 1 denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 1 denied", Font_7x10, RED,BLACK);
		break;
	case 2 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Security Level 2 denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 2 denied", Font_7x10, RED,BLACK);
		break;
	case 3 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Security Level 3 denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Security Level 3 Denied", Font_7x10, RED,BLACK);
		break;
	case 4 :

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Reading Temp Denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Reading Temp Denied", Font_7x10, RED,BLACK);
		break;
	case 5 :

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Reading Mirror Denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Reading Mirror Denied", Font_7x10, RED,BLACK);
		break;
	case 6 :

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Enabling Features is Denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Enabling Features is", Font_7x10, RED,BLACK);
		ST7735_WriteString(60, 25, "Denied", Font_7x10, RED,BLACK);
		break;
	case 7 :
#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZR    \n\n\n        Disabling Features is Denied\n");

#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Disabling Features is", Font_7x10, RED,BLACK);\
		ST7735_WriteString(60, 25, "Denied", Font_7x10, RED,BLACK);
		break;
	}
}


void SCREEN_Temp(uint8 Copy_u8DTC, uint8 Copy_u8CurrentReading){
	char str[] = "000";

	str[2] = (Copy_u8CurrentReading % 10)+48;
	Copy_u8CurrentReading /= 10;
	str[1] = (Copy_u8CurrentReading % 10)+48;
	Copy_u8CurrentReading /= 10;
	str[0] = (Copy_u8CurrentReading % 10)+48;
	//   Copy_u8CurrentReading /= 10;

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZB    \n\n\n             Temp Value: ");
	Usart_enuTransmitCharBlocking( &Usart1,'V' );
	Usart_enuTransmitStringBlocking( &Usart1,(uint8*)str );
	if(Copy_u8DTC ==0)
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"zGNLG    \n\n	       NO ERROR");
	else
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"zRNLR    \n\n		 ERROR");

#endif

	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(10,2, "Temp Value", Font_11x18, RED,BLACK);
	HTFT_voidDrawRect(0,160,30,75,CYAN);


	switch(Copy_u8DTC){
	case 0 :
		ST7735_WriteString(3, 35, "DTC        No Error ", Font_7x10, MAGENTA,CYAN);
		break;
	case 1 :
		ST7735_WriteString(3, 35, "DTC        Error ", Font_7x10, RED,CYAN);
		break;
	}



	ST7735_WriteString(3, 56, "Curr Read", Font_7x10, BLACK,CYAN);
	ST7735_WriteString(90, 56, str, Font_7x10, BLACK,CYAN);

	drawRect(2,32,156,96,BLACK);
	drawFastVLine(77,32,96,BLACK);
	// drawFastVLine(110,32,96,BLACK);
	drawFastHLine(2,53,156,BLACK);
	drawFastHLine(2,71,156,BLACK);
	//  drawFastHLine(2,90,156,BLACK);
	// drawFastHLine(2,115,156,BLACK);


}

void SCREEN_Mirror(uint8 Copy_u8DTC, uint8 Copy_u8CurrentReading){


#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZB    \n\n\n             Read Mirror: ");
	Usart_enuTransmitCharBlocking( &Usart1,'V' );
	if (Copy_u8CurrentReading == ZERO_VALUE){
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"OPEN");
	}
	else if (Copy_u8CurrentReading == ONE_VALUE){
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"CLOSED");

	}

	if(Copy_u8DTC ==ZERO_VALUE)
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"zGNMG    \n\n	       NO ERROR");
	else
		Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"zRNMR    \n\n		 ERROR");

#endif


	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(20,2, "Read Mirror", Font_11x18, RED,BLACK);
	HTFT_voidDrawRect(0,160,30,75,CYAN);
	switch(Copy_u8DTC){
	case 0 :
		ST7735_WriteString(5, 36, "DTC        No Error ", Font_7x10, MAGENTA,CYAN);
		break;
	case 1 :
		ST7735_WriteString(5, 36, "DTC        Error ", Font_7x10, RED,CYAN);
		break;
	}

	switch(Copy_u8CurrentReading){
	case 0 :
		ST7735_WriteString(5, 56, "State       Open ", Font_7x10, BLACK,CYAN);
		break;

	case 1 :
		ST7735_WriteString(5, 56, "State       Closed ", Font_7x10, BLACK,CYAN);
		break;

	}

	drawRect(2,32,156,96,BLACK);
	drawFastVLine(77,32,50,BLACK);
	//drawFastVLine(110,32,96,BLACK);
	drawFastHLine(2,53,156,BLACK);
	// drawFastHLine(2,71,156,BLACK);
	// drawFastHLine(2,90,156,BLACK);
	//drawFastHLine(2,115,156,BLACK);

}
