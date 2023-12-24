
//======================================================================
//Includes
//======================================================================
#include "main.h"

int main(void)
{
	Tool_Init();
	OS_vTaskStartScheduler();

	return 0;
}

void Tool_Init(void)
{
	//enable HSE and select it as the system clock for higher accuracy and disable the HSI to save power
	Rcc_enuControlCLk(RCC_CNTROL_HSION, RCC_CNTROL_HSEON, RCC_CNTROL_PLLOFF);
	Rcc_enuSelectSysCLk(RCC_CLK_HSE, RCC_STATE_NOTPRESERVE);
	//should be done inside the HAL
	GPIO_Port_Enable_clock(GPIO_PORT_A);
	GPIO_Port_Enable_clock(GPIO_PORT_B);

	TFT_SPI_CONFIG();
	/*KEYPAD INIT*/
	KEYPAD_voidInit();
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);

	UDS_VoidInit();
	UDS_voidSetCallBack(UDS_Isr_CallBack);


	/********************* Start of Uart *****************************************************/


	/* Usart Tx PA9 */
	GPIO_PIN_INIT(GPIO_PIN_9,GPIO_PORT_A,AF_output_Push_pull,GPIO_max_speed_2_MHz,pull_UP);

	/* USART RX PA10*/
	GPIO_PIN_INIT(GPIO_PIN_10,GPIO_PORT_A,InputFloating,GPIO_INPUT,FLOATING);

	Usart_enuSetCallbackRxFunction(&Usart1, Usart_Isr);
	Usart_enuInit(&Usart1);
	Usart_enuEnableRxInterrupt(&Usart1);
	Nvic_enuEnableInterrupt(NVIC_USART1);

		/********************* End of Uart *****************************************************




	/*Tasks creation*/
	OS_xTaskCreate(Tool_Control_Task,"TFT_Task",512,NULL,Tool_TFT_Task_Priority,&Tool_TFT_Handle);
}

void Tool_Control_Task(void* Param)
{
	/* TFT Init */
	HTFT_voidInitialize();


	while(1)
	{
		switch(Tool_Current_State)
		{
		case ST_Tool_Start_Window:
			Tool_Start_Window();
			break;
		case ST_Tool_Security_level_Window:
			Tool_Security_level_Window();
			break;

		case ST_Tool_Car_Options_Window:
			Tool_Car_Options_Window();
			break;

		case ST_Tool_UDS_Send_Req:
			Tool_UDS_Send_Req();
			break;

		case ST_Tool_Display_Response:
			Tool_Display_Response();
			break;
		}
	}
}


void Tool_Start_Window(void)
{

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking( &Usart1, (uint8*)"ZB                  GROUP 1-A\n");
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("                Diagnostic Tool\n\n\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("1)Unlock Security LVL\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("2)Show Car Options\n"));
#endif

	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(10,5, "GROUP1A", Font_16x26, RED,BLACK);
	ST7735_WriteString(10, 30, "Diagnostic tool", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 50, "1)Unlock Security LVL", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 70, "2)Show Car Options", Font_7x10, BLUE,BLACK);
	while(entered_key == KEY_NOT_PRESSED || entered_key == 0)
	{
		Tool_Keypad_Read();
	}
	entered_key = KEY_NOT_PRESSED;
}

void Tool_Security_level_Window(void)
{

#if (UART_GUI == ONE_VALUE)
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("ZB                  Select Level\n\n\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("1)Unlock Security L_A\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("2)Unlock Security L_B\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("3)Unlock Security L_C\n"));
#endif

	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(10, 10, "Select Level", Font_7x10, RED,BLACK);
	ST7735_WriteString(0, 35, "1)Unlock Security L_1", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 60, "2)Unlock Security L_2", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 85, "3)Unlock Security L_3", Font_7x10, BLUE,BLACK);
	while(entered_key == KEY_NOT_PRESSED)
	{
		Tool_Keypad_Read();
	}
	entered_key = KEY_NOT_PRESSED;
}

void Tool_Car_Options_Window(void)
{
#if (UART_GUI == ONE_VALUE)

	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("ZBN                  Select Option\n\n\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("1)Read Temperature\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("2)View Mirror State\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("3)LED Feature Enable\n"));
	Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("4)LED Feature Disable"));

