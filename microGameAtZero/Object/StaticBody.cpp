//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "StaticBody.h"


/**
 * @brief Construct a new Static Body:: Static Body object
 * 
 */
StaticBody::StaticBody()
{
	bodySprite.ppSprite = NULL;
	hidden = false;
}


/**
 * @brief Destroy the Static Body:: Static Body object
 * 
 */
StaticBody::~StaticBody()
{
	bodySprite.ppSprite = NULL;
}


/**
 * @brief This function sets the settings of the object with sprite, size, and position.
 * 
 * @param size size of the object (sprite size == object size)
 * @param image pointer to the sprite array (all sprites in the array must have the same size)
 * @param position start position of the object
 * @param mass mass of the object
 * @param transparentColor color that should not be rendered (the transparent color of all sprite in the array must be the same)
 */
void StaticBody::setSprite(vector2 size, uint8_t **image, vector2 position, int8_t mass, int32_t transparentColor)
{
	settings.position = position;
	settings.size = size;
	settings.mass = mass;
	bodySprite.ppSprite = image;
	if( transparentColor >= -1 && transparentColor <= 0xff)
		bodySprite.transparentColor = transparentColor;	
}


/**
 * @brief This function returns the currently used sprite.
 * 
 * @return uint8_t* currently used sprite
 */
uint8_t* StaticBody::getSprite()
{
    return bodySprite.ppSprite[showSprite];
}


/**
 * @brief This function returns the transparent color (8-bit ture color). 
 * 
 * @return int32_t trapnsparent color
 */
int32_t StaticBody::getTransparentColor()
{
	return bodySprite.transparentColor;
}
