#ifndef _CAMERA2D_MICROGAMEATZERO_
#define _CAMERA2D_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../Object/Object.h"
#include "../Object/StaticBody.h"
#include "../Object/KinectBody.h"
#include "../Object/RigidBody.h"
#include "../microGameAtZeroError.h"
#include "../Physic/vector2.h"



/**
 * @brief Camera structure
 * 
 */
struct camera_s {
    bool cameraOn = false;
    KinectBody *objectToCamera = NULL;
    vector2 notFollowAreaRect;
    vector2    viewSize;
    vector2 position;
    vector2 mapeSize;
    vector2 tileSize;
};

/**
 * @brief structure for the dead zone of camera tracking
 * 
 */
struct cameraAreaRect {
    uint16_t min[2] = {0,0};
    uint16_t max[2] = {0,0};
};


/**
 * @brief scroll structure
 * 
 */
struct scroll_s {
    uint16_t scrollTile = 0;
    vector2  direction;
    uint16_t scrollRow = 0;
};

/**
 * @brief 2D camera class
 * 
 */
class CAMERA2D {

public: 
    CAMERA2D();
    ~CAMERA2D();
    void setCamera(camera_s settings);

    bool getCameraStatus();
    scroll_s getScrollTile();
    vector2 getCameraPosition();

    
private:
    camera_s camSettings;
    scroll_s scrollSettings;
    cameraAreaRect areaFollowRect;
};


#endif