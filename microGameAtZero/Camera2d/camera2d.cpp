//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "camera2d.h"
#include "../2DRendering/rendering2DEngine.h"

/**
 * @brief Construct a new CAMERA2D::CAMERA2D object
 * 
 */
CAMERA2D::CAMERA2D()
{

}


/**
 * @brief Destroy the CAMERA2D::CAMERA2D object
 * 
 */
CAMERA2D::~CAMERA2D()
{

}


/**
 * @brief This function returns the camera position of the camera on the screen.
 * 
 * @return camera position 
 */
vector2 CAMERA2D::getCameraPosition()
{
    return camSettings.position;
}


/**
 * @brief This function calculates how the tilemap must be scrolled in relation to the camera position.
 * 
 * @return  the calculated values for scrolling
 */
scroll_s CAMERA2D::getScrollTile()
{    
    uint16_t diff = 0;


    if(camSettings.objectToCamera != NULL)
    {
        objectSettings positionObject = camSettings.objectToCamera->getValues();
  


        if(positionObject.position.x >= (areaFollowRect.max[0] + camSettings.position.x ) && (camSettings.position.x < (camSettings.mapeSize.x - viewSize.x)))
        {
            diff =  positionObject.position.x - (areaFollowRect.max[0] + camSettings.position.x );
            camSettings.position.x += diff;
            scrollSettings.scrollTile = (camSettings.position.x/(camSettings.tileSize.x));
            scrollSettings.direction.x = (camSettings.position.x)% (camSettings.tileSize.x); 
        }
        else if((camSettings.position.x > (camSettings.mapeSize.x - viewSize.x)))
        {
            camSettings.position.x = (camSettings.mapeSize.x - viewSize.x);
            scrollSettings.scrollTile = (camSettings.position.x/(camSettings.tileSize.x));
            scrollSettings.direction.x = (camSettings.position.x)% (camSettings.tileSize.x);             
        }
        else if(positionObject.position.x < (areaFollowRect.min[0] + camSettings.position.x ) && (camSettings.position.x > 0))
        {
            diff =  (areaFollowRect.min[0] + camSettings.position.x ) - positionObject.position.x;
            camSettings.position.x -= diff;
            scrollSettings.scrollTile = (camSettings.position.x/(camSettings.tileSize.x));
            scrollSettings.direction.x = (camSettings.position.x)% (camSettings.tileSize.x); 
        }
        if(camSettings.position.x  < 0)
        {
            camSettings.position.x = 0;
            scrollSettings.scrollTile = 0;
            scrollSettings.direction.x = 0;
        }


        if((positionObject.position.y >= (areaFollowRect.max[1] + camSettings.position.y )) && (camSettings.position.y < (camSettings.mapeSize.y - viewSize.y)))
        {
            diff = positionObject.position.y - (areaFollowRect.max[1] + camSettings.position.y );
            camSettings.position.y += diff;
            scrollSettings.scrollRow = (camSettings.position.y/(camSettings.tileSize.y));
            scrollSettings.direction.y = (camSettings.position.y)% (camSettings.tileSize.y);
        }
        else if (camSettings.position.y > (camSettings.mapeSize.y - viewSize.y))
        {
            camSettings.position.y = (camSettings.mapeSize.y - viewSize.y);
            scrollSettings.scrollRow = (camSettings.position.y/(camSettings.tileSize.y));
            scrollSettings.direction.y = (camSettings.position.y)% (camSettings.tileSize.y);
        }       
        else if(positionObject.position.y < (areaFollowRect.min[1] + camSettings.position.y ) && camSettings.position.y > 0)
        {
            diff = (areaFollowRect.min[1] + camSettings.position.y ) - positionObject.position.y;
            camSettings.position.y -= diff;
            scrollSettings.scrollRow = (camSettings.position.y/(camSettings.tileSize.y));
            scrollSettings.direction.y = (camSettings.position.y)% (camSettings.tileSize.y);
        }
        if( camSettings.position.y < 0)
        {
            camSettings.position.y = 0;
            scrollSettings.scrollRow = 0;
            scrollSettings.direction.y = 0;
        }
    }

    return scrollSettings;
}




/**
 * @brief This function passes the camera settings to the camera.
 * 
 * @param settings camera settings 
 */
void CAMERA2D::setCamera(camera_s settings)
{
    RENDERING2D *renderingEngine = RENDERING2D::getInstance();
    renderingEngine->getScreenSize(&viewSize.x, &viewSize.y);
    camSettings  = settings;

    areaFollowRect.max[0] = (viewSize.x/2 + camSettings.notFollowAreaRect.x/2);
    areaFollowRect.min[0] = (viewSize.x/2 - camSettings.notFollowAreaRect.x/2);
    areaFollowRect.max[1] = (viewSize.y/2 + camSettings.notFollowAreaRect.y/2);
    areaFollowRect.min[1] = (viewSize.y/2 - camSettings.notFollowAreaRect.y/2);
    
}


/**
 * @brief This function returns whether the camera is switch on or off.
 * 
 * @return true turned on
 * @return false turned off
 */
bool CAMERA2D::getCameraStatus()
{
    return camSettings.cameraOn;
}