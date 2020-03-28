#ifndef _STATICBODY_MICROGAMEATZERO_
#define _STATICBODY_MICROGAMEATZERO_
  

#include "Object.h"


/**
 * @brief Static body class
 * 
 */
class StaticBody : public Object {

public: 
    StaticBody();
	~StaticBody();
	void setSprite(vector2 size, uint8_t **image, vector2 position, int8_t mass, int32_t transparentColor);
	virtual uint8_t *getSprite();
	virtual int32_t getTransparentColor();

private:
	sprite bodySprite;
};


#endif