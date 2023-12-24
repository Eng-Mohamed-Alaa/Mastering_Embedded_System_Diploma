/***************************************************************/
/* Author    : Mahmoud Korayem                                    */
/* Version   : V01                                             */
/* Date      : 24 NOV 2022                                     */
/***************************************************************/
#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void MSPI1_voidInit(void); 

void MSPI1_voidSendReceiveSynch(uint8 Copy_uint8DataToTransmit, uint8 *Copy_DataToReceive);

void MSPI1_voidSendReceiveAsynch(uint8 Copy_uint8DataToTransmit, void (*CallBack)(uint8));

#endif
