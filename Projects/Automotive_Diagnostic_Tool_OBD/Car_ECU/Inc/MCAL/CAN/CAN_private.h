/**************************************************************************/
/* Filename						: CAN_private.h                            */
/* Author  	    				: Muhammad Ammar                          */
/* Date 						: Nov 15, 2023  	           	 	         	 */ 
/* Version 	 					: V01                                     */
/* MicroController  			: STM32429 								   */
/**************************************************************************/


#ifndef CAN_CAN_PRIVATE_H_
#define CAN_CAN_PRIVATE_H_



/********************************** Includes *********************************************/


/********************************** Data Type Declarations ****************************/
static void (*Can_RxInterruptHandler[TWO_VALUE])(Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8 Copy_u8FilterIndex);

typedef volatile struct{
	uint32 CAN_TIR;
	uint32 CAN_TDTR;
	uint32 CAN_TDLR;
	uint32 CAN_TDHR;
}Can_TxMailBoxRegisterType;

typedef volatile struct{
	uint32 CAN_RIR;
	uint32 CAN_RDTR;
	uint32 CAN_RDLR;
	uint32 CAN_RDHR;
}Can_RxFifoMailBoxRegisterType;

typedef volatile struct{
	uint32 CAN_FR[TWO_VALUE];
}Can_FilterBanKRegisterType;


typedef volatile struct{
	uint32 CAN_MCR;
	uint32 CAN_MSR;
	uint32 CAN_TSR;
	uint32 CAN_RFxR[TWO_VALUE];
	uint32 CAN_IER;
	uint32 CAN_ESR;
	uint32 CAN_BTR;
	uint32 Reserverd0[88];

	/*
	 * tx mail box0 ID
	 * tx mail box0 lengh
	 * tx mail box0 low
	 * tx mail box0 high
	 *
	 * tx mail box1 ID
	 * tx mail box2 lengh
	 * tx mail box3 low
	 * tx mail box3 high
	 *  mail box2
	 * struct for each mail box and create 3 of it
	 */
	Can_TxMailBoxRegisterType CAN_TxMailBoxRegs[THREE_VALUE];
	Can_RxFifoMailBoxRegisterType CAN_RxFifoMailBoxRegs[TWO_VALUE];

	uint32 Reserverd1[TWELVE_VALUE];

	/* Filter Regs Part */
	uint32 CAN_FMR;
	uint32 CAN_FM1R;
	uint32 Reserverd2;
	uint32 CAN_FS1R;
	uint32 Reserverd3;
	uint32 CAN_FFA1R;
	uint32 Reserverd4;
	uint32 CAN_FA1R;

	uint32 Reserverd5;
	uint32 Reserverd6[SEVEN_VALUE];
	/*
	 * Each Filter Bank Register consists of 2 register
	 * FilterBank0, Reg 0
	 * Filter Bank0, Reg 1
	 */
	Can_FilterBanKRegisterType CAN_FilterBankReg[TWENTYEIGHT_VALUE];

}CANx_Type;


/********************************** Macros Declarations *******************************/

#define CAN_1		((volatile CANx_Type*)(0x40006400))


#define CAN_MAX_TX_MAILBOX_INDEX			(TWO_VALUE)
#define CAN_MAX_TIMEOUT_COUNTER_VALUE		(0xFFFF)


/*
 * This Part For Filter Configuration
 *
 */

#define FILTER_ON				1
#define FILTER_OFF				0

#define MASK_MODE				0
#define ID_LIST_MODE			1

#define SCALE_16BIT_DUAL		0
#define SCALE_32BIT_SINGLE		1

#define FIFO_0					0
#define FIFO_1					1
/********************************** Macros Function Declarations *********************/

/* First Register */
#define Can_ExitSleepMode()						(CLR_BIT( (CAN_1->CAN_MCR),  (ONE_VALUE)))
#define Can_IsExitSleepModeDone()				( READ_BIT((CAN_1->CAN_MSR),ONE_VALUE ) == ZERO_VALUE )

#define Can_InitRequest()						(SET_BIT( (CAN_1->CAN_MCR),  ZERO_VALUE))
#define Can_IsInitRequestDone()					( READ_BIT((CAN_1->CAN_MSR),ZERO_VALUE ) == ONE_VALUE )


