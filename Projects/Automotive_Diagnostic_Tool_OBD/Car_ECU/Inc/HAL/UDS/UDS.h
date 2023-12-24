// Defining values for Sessions.
#include "../SERVICES/Standard_Data_Types.h"
#include "../SERVICES/Bit_Wise_Operations.h"
#include "../SERVICES/MAGIC_NUMBERS.h"

#include "../../../Inc/MCAL/NVIC/NVIC.h"
#include "../../../Inc/HAL/UDS/UDS_prv.h"

#include "../../../Inc/MCAL/CAN/CAN.h"
#include "../../../Inc/HAL/EEPROM/EEPROM.h"


#define UDS_NO_DATA                                         (0x00)
#define DEFAULT_SESSION                                     (0x01)
#define PROGRAMMING_SESSION                                 (0x02)
#define EXTENDED_SESSION                                    (0x03)

// Defining values for Security Levels.
#define SECURITY_LEVEL_1                                    (0x02)
#define SECURITY_LEVEL_2                                    (0x03)
#define SECURITY_LEVEL_3                                    (0x04)

// Defining values for SIDs.
#define SID_DIAGNOSTIC_SESSION_CONTROL                      (0x10)
#define SID_ECU_RESET                                       (0x11)
#define SID_SECURITY_ACCESS                                 (0x27)
#define SID_TESTER_PRESENT                                  (0x3E)
#define SID_READ_DATA_BY_IDENTIFIER                         (0x22)
#define SID_WRITE_DATA_BY_IDENTIFIER                        (0x2E)
#define SID_READ_DTC_INFORMATION                            (0x19)
#define SID_CLEAR_DIAGNOSTIC_INFORMATION                    (0x14)
#define SID_CONTROL_DTC_SETTINGS                            (0x85)
#define SID_ROUTINE_CONTROL                                 (0x31)

// Defining values for RSID.
#define RSID_POSITIVE_RESPONSE                              (0x40)
#define RSID_NEGATIVE_RESPONSE                              (0x7F)

// Defining values for NRCs.
#define NRC_GENERAL_REJECT                                  (0x10)
#define NRC_SERVICE_NOT_SUPPORTED                           (0x11)
#define NRC_SUB_FUNCTION_NOT_SUPPORTED                      (0x12)
#define NRC_INVALID_MESSAGE_LENGTH_OR_FORMAT                (0x13)
#define NRC_CONDITIONS_NOT_CORRECT                          (0x22)
#define NRC_REQUEST_OUT_OF_RANGE                            (0x31)
#define NRC_SECURITY_ACCESS_DENIED                          (0x33)
#define NRC_INVALID_KEY                                     (0x35)
#define NRC_SUB_FUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION    (0x7E)

#define UDS_REQUEST_LEVEL_1_SECURITY_SEED                   (0x01)
#define UDS_REQUEST_LEVEL_2_SECURITY_SEED                   (0x03)
#define UDS_REQUEST_LEVEL_3_SECURITY_SEED                   (0x05)

#define UDS_SEND_LEVEL_1_SECURITY_KEY                       (0x02)
#define UDS_SEND_LEVEL_2_SECURITY_KEY                       (0x04)
#define UDS_SEND_LEVEL_3_SECURITY_KEY                       (0x06)

#define DATA_DISABLE                                        (0xD0)
#define DATA_ENABLE                                         (0xE1)

#define DID_LED_FEATURE                                     (0x01)

void UDS_Request(uint8 Copy_SID, uint8 Copy_SUBfn, uint8 Copy_DID, uint32 Copy_Data);
void UDS_requestHandler();
void UDS_GenerateNegativeResponse(uint8 Copy_uint8NRC);
void UDS_GeneratePositiveResponse(uint32 Copy_Data);
void UDS_VoidInit(void);
void UDS_voidSetCallBack( void (*callback)(Can_MessageType* Address_Message,uint8 _ArrMessageData[EIGHT_VALUE],uint8 Copy_uint8FilterIndex));
