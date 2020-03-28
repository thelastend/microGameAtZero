//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "KinectBody.h"
#include "../Physic/physicEngine.h"

/**
 * @brief Construct a new Kinect Body:: Kinect Body object
 * 
 */
KinectBody::KinectBody()
{
	bodySprite.ppSprite = NULL;
	animationExistCount = 0;
	animationStarted = -1;
	showSprite = 0;
	fps = 20;
	for(uint8_t ii = 0; ii < MAXANIMATIONS; ii++)
	{
		animations[ii].ppSprite = NULL;
		animations[ii].inUse = false;
	}
	hidden = false;
}


/**
 * @brief Destroy the Kinect Body:: Kinect Body object
 * 
 */
KinectBody::~KinectBody()
{
	bodySprite.ppSprite = NULL;
	for(uint8_t ii = 0; ii < MAXANIMATIONS; ii++)
	{
		animations[ii].ppSprite = NULL;
	}
}


/**
 * @brief This function sets the settings of the object with sprite, size and position.
 * 
 * @param size size of the object (sprite size == object size)
 * @param ppSprite pointer to the sprite array (all sprites in the array must have the same size)
 * @param position start position of the object
 * @param mass mass of the object
 * @param transparentColor color that should not be rendered (the transparent color of all sprite in the array must be the same)
 */
void KinectBody::setSprite(vector2 size, uint8_t **ppSprite, vector2 position, int8_t mass, int32_t transparentColor)
{
	settings.position = position;
	settings.size = size;
	settings.mass = mass;
	bodySprite.ppSprite = ppSprite;
	if( transparentColor >= -1 && transparentColor <= 0xff)
		bodySprite.transparentColor = transparentColor;	
}

/**
 * @brief This function shifts the position with the given value.
 * 
 * @param update the position is moved by this value 
 * @return current position 
 */
vector2 KinectBody::move(vector2 update)
{
	settings.position.x += update.x;
	settings.position.y += update.y;

	collision.position.x += update.x;
	collision.position.y += update.y;

	return settings.position;
}


/**
 * @brief This function adds a new animation to the object.
 * 
 * @param ppSprite list of animation sprites
 * @param numbSprites how many sprites the animation has
 * @param changeRate how fast the animation should be played
 * @param transparentColor color that should not be rendered (8-bit ture color)
 * @return >= 0 index of the animation
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more room for a new animation
 */
microGameAtZero_err KinectBody::setAnimation(uint8_t **ppSprite, uint8_t numbSprites, uint8_t changeRate,  int32_t transparentColor)
{
	microGameAtZero_err set = MICRO_GAME_AT_ZERO_INVALID_PARAM;

	if(animationExistCount < MAXANIMATIONS && changeRate > 0)
	{
		for(uint8_t index = 0; index < MAXANIMATIONS; index++)
		{
			if(!animations[index].inUse)
			{
				animations[index].ppSprite = ppSprite;
				animations[index].numbSprites = numbSprites;
				animations[index].changeRate = changeRate;
				animations[index].transparentColor = transparentColor;
				animations[index].inUse = true;
				set = index;
				break;
			}
		}

		if(set != MICRO_GAME_AT_ZERO_INVALID_PARAM)
			animationExistCount++;
	}
	else if( changeRate > 0)
	{
		set = MICRO_GAME_AT_ZERO_FULL_ERROR;
	}

	return set;
}



/**
 * @brief This function starts the selected animation.
 * 
 * @param animationNumber index of the animation to be starts
 * @param oneShot if true the animation is playing only once otherwise playing in a loop 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err KinectBody::startAnimation(uint8_t animationNumber, bool oneShot)
{
	microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	if((animationNumber < MAXANIMATIONS) && (animationNumber != animationStarted))
	{
		if(animations[animationNumber].inUse)
		{
			error = MICRO_GAME_AT_ZERO_OK;
			animationStarted = animationNumber;
			animationRunCounter = 0;
			animationPosition = 0;	
			animations[animationNumber].oneShot = oneShot;
		}	
	}

	return error;
}


/**
 * @brief This function stops the current animation.
 * 
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no animation is running
 */
microGameAtZero_err KinectBody::stopAnimation()
{
	microGameAtZero_err ret = MICRO_GAME_AT_ZERO_INVALID_PARAM;
        
    if(animationStarted > NO_ANIMATION_STARDED)
	{
        ret = MICRO_GAME_AT_ZERO_OK;
		animationStarted = NO_ANIMATION_STARDED;
    }   
    return ret;
}



/**
 * @brief This function returns the index of the currently running animation.
 * 
 * @return -1 no animation is started otherwise the index of the animation
 */
int8_t KinectBody::animationStatus()
{
	return animationStarted;
}


/**
 * @brief This function returns the sprite to be displayed.
 * 
 * @return uint8_t* pointer to the sprite
 */
uint8_t* KinectBody::getSprite()
{
    uint8_t *sprite = bodySprite.ppSprite[showSprite];

    if(animationStarted > NO_ANIMATION_STARDED)
    {        
        sprite = animations[animationStarted].ppSprite[animationPosition];
            
        animationRunCounter++;
        if(animationRunCounter >= animations[animationStarted].changeRate) 
		{ 
            animationPosition++;
            animationRunCounter = 0;
		}   
        if(animationPosition >= animations[animationStarted].numbSprites)
        {
            animationPosition = 0;
			if(animations[animationStarted].oneShot)
				animationStarted = NO_ANIMATION_STARDED;
        }
    }

    return sprite;
}


/**
 * @brief This function returns the transparent color of the current sprite.
 * 
 * @return transparent color value
 */
int32_t KinectBody::getTransparentColor()
{
	int32_t transparent = bodySprite.transparentColor;
	
	if(animationStarted > -1)
    {
		transparent = animations[animationStarted].transparentColor;
	}
	return transparent;
}


/**
 * @brief This function removes the selected animation.
 * 
 * @param animationNumber index of the animation which should be removed
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM is not existing
 */
microGameAtZero_err KinectBody::removeAnimation(uint8_t animationNumber)
{
	microGameAtZero_err remove = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	
	if(animationNumber < MAXANIMATIONS)
	{
		if(animations[animationNumber].inUse)
		{
			animations[animationNumber].numbSprites = 0;
			animations[animationNumber].changeRate = 0;
			animations[animationNumber].transparentColor = -1;
			animations[animationNumber].ppSprite = NULL;
			animations[animationNumber].inUse = false;
			animationExistCount--;
			remove = MICRO_GAME_AT_ZERO_OK;
				
		}
	}
	return remove;
}