/*===============================================================================================*
 * =================================== Car's (Server) ECU =======================================*
 * ==============================================================================================*
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
#include "../INC/MCAL/EXTI/EXTI.h"

/*HAL includes*/
#include "../Inc/HAL/UDS/UDS.h"
#include "HAL/Servo_Motor/Servo_Motor.h"
#include "../Inc/HAL/LM35/LM35.h"
#include "../Inc/HAL/CAR_DC_MOTORS/CAR_DC_MOTORS.h"


/*APP includes*/
#include "../Inc/APP/APP.h"

/* OS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"


Can_MessageType G_Receive_Message;
uint8 G_ArrMessageData[8];
uint8  G_UDS_SID;
uint8  G_UDS_SubFun;
uint8  G_UDS_DID;
uint32 G_UDS_DATA;

volatile uint8 APP_CURRENT_SECURITY_LEVEL=SECURITY_LEVEL_1;
volatile uint8 APP_CURRENT_SESSION=DEFAULT_SESSION;


void UDS_Isr_CallBack(Can_MessageType* Receive_Message, uint8 ArrMessageData[8], uint8 Copy_uint8FilterIndex);

 /*=========================================================================================================================================*/

int main(void)
{
	UDS_voidSetCallBack(UDS_Isr_CallBack);
	APP_vidInit();

	/*start Scheduler */
	vTaskStartScheduler();
	while(1)
	{

		//Never Enters Here
	}
}

/*==========================================================================================================================================*/
/*=================================== ISR CallBacks ===================================*/
void UDS_Isr_CallBack(Can_MessageType* Receive_Message, uint8 ArrMessageData[8], uint8 Copy_uint8FilterIndex)
{
	for(uint8 i=0;i < Receive_Message->can_DLC_FROM_0_TO_8;++i)
	{
		G_ArrMessageData[i] = ArrMessageData[i];
	}
	G_UDS_SID    = G_ArrMessageData[0] ;
	G_UDS_SubFun = G_ArrMessageData[1] ;
	G_UDS_DID    = G_ArrMessageData[2] ;
	G_UDS_DATA   = *((uint32*)(G_ArrMessageData+3)) ;
	UDS_requestHandler();

}
