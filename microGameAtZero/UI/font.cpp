//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "font.h"

/**
 * @brief This function returns the pixels of the selected char for the chosen font on the
 *        desired row. (this function is only called in the renderer and is not needed otherwise)
 * 
 * @param input char to be set
 * @param font the font to be used
 * @param row the row of the char to be drawn
 * @return uint32_t the pixels of the row for the selected char with the desired font 
 */
uint32_t setPixelForChar(char input, fontType font, uint8_t row)
{
    uint32_t set = 0;
    uint8_t h = 0;

    switch(font)
    {
        case FONT_10:
            h = PIXEL_F10_HEIGHT;
            break;
        case FONT_20:
            h = PIXEL_F20_HEIGHT;
            break;
        default:
            set = 0;
    }

    if(input > 31 && input <= 127)
    {

        if(font == FONT_10 && row < h)
            set = font10[input-32][row]<<1;
        else if(font == FONT_20 && row < h)
        {
            for(int8_t index = 0;index < PIXEL_F10_HEIGHT;index++)
            {
                if((font10[input-32][row/2] >> index) & 1)
                {
                    set |= 3 << index*2;

                }                
            }
        }

    }

    return set;
}


/**
 * @brief This function dereferences the pointer *height with the height value of the selected font.
 * 
 * @param font selected font
 * @param height pointer to be dereferences
 */
void getFontSize(fontType font, uint8_t *height)
{
    switch(font)
    {
        case FONT_10:
            *height = PIXEL_F10_HEIGHT;
            break;
        case FONT_20:
            *height = PIXEL_F20_HEIGHT;
            break;
        default:
            *height = 0;
    }
}

/**
 * @brief This function returns the char width of the selected char of the selected font.
 * 
 * @param font selected font
 * @param input selected char
 * @return uint16_t width of the selected char
 */
uint16_t getCharWidth(fontType font, char input)
{
    uint16_t width = 0;

    if(input > 31 && input <= 127)
    {
        if(font == FONT_10)
            width = font10Width[input-32];  
        else if(font == FONT_20)
            width = font10Width[input-32]*2;  
    }
    return width;
}