#define Can_GoToInitMode()							do{ \
													Can_ExitSleepMode();\
													while(Can_IsExitSleepModeDone() == STD_FALSE);\
													Can_InitRequest();\
													while(Can_IsInitRequestDone() == STD_FALSE);\
														}while(ZERO_VALUE)

#define Can_DeinitRequest()						(CLR_BIT( (CAN_1->CAN_MCR),  ZERO_VALUE))
#define Can_IsDeInitRequestDone()					( READ_BIT((CAN_1->CAN_MSR),ZERO_VALUE ) == ZERO_VALUE )

#define Can_GoOutFromInitMode()						do{ \
														Can_DeinitRequest();\
													while(Can_IsDeInitRequestDone() == STD_FALSE);\
														}while(ZERO_VALUE)


#define Can_SelectTxFifoPriority(_ARGU_)			(WRITE_BIT( (CAN_1->CAN_MCR),(TWO_VALUE),(_ARGU_)  ) )
#define Can_SelectRxFifoLockMode(_ARGU_)			(WRITE_BIT( (CAN_1->CAN_MCR),(THREE_VALUE),(_ARGU_)  ) )
#define Can_SelectRetransmissionAutomatic(_ARGU_)   (WRITE_BIT( (CAN_1->CAN_MCR),(FOUR_VALUE),(_ARGU_)  ) )


#define Can_SelectWakeupAutomatic(_ARGU_)		    	 	 (WRITE_BIT( (CAN_1->CAN_MCR),(FIVE_VALUE),(_ARGU_)  ) )
#define Can_SelectBackFromBusOffStateAutomatic(_ARGU_)     	 (WRITE_BIT( (CAN_1->CAN_MCR),(SIX_VALUE),(_ARGU_)  ) )
#define Can_SelectTimeTriggerCommunicationMode(_ARGU_)    	 (WRITE_BIT( (CAN_1->CAN_MCR),(SEVEN_VALUE),(_ARGU_)  ) )
#define Can_ResetMasterSW() 							 	 (SET_BIT( (CAN_1->CAN_MCR),  FIFTEEN_VALUE))
#define Can_SelectDuringDebugModeCanWorking(_ARGU_)      	 (WRITE_BIT( (CAN_1->CAN_MCR),(SIXTEEN_VALUE),(_ARGU_)  ) )

#define Can_IsNodeCurrentlyTransmitter()					( READ_BIT((CAN_1->CAN_MSR),EIGHT_VALUE ) == ONE_VALUE )
#define Can_IsNodeCurrentlyReceiver()				    	( READ_BIT((CAN_1->CAN_MSR),NINE_VALUE ) == ONE_VALUE )
#define Can_GetActualValueOfCanRxPin()				    	( READ_BIT((CAN_1->CAN_MSR),ELEVEN_VALUE ) == ONE_VALUE )
#define Can_GetCurrentReceivedBitValue()				    ( READ_BIT((CAN_1->CAN_MSR),TEN_VALUE ) == ONE_VALUE )


#define Can_SelectNodeMode(_VALUE_)						((CAN_1->CAN_BTR) = (((CAN_1->CAN_BTR) &0x3FFFFFFF) | (((_VALUE_)<<THIRTY_VALUE) & 0xC0000000 )))

/* Transmiting Part */

#define Can_IsRequestCompletedMailBox_x(_ID_)				( READ_BIT((CAN_1->CAN_TSR),((EIGHT_VALUE*_ID_)  ) ) == ONE_VALUE )
#define Can_IsTransmissionCompletedMailBox_x(_ID_)			( READ_BIT((CAN_1->CAN_TSR),((EIGHT_VALUE*_ID_+ONE_VALUE)  ) ) == ONE_VALUE )
#define Can_IsArbitrationLostHappenedMailBox_x(_ID_)			( READ_BIT((CAN_1->CAN_TSR),((EIGHT_VALUE*_ID_+TWO_VALUE)  ) ) == ONE_VALUE )
#define Can_IsTransmissionErrorHappenedMailBox_x(_ID_)			( READ_BIT((CAN_1->CAN_TSR),((EIGHT_VALUE*_ID_+THREE_VALUE)  ) ) == ONE_VALUE )

