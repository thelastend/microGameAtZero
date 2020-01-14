//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "rect.h"


/**
 * @brief Construct a new RECT::RECT object
 * 
 * @param setting rectangle settings
 */
RECT::RECT(rect_ui setting)
{
    rectSetting = setting;
}
    

/**
 * @brief Destroy the RECT::RECT object
 * 
 */
RECT::~RECT()
{

}


/**
 * @brief This function sets the fill level of the rectangle in percent (horizontal).
 * 
 * @param percent percent to be fill
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM the input was > 100
 */
microGameAtZero_err RECT::setFillSize(uint8_t percent)
{
    microGameAtZero_err err = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(percent <= 100)
    {
        uint16_t xSize = rectSetting.size.x -(rectSetting.lineWidth*2);
        float onePercent = ((float)xSize)/100.0;
        rectSetting.fillArea = (uint16_t)(onePercent*percent) +rectSetting.position.x;
        err = MICRO_GAME_AT_ZERO_OK;
    }

    return err;
}


/**
 * @brief This function sets the fill color (true 8-bit color)
 * 
 * @param color the fill color to be set (ture 8-bit color)
 */
void RECT::setFillColor(uint8_t color)
{
    rectSetting.colorFill = color;
}
    

/**
 * @brief This function sets the line color of the rectangle.
 * 
 * @param color the line color to be set (true 8-bit color)
 */
void RECT::setLineColor(uint8_t color)
{
    rectSetting.colorLine = color;
}


/**
 * @brief This function returns the rectangle object settings.
 * 
 * @return rect_ui structur of the rectangle object settings
 */
rect_ui RECT::getRectSettings()
{
    return rectSetting;
}


/**
 * @brief This function sets the hidden flag of the rectangle object.
 * 
 * @param hiden if ture the rectangle object is hidden otherwise it will be shown.
 */
void RECT::setHidden(bool hidden)
{
    rectSetting.hidden = hidden;
}
    

/**
 * @brief This function returns the hidden status of the rectangle object.
 * 
 * @return true rectangle object is hidden
 * @return false rectangle object is not hidden
 */
bool RECT::getHidden()
{
    return rectSetting.hidden;
}