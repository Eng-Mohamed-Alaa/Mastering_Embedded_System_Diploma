#include <memory_map.h>
#include <avr/io.h>
#include <LCD.h>
#include <Keypad.h>
#include <UART.h>
#include <string.h>
#include <stdint.h>
#include <SPI.h>
#include <I2C.h>
#include <Timer0.h>
#include <PWM0.h>
#include <ADC.h>

enum Value_to_show
{
	ADC_Reg,
	Voltage_Value,
	Voltage_Percenteage
};

ADC_Configurations_t ADC_CFG = {ADC_Left_Adjust_Result_Disable, ADC_V_Ref_Avcc, ADC_Sytem_CLK_divided_by_64, ADC_Interrupt_Disable, ADC_Auto_Trigger_None};


void ADC_Test(enum Value_to_show);


int main()
{
	LCD_INIT();
	ADC_Init(&ADC_CFG);
	while(1)
	{
		//ADC_Test(ADC_Reg);
 		ADC_Test(Voltage_Value);
 		//ADC_Test(Voltage_Percenteage);
	}
	return 0;
}
	

void ADC_Test(enum Value_to_show Test_value)
{
	uint32_t ADC_Data_Reg = 0, value = 0;
	ADC_Data_Reg = ADC_Read_Single_Conversion(ADC0);
	LCD_Clear_Screen();
	LCD_GOTO_XY(1,0);
	switch(Test_value)
	{
		case ADC_Reg:
			value = ADC_Data_Reg;
			LCD_WRITE_STRING((uint8_t*)"ADC_Reg: ");
			break;
			
		case Voltage_Value:
			value = ADC_Data_Reg*ADC_AVCC/(1 << ADC_Resoultion);	//voltage in mv
			LCD_WRITE_STRING((uint8_t*)"V(mv): ");
			break;
			
		case Voltage_Percenteage:
			value = (ADC_Data_Reg*100)/(1 << ADC_Resoultion);
			LCD_WRITE_STRING((uint8_t*)"V(%): ");
			break;
	}
	LCD_Write_Number(value);
	_delay_ms(500);
}

