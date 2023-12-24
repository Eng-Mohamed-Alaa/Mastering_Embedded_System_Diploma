/***************************************************************/
/* Author    : Mahmoud Korayem                                    */
/* Version   : V01                                             */
/* Date      : 25 NOV 2022                                     */
/***************************************************************/
//#include "../../services/Bit_utils.h"
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../Inc/MCAL/GPIO/GPIO.h"
#include "../Inc/HAL/KEYPAD/KEYPAD_private.h"
#include "../Inc/HAL/KEYPAD/KEYPAD_cfg.h"
#include "../Inc/HAL/KEYPAD/KEYPAD.h"

#define ERROR_FREE 9

void KEYPAD_voidInit(void)
{
	GPIO_Port_Enable_clock(GPIO_PORT_B);

	GPIO_PIN_INIT(KEY_RAW0,KEY_RAW0_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	GPIO_PIN_INIT(KEY_RAW1,KEY_RAW1_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	GPIO_PIN_INIT(KEY_RAW2,KEY_RAW2_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);
	GPIO_PIN_INIT(KEY_RAW3,KEY_RAW3_PORT,output_push_pull,GPIO_max_speed_2_MHz,pull_UP);

	GPIO_PIN_INIT(KEY_COL0,KEY_COL0_PORT,Input_pull_up_down,GPIO_INPUT,pull_UP);
	GPIO_PIN_INIT(KEY_COL1,KEY_COL1_PORT,Input_pull_up_down,GPIO_INPUT,pull_UP);
	GPIO_PIN_INIT(KEY_COL2,KEY_COL2_PORT,Input_pull_up_down,GPIO_INPUT,pull_UP);
	GPIO_PIN_INIT(KEY_COL3,KEY_COL3_PORT,Input_pull_up_down,GPIO_INPUT,pull_UP);

}
void KEYPAD_WritrPins(uint8 value)
{
	GPIO_set_PIN_value(KEY_RAW0,KEY_RAW0_PORT,GET_BIT(value,0));
	GPIO_set_PIN_value(KEY_RAW1,KEY_RAW1_PORT,GET_BIT(value,1));
	GPIO_set_PIN_value(KEY_RAW2,KEY_RAW2_PORT,GET_BIT(value,2));
	GPIO_set_PIN_value(KEY_RAW3,KEY_RAW3_PORT,GET_BIT(value,3));
}

void KEYPAD_ReadPins(uint8 *value)
{
	uint8 loc_read=0;
	GPIO_get_PIN_value(KEY_COL0,KEY_COL0_PORT,&loc_read);
	*value=loc_read;
	GPIO_get_PIN_value(KEY_COL1,KEY_COL1_PORT,&loc_read);
	*value|=(loc_read<<1);
	GPIO_get_PIN_value(KEY_COL2,KEY_COL2_PORT,&loc_read);
	*value|=(loc_read<<2);
	GPIO_get_PIN_value(KEY_COL3,KEY_COL3_PORT,&loc_read);
	*value|=(loc_read<<3);

}	
ERROR_KEYPAD_STATUS KEYPAD_FindKey(uint8 *Loc_keyPress)
{
  ERROR_KEYPAD_STATUS ERROR_KEYPAD_RET=ERROR_FREE;
	    uint8 temp=0x00;
	    uint8 reg;
	    for(uint8 i=0;i<RAW_NUM;i++)
	    {
		    reg=0x0F;
		    KEYPAD_WritrPins(TGLWITHOUTASSIGN_BIT(reg,i));
		    KEYPAD_ReadPins(&temp);
		    switch(temp)
		    {
			    case 0b1110:
			    *Loc_keyPress=KEYPAD_SYMBOL[(4*i)+0];
				while(temp == 0b1110)
				{
				KEYPAD_ReadPins(&temp);
				}
			    break;
			    case 0b1101:
			    *Loc_keyPress=KEYPAD_SYMBOL[(4*i)+1];
				while(temp == 0b1101)				
				{
					KEYPAD_ReadPins(&temp);
				}				
			    break;
			    case 0b1011:
			    *Loc_keyPress=KEYPAD_SYMBOL[(4*i)+2];
				while(temp == 0b1011 )
				{
					KEYPAD_ReadPins(&temp);
				}				
			    break;
			    case 0b0111:
			    *Loc_keyPress=KEYPAD_SYMBOL[(4*i)+3];
				while(temp == 0b0111)
				{
					KEYPAD_ReadPins(&temp);
				}				
			    break;
			    default:
			    ERROR_KEYPAD_RET = NO_KEY_PRESSED;
			    *Loc_keyPress = KEY_NOT_PRESSED;
			    break;
		    }
		    if(*Loc_keyPress!=KEY_NOT_PRESSED)
		    {
		    	break;
		    }
	    }
	return ERROR_KEYPAD_RET;

}
