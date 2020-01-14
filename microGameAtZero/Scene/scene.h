#ifndef _SCENE_MICROGAMEATZERO_
#define _SCENE_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../Object/Object.h"
#include "../Object/StaticBody.h"
#include "../Object/KinectBody.h"
#include "../Object/RigidBody.h"
#include "../Object/area.h"
#include "../configMicroGameAtZero.h"
#include "../microGameAtZeroError.h"
#include "../Camera2d/camera2d.h"
#include "../Physic/vector2.h"
#include "../Physic/physicEngine.h"
#include "../UI/ui.h"

#define NO_TILE_USEDED		    255
#define MAX_TILES               900

/**
 * @brief enumeration of the object types 
 * 
 */
enum objects_t {
    KINECT = 0,
    RIGID  = 1,
    STATIC = 2,
    OBJECTS_TYPES
};


/**
 * @brief structure of the tile map settinges
 * 
 */
struct tileMap {
    vector2 tileSize;
    vector2 amountTile;
    uint8_t  *order = NULL;
};


/**
 * @brief enumeration of the scene layer types
 * 
 */
enum sceneLayer_t {
    BACKGROUND_LAYER = 0,
    OBJECT_LAYER = 1,
    MAX_LAYER  
};


/**
 * @brief structure of the texture tile settings
 * 
 */
struct textureTile {
    uint8_t *texture;
    int32_t transparentColor = -1;
    collisionType collision;
};


/**
 * @brief SCENE class
 * 
 */
class SCENE {

public:  
    SCENE();
    ~SCENE();
    void setBackgroundColor(uint8_t color);
    uint8_t getBackgroundColor();
    microGameAtZero_err setTileMap(tileMap map, sceneLayer_t index);
    tileMap getTileMap(sceneLayer_t index);
    virtual void sceneLogic(uint32_t deltaT){(void)deltaT;};
    microGameAtZero_err addStatic(StaticBody *pObj);
    microGameAtZero_err removeStatic(StaticBody *pObj);
    StaticBody* getStatic(uint16_t numbObjects);
    uint16_t getStaticCount();

    microGameAtZero_err addTexture(uint8_t *pTexture, int32_t transparentColor, bool wallOrGround);
    textureTile* getTexture(uint16_t numbTexture);
   
    microGameAtZero_err addKinect(KinectBody *pObj);
    microGameAtZero_err removeKinect(KinectBody *pObj);
    KinectBody* getKinect(uint16_t numbObjects);  
    uint16_t getKinectCount();

    microGameAtZero_err addRigid(RigidBody *pObj);
    microGameAtZero_err removeRigid(RigidBody *pObj);
    RigidBody* getRigid(uint16_t numbObjects);  
    uint16_t getRigidCount();

    microGameAtZero_err addArea(AREA *pObj);
    microGameAtZero_err removeArea(AREA *pObj);
    AREA* getArea(uint16_t numbObjects);  
    uint16_t getAreaCount();

    vector2 getSceneParam();

    microGameAtZero_err addCamera(CAMERA2D *pCam);
    CAMERA2D *getCamera();

    microGameAtZero_err addUI(UI *pUi);
    UI *getUI();

	vector2 moveCollisionWallGround(KinectBody *pObject,vector2 positionUpdate);
    
private:
    tileMap layer[MAX_LAYER];
    StaticBody *staticList[MAX_DIF_STATIC];
    KinectBody *kinectList[MAX_DIF_KINECT];
    RigidBody *rigidList[MAX_DIF_RIGID];
    AREA *areaList[MAX_DIF_AREA];
    textureTile textureList[MAX_TEXTURES];
    uint16_t textureCounter;
    uint16_t staticCounter;
    uint16_t kinectCounter;
    uint16_t rigidCounter;
    uint16_t areaCounter;
    uint16_t backgroundColor;
    vector2 sceneSize;
    CAMERA2D *camera2d;
    UI *uiSettings;
    vector2 tilesPosition[MAX_TILES];
    bool tilePositionSet;
};


#endif