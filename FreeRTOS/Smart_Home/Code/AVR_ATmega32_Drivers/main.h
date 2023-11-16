
#ifndef MAIN_H_
#define MAIN_H_


//===========================================================
//Includes
//===========================================================
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "semphr.h"
#include <MCAL/DIO/DIO_Includes/DIO.h>
#include <MCAL/PORT/PORT_Includes/Port.h>
#include <HAL/Keypad/Keypad_Includes/Keypad.h>
#include <HAL/LCD/LCD_Includes/LCD.h>
#include <MCAL/ADC/ADC_Includes/ADC.h>
#include <HAL/LM35_Sensor/LM35_Includes/lm35_sensor.h>

//===========================================================
//Macros
//===========================================================
#define System_Password					1234
#define Temperature_Threshold			60

#define OS_LCD_Init_PRI					3
#define OS_LCD_Display_PRI				2
#define System_Control_PRI				1
#define OS_Read_Temp_PRI				0

#define LED1_PORT						PORTA_ADD
#define LED1_PIN						PORT_PIN3

#define	Motor_PORT						PORTA_ADD
#define Motor_PIN						PORT_PIN4

#define	ALarm_PORT						PORTA_ADD
#define ALarm_PIN						PORT_PIN5

//===========================================================
//user defined data types (tasks states)
//===========================================================
enum{
	LCD_Step0,
	LCD_Step1,
	LCD_Step2,
	LCD_Step3
	}LCD_Init_State = LCD_Step0;
	
enum{
	LCD_Write_string,
	LCD_Write_Clear,
	LCD_Wait,
}LCD_Run_State = LCD_Wait;

enum{
	System_Get_Password,
	System_Main_Menu,
	System_Current_Temp,
	System_Desired_Temp,
	System_LED_Control,
	System_Get_input
}System_State = System_Get_Password;


//===========================================================
//Global variables
//===========================================================
uint8 LCD_Init_Flag = 1;


uint8 Current_Temperature = 0;
uint8 Desired_Temperature = 150;		//this will not make the motor work  until the user log in and set the desired temperature as the maximum value of the temperature to be measured is 150
										

QueueHandle_t LCD_Queue1;

xTaskHandle OS_LCD_Init_Handle = PTR_NULL;
xTaskHandle OS_Read_Temp_Handle = PTR_NULL;
xTaskHandle OS_LCD_Display_Char_Handle = PTR_NULL;
xTaskHandle System_Control_Handle = PTR_NULL;

xSemaphoreHandle LCD_Queue1_Semaphore = PTR_NULL;

//===========================================================
//Prototypes
//===========================================================
void Init(void);
void Create_Tasks(void);
void OS_LCD_Init(void* pvParamter);
void OS_Read_Temp(void* pvParamter);
void OS_LCD_Display(void* pvParamter);
void System_Control(void* pvParamter);
void Add_Message(char *message);
void OS_LCD_GoTO_XY(uint8 Line, uint8 Column);
#endif /* MAIN_H_ */