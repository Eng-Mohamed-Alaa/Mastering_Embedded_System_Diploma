#ifndef UDS_PRV_H_
#define UDS_PRV_H_

#define UDS_CAR             1
#define UDS_TOOL            2

#include "../SERVICES/Standard_Data_Types.h"

void Security_LevelHandler();

uint32 custom_hash_function(uint32 input);

uint32 generate_random_number();

#endif
