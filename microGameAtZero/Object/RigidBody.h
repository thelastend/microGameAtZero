#ifndef _RIGIDBODY_MICROGAMEATZERO_
#define _RIGIDBODY_MICROGAMEATZERO_
  

#include "Object.h"

/**
 * @brief Rigid Body class
 * 
 */
class RigidBody : public Object {

public: 
    RigidBody();
	~RigidBody();
	void setSprite(vector2 size, uint8_t **image, vector2 position, int8_t mass, int32_t transparentColor);
	virtual uint8_t *getSprite();
	void update(uint32_t deltaTime);
	void setBreak(bool set);
	int32_t getTransparentColor();
private:
	sprite bodySprite;
	bool breakUpdate;
};


#endif