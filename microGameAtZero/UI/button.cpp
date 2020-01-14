//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "button.h"


/**
 * @brief Construct a new BUTTON::BUTTON object
 * 
 * @param settings button settings
 */
BUTTON::BUTTON(button_ui settings)
{
    buttonSettings = settings;
}


/**
 * @brief Destroy the BUTTON::BUTTON object
 * 
 */
BUTTON::~BUTTON()
{
    buttonSettings.pText = NULL;
}


/**
 * @brief This function sets the button text.
 * 
 * @param text button text to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no text 
 */
microGameAtZero_err BUTTON::setText(char text[MAX_BUTTON_TEXT])
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(text != NULL)
    {
        buttonSettings.pText = text;
        error = MICRO_GAME_AT_ZERO_OK;
    }

    return error;
}


/**
 * @brief This function returns the button settings.
 * 
 * @return button_ui button setting sturct
 */
button_ui BUTTON::getButtonSettings()
{
    return buttonSettings;
}


/**
 * @brief This function set the hidden  flag of the button.
 * 
 * @param hiden if ture the button is hidden  otherwise it will be shown.
 */
void BUTTON::setHidden(bool hidden)
{
    buttonSettings.Hidden = hidden;
}


/**
 * @brief This function returns the status of the hidden flag.
 * 
 * @return true button is hidden
 * @return false button is not hidden
 */
bool BUTTON::getHidden()
{
    return buttonSettings.Hidden;
}



/**
 * @brief This function set the button highlight flag.
 * 
 * @param light if true the button is highlighted otherwise not.
 */
void BUTTON::setHighLight(bool light)
{
    buttonSettings.highLightOn = light;
}


/**
 * @brief This function returns the status of the highlight flag.
 * 
 * @return true button is highlighted
 * @return false button is not highlighted
 */
bool BUTTON::getHighLight()
{
    return buttonSettings.highLightOn;
}