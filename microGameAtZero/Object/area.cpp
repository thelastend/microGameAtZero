//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "area.h"


/**
 * @brief Construct a new AREA::AREA object
 * 
 */
AREA::AREA()
{

}
	
/**
 * @brief Destroy the AREA::AREA object
 * 
 */
AREA::~AREA()
{

}
	

/**
 * @brief This function sets the settings of the area.
 * 
 * @param size the size of the area
 * @param position the position of the area
 * @param collisionLevel what collision level the area has @collisionType
 */
void AREA::setArea(vector2 size, vector2 position, collisionType collisionLevel)
{
    collision.position.x =  position.x;
	collision.position.y =  position.y;
	collision.size = size;
	collision.collisionLevel = collisionLevel;
}