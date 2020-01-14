//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "number.h"



/**
 * @brief Construct a new NUMBER::NUMBER object
 * 
 * @param settings number settings
 */
NUMBER::NUMBER(number_ui settings)
{
    numberSetting = settings;
}


/**
 * @brief Destroy the NUMBER::NUMBER object
 * 
 */
NUMBER::~NUMBER()
{

}


/**
 * @brief This function changes the registered number to the passed.
 * 
 * @param number the number to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is ok 
 */
microGameAtZero_err NUMBER::changeNumber(uint32_t number)
{
    numberSetting.number = number;
    return MICRO_GAME_AT_ZERO_OK;
}


/**
 * @brief This function returns the number object settings.
 * 
 * @return number_ui number object settings.
 */
number_ui NUMBER::getNumberSettings()
{
    return numberSetting;
}


/**
 * @brief This function returns the registered number.
 * 
 * @return uint32_t registered number
 */
uint32_t NUMBER::getNumber()
{
    return numberSetting.number;
}


/**
 * @brief This function can set the hidden flag of the number object.
 * 
 * @param hiden if ture the number object is hidden otherwise it will be shown.
 */
void NUMBER::setHidden(bool hidden)
{
    numberSetting.hidden = hidden;
}


/**
 * @brief This function returns the hidden status of the number object.
 * 
 * @return true number object is hidden
 * @return false number object is not hidden
 */
bool NUMBER::getHidden()
{
    return numberSetting.hidden;
}