#define Can_AbortRequestForMailBox_x(_ID_)						( SET_BIT((CAN_1->CAN_TSR),((EIGHT_VALUE*_ID_+SEVEN_VALUE)  ) )  )

#define Can_IsMailBox_x_Empty(_ID_)								( READ_BIT((CAN_1->CAN_TSR),((TWENTYSIX_VALUE+_ID_)  ) ) == ONE_VALUE )
#define Can_IsMailBox_x_LowestPriority(_ID_)						( READ_BIT((CAN_1->CAN_TSR),((TWENTYNINE_VALUE+_ID_)  ) ) == ONE_VALUE )

#define Can_GetBestMailBoxIndex()							    ( ((CAN_1->CAN_MSR)>>TWENTYFOUR_VALUE )& 0x3 )

#define Can_SetDLCinTxMailBox_x(_MAILBOX_ID_, _DLC_)						( (CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TDTR ) = (((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TDTR ) &0xFFFFFFF0) | (((_DLC_)) & 0xF )))
#define Can_SetExtendedIDinTxMailBox_x(_MAILBOX_ID_, _EXTENDED_ID_)			( (CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR ) = (((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR ) & 0xFFE00007) | (((_EXTENDED_ID_)<<THREE_VALUE) & 0x1FFFF8 )))
#define Can_SetIDEinTxMailBox_x(_MAILBOX_ID_, _IDE_)						(WRITE_BIT( ((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR )),(TWO_VALUE),(_IDE_)  ) )

#define Can_SetRTRinTxMailBox_x(_MAILBOX_ID_, _RTR_)						(WRITE_BIT( ((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR )),(ONE_VALUE),(_RTR_)  ) )
#define Can_SetStandardIDinTxMailBox_x(_MAILBOX_ID_, _Standard_ID_)			( (CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR ) = (((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR ) & 0x1FFFFF) | (((_Standard_ID_)<<TWENTYONE_VALUE) & 0xFFE00000 )))

#define Can_SetDataMessaginMailBox_x(_MAILBOX_ID_, _Arr_Data_)			do{\
																				(CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TDLR ) =   (*((uint32*)(_Arr_Data_)))  ;\
																				(CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TDHR ) =   (*((uint32*)(_Arr_Data_+FOUR_VALUE)));\
																					}while(ZERO_VALUE)



#define Can_StartTransmit(_MAILBOX_ID_)											(SET_BIT( ((CAN_1->CAN_TxMailBoxRegs[_MAILBOX_ID_].CAN_TIR )),(ZERO_VALUE)  ) )
#define Can_GetLastErrorCode()													( ((CAN_1->CAN_ESR)>>FOUR_VALUE )& 0x3 )

#define Can_SetBitTimeCalulation(_VALUE_)										((CAN_1->CAN_BTR) = (((CAN_1->CAN_BTR) &0xC0000000) | (((_VALUE_)<<ZERO_VALUE) & 0x3FFFFFFF )))


// Receive Part


#define Can_GetNumberOfPendingMessages_FIFOx(_INDEX_)									( ((CAN_1->CAN_RFxR[_INDEX_])>>ZERO_VALUE )& 0x3 )

#define Can_IsFIFOxFull(_INDEX_)														( READ_BIT((CAN_1->CAN_RFxR[_INDEX_]),THREE_VALUE ) == ONE_VALUE )
#define Can_IsOverRunInFifoxFull(_INDEX_)												( READ_BIT((CAN_1->CAN_RFxR[_INDEX_]),FOUR_VALUE ) == ONE_VALUE )

#define Can_ClearFIFOxFullFlag(_INDEX_)													( CLR_BIT((CAN_1->CAN_RFxR[_INDEX_]),THREE_VALUE ) )
#define Can_ClearOverRunInFifoxFullFlag(_INDEX_)										( CLR_BIT((CAN_1->CAN_RFxR[_INDEX_]),FOUR_VALUE ) )

#define Can_RelaseFIFOxMailBox(_INDEX_)													( SET_BIT((CAN_1->CAN_RFxR[_INDEX_]),FIVE_VALUE ) )


