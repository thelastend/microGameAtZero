//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "image.h"

/**
 * @brief Construct a new IMAGE::IMAGE object
 * 
 * @param setting image settings
 */
IMAGE::IMAGE(image_ui setting)
{
    imageSetting = setting;
}


/**
 * @brief Destroy the IMAGE::IMAGE object
 * 
 */
IMAGE::~IMAGE()
{
    imageSetting.pSprite = NULL;
}


/**
 * @brief This function changes the Sprite of the image object.
 * 
 * @param pSprite  pointer to the sprite to be set
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM pSprite is NULL
 */
microGameAtZero_err IMAGE::changeImage(uint8_t *pSprite)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(pSprite != NULL)
    {
        imageSetting.pSprite = pSprite;
        error = MICRO_GAME_AT_ZERO_OK;
    }

    return error;
}


/**
 * @brief This function returns the image values.
 * 
 * @return image_ui structure of the image values
 */
image_ui IMAGE::getImageSettings()
{
    return imageSetting;
}
    

/**
 * @brief This function set the hidden flag of the image.
 * 
 * @param hidden if ture the image is hidden otherwise it will be shown.
 */
void IMAGE::setHidden(bool hidden)
{
    imageSetting.hidden = hidden;
}


/**
 * @brief This function returns the hidden status of the image.
 * 
 * @return true image is hidden
 * @return false image is not hidden
 */
bool IMAGE::getHidden()
{
    return imageSetting.hidden;
}