#endif

	ST7735_SetRotation(0);
	HTFT_voidFillColor(BLACK);
	ST7735_SetRotation(1);
	ST7735_WriteString(10, 10, "Select Option", Font_7x10, RED,BLACK);
	ST7735_WriteString(0, 30, "1)Read Temperature", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 50, "2)View Mirror State", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 70, "3)LED Feature Enable", Font_7x10, BLUE,BLACK);
	ST7735_WriteString(0, 90, "4)LED Feature Disable", Font_7x10, BLUE,BLACK);
	while(entered_key == KEY_NOT_PRESSED)
	{
		Tool_Keypad_Read();
	}
	entered_key = KEY_NOT_PRESSED;
}

void Tool_UDS_Send_Req(void)
{
	switch(Frame_Type)
	{
	case Security_Level1:
		UDS_Request(SID_SECURITY_ACCESS,UDS_REQUEST_LEVEL_1_SECURITY_SEED,UDS_NO_DATA,UDS_NO_DATA);
		Tool_Communication_Check();
		if(Tool_Current_State == ST_Tool_UDS_Send_Req)
		{
			uint32 Local_u32Key = custom_hash_function(G_UDS_DATA);
			UDS_Request(SID_SECURITY_ACCESS,UDS_SEND_LEVEL_1_SECURITY_KEY,UDS_NO_DATA,Local_u32Key);
		}
		break;

	case Security_Level2:
		UDS_Request(SID_SECURITY_ACCESS,UDS_REQUEST_LEVEL_2_SECURITY_SEED,UDS_NO_DATA,UDS_NO_DATA);
		Tool_Communication_Check();
		if(Tool_Current_State == ST_Tool_UDS_Send_Req)
		{
			uint32 Local_u32Key = custom_hash_function(G_UDS_DATA);
			UDS_Request(SID_SECURITY_ACCESS,UDS_SEND_LEVEL_2_SECURITY_KEY,UDS_NO_DATA,Local_u32Key);
		}
		break;

	case Security_Level3:
		UDS_Request(SID_SECURITY_ACCESS,UDS_REQUEST_LEVEL_3_SECURITY_SEED,UDS_NO_DATA,UDS_NO_DATA);
		Tool_Communication_Check();
		if(Tool_Current_State == ST_Tool_UDS_Send_Req)
		{
			uint32 Local_u32Key = custom_hash_function(G_UDS_DATA);
			UDS_Request(SID_SECURITY_ACCESS,UDS_SEND_LEVEL_3_SECURITY_KEY,UDS_NO_DATA,Local_u32Key);
		}
		break;

	case Temperature_Read:
		//send UDS Request to Read the Oil Temperature
		UDS_Request(SID_READ_DATA_BY_IDENTIFIER, UDS_NO_DATA, APP_TEMPERATURE_DID, UDS_NO_DATA);
		break;

	case Mirror_Read_State:
		UDS_Request(SID_READ_DATA_BY_IDENTIFIER, UDS_NO_DATA, APP_MIRROR_STATE, UDS_NO_DATA);
		break;

	case Feature_Enable:
		//send UDS Request to Change Session to Programming Session
		UDS_Request(SID_DIAGNOSTIC_SESSION_CONTROL, PROGRAMMING_SESSION, UDS_NO_DATA, UDS_NO_DATA);
		Tool_Communication_Check();
		if(Tool_Current_State == ST_Tool_UDS_Send_Req)
		{
			UDS_Request(SID_WRITE_DATA_BY_IDENTIFIER, UDS_NO_DATA, DID_LED_FEATURE, DATA_ENABLE);
		}
		break;
	case Feature_Disable:
		//send UDS Request to Change Session to Programming Session
		UDS_Request(SID_DIAGNOSTIC_SESSION_CONTROL, PROGRAMMING_SESSION, UDS_NO_DATA, UDS_NO_DATA);
		Tool_Communication_Check();
		if(Tool_Current_State == ST_Tool_UDS_Send_Req)
		{
			UDS_Request(SID_WRITE_DATA_BY_IDENTIFIER, UDS_NO_DATA, DID_LED_FEATURE, DATA_DISABLE);
		}
		break;
	}

	if(Tool_Current_State == ST_Tool_UDS_Send_Req)
	{
		Tool_Communication_Check();
	}

	if(Tool_Current_State == ST_Tool_UDS_Send_Req)
	{
		Tool_Current_State = ST_Tool_Display_Response;
	}
}

