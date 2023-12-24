#include "../SERVICES/Standard_Data_Types.h"
#include "../../../Inc/HAL/UDS/UDS.h"
#include "../../../Inc/HAL/UDS/UDS_prv.h"
#include "MCAL/ADC/ADC.h"

/* OS Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

extern uint8 Security_Level ;


extern uint8 SID  ;
extern uint8 SUBfn;
extern uint8 DID  ;
extern uint8 RSID ;
extern uint8 NRC  ;
extern uint32 DATA;
uint32 SEED;

extern Can_MessageType G_Receive_Message;
extern uint8 G_ArrMessageData[8];
extern uint8  G_UDS_SID;
extern uint8  G_UDS_SubFun;
extern uint8  G_UDS_DID;
extern uint32 G_UDS_DATA;


extern uint8 APP_CURRENT_SECURITY_LEVEL ;
extern uint8 APP_CURRENT_SESSION        ;


 void Security_LevelHandler(){
    
    if (G_UDS_SubFun > 0 && G_UDS_SubFun < 7){
        // requesting seed branch
        if (G_UDS_SubFun %2 == 1){
            SEED = generate_random_number();
            UDS_GeneratePositiveResponse(SEED);
        }
        // key checking branch
        else {
            uint32 hash = custom_hash_function(SEED);
            // unlock security level
            if (hash == G_UDS_DATA){
                UDS_GeneratePositiveResponse(0);
                APP_CURRENT_SESSION = DEFAULT_SESSION;
                switch (G_UDS_SubFun)
                {
                    case 0x02:APP_CURRENT_SECURITY_LEVEL = SECURITY_LEVEL_1;break;
                    case 0x04:APP_CURRENT_SECURITY_LEVEL = SECURITY_LEVEL_2;break;
                    case 0x06:APP_CURRENT_SECURITY_LEVEL = SECURITY_LEVEL_3;break;
                }
            }else {
                UDS_GenerateNegativeResponse(NRC_SECURITY_ACCESS_DENIED);
            }
        }
    }else {
       UDS_GenerateNegativeResponse(NRC_SUB_FUNCTION_NOT_SUPPORTED);
    }
}

uint32 custom_hash_function(uint32 input) {
    // Custom hash function using multiplication and bitwise operations
    unsigned int hash = input;

    // Some arbitrary constants for mixing
    unsigned int constant1 = 31;
    unsigned int constant2 = 17;

    // Mix the bits using bitwise XOR and left shift operations
    hash = (hash ^ (hash << constant1)) + constant2;
    hash = (hash ^ (hash >> constant2)) * constant1;

    return hash;
}

uint32 generate_random_number(){
    uint16 uint16_SourceOfRandomness = 0;
    portTickType Mil = xTaskGetTickCount();
    ADC_enu_Read_Regular_Channel(&uint16_SourceOfRandomness);
    uint32 randomValue = uint16_SourceOfRandomness * Mil ;
    return randomValue;
}
