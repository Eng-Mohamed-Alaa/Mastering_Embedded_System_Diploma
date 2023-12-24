/* vim: set ai et ts=4 sw=4: */
#ifndef __FONTS_H__
#define __FONTS_H__

#include <stdint.h>
//#include "STD_TYPES.h"
#include "../SERVICES/Standard_Data_Types.h"

typedef struct {
    const uint8 width;
    uint8 height;
    const uint16 *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;

#endif // __FONTS_H__