#define Can_GetREC_ReceiveErrorCounter()												( ((CAN_1->CAN_ESR)>>TWENTYFOUR_VALUE )& 0xFF )
#define Can_GetTEC_TransimissionErrorCounter()											( ((CAN_1->CAN_ESR)>>SIXTEEN_VALUE )& 0xFF )

#define Can_GetErrorWarningFlag_TEC_OR_REC_GREATER_THAN_95()							( READ_BIT((CAN_1->CAN_ESR),ZERO_VALUE ) )
#define Can_GetErrorPassiveFlag_TEC_OR_REC_GREATER_THAN_127()							( READ_BIT((CAN_1->CAN_ESR),ONE_VALUE ) )
#define Can_IsNodeInBusOffMode()														( READ_BIT((CAN_1->CAN_ESR),TWO_VALUE ) )




/* Rx Part */

#define Can_GetDLCinRxFifoMailBox_x(_FIFO_MAILBOX_ID_)						( ((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RDTR ) >> ZERO_VALUE ) &0xF)
#define Can_GetRTRinRxFifoMailBox_x(_FIFO_MAILBOX_ID_)						( READ_BIT((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RIR),ONE_VALUE ) )
#define Can_GetIDEinRxFifoMailBox_x(_FIFO_MAILBOX_ID_)						( READ_BIT((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RIR),TWO_VALUE ) )
#define Can_GetExtendedIDinRxFifoMailBox_x(_FIFO_MAILBOX_ID_)				( ((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RDTR ) >> THREE_VALUE ) &0x3FFFF)
#define Can_GetStandardIDinRxFifoMailBox_x(_FIFO_MAILBOX_ID_)				( ((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RDTR ) >> TWENTYONE_VALUE ) &0x7FF)
#define Can_GetDataMessaginFifoMailBox_x(_MAILBOX_ID_, _Arr_Data_)			do{\
																				(*((uint32*)(_Arr_Data_))) = (CAN_1->CAN_RxFifoMailBoxRegs[_MAILBOX_ID_].CAN_RDLR );\
																				(*((uint32*)(_Arr_Data_+FOUR_VALUE))) = (CAN_1->CAN_RxFifoMailBoxRegs[_MAILBOX_ID_].CAN_RDHR );\
																					}while(ZERO_VALUE)


#define Can_SetNumberOfCan1Filters(_VALUE_)									((CAN_1->CAN_FMR) = (((CAN_1->CAN_FMR) &0xFFFFC0FF) | (((_VALUE_)<<EIGHT_VALUE) & 0x3F00 )))
#define Can_GoToFilterInitMode()											( SET_BIT((CAN_1->CAN_FMR),ZERO_VALUE ) )
#define Can_GoOutFromFilterInitMode()										( CLR_BIT((CAN_1->CAN_FMR),ZERO_VALUE ) )
#define Can_SelectFilterMode(_INDEX_ , _ARGU_)								(WRITE_BIT( ((CAN_1->CAN_FM1R )),(_INDEX_),(_ARGU_)  ) )
#define Can_SelectFilterScale(_INDEX_ , _ARGU_)								(WRITE_BIT( ((CAN_1->CAN_FS1R )),(_INDEX_),(_ARGU_)  ) )
#define Can_SelectFilterFifo(_FILTER_INDEX_ , _FIFO_INDEX_)					(WRITE_BIT( ((CAN_1->CAN_FFA1R )),(_FILTER_INDEX_),(_FIFO_INDEX_)  ) )
#define Can_ActivateFilter(_FILTER_INDEX_)									(SET_BIT( ((CAN_1->CAN_FA1R )),(_FILTER_INDEX_)  ) )

#define Can_SetBankRegister(_REG_INDEX_,_FILTER_INDEX_, _VALUE_)			(CAN_1->CAN_FilterBankReg[_FILTER_INDEX_].CAN_FR[_REG_INDEX_] ) = (_VALUE_)
#define Can_GetFilterIndexFifox(_FIFO_MAILBOX_ID_)			    	( ((CAN_1->CAN_RxFifoMailBoxRegs[_FIFO_MAILBOX_ID_].CAN_RDTR ) >> EIGHT_VALUE ) &0xFF)


