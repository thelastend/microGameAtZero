//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "physicEngine.h"

/**
 * @brief This function calculates if there is a collision between the two passed collision settings.
 * 
 * @param coll1 collisionSettings of object one.
 * @param coll2 collisionSettings of object two.
 * @return vector2 specifies in x and y how large the overlap of the collision of the objects is. If one or both values are 0,
 *                 there is no collision.
 */
vector2 PHYSICENGINE::collisionRect(collisionSettings coll1, collisionSettings coll2)
{
    vector2 minA, maxA, minB, maxB;
    vector2 collisionCheck;

    if(((coll1.collisionLevel & GROUND_AND_WALL) == (coll2.collisionLevel & GROUND_AND_WALL)) ||
       ((coll1.collisionLevel & PLAYER) == (coll2.collisionLevel & PLAYER)) ||
       ((coll1.collisionLevel & ENEMEY) == (coll2.collisionLevel & ENEMEY)) ||
       ((coll1.collisionLevel & OBJECT) == (coll2.collisionLevel & OBJECT)) ||
       ((coll1.collisionLevel & OTHER) == (coll2.collisionLevel & OTHER)))
    {
        minA = coll1.position;
        maxA.x = coll1.position.x+coll1.size.x;
        maxA.y = coll1.position.y+coll1.size.y;
        minB = coll2.position;
        maxB.x = coll2.position.x+coll2.size.x;
        maxB.y = coll2.position.y+coll2.size.y;

        if((maxA.x > minB.x) && (minA.x < maxB.x) && 
            (maxA.y > minB.y) && (minA.y < maxB.y))
        {
            if(maxA.x < maxB.x)
                collisionCheck.x = minB.x-maxA.x;

            else if(maxA.x >= maxB.x)
                collisionCheck.x = maxB.x - minA.x;

            if(maxA.y < maxB.y)
                collisionCheck.y = minB.y-maxA.y; 
            else if(maxA.y >= maxB.y)
               collisionCheck.y = maxB.y - minA.y;
        }
    }
    
    return collisionCheck;
}
