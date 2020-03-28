//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "RigidBody.h"


/**
 * @brief Construct a new Rigid Body:: Rigid Body object
 * 
 */
RigidBody::RigidBody()
{
	bodySprite.ppSprite = NULL;
	hidden = false;
	breakUpdate = false;
}


/**
 * @brief Destroy the Rigid Body:: Rigid Body object
 * 
 */
RigidBody::~RigidBody()
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
 * @param transparentColor color that should not be rendered (the transparent color of all sprite in the array must have the same)
 */
void RigidBody::setSprite(vector2 size, uint8_t **image, vector2 position, int8_t mass, int32_t transparentColor)
{
	settings.position = position;
	settings.size = size;
	settings.mass = mass;
	bodySprite.ppSprite = image;
	if( transparentColor >= -1 && transparentColor <= 0xff)
		bodySprite.transparentColor = transparentColor;	
}



/**
 * @brief This function calculates the new position of the object with the physicparam. The function
 * 		  is called automatically and should not be called by the user.
 * 
 * @param deltaTime The time that has passed since last call
 */
void RigidBody::update(uint32_t deltaTime)
{
	if(!breakUpdate)
	{
		static vector2 force = vector2();
		int32_t time = deltaTime; 
		if(settings.mass != 0 && physicSettings.velocity.y == 0)
			physicSettings.velocity.y = 1;
		force.y=(physicSettings.gravity * settings.mass);

		if(settings.mass != 0)
		{
			static vector2 acc;
			acc.y = force.y/settings.mass;
			physicSettings.velocity.x = physicSettings.velocity.x + (acc.x*time)/1000;
			physicSettings.velocity.y = physicSettings.velocity.y + (acc.y*time)/1000;
		}	
		int32_t xUpdate = (physicSettings.velocity.x*time)/1000;
		int32_t yUpdate = (physicSettings.velocity.y*time)/1000;
		if(physicSettings.velocity.x > 0 && xUpdate == 0)
			xUpdate = 1;
		if(physicSettings.velocity.y > 0 && yUpdate == 0)
			yUpdate = 1;
			
		settings.position.x = settings.position.x + xUpdate;
		settings.position.y = settings.position.y + yUpdate;
		collision.position.x += xUpdate;
		collision.position.y += yUpdate;
	}

}


/**
 * @brief This function returns the currently used sprite. 
 * 
 * @return uint8_t* used sprite
 */
uint8_t* RigidBody::getSprite()
{
    return bodySprite.ppSprite[showSprite];
}


/**
 * @brief This function returns the transparent color.
 * 
 * @return int32_t transparent color
 */
int32_t RigidBody::getTransparentColor()
{
	return bodySprite.transparentColor;
}

/**
 * @brief This function sets the break. If the break is set on, 
 *        the update function call is switched off and the position doesn't change.
 * 
 * @param set true break on, false break off
 */
void RigidBody::setBreak(bool set)
{
	breakUpdate = set;
}
