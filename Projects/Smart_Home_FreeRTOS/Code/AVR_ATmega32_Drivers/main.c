#include <main.h>

int main(void)
{
	//initialize all the PORTs
	PORT_Init();
	//initialize the keypad
	Keypad_Init();
	//initialize the ADC
	ADC_Config_t PS_ADC_Config = {PTR_NULL,ADC_VREF_AVCC, ADC_Channel_ADC0, ADC_Auto_Trigger_Disable, ADC_Interrupt_State_Disable, ADC_Prescale_64, ADC_Trigger_Free};
	ADC_Set_Config(&PS_ADC_Config);
	
	//Create 3 tasks to initialize the LCD, Display on the LCD, Control the System respectively
 	xTaskCreate(OS_LCD_Init,(const char*)"Task0",85,PTR_NULL,OS_LCD_Init_PRI,&OS_LCD_Init_Handle);
	xTaskCreate(OS_LCD_Display,(const char*)"Task1",85,PTR_NULL,OS_LCD_Display_PRI,&OS_LCD_Display_Char_Handle);
	xTaskCreate(System_Control,(const char*)"Task2",85,PTR_NULL,System_Control_PRI,&System_Control_Handle);
	
	//this task is created here because it's related to life safety because it measures the temperature and give an alarm if (Temperature_Threshold < Current_Temperature)
	//also the motor of the fan or air conditioner will not start until the user login and set the desired temperature within the accepted range from (15 to 40)
	//if you want the alarm to work after login create this task inside the System_Control task when password equals to system password
	xTaskCreate(OS_Read_Temp,(const char*)"Task3",85,PTR_NULL,OS_Read_Temp_PRI,&OS_Read_Temp_Handle);
	
	//create Semaphore for the LCD_Queue1
	vSemaphoreCreateBinary(LCD_Queue1_Semaphore);

	//Call the OS scheduler to control the tasks of the Program
	vTaskStartScheduler();
}

void OS_LCD_Init(void* pvParamter)
{

	//this loop will initialize the LCD
	while(LCD_Init_Flag)
	{
		switch(LCD_Init_State)
		{
			case LCD_Step0:
			LCD_Send_Command(LCD_8Bit);
			LCD_Kick1();
			vTaskDelay(1);	//time delay 1ms
			LCD_Kick2();
			LCD_Init_State = LCD_Step1;
			break;
			
			case LCD_Step1:
			LCD_Send_Command(LCD_Display_On);
			LCD_Kick1();
			vTaskDelay(1);	//time delay 1ms
			LCD_Kick2();
			LCD_Init_State = LCD_Step2;
			break;

			case LCD_Step2:
			LCD_Send_Command(LCD_Display_Clear);
			LCD_Kick1();
			vTaskDelay(1);	//time delay 1ms
			LCD_Kick2();
			vTaskDelay(4);
			LCD_Init_State = LCD_Step3;
			break;
			
			case LCD_Step3:
			LCD_Send_Command(LCD_Shift_Cursor_Disp_fix);
			LCD_Kick1();
			vTaskDelay(1);	//time delay 1ms
			LCD_Kick2();
			vTaskDelay(1);
 			LCD_Init_Flag = 0;	//this flag indicates that the LCD initialization is done successfully
			break;
		}
	}
	
	//create a queue to store the string to be displayed on the LCD 
	LCD_Queue1 = xQueueCreate(20, sizeof(uint8));
	
	//insert the string into the queue
	Add_Message("Enter Password: ");
	
	//set the state for the LCD
	LCD_Run_State = LCD_Write_string;
	
	//LCD initialization is completed and the task goes to the waiting state and it will be deleted in task (OS_LCD_Display)
	vTaskDelay(10);
}


void OS_LCD_Display(void* pvParamter)
{
	vTaskDelay(15); //wait 15ms for LCD_Init to be complete
	
	//delete task (OS_LCD_Init)
	if( OS_LCD_Init_Handle != PTR_NULL && LCD_Init_Flag == 0)
	{
		vTaskDelete( OS_LCD_Init_Handle );
	}
	
	uint8 data = 0;
	BaseType_t LCD_Queue1_State = pdPASS;
	portTickType Freq = 20; //the task periodicity in the wait state
	portTickType Start = xTaskGetTickCount();
	while (1)
	{
		switch(LCD_Run_State)
		{
			case LCD_Write_string:		//display the string stored in LCD_Queue1
			if (pdTRUE == xSemaphoreTake(LCD_Queue1_Semaphore,10)) 	//only one task can access the queue to read or write at a time
			{
				while(1)				//continue printing as long as the queue is not empty
				{
					LCD_Queue1_State = xQueueReceive(LCD_Queue1,&data,0);
					if (LCD_Queue1_State == pdPASS)
					{
						LCD_Display_Character(data);
						LCD_Kick1();
						vTaskDelay(1);
						LCD_Kick2();
					}
					else
					{
						LCD_Run_State = LCD_Wait;	//when the queue is empty go to the wait state
						break;
					}
				}
				xSemaphoreGive(LCD_Queue1_Semaphore); //make LCD_Queue1_Semaphore available for the next usage
			}
			break;
			
			case LCD_Write_Clear:	//clear the LCD for the next Display
			LCD_Send_Command(LCD_Display_Clear);
			LCD_Kick1();
			vTaskDelay(1);
			LCD_Kick2();
			vTaskDelay(1);
			break;
			
			case LCD_Wait:			//waiting for a change in the state to take action (Clear or Display)
			vTaskDelayUntil(&Start,Freq);
			break;
		}
	}
}

