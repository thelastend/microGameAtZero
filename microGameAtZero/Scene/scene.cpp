//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/


#include "scene.h"
#include "../core/middleware.h"




/**
 * @brief Construct a new SCENE::SCENE object
 * 
 */
SCENE::SCENE()
{
   uint8_t index = 0;
   for(index = 0; index < MAX_DIF_STATIC;index++)
   {
       staticList[index] = NULL;
   }

   for(index = 0; index < MAX_DIF_KINECT;index++)
   {
       kinectList[index] = NULL;
   }
   
   for(index = 0; index < MAX_DIF_RIGID;index++)
   {
       rigidList[index] = NULL;
   }
   for(index = 0; index < MAX_SPRITES;index++)
   {
       spriteList[index].sprite = NULL;
   }
   for(index = 0; index < MAX_DIF_AREA;index++)
   {
       areaList[index] = NULL;
   }

   backgroundColor = 0;
   staticCounter = 0;
   rigidCounter = 0;
   kinectCounter = 0;
   spriteCounter = 0;
   areaCounter = 0;
   camera2d = NULL;
   uiSettings = NULL;
   tilePositionSet = false;
}


/**
 * @brief Destroy the SCENE::SCENE object
 * 
 */
SCENE::~SCENE()
{
   uint8_t index = 0;    
   for(index = 0; index < MAX_DIF_STATIC;index++)
   {
       staticList[index]->~StaticBody();
       staticList[index] = NULL;
   }

   for(index = 0; index < MAX_DIF_KINECT;index++)
   {
       kinectList[index]->~KinectBody();
       kinectList[index] = NULL;
   }
    
   for(index = 0; index < MAX_DIF_RIGID;index++)
   {
       rigidList[index]->~RigidBody();
       rigidList[index] = NULL;
   }
   for(index = 0; index < MAX_SPRITES;index++)
   {
       spriteList[index].sprite = NULL;
   }
   for(index = 0; index < MAX_DIF_AREA;index++)
   {
       areaList[index] = NULL;
   }

   camera2d->~CAMERA2D();
   camera2d = NULL;

   uiSettings->~UI();
   uiSettings = NULL;
}




/**
 * @brief This function sets the background color of the scene.
 * 
 * @param color background color to be set (8-bit ture color)
 */
void SCENE::setBackgroundColor(uint8_t color)
{
    backgroundColor = color;
}


/**
 * @brief This function returns the current background color.
 * 
 * @return uint8_t current background color (8-bit ture color)
 */
uint8_t SCENE::getBackgroundColor()
{
    return backgroundColor;
}


/**
 * @brief This function sets the tilemap for the selected layer of the scene.
 * 
 * @param map tilemap to be set
 * @param index the selected layer (in the moment just two layer available BACKGROUND_LAYER and OBJECT_LAYER)
 * @return MICRO_GAME_AT_ZERO_OK is everything is okey
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err SCENE::setTileMap(tileMap map, sceneLayer_t index)
{
    microGameAtZero_err setError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    uint32_t amountTiles = map.amountTile.x*map.amountTile.y;
    uint16_t x = 0;
    uint16_t y = 0;
    vector2 size = map.tileSize;

    if((index >=  BACKGROUND_LAYER) && (index < MAX_LAYER) && (amountTiles< MAX_TILES))
    {
        layer[index] = map;
        setError = MICRO_GAME_AT_ZERO_OK;
        if(tilePositionSet == false)
        {
            for(uint16_t ii = 0; ii < amountTiles; ii++)
            {
                tilesPosition[ii].x = x*size.x;
                tilesPosition[ii].y = y*size.y;
                x++;
                if(x == map.amountTile.x)
                {
                    x = 0;
                    y++;
                }
            }

            sceneSize.x = map.amountTile.x * map.tileSize.x;
            sceneSize.y = map.amountTile.y * map.tileSize.y;
            tilePositionSet = true;
        }
    }

    return setError;
}


/**
 * @brief This function returns the tilemap of the selected layer.
 * 
 * @param index selcted layer
 * @return tileMap  tilemap of the selected layer 
 */
tileMap ATTR_RAM SCENE::getTileMap(sceneLayer_t index)
{
    return layer[index];
}


/**
 * @brief This function adds a static object to the scene.
 * 
 * @param pObj static object to be add
 * @return index of the static object (identification number).
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter or there is no more room for this 
 *         object
 */