void Tool_Communication_Check(void)
{
	//wait car response for 1 sec
	for(uint32 Cnt = 0; Cnt < 800000 && Communication_State == Data_not_recieved; ++Cnt);
	if(Communication_State == Data_recieved)
	{
		Communication_State = Data_not_recieved;
		if (G_UDS_SID == RSID_NEGATIVE_RESPONSE){
			Tool_Current_State = ST_Tool_Display_Response;
		}
	}
	else
	{
		Tool_Error_Messages();
		Tool_Current_State = ST_Tool_Start_Window;
	}
}

void Tool_Error_Messages(void)
{

	switch(Tool_Current_State)
	{
	case ST_Tool_Start_Window:
	case ST_Tool_Car_Options_Window:
#if (UART_GUI == ONE_VALUE)
		Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("ZR        Invalid Option\n"));
#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Invalid Option", Font_7x10, RED,BLACK);
		break;

	case ST_Tool_Security_level_Window:

#if (UART_GUI == ONE_VALUE)
		Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("ZR        Invalid Security Level\n"));
#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Invalid Security Level", Font_7x10, RED,BLACK);
		break;

	case ST_Tool_UDS_Send_Req: //if the Car responded with invalid Frame or if the time limit is exceeded
#if (UART_GUI == ONE_VALUE)

		Usart_enuTransmitStringBlocking(&Usart1, (uint8*)("ZR        Communication Error\n"));
#endif
		ST7735_SetRotation(0);
		HTFT_voidFillColor(BLACK);
		ST7735_SetRotation(1);
		ST7735_WriteString(10, 10, "Communication Error", Font_7x10, RED,BLACK);
		break;
	default : break;
	}

	//time delay 2 sec
	OS_vTaskDelay(2000);
}

/*
 * to display security level response
 * to show Car data
 * to show negative responses
 */

void Tool_Display_Response(void)
{
	switch(Frame_Type)
	{
	case Security_Level1:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_SECURITY_ACCESS))
		{
			SCREEN_securityLevel1POS(1);
			Tool_Current_State = ST_Tool_Start_Window;

		}
		else
		{
			SCREEN_securityLevel1NEG(1);
			Tool_Current_State = ST_Tool_Security_level_Window;
		}
			//time delay 2 sec
			OS_vTaskDelay(2000);
			break;

	case Security_Level2:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_SECURITY_ACCESS))
		{
			SCREEN_securityLevel1POS(2);
			Tool_Current_State = ST_Tool_Start_Window;

		}
		else
		{
			SCREEN_securityLevel1NEG(2);
			Tool_Current_State = ST_Tool_Security_level_Window;

		}
			// wait 2 sec
			OS_vTaskDelay(2000);
			break;

	case Security_Level3:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_SECURITY_ACCESS))
		{
			SCREEN_securityLevel1POS(3);
			Tool_Current_State = ST_Tool_Start_Window;
		}
		else
		{
			SCREEN_securityLevel1NEG(3);
			Tool_Current_State = ST_Tool_Security_level_Window;
		}
			// wait 2 sec
			OS_vTaskDelay(2000);
			break;

	case Temperature_Read:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_READ_DATA_BY_IDENTIFIER))
		{
			SCREEN_Temp(G_ArrMessageData[4],G_ArrMessageData[3]);
			while(entered_key != 0)
			{

				KEYPAD_FindKey(&entered_key);
#if (UART_GUI == ONE_VALUE)

				if(Uart_Flag == ONE_VALUE){
					Uart_Flag = ZERO_VALUE;
					entered_key = Uart_Value;
				}
#endif
				OS_vTaskDelay(50);
			}
			entered_key = KEY_NOT_PRESSED;
		}
		else
		{
			// inform the user with unsuccessful process to read the temperature
			SCREEN_securityLevel1NEG(4);
			OS_vTaskDelay(2000);
		}
		Tool_Current_State = ST_Tool_Car_Options_Window;
		break;

	case Mirror_Read_State:
		if(G_UDS_SID == RSID_POSITIVE_RESPONSE + SID_READ_DATA_BY_IDENTIFIER)
		{
			SCREEN_Mirror(G_ArrMessageData[4],G_ArrMessageData[3]);

			while(entered_key != 0)
			{
				KEYPAD_FindKey(&entered_key);

#if (UART_GUI == ONE_VALUE)

				if(Uart_Flag == ONE_VALUE){
					Uart_Flag = ZERO_VALUE;
					entered_key = Uart_Value;
				}
#endif
				OS_vTaskDelay(50);
			}
			entered_key = KEY_NOT_PRESSED;
		}
		else
		{
			// inform the user with unsuccessful process to read the mirror state
			SCREEN_securityLevel1NEG(5);
			OS_vTaskDelay(2000);
		}
		Tool_Current_State = ST_Tool_Car_Options_Window;
		break;

	case Feature_Enable:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_WRITE_DATA_BY_IDENTIFIER))
		{
			SCREEN_securityLevel1POS(4);
			Tool_Current_State = ST_Tool_Start_Window;
		}
		else
		{
			SCREEN_securityLevel1NEG(6);
			Tool_Current_State = ST_Tool_Car_Options_Window;
		}
			// wait 2 sec
			OS_vTaskDelay(2000);
			break;

	case Feature_Disable:
		if(G_UDS_SID == (RSID_POSITIVE_RESPONSE + SID_WRITE_DATA_BY_IDENTIFIER))
		{
			SCREEN_securityLevel1POS(5);
			Tool_Current_State = ST_Tool_Start_Window;
		}
		else
		{
			SCREEN_securityLevel1NEG(7);
			Tool_Current_State = ST_Tool_Car_Options_Window;
		}
			// wait 2 sec
			OS_vTaskDelay(2000);
			break;

	}
}

