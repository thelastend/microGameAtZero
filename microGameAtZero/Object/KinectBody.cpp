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
	bodyTexture.ppTexture = NULL;
	animationExistCount = 0;
	animationStarted = -1;
	showTexture = 0;
	fps = 20;
	for(uint8_t ii = 0; ii < MAXANIMATIONS; ii++)
	{
		animations[ii].ppTexture = NULL;
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
	bodyTexture.ppTexture = NULL;
	for(uint8_t ii = 0; ii < MAXANIMATIONS; ii++)
	{
		animations[ii].ppTexture = NULL;
	}
}


/**
 * @brief This function sets the settings of the object with texture, size and position.
 * 
 * @param size size of the object (texture size == object size)
 * @param ppTexture pointer to the texture array (all textures in the array must have the same size)
 * @param position start position of the object
 * @param mass mass of the object
 * @param transparentColor color that should not be rendered (the transparent color of all texture in the array must be the same)
 */
void KinectBody::setTexture(vector2 size, uint8_t **ppTexture, vector2 position, int8_t mass, int32_t transparentColor)
{
	settings.position = position;
	settings.size = size;
	settings.mass = mass;
	bodyTexture.ppTexture = ppTexture;
	if( transparentColor >= -1 && transparentColor <= 0xff)
		bodyTexture.transparentColor = transparentColor;	
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
 * @param ppTexture list of animation textures
 * @param numbTextures how many textures the animation has
 * @param changeRate how fast the animation should be played
 * @param transparentColor color that should not be rendered (8-bit ture color)
 * @return >= 0 index of the animation
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 * @return MICRO_GAME_AT_ZERO_FULL_ERROR no more room for a new animation
 */
microGameAtZero_err KinectBody::setAnimation(uint8_t **ppTexture, uint8_t numbTextures, uint8_t changeRate,  int32_t transparentColor)
{
	microGameAtZero_err set = MICRO_GAME_AT_ZERO_INVALID_PARAM;

	if(animationExistCount < MAXANIMATIONS && changeRate > 0)
	{
		for(uint8_t index = 0; index < MAXANIMATIONS; index++)
		{
			if(!animations[index].inUse)
			{
				animations[index].ppTexture = ppTexture;
				animations[index].numbTextures = numbTextures;
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
 * @brief This function returns the texture to be displayed.
 * 
 * @return uint8_t* pointer to the texture
 */
uint8_t* KinectBody::getTexture()
{
    uint8_t *texture = bodyTexture.ppTexture[showTexture];

    if(animationStarted > NO_ANIMATION_STARDED)
    {        
        texture = animations[animationStarted].ppTexture[animationPosition];
            
        animationRunCounter++;
        if(animationRunCounter >= animations[animationStarted].changeRate) 
		{ 
            animationPosition++;
            animationRunCounter = 0;
		}   
        if(animationPosition >= animations[animationStarted].numbTextures)
        {
            animationPosition = 0;
			if(animations[animationStarted].oneShot)
				animationStarted = NO_ANIMATION_STARDED;
        }
    }

    return texture;
}


/**
 * @brief This function returns the transparent color of the current texture.
 * 
 * @return transparent color value
 */
int32_t KinectBody::getTransparentColor()
{
	int32_t transparent = bodyTexture.transparentColor;
	
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
			animations[animationNumber].numbTextures = 0;
			animations[animationNumber].changeRate = 0;
			animations[animationNumber].transparentColor = -1;
			animations[animationNumber].ppTexture  = NULL;
			animations[animationNumber].inUse = false;
			animationExistCount--;
			remove = MICRO_GAME_AT_ZERO_OK;
				
		}
	}
	return remove;
}