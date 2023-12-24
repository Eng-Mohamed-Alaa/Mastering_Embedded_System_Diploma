/*
 * APP.h
 *
 *  Created on: Dec 5, 2023
 *      Author: Mahmoud Tariq
 */

#ifndef APP_APP_H_
#define APP_APP_H_


/*** OS Priorities ***/
#define First_Priority 			4
#define Second_Priority 		3
#define Third_Priority 			2
#define Fourth_Priority 		1


/* OS Wrappers */




/*#defs*/
#define Dont_care_value	   					1
#define Normal_Temperature_Threshold	    80
#define Feature_Unlocked					1
/*Tasks Periodicities*/
#define LM35_TASK_DELAY						20
#define Move_Car_Task_Delay					100
#define Car_Mirror_Check_Delay				1000

/*Tasks Priorities*/
#define Move_Car_Task_Priority				First_Priority
#define LM35_TASK_Priority		    		Second_Priority
#define Car_Mirror_Check_Priority			Third_Priority

/*DTC Address in EEPROM*/
#define Car_Mirror_DTC_Address				0xA1

#define Car_Temperature_DTC_Address			0xB1

/*DTC values*/
#define DTC_Clear							0
#define Car_Mirror_DTC_Value				1
#define Car_Temperature_DTC_Value			1





/*TASKS Prototypes*/
 void LM35_TCode(Pv Param);
 void CAR_MOVE_TCode(Pv Param);
 void Car_Mirror_Check(Pv Param);
 void TEMP(void* Param);





/*Functions ProtoTypes*/
void APP_vidInit(void);
void Car_Unlock_Led(void);




#endif /* APP_APP_H_ */
