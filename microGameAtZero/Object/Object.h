#ifndef _OBJECT_MICROGAMEATZERO_
#define _OBJECT_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../Physic/vector2.h"
#include "../microGameAtZeroError.h"


/**
 * @brief enumeration of the collision type
 *        (only collisions of objects with at least 1 identical collision type are detected) 
 * 
 */
enum collisionType
{
	COLLISION_OFF = 0,
	GROUND_AND_WALL = 1,
	PLAYER = 2,
	ENEMEY = 4,
	OBJECT = 8,
	OTHER = 16
};


/**
 * @brief structure of the physics settings
 * 
 */
struct physicParam{
	vector2 velocity;
	int8_t gravity = 0;
};


/**
 * @brief structure of the collision settings
 * 
 */
struct collisionSettings
{
	vector2 position;
	vector2 size;
	collisionType  collisionLevel = GROUND_AND_WALL;
};


/**
 * @brief structure of the object settings
 * 
 */
struct objectSettings
{
	vector2 position;
	vector2 size;
	int8_t mass = 0;
};


/**
 * @brief structure of the sprite settings
 * 
 */
struct sprite
{
	uint8_t **ppSprite;	
	int32_t transparentColor = -1;
};


/**
 * @brief Object class
 * 
 */
class Object {

public: 
    Object();
	~Object();
	void setupCollisionWindow(vector2 position, vector2 size, collisionType setCollisionType = GROUND_AND_WALL);
	collisionSettings getCollisionWindow();
	virtual uint8_t *getSprite();
	virtual int32_t getTransparentColor();
	objectSettings getValues();	
	void setHidden(bool set);
	bool getHidden();
	void setPhysic(physicParam settings);
	physicParam getPhysic();
	void setVelocity(vector2 vel);
	void setGravity(int8_t grav);
	void setShowSprite(uint8_t set);
	uint16_t getObjectNumb();
	void setObjectNumb(uint16_t numb);
	void setPosition(vector2 position);

protected:
	collisionSettings collision;
	objectSettings settings;
	uint8_t showSprite;
	bool hidden;
	physicParam physicSettings;
	uint16_t objectNumb;
};


#endif