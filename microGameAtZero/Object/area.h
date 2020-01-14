#ifndef _AREA_MICROGAMEATZERO_
#define _AREA_MICROGAMEATZERO_
  

#include "Object.h"



/**
 * @brief Area class
 * 
 */
class AREA : public Object {

public: 
    AREA();
	~AREA();
	void setArea(vector2 size, vector2 position, collisionType collisionLevel);



private:

};


#endif