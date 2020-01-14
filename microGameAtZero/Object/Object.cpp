//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "Object.h"
#include "../Physic/physicEngine.h"


/**
 * @brief Construct a new Object:: Object object
 * 
 */
Object::Object()
{
	showTexture = 0;
	objectNumb = 0;
}

/**
 * @brief Destroy the Object:: Object object
 * 
 */
Object::~Object()
{
	//Todo
}


/**
 * @brief This function sets the collision window of the object
 * 
 * @param position This value specifies the position of the collision window in relation to the object center. If x = 0 and y = 0
 * 				   the collision window is centerd. Otherwise, it will be moved away from the center by the entered value. 
 * @param size The size of the collision window
 * @param setCollisionType collision type 
 */
void Object::setupCollisionWindow(vector2 position, vector2 size, collisionType setCollisionType)
{
	collision.position.x = (settings.position.x + settings.size.x/2) + position.x - size.x/2;
	collision.position.y = (settings.position.y + settings.size.y/2) + position.y - size.y/2;
	collision.size = size;
	collision.collisionLevel = setCollisionType;
}
	
	
/**
 * @brief This function returns the collision window settings.
 * 
 * @return collisionSettings collision window settings 
 */
collisionSettings Object::getCollisionWindow()
{
	return collision;
}


/**
 * @brief This function returns the object settings (position, mass, and size)
 * 
 * @return objectSettings object settings
 */
objectSettings Object::getValues()
{
	return settings;
}


/**
 * @brief This function returns the texture (is a virtual function, see the derived classes)
 * 
 * @return NULL
 */
uint8_t *Object::getTexture()
{
	return NULL;
}


/**
 * @brief This function returns the transparent color (is a virtual function, see the derived classes)
 * 
 * @return -1 
 */
int32_t Object::getTransparentColor()
{
	return -1;
}

/**
 * @brief This function can set the visibility of the object. 
 * 
 * @param set if ture the object is hidden, otherwise not.
 */
void Object::setHidden(bool set)
{
	hidden = set;
}


/**
 * @brief This function returns  the hidden status of the object.
 * 
 * @return true the object is hidden
 * @return false the object is not hidden
 */
bool Object::getHidden()
{
	return hidden;
}


/**
 * @brief This function set which texture should  be displayed
 * 
 * @param set index of the texture that should be shown
 */
void Object::setShowTexture(uint8_t set)
{
	showTexture = set;
}


/**
 * @brief This function sets the physic of the object.
 * 
 * @param settings physic settings
 */
void Object::setPhysic(physicParam settings)
{
	physicSettings = settings;
}


/**
 * @brief This function returns the physic settings.
 * 
 * @return physicParam physic settings
 */
physicParam Object::getPhysic()
{
	return physicSettings;
}


/**
 * @brief This function sets the velocity of the object.
 * 
 * @param vel velocity to be set
 */
void Object::setVelocity(vector2 vel)
{
	physicSettings.velocity = vel;
}


/**
 * @brief This function sets the gravity acting on the object.
 * 
 * @param grav gravity to the object
 */
void Object::setGravity(int8_t grav)
{
	physicSettings.gravity = grav;
}


/**
 * @brief This function returns the object number of the object (identification number).
 * 
 * @return object number
 */
uint16_t Object::getObjectNumb()
{
	return objectNumb;
}


/**
 * @brief This function sets the object number of the object (identification number). 
 * 
 * @param numb object number
 */
void Object::setObjectNumb(uint16_t numb)
{
	objectNumb = numb;
}


/**
 * @brief This function sets the object to the new position.
 * 
 * @param position position to be set
 */
void Object::setPosition(vector2 position)
{
	settings.position = position;
	collision.position.x = (settings.position.x + settings.size.x/2)  - collision.size.x/2;
	collision.position.y = (settings.position.y + settings.size.y/2)  - collision.size.y/2;
}
