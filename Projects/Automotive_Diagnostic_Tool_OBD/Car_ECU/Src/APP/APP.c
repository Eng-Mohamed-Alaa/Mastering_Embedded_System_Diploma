/*
 * APP.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Tariq
 */

/*Services Includes*/
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

/*MCAL Includes*/
#include "../Inc/MCAL/RCC/RCC.h"
#include "../Inc/MCAL/GPIO/GPIO.h"
#include "../Inc/MCAL/CAN/CAN.h"
#include "../Inc/MCAL/UART/USART.h"
#include "../Inc/MCAL/NVIC/NVIC.h"
#include "../INC/MCAL/EXTI/EXTI.h"
#include "../INC/MCAL/AFIO/AFIO_interface.h"

/*HAL includes*/
#include "../Inc/HAL/UDS/UDS.h"
#include "../Inc/HAL/LM35/LM35.h"
#include "../Inc/HAL/CAR_DC_MOTORS/CAR_DC_MOTORS.h"
#include "HAL/Servo_Motor/Servo_Motor.h"
#include "../Inc/HAL/EEPROM/EEPROM.h"
#include "HAL/Mirror/Mirror.h"
#include "HAL/LED/LED.h"
#include "../Inc/HAL/HC_05/HC_05.h"
#include "HAL/NVRAM/NVRAM.h"

/*APP includes*/
#include "../Inc/APP/APP.h"

/* OS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"


////LED feature configuration variable
//const uint16 LED_Feature = 0;
//#define LED_Feature_Value 		(*(uint16 *) &LED_Feature)

#define LED_Feature 			((*(uint16 *) 0x800FC00))
#define LED_Feature_Value 		(*(uint16 *) 0x800FC00)




/*LM35 Global Variables*/
uint8 Global_u8Number_Of_lm35_readings  = 10 ;
uint8 Global_u8Temperature;

/*Mirror global variables*/
Mirror_State_t	Desired_Mirror_State = Mirror_ST_Closed;
Mirror_State_t	Actual_Mirror_State = Mirror_ST_Closed;



/*Tasks Handlers*/
xTaskHandle LM35_Handle = NULL;
xTaskHandle CAR_MOVE_Handle = NULL;
xTaskHandle Car_Mirror_Check_Handle = NULL;
xTaskHandle TEMP_Handle = NULL;

/*Semaphores*/
SemaphoreHandle_t EEPROM_Semaphore;


void APP_vidInit(void)
{
	//enable HSE and select it as the system clock for higher accuracy and disable the HSI to save power
	Rcc_enuControlCLk(RCC_CNTROL_HSION,RCC_CNTROL_HSEON,RCC_CNTROL_PLLON);
	Rcc_enuSelectSysCLk(RCC_CLK_HSE,RCC_STATE_PRESERVE);

	/*System Drivers Initialization*/
	lm35_VidInit();
	CAR_DC_MOTORS_vidInit();
	Mirror_Init();
	EEPROM_INIT();
	UDS_VoidInit();


	/*Tasks Creation*/
	xTaskCreate(LM35_TCode,"LM35_TASK",128,NULL,LM35_TASK_Priority,&LM35_Handle);					//Temperature Reading from LM35 Task Creation
	xTaskCreate(CAR_MOVE_TCode,"MOVE_CAR_TASK",128,NULL,Move_Car_Task_Priority,&CAR_MOVE_Handle);	//Creation of a TASK Responsible of Car movements
	xTaskCreate(Car_Mirror_Check,"Mirror_Task",128,NULL,Car_Mirror_Check_Priority,&Car_Mirror_Check_Handle); //Creation of a Task Responsible for checking any mirror errors

	/*create Semaphore for the EEPROM*/
	EEPROM_Semaphore = xSemaphoreCreateBinary();

	if(LED_Feature_Value == Feature_Unlocked)
	{
		LED_Init();

	}
	else
	{

		LED_DeInit();

	}
}