void System_Control(void* pvParamter)
{
	uint8 Temp_Copy = Desired_Temperature;
	vTaskDelay(15);	 //wait 15ms for LCD_Init to be completed
	uint16 Password = 0;
	uint16 Button = 'N';
	while(1)
	{
		if (System_State == System_Get_Password) //the default state when the system start
		{
			Button = Keypad_Read_Character(Keypad_Read_Single_Press);
			if( '0' <= Button && Button <= '9')
			{
				LCD_Display_Character(Button); //simple case no need to make a semaphore for the LCD
				LCD_Kick1();
				vTaskDelay(1);
				LCD_Kick2();
				Password *= 10;
				Password += (Button -'0');
			}
			else if (Button == '=') //end of the Password
			{
				if (Password == System_Password) //correct password
				{
					System_State = System_Main_Menu;	//move the system state to System_Main_Menu to display the features that the user can monitor and control
				}
				else //handling for a wrong password
				{
					Add_Message("Invalid Input");	
					LCD_Run_State = LCD_Write_Clear;
					vTaskDelay(30);
					LCD_Run_State = LCD_Write_string;
					vTaskDelay(1000);
					Add_Message("Enter Password: ");
					LCD_Run_State = LCD_Write_Clear;
					vTaskDelay(30);
					LCD_Run_State = LCD_Write_string;
				}
				Password = 0;
			}
		}	
		else if(System_State == System_Main_Menu) //display the features that the user can monitor and control
		{
			LCD_Run_State = LCD_Write_Clear;
			vTaskDelay(30); //give a window of 30ms to OS_LCD_Display task to clear the screen
			Add_Message("1) Current Temp");
			LCD_Run_State = LCD_Write_string;
			vTaskDelay(40); //give a window of 40ms to OS_LCD_Display task to display the string
			OS_LCD_GoTO_XY(LCD_Line2, LCD_Col1);
			Add_Message("2) Desired Temp");
			LCD_Run_State = LCD_Write_string;
			vTaskDelay(40);
			OS_LCD_GoTO_XY(LCD_Line3, LCD_Col1);
			Add_Message("3) LED control");
			LCD_Run_State = LCD_Write_string;
			vTaskDelay(40);
			System_State = System_Get_input;	//move the system state to System_Get_input get input from the user for which feature to access
		}
		else if(System_State == System_Get_input) //this state works after System_Main_Menu state to get input from the user for which feature he wants to access
		{
			Button = Keypad_Read_Character(Keypad_Read_Single_Press);
			switch(Button)
			{
				case '1': //"1) Current Temp"
				System_State = System_Current_Temp; //update the system state to allow the OS_Read_Temp task to display the actual current temperature measured by the sensor to the user
				vTaskDelay(2000); //give a window of two seconds to display the actual current temperature
				System_State = System_Main_Menu; //return to the System_Main_Menu state
				break;
				
				case '2': //"2) Desired Temp"
				Temp_Copy = 0;
				LCD_Run_State = LCD_Write_Clear; //clear the LCD
				vTaskDelay(30); //give a window of 30ms to OS_LCD_Display task to clear the screen
				Add_Message("Desired Temp: ");
				LCD_Run_State = LCD_Write_string;
				vTaskDelay(40); //give a window of 40ms to OS_LCD_Display task to display the string
				System_State = System_Desired_Temp; //move the System_State to System_Desired_Temp to read the desired temperature from the user
				break;
				
				case '3': //"3) LED control"
				LCD_Run_State = LCD_Write_Clear;
				vTaskDelay(30);
				Add_Message("Enter 1/0: ");
				LCD_Run_State = LCD_Write_string;
				vTaskDelay(40);
				System_State = System_LED_Control; //move the System_State to System_LED_Control to read user input 1/0 to turn on/off the LED respectively 
				break;
				
				default: //invalid input
				if(Button != 'N') //'N' means no button is pressed
				{
					LCD_Run_State = LCD_Write_Clear;
					vTaskDelay(30);
					Add_Message("Invalid Input");
					LCD_Run_State = LCD_Write_string;
					vTaskDelay(1000); //display the message for 1 second
					System_State = System_Main_Menu;
				}
				
				break;
			}
		}
		else if(System_State == System_Desired_Temp) //read the desired temperature from the user
		{
			Button = Keypad_Read_Character(Keypad_Read_Single_Press);
			if( '0' <= Button && Button <= '9')
			{
				LCD_Display_Character(Button);
				LCD_Kick1();
				vTaskDelay(1);
				LCD_Kick2();
				Temp_Copy *= 10;
				Temp_Copy += (Button -'0');
			}
			else if (Button == '=')	//the desired temperature is inserted
			{
				//handling wrong input for the desired temperature as in a real application the desired temperature must have limits because no motor can support any temperature
				if( 15 > Temp_Copy || Temp_Copy > 40 ) 
				{
					Add_Message("Invalid Input");
					LCD_Run_State = LCD_Write_Clear;
					vTaskDelay(30);
					LCD_Run_State = LCD_Write_string;
					vTaskDelay(1000);
				}
				else  //correct input for the desired temperature so update the Desired_Temperature value
				{
					Desired_Temperature = Temp_Copy;
				}
				System_State = System_Main_Menu;	//return back to the main menu
			}
		}
		else if(System_State == System_LED_Control) //read the user input 1/0 to turn on/off the LED respectively
		{
			Button = Keypad_Read_Character(Keypad_Read_Single_Press);
			if (Button == '1' || Button == '0') //other inputs will be ignored and the system remain in the System_Led_Control state
			{
				LCD_Display_Character(Button);
				LCD_Kick1();
				vTaskDelay(1);
				LCD_Kick2();
				DIO_Write_Channel(LED1_PORT, LED1_PIN,(Button - '0')); 		//LED (on/off)
				System_State = System_Main_Menu;	//return to the System_Main_Menu state if the user entered 1 or 0
			}
		}

		vTaskDelay(160); //Periodicity to read pressed buttons from the user
	}
}