void Tool_Keypad_Read(void)
{
	KEYPAD_FindKey(&entered_key);
	if(Uart_Flag == ONE_VALUE){
		Uart_Flag = ZERO_VALUE;
		entered_key = Uart_Value;
	}

	if(Tool_Current_State == ST_Tool_Start_Window)
	{
		switch(entered_key)
		{
		case 0:
		case KEY_NOT_PRESSED:
			Tool_Current_State = ST_Tool_Start_Window;
			break;

		case 1:
			Tool_Current_State = ST_Tool_Security_level_Window;
			break;

		case 2:
			Tool_Current_State = ST_Tool_Car_Options_Window;
			break;

		default:
			Tool_Error_Messages();
			break;
		}
	}
	else if(Tool_Current_State == ST_Tool_Security_level_Window)
	{
		switch(entered_key)
		{
		case 0:
			Tool_Current_State = ST_Tool_Start_Window;
			break;

		case 1:
			Frame_Type = Security_Level1;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case 2:
			Frame_Type = Security_Level2;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case 3:
			Frame_Type = Security_Level3;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case KEY_NOT_PRESSED:
			Tool_Current_State = ST_Tool_Security_level_Window;
			break;

		default:
			Tool_Error_Messages();
			break;
		}
	}
	else if(Tool_Current_State == ST_Tool_Car_Options_Window)
	{
		switch(entered_key)
		{
		case 0:
			Tool_Current_State = ST_Tool_Start_Window;
			break;

		case 1:
			Frame_Type = Temperature_Read;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case 2:
			Frame_Type = Mirror_Read_State;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case 3:
			Frame_Type = Feature_Enable;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;
		case 4:
			Frame_Type = Feature_Disable;
			Tool_Current_State = ST_Tool_UDS_Send_Req;
			break;

		case KEY_NOT_PRESSED:
			Tool_Current_State = ST_Tool_Car_Options_Window;
			break;

		default:
			Tool_Error_Messages();
			break;
		}
	}

	OS_vTaskDelay(50);
}

void UDS_Isr_CallBack(Can_MessageType* Receive_Message, uint8_t ArrMessageData[8], uint8_t Copy_uint8FilterIndex)
{
	/*Set flag to be handled in TFT function*/
	Communication_State = Data_recieved;

	G_Receive_Message = *Receive_Message;

	for(uint8 i=0;i < Receive_Message->can_DLC_FROM_0_TO_8;++i)
	{
		G_ArrMessageData[i] = ArrMessageData[i];
	}
	G_UDS_SID    = G_ArrMessageData[0] ;
	G_UDS_SubFun = G_ArrMessageData[1] ;
	G_UDS_DID    = G_ArrMessageData[2] ;
	G_UDS_DATA   = *((uint32*)(G_ArrMessageData+3)) ;

	G_Copy_uint8FilterIndex = Copy_uint8FilterIndex;
}


void Usart_Isr(uint16 Copy_u16Result){

	Uart_Flag = ONE_VALUE;
	Uart_Value = Copy_u16Result;
}
