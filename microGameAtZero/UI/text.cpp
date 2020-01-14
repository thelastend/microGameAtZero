//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "text.h"



/**
 * @brief Construct a new TEXT::TEXT object
 * 
 * @param settings 
 */
TEXT::TEXT(text_ui settings)
{
    textSetting = settings;
}


/**
 * @brief Destroy the TEXT::TEXT object
 * 
 */
TEXT::~TEXT()
{
    textSetting.pText = NULL;
}
    

/**
 * @brief This function changes the registered text to the passed text.
 * 
 * @param pText pointer to the new text
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM pText is NULL
 */
microGameAtZero_err TEXT::changeText(char *pText)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(pText != NULL)
    {
        textSetting.pText = pText;
        error = MICRO_GAME_AT_ZERO_OK;
    }

    return error;    
}


/**
 * @brief This function returns  the text object settings.
 * 
 * @return text_ui structure of the text object settings
 */
text_ui TEXT::getTextSettings()
{
    return textSetting;
}
    

/**
 * @brief This function sets the hidden flag of the text object.
 * 
 * @param hiden if ture the text object is hidden otherwise it will be shown.
 */
void TEXT::setHidden(bool hidden)
{
    textSetting.hidden = hidden;
}
    

/**
 * @brief This function returns the hidden status of the text object.
 * 
 * @return true text object is hidden
 * @return false text object is not hidden
 */
bool TEXT::getHidden()
{
    return textSetting.hidden;
}