//=========================== LM35 Task Implementation =================================/
void LM35_TCode(Pv Param)
{
	for(;;)
	{

		static uint8  Static_u8Entry_Count = 0;
		static uint16 Static_u16Temperature_readings_accumlator = 0;
		static uint16  Static_Temp_u16 = 0;
		static uint16 prevloccheck=0;
		static uint8 Loc_u8FirstTime = ONE_VALUE;
		Static_u8Entry_Count++;
		if(Static_u8Entry_Count <= Global_u8Number_Of_lm35_readings)
		{
			Static_u16Temperature_readings_accumlator += lm35_u16Read(Dont_care_value,&Static_Temp_u16);
			Static_Temp_u16 = 0 ;
		}
		else
		{

			Global_u8Temperature = Static_u16Temperature_readings_accumlator/Global_u8Number_Of_lm35_readings;

			if( (Global_u8Temperature >prevloccheck &&Global_u8Temperature-prevloccheck>1) ||
					((Global_u8Temperature<prevloccheck&&prevloccheck-Global_u8Temperature>1)   ) ||
					Loc_u8FirstTime == ONE_VALUE)

			{
				Loc_u8FirstTime = ZERO_VALUE;
				if(Global_u8Temperature > Normal_Temperature_Threshold)
				{
					while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

					//Store DTC (Diagnostic Trouble Code) in EEPROM
					EEPROM_Write_byte(Car_Temperature_DTC_Address, Car_Temperature_DTC_Value);
					vTaskDelay(10);
					xSemaphoreGive( EEPROM_Semaphore);
				}
				else
				{
					while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

					//Clear DTC
					EEPROM_Write_byte(Car_Temperature_DTC_Address, DTC_Clear);
					vTaskDelay(10);
					xSemaphoreGive( EEPROM_Semaphore);
				}

				while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

				EEPROM_Write_byte(Car_Temperature_DTC_Address+1, Global_u8Temperature);
				vTaskDelay(10);
				prevloccheck=Global_u8Temperature;
				xSemaphoreGive( EEPROM_Semaphore);
			}
			Static_u16Temperature_readings_accumlator &= 0x0000;
			Static_u8Entry_Count &= 0x00;

		}

		vTaskDelay(LM35_TASK_DELAY);

	}

}

//=================================== MOVE CAR TASK Implementation =============================/
void CAR_MOVE_TCode(Pv Param)
{
	for(;;)
	{
		static uint8 static_u8_recieved_char = 0;
		static_u8_recieved_char = (uint8) HC05_u8Recieve();



		switch(static_u8_recieved_char)
		{
		case 'F':


			CAR_vidMove_Forward();
			break;
		case 'B':
			CAR_vidMove_Backward();
			break;
		case 'G':
			CAR_vidTurn_Right();
			break;
		case 'I':
			CAR_vidTurn_Left();
			break;
		case 'W': //STOP LEFT
			CAR_vid_Stop_with_Steering_turned_left();
			break;
		case 'w': //STOP Right
			CAR_vid_Stop_with_Steering_turned_right();
			break;
		case 'L':
			Mirror_Open();
			Desired_Mirror_State = Mirror_ST_Open;
			break;
		case 'R':
			Mirror_Close();
			Desired_Mirror_State = Mirror_ST_Closed;
			break;
		case 'H':
			if(LED_Feature_Value == Feature_Unlocked)
				LED_On();
			break;
		case 'J':

			if(LED_Feature_Value == Feature_Unlocked)
				LED_OFF();
			break;
		default:
			CAR_vid_Stop();
			Servo_Stop();
			break;

		}
		vTaskDelay(Move_Car_Task_Delay);
	}
}



/*=================================== Mirror check TASK Implementation ===================================*/

void Car_Mirror_Check(void* Param)
{
	while(1)
	{
		static uint8 prevstate = Mirror_ST_Closed;
		static uint8 Loc_u8FirstTime = ONE_VALUE;

		Actual_Mirror_State = Mirror_Get_State();
		if( (prevstate != Actual_Mirror_State) || (Loc_u8FirstTime == ONE_VALUE))
		{

			if(Actual_Mirror_State != Desired_Mirror_State)
			{
				while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

				Loc_u8FirstTime = ZERO_VALUE;
				//store the mirror DTC in the EEPROM
				EEPROM_Write_byte(Car_Mirror_DTC_Address, Car_Mirror_DTC_Value);
				vTaskDelay(10);
				xSemaphoreGive(EEPROM_Semaphore);
			}
			else
			{
				while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

				//clear the mirror DTC in the EEPROM
				EEPROM_Write_byte(Car_Mirror_DTC_Address, DTC_Clear);
				vTaskDelay(10);
				xSemaphoreGive(EEPROM_Semaphore);
			}

			while(xSemaphoreTake(EEPROM_Semaphore, ( TickType_t )10) != pdTRUE);

			EEPROM_Write_byte(Car_Mirror_DTC_Address+1, Actual_Mirror_State);
			vTaskDelay(10);
			prevstate=Actual_Mirror_State;
			xSemaphoreGive(EEPROM_Semaphore);
		}
		vTaskDelay(Car_Mirror_Check_Delay);
	}
}



