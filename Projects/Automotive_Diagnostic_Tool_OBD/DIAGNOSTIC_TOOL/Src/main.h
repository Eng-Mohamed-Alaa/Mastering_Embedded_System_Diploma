/*
 * main_Tasks.h
 *
 *  Created on: Nov 30, 2023
 *      Author: computer store
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../Inc/MCAL/RCC/RCC.h"
#include "../Inc/MCAL/GPIO/GPIO.h"
#include "../Inc/MCAL/SPI/SPI_interface.h"

#include "../Inc/MCAL/UART/USART.h"


#include "../Inc/HAL/TFT/fonts.h"
#include "../Inc/HAL/TFT/TFT_interface.h"
#include "../Inc/HAL/KEYPAD/KEYPAD.h"
#include "../Inc/HAL/UDS/UDS.h"
#include "OS_Rupper/OS_Rupper.h"
#include "screens.h"


/*** OS Priorities ***/
#define First_Priority 			4
#define Second_Priority 		3
#define Third_Priority 			2
#define Fourth_Priority 		1

/*Tasks priorities*/
#define Tool_TFT_Task_Priority				First_Priority
#define Tool_Keypad_Task_Priority			Second_Priority


/* Define DIDs */
#define APP_TEMPERATURE_DID				(0xB1)
#define APP_MIRROR_STATE				(0xA1)



//======================================================================
//Global variables
//======================================================================
Can_MessageType G_Receive_Message;
uint8 G_ArrMessageData[8];
uint8  G_UDS_SID;
uint8  G_UDS_SubFun;
uint8  G_UDS_DID;
uint32 G_UDS_DATA;


uint8 Uart_Flag= ZERO_VALUE;
uint8 Uart_Value = ZERO_VALUE;
extern Usart_ConfigType Usart1;



uint8 G_Copy_uint8FilterIndex;
uint8 entered_key = KEY_NOT_PRESSED;
OS_xTaskHandle Tool_TFT_Handle = NULL;
OS_xTaskHandle Tool_Keypad_Handle = NULL;

enum {
	ST_Tool_Start_Window,
	ST_Tool_Security_level_Window,
	ST_Tool_Car_Options_Window,
	ST_Tool_Display_Response,
	ST_Tool_UDS_Send_Req,
}Tool_Current_State = ST_Tool_Start_Window;

enum
{
	Data_recieved,
	Data_not_recieved,
} Communication_State = Data_not_recieved;

enum{
	Temperature_Read,
	Mirror_Read_State,
	Security_Level1,
	Security_Level2,
	Security_Level3,
	Feature_Enable,
	Feature_Disable,
} Frame_Type = Temperature_Read;


/*TASKS Prototypes*/
 void Tool_Control_Task(void* Param);

void Tool_Init(void);
void Tool_Start_Window(void);
void Tool_Security_level_Window(void);
void Tool_Car_Options_Window(void);
void Tool_UDS_Send_Req(void);
void Tool_Display_Response(void);
void Tool_Error_Messages(void);
void Tool_Keypad_Read(void);
void UDS_Isr_CallBack(Can_MessageType* Receive_Message, uint8_t ArrMessageData[8], uint8_t Copy_uint8FilterIndex);
void Tool_Communication_Check(void);
void State_Manager(void);
void Usart_Isr(uint16 Copy_u16Result);


#endif /* MAIN_H_ */