void OS_Read_Temp(void* pvParamter)
{
	vTaskDelay(15);
	while (1)
	{

		uint8 Temp_Arr[20] = "Current Temp: ";	
		uint8 Temp_Index = 13;
		uint8 Cnt_Temp_Digits = 0;
		LM35_getTemperature(&Current_Temperature);
		uint8 Temp_Copy = Current_Temperature;		
		//if Temperature != 0, calculate the number of digits
		while(Temp_Copy)
		{
			Temp_Copy /= 10;
			Cnt_Temp_Digits++;
		}
		Temp_Copy = Current_Temperature;
		//if Temperature != 0, store the the Temperature in the array
		while(Cnt_Temp_Digits)
		{
			Temp_Arr[Temp_Index+Cnt_Temp_Digits] = (Temp_Copy%10)+'0';
			Temp_Copy /= 10;
			Cnt_Temp_Digits--;
		}
		
		//to control the Motor of the Fan or Air conditioner in case (Desired_Temperature < Current_Temperature) 
		uint8 Motor_Alarm_State = (Desired_Temperature < Current_Temperature) ;
		DIO_Write_Channel(Motor_PORT, Motor_PIN, Motor_Alarm_State);
		
		//to control the alarm in case of very high temperature (Temperature_Threshold < Current_Temperature)
		Motor_Alarm_State = (Temperature_Threshold < Current_Temperature);
		DIO_Write_Channel(ALarm_PORT, ALarm_PIN, Motor_Alarm_State);

		if(System_State == System_Current_Temp)
		{
			Add_Message((char*)Temp_Arr);
			LCD_Run_State = LCD_Write_Clear;
			vTaskDelay(30);
			LCD_Run_State = LCD_Write_string;
			vTaskDelay(2000);//when the user wants to see the current temperature the last measured one will be displayed for two seconds without update
		}
		vTaskDelay(20);  // periodicity to read the temperature from the sensor and to control the motor and the alarm as long as user not reading the the current temperature 
	}
}

void Add_Message(char *message) //inset the message into the queue to be printed by the LCD
{
	//only one task can access the queue to read or write at a time
	if (pdTRUE == xSemaphoreTake(LCD_Queue1_Semaphore,10))
	{
		for(uint8 cnt=0; message[cnt]; cnt++)
		{
			xQueueSend(LCD_Queue1, &message[cnt], 10);
		}
		xSemaphoreGive(LCD_Queue1_Semaphore); //make LCD_Queue1_Semaphore available for the next usage
	}
}

void OS_LCD_GoTO_XY(uint8 Line, uint8 Column) //move to certain line and column in the LCD
{
	LCD_GoTO_XY(Line, Column);
	LCD_Kick1();
	vTaskDelay(1);	//time delay 1ms
	LCD_Kick2();
}