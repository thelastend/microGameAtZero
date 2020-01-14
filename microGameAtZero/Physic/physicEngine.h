#ifndef _PHYSICENGINE_MICROGAMEATZERO_
#define _PHYSICENGINE_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"
#include "../Scene/scene.h"
#include "../Physic/vector2.h"


/**
 * @brief PHYSICENGINE class
 * 
 */
class PHYSICENGINE {
    public:
    static vector2 collisionRect(collisionSettings coll1, collisionSettings coll2);
};

#endif