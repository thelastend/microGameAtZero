#ifndef _FONT_MICROGAMEATZERO_
#define _FONT_MICROGAMEATZERO_

#include "../Driver/microGameAtZeroTargetSettings.h"
#include "font10.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>



/**
 * @brief enumeration of the available fonts
 * 
 */
enum fontType{
    FONT_10 = 0,
    FONT_20 = 1,
    FONT_MAX
};



uint32_t setPixelForChar(char input, fontType font, uint8_t row);
void getFontSize(fontType font, uint8_t *height);
uint16_t getCharWidth(fontType font, char input);

#endif 