microGameAtZero_err SCENE::addStatic(StaticBody *pObj)
{
    microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(pObj != NULL)
    {
        if(staticCounter < MAX_DIF_STATIC)
        {
            for(uint16_t index = 0; index < MAX_DIF_STATIC;index++)
            {
                if(staticList[index] == NULL)
                {
                    staticList[index] = pObj;   
                    staticList[index]->setObjectNumb(index);          
                    staticCounter++;
                    addError = index;
                    break;
                }
            }
        }

    }

    return addError;
}


/**
 * @brief This function removes the passed static body from the scene.
 * 
 * @param pObj static body to be remove
 * @return MICRO_GAME_AT_ZERO_OK is everything is okey
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter (object not exist)
 */
microGameAtZero_err SCENE::removeStatic(StaticBody *pObj)
{
    microGameAtZero_err removError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pObj != NULL)
    {
        uint16_t index = pObj->getObjectNumb();
        if(index < MAX_DIF_STATIC)
        {
            staticList[index]->~StaticBody();
            staticList[index] = NULL;            
            staticCounter--;
            removError = MICRO_GAME_AT_ZERO_OK;
        }
        
    }
    
    return removError;
}



/**
 * @brief This function returns the static body of the passed index.
 * 
 * @param numbObjects index of the static body
 * @return StaticBody* if NULL no object on this possition, otherwise the object.
 */
