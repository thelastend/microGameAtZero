#ifndef _KINECTBODY_MICROGAMEATZERO_
#define _KINECTBODY_MICROGAMEATZERO_
  

#include "Object.h"
#include <string.h>
#include "../microGameAtZeroError.h"




#define MAXANIMATIONS 			10
#define NO_ANIMATION_STARDED 	-1

/**
 * @brief structure of the animation settings
 * 
 */
struct animation
{
	uint8_t numbSprites = 0;
	uint8_t changeRate = 0;
	int32_t transparentColor = -1;
	uint8_t **ppSprite  = NULL;
	bool inUse = false;
	bool oneShot = false;
};


/**
 * @brief Kinect body class
 * 
 */
class KinectBody : public Object {

public: 
    KinectBody();
	~KinectBody();
	void setSprite(vector2 size, uint8_t **ppSprite, vector2 position, int8_t mass, int32_t transparentColor);
	vector2 move(vector2 update);
	microGameAtZero_err setAnimation(uint8_t **ppSprite, uint8_t numbSprites, uint8_t changeRate,  int32_t transparentColor);
	microGameAtZero_err removeAnimation(uint8_t animationNumber);
	microGameAtZero_err startAnimation(uint8_t animationNumber, bool oneShot);
	microGameAtZero_err stopAnimation();
	int8_t animationStatus();
	virtual uint8_t *getSprite();
	int32_t getTransparentColor();

private:
	uint8_t fps;
	animation animations[MAXANIMATIONS];
	sprite bodySprite;
	int8_t animationStarted;
	uint8_t animationPosition;
	uint8_t animationRunCounter;
	uint8_t animationExistCount;
};


#endif