/* Interrupt Part */
#define Can_EnableRxInterruptFifoMailBox_x(_FIFO_ID_)			(SET_BIT( ((CAN_1->CAN_IER )),( (!_FIFO_ID_)+(_FIFO_ID_*FOUR_VALUE)  )  ) )
#define Can_DisableRxInterruptFifoMailBox_x(_FIFO_ID_)			(CLR_BIT( ((CAN_1->CAN_IER )),( (!_FIFO_ID_)+(_FIFO_ID_*FOUR_VALUE)  )  ) )


#define	Filter_concat(...)		Filter_concatHelper(__VA_ARGS__)


#define Filter_concatHelper(\
							_FILTER13_ACTIVE_, _FILTER13_MODE_, _FILTER13_SCALE_,_FILTER13_FIFO_,  _FILTER13_REG0_VALUE, _FILTER13_REG1_VALUE, \
							_FILTER12_ACTIVE_, _FILTER12_MODE_, _FILTER12_SCALE_,_FILTER12_FIFO_,  _FILTER12_REG0_VALUE, _FILTER12_REG1_VALUE, \
							_FILTER11_ACTIVE_, _FILTER11_MODE_, _FILTER11_SCALE_,_FILTER11_FIFO_,  _FILTER11_REG0_VALUE, _FILTER11_REG1_VALUE, \
							_FILTER10_ACTIVE_, _FILTER10_MODE_, _FILTER10_SCALE_,_FILTER10_FIFO_,  _FILTER10_REG0_VALUE, _FILTER10_REG1_VALUE, \
							_FILTER9_ACTIVE_, _FILTER9_MODE_, _FILTER9_SCALE_,_FILTER9_FIFO_,  _FILTER9_REG0_VALUE, _FILTER9_REG1_VALUE, \
							_FILTER8_ACTIVE_, _FILTER8_MODE_, _FILTER8_SCALE_,_FILTER8_FIFO_,  _FILTER8_REG0_VALUE, _FILTER8_REG1_VALUE, \
							_FILTER7_ACTIVE_, _FILTER7_MODE_, _FILTER7_SCALE_,_FILTER7_FIFO_,  _FILTER7_REG0_VALUE, _FILTER7_REG1_VALUE, \
							_FILTER6_ACTIVE_, _FILTER6_MODE_, _FILTER6_SCALE_,_FILTER6_FIFO_,  _FILTER6_REG0_VALUE, _FILTER6_REG1_VALUE, \
							_FILTER5_ACTIVE_, _FILTER5_MODE_, _FILTER5_SCALE_,_FILTER5_FIFO_,  _FILTER5_REG0_VALUE, _FILTER5_REG1_VALUE, \
							_FILTER4_ACTIVE_, _FILTER4_MODE_, _FILTER4_SCALE_,_FILTER4_FIFO_,  _FILTER4_REG0_VALUE, _FILTER4_REG1_VALUE, \
							_FILTER3_ACTIVE_, _FILTER3_MODE_, _FILTER3_SCALE_,_FILTER3_FIFO_,  _FILTER3_REG0_VALUE, _FILTER3_REG1_VALUE, \
							_FILTER2_ACTIVE_, _FILTER2_MODE_, _FILTER2_SCALE_,_FILTER2_FIFO_,  _FILTER2_REG0_VALUE, _FILTER2_REG1_VALUE, \
							_FILTER1_ACTIVE_, _FILTER1_MODE_, _FILTER1_SCALE_,_FILTER1_FIFO_,  _FILTER1_REG0_VALUE, _FILTER1_REG1_VALUE, \
							_FILTER0_ACTIVE_, _FILTER0_MODE_, _FILTER0_SCALE_,_FILTER0_FIFO_,  _FILTER0_REG0_VALUE, _FILTER0_REG1_VALUE)\
																												do{\
																					CAN_1->CAN_FM1R = (0b0000## 0##0##0##0##0##\
                    																		0##0##0##0##0##0##0##\
																							0##0##_FILTER13_MODE_##_FILTER12_MODE_##_FILTER11_MODE_##_FILTER10_MODE_##_FILTER9_MODE_##\
																							_FILTER8_MODE_##_FILTER7_MODE_##_FILTER6_MODE_##_FILTER5_MODE_##_FILTER4_MODE_##_FILTER3_MODE_##_FILTER2_MODE_##\
																							_FILTER1_MODE_##_FILTER0_MODE_);\
																					CAN_1->CAN_FS1R = (0b0000## 0##0##0##0##0##\
																									0##0##0##0##0##0##0##\
																									0##0##_FILTER13_SCALE_##_FILTER12_SCALE_##_FILTER11_SCALE_##_FILTER10_SCALE_##_FILTER9_SCALE_##\
																									_FILTER8_SCALE_##_FILTER7_SCALE_##_FILTER6_SCALE_##_FILTER5_SCALE_##_FILTER4_SCALE_##_FILTER3_SCALE_##_FILTER2_SCALE_##\
																									_FILTER1_SCALE_##_FILTER0_SCALE_);\
																										\
																					CAN_1->CAN_FFA1R = (0b0000## 0##0##0##0##0##\
																														0##0##0##0##0##0##0##\
																														0##0##_FILTER13_FIFO_##_FILTER12_FIFO_##_FILTER11_FIFO_##_FILTER10_FIFO_##_FILTER9_FIFO_##\
																														_FILTER8_FIFO_##_FILTER7_FIFO_##_FILTER6_FIFO_##_FILTER5_FIFO_##_FILTER4_FIFO_##_FILTER3_FIFO_##_FILTER2_FIFO_##\
																														_FILTER1_FIFO_##_FILTER0_FIFO_);\
																															\
																				((CAN_1->CAN_FilterBankReg)[0]).CAN_FR[0] = _FILTER0_REG0_VALUE; \
																				CAN_1->CAN_FilterBankReg[0].CAN_FR[1] = _FILTER0_REG1_VALUE; \
																				CAN_1->CAN_FilterBankReg[1].CAN_FR[0] = _FILTER1_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[1].CAN_FR[1] = _FILTER1_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[2].CAN_FR[0] = _FILTER2_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[2].CAN_FR[1] = _FILTER2_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[3].CAN_FR[0] = _FILTER3_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[3].CAN_FR[1] = _FILTER3_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[4].CAN_FR[0] = _FILTER4_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[4].CAN_FR[1] = _FILTER4_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[5].CAN_FR[0] = _FILTER5_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[5].CAN_FR[1] = _FILTER5_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[6].CAN_FR[0] = _FILTER6_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[6].CAN_FR[1] = _FILTER6_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[7].CAN_FR[0] = _FILTER7_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[7].CAN_FR[1] = _FILTER7_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[8].CAN_FR[0] = _FILTER8_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[8].CAN_FR[1] = _FILTER8_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[9].CAN_FR[0] = _FILTER9_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[9].CAN_FR[1] = _FILTER9_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[10].CAN_FR[0] = _FILTER10_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[10].CAN_FR[1] = _FILTER10_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[11].CAN_FR[0] = _FILTER11_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[11].CAN_FR[1] = _FILTER11_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[12].CAN_FR[0] = _FILTER12_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[12].CAN_FR[1] = _FILTER12_REG1_VALUE; \
																															CAN_1->CAN_FilterBankReg[13].CAN_FR[0] = _FILTER13_REG0_VALUE; \
																															CAN_1->CAN_FilterBankReg[13].CAN_FR[1] = _FILTER13_REG1_VALUE; \
																														\
																																				\
																	CAN_1->CAN_FA1R = (0b0000## 0##0##0##0##0##\
																			0##0##0##0##0##0##0##\
																			0##0##_FILTER13_ACTIVE_##_FILTER12_ACTIVE_##_FILTER11_ACTIVE_##_FILTER10_ACTIVE_##_FILTER9_ACTIVE_##\
																			_FILTER8_ACTIVE_##_FILTER7_ACTIVE_##_FILTER6_ACTIVE_##_FILTER5_ACTIVE_##_FILTER4_ACTIVE_##_FILTER3_ACTIVE_##_FILTER2_ACTIVE_##\
																			_FILTER1_ACTIVE_##_FILTER0_ACTIVE_);\
																			\
																							}while(0)





/********************************** Software Interfaces Declarations *******************/



#endif /* CAN_CAN_PRIVATE_H_ */