StaticBody* SCENE::getStatic(uint16_t numbObjects)
{
    if(numbObjects < MAX_DIF_STATIC)
    {
        return staticList[numbObjects];
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief This function returns the current number of static body objects included in the scene.
 * 
 * @return uint16_t current number of static body object in the scene.
 */
uint16_t SCENE::getStaticCount()
{
    return staticCounter;
}


/**
 * @brief This function adds a sprite tile to the scene.
 * 
 * @param pSprite pointer to the sprite to be add
 * @param transparentColor color that should not be rendered (8-bit ture color)
 * @param wallOrGround if true then the collision type GROUND_AND_WALL is set for this Sprite 
 *                     (collision window size == sprite size)
 * @return position of the Sprite in the array (identification number).
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err SCENE::addSprite(uint8_t *pSprite, int32_t transparentColor, bool wallOrGround)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pSprite != NULL)
    {
        if(spriteCounter < MAX_SPRITES)
        {
            spriteList[spriteCounter].sprite = pSprite;
            spriteList[spriteCounter].transparentColor = transparentColor;
            if(wallOrGround)
                spriteList[spriteCounter].collision = GROUND_AND_WALL;
            else
                spriteList[spriteCounter].collision = COLLISION_OFF;

            error = spriteCounter;   
            spriteCounter++;
        }
    }
    
    return error;    
}


/**
 * @brief This function returns the sprite tile on the passed index.
 * 
 * @param numbSprite position of the sprite in the array  (identification number)
 * @return spriteTile* structure  of the sprite tile on the passed position is no sprite tile on this
 *         position a NULL is returned.
 */
spriteTile* ATTR_RAM SCENE::getSprite(uint16_t numbSprite)
{
    if(numbSprite < spriteCounter)
    {
        return &spriteList[numbSprite];
    }
    else
    {
        return NULL;
    }
    
}


/**
 * @brief This function adds a Kinect body to the scene.
 * 
 * @param pObj pointer to the Kinect body to be add.
 * @return index of the kinect body (identification number).
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter or there is no more space
 */
microGameAtZero_err SCENE::addKinect(KinectBody *pObj)
{
    microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(pObj != NULL)
    {
        if(kinectCounter < MAX_DIF_KINECT)
        {
            for(uint16_t index = 0; index < MAX_DIF_KINECT;index++)
            {
                if(kinectList[index] == NULL)
                {
                    kinectList[index] = pObj; 
                    kinectList[index]->setObjectNumb(index);   
                    addError = index;        
                    kinectCounter++;
                    break;
                }
            }
        }

    }

    return addError;
}


/**
 * @brief This function removes the passed Kinect body from the scene.
 * 
 * @param pObj pointer to the Kinect body to be remove
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no pObj is passed 
 */
microGameAtZero_err SCENE::removeKinect(KinectBody *pObj)
{
    microGameAtZero_err removError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pObj != NULL)
    {
        uint16_t index = pObj->getObjectNumb();
        if(index < MAX_DIF_KINECT)
        {
            kinectList[index]->~KinectBody();
            kinectList[index] = NULL;            
            kinectCounter--;
            removError = MICRO_GAME_AT_ZERO_OK;
        }
    }
    
    return removError;
}


/**
 * @brief This function returns the Kinect body on the passed index.
 * 
 * @param numbObjects position of the Kinect body in the array (identification number).
 * @return KinectBody* Kinect body on the passed position, if no Kinect body on this
 *         position a NULL is returned.
 */
KinectBody* SCENE::getKinect(uint16_t numbObjects)
{
    if(numbObjects < MAX_DIF_KINECT)
    {
        return kinectList[numbObjects];
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief This function returns the current number of Kinect body objects included in the scene.
 * 
 * @return uint16_t the current number of Kinect body object in the scene
 */
uint16_t SCENE::getKinectCount()
{
    return kinectCounter;
}


/**
 * @brief This function adds a rigid body to the scene.
 * 
 * @param pObj pointer to the rigid body to be add
 * @return index of the rigid body (identification number)
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter or there is no more space
 */
microGameAtZero_err SCENE::addRigid(RigidBody *pObj)
{
    microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(pObj != NULL)
    {
        if(rigidCounter < MAX_DIF_RIGID)
        {
            for(uint16_t index = 0; index < MAX_DIF_RIGID;index++)
            {
                if(rigidList[index] == NULL)
                {
                    rigidList[index] = pObj;        
                    rigidList[index]->setObjectNumb(index);                
                    addError = index;
                    rigidCounter++;
                    break;
                }
            }
        }

    }

    return addError;
}


/**
 * @brief This function removes the passed rigid body from the scene.
 * 
 * @param pObj pointer to the rigid body to be remove
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no pObj is passed 
 */
microGameAtZero_err SCENE::removeRigid(RigidBody *pObj)
{
    microGameAtZero_err removError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pObj != NULL)
    {
        uint16_t index = pObj->getObjectNumb();
        if(index < MAX_DIF_RIGID)
        {
            rigidList[index]->~RigidBody();
            rigidList[index] = NULL;            
            rigidCounter--;
            removError = MICRO_GAME_AT_ZERO_OK;
        }
    }
    
    return removError;
}


/**
 * @brief This function returns the rigid body on the passed index.
 * 
 * @param numbObjects position of the rigid body in the array (identification number).
 * @return RigidBody* rigid body on the passed position, if no rigid body on this
 *         position a NULL is returned.
 */
RigidBody* SCENE::getRigid(uint16_t numbObjects)
{
    if(numbObjects < MAX_DIF_RIGID)
    {
        return rigidList[numbObjects];
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief This function returns the current number of rigid body objects included in the scene.
 * 
 * @return uint16_t current number of rigid body object in the scene.
 */
uint16_t SCENE::getRigidCount()
{
    return rigidCounter;
}


/**
 * @brief This function adds an area to the scene.
 * 
 * @param pObj pointer to the area to be add.
 * @return index of the area (identification number).
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter or there is no more space
 */
microGameAtZero_err SCENE::addArea(AREA *pObj)
{
    microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(pObj != NULL)
    {

        if(areaCounter < MAX_DIF_AREA)
        {
            for(uint16_t index = 0; index < MAX_DIF_AREA;index++)
            {
                if(areaList[index] == NULL)
                {
                    areaList[index] = pObj;    
                    areaList[index]->setObjectNumb(index);        
                    addError = index;
                    areaCounter++;
                    break;
                }
            }
        }

    }

    return addError;
}


/**
 * @brief This function remove the passed area from the scene.
 * 
 * @param pObj pointer to the area to be remove
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM no pObj is passed 
 */
microGameAtZero_err SCENE::removeArea(AREA *pObj)
{
    microGameAtZero_err removError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pObj != NULL)
    {
        uint16_t index = pObj->getObjectNumb();
        if(index < MAX_DIF_AREA)
        {
            areaList[index]->~AREA(); 
            areaList[index] = NULL;            
            areaCounter--;
            removError = MICRO_GAME_AT_ZERO_OK;

        }
    }
    
    return removError;
}


/**
 * @brief This function returns the area on the passed index.
 * 
 * @param numbObjects position of the area in the array (identification number).
 * @return RigidBody* area on the passed position, if no area on this
 *         position a NULL is returned.
 */
AREA* SCENE::getArea(uint16_t numbObjects)
{
    if(areaCounter < MAX_DIF_AREA)
    {
        return areaList[areaCounter];
    }
    else
    {
        return NULL;
    }
}


/**
 * @brief This function returns the current number of area objects included in the scene.
 * 
 * @return uint16_t current number of area object in the scene.
 */
uint16_t SCENE::getAreaCount()
{
    return areaCounter;
}


/**
 * @brief This function returns the scene size.
 * 
 * @return uint16_t scene size.
 */
vector2 SCENE::getSceneParam()
{
    return sceneSize;
}


/**
 * @brief This function adds a 2D camera to the scene.
 * 
 * @param pCam pointer to the camera to be add.
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err SCENE::addCamera(CAMERA2D *pCam)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    
    if(pCam != NULL)
    {
        camera2d = pCam;
        error = MICRO_GAME_AT_ZERO_OK;
    }

    return error;
}


/**
 * @brief This function returns the connected camera.
 * 
 * @return CAMERA2D*
 */
CAMERA2D * ATTR_RAM SCENE::getCamera()
{
    return camera2d;
}


/**
 * @brief This function adds a UI interface to the scene.
 * 
 * @param pUi pointer to the UI interface to be add.
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err SCENE::addUI(UI *pUi)
{
    microGameAtZero_err error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(pUi != NULL)
    {
        uiSettings = pUi;
        error = MICRO_GAME_AT_ZERO_OK;
    }

    return error;
}


/**
 * @brief This function returns the UI interface of the scene.
 * 
 * @return UI ui interface of the scene
 */
UI  ATTR_RAM *SCENE::getUI()
{
    return uiSettings;
}


/**
 * @brief This function moves the body by the given value and checks if it a collision with tiles 
 *        where the collision type GROUND_AND_WALL is enabled. If a collision is detected, 
 *        the Kinect body will be position on the ground or/and near the wall.
 * 
 * @param pObject Kinect body to be move
 * @param positionUpdate the position is move by this value
 * @return vector2 new position of the object
 */
vector2 SCENE::moveCollisionWallGround(KinectBody *pObject,vector2 positionUpdate)
{
    tileMap map = layer[OBJECT_LAYER];
    uint32_t tilePosition;
    uint16_t maxTiles = map.amountTile.x*map.amountTile.y;
    collisionSettings collisionWindowObject = pObject->getCollisionWindow();
    collisionSettings collisionWindowTile;
    spriteTile *tile;
    int16_t tileNumber;
    vector2 zone;
    vector2 collisionUpdate;
    vector2 collision;
    int8_t loopUpCheck[] = {0,0,0,-1,1,0,0,0};

    loopUpCheck[0] = -(map.amountTile.x+1);
    loopUpCheck[1] = -map.amountTile.x;
    loopUpCheck[2] = -(map.amountTile.x-1);   
    loopUpCheck[5] = (map.amountTile.x-1);
    loopUpCheck[6] = map.amountTile.x;
    loopUpCheck[7] = (map.amountTile.x+1);  

    collisionWindowTile.size = map.tileSize;

    if(collisionWindowObject.position.x > 0)
        zone.x = collisionWindowObject.position.x/map.tileSize.x;
    else
        zone.x = 0;
    
    if(collisionWindowObject.position.y > 0) 
        zone.y = collisionWindowObject.position.y/map.tileSize.y;         
    else
        zone.y = 0;


    tilePosition = zone.x + (zone.y*map.amountTile.x);
    collisionWindowObject.position + positionUpdate;

    for(uint8_t ii = 0; ii < 8;ii++)
    {

        tileNumber = tilePosition+loopUpCheck[ii];   

            
        if(tileNumber < maxTiles && tileNumber > -1)
        {
            tile = NULL;
            uint8_t tileInList = map.order[tileNumber];
            if(NO_TILE_USEDED != tileInList)
            {
                tile = &spriteList[tileInList];
            }
            if(tile != NULL)
            {
                if(tile->collision == GROUND_AND_WALL)
                {
                    collisionWindowTile.position = tilesPosition[tileNumber];
                    collision = PHYSICENGINE::collisionRect(collisionWindowObject,collisionWindowTile);
                    if((collisionUpdate.x == 0) && (collision.x != 0) && ((ii == 3) || (ii == 4) ))
                        collisionUpdate.x = collision.x;

                    if((collisionUpdate.y == 0) && (collision.y != 0) && ((ii == 0) || (ii == 1) || (ii == 2) || (ii == 5) || (ii == 6) || (ii == 7)))
                        collisionUpdate.y = collision.y;                
                }
            }
        }
    }

    positionUpdate + collisionUpdate;

    return pObject->move(positionUpdate);

}