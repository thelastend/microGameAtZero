//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "microGameAtZero.h"
#include "core/middleware.h"
#include "Physic/physicEngine.h"


MICROGAMEATZERO* MICROGAMEATZERO::instance;
COREENGINE* MICROGAMEATZERO::core;
TIMERENGINE* MICROGAMEATZERO::timer;
AUDIOENGINE* MICROGAMEATZERO::audio;


/**
 * @brief Construct a new MICROGAMEATZERO::MICROGAMEATZERO object
 * 
 */
MICROGAMEATZERO::MICROGAMEATZERO()
{
   core = NULL;
}


/**
 * @brief Destroy the MICROGAMEATZERO::MICROGAMEATZERO object
 * 
 */
MICROGAMEATZERO::~MICROGAMEATZERO()
{

}



/**
 * @brief This function initialization the microGameAtZero engine.
 * 
 * @param settings engine settings (x size, y size of the display, and max fps)
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter
 */
microGameAtZero_err MICROGAMEATZERO::initMicroGameAtZero(settingsEngine settings)
{
    microGameAtZero_err initError = MICRO_GAME_AT_ZERO_INVALID_PARAM;
    if(settings.screenX <= MAX_WIDHT_DISPLAY && settings.screenY <= MAX_HEIGHT_DISPLAY)
    {
       setupUart();
       timer = TIMERENGINE::getInstance();
       core = COREENGINE::getInstance(settings, timer);
       timer->init();
       audio = AUDIOENGINE::getInstance();
       initError = MICRO_GAME_AT_ZERO_OK;
    }
    return initError;
}



/**
 * @brief This function adds a new scene.
 * 
 * @param pScene pointer to the new scene to be add 
 * @return MICRO_GAME_AT_ZERO_OK everything is ok
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter 
 */
microGameAtZero_err MICROGAMEATZERO::addNewScene(SCENE *pScene)
{
   microGameAtZero_err addError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

    if(pScene != NULL)
    {
       core->addScene(pScene);
       addError = MICRO_GAME_AT_ZERO_OK;
    }
     
    return addError;
}



/**
 * @brief This function loads the selected scene.
 * 
 * @param position index of the selected scene.
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM there is no scene at this position 
 */
microGameAtZero_err MICROGAMEATZERO::loadScene(uint16_t position)
{
   return core->loadScene(position);
}


/**
 * @brief This function starts the game loop before calling this function, everything must be initialized.
 * 
 */
void MICROGAMEATZERO::startGame()
{
   timer->startUp();
   core->gameLoop();
}



/**
 * @brief This function returns the status of the selected button (example A or B)
 * 
 * @param selectButton selected button @button_t
 * @return true the button is pressed
 * @return false the button is not pressed
 */
bool MICROGAMEATZERO::getButton(uint8_t  selectButton)
{
   return getInputButton(selectButton);
}

/**
 * @brief This function returns the status of the selected joypad direction.
 * 
 * @param direction selected direction @direction_t
 * @return true the direction is pressed
 * @return false the direction is not pressed
 */
bool MICROGAMEATZERO::getJoyPad(uint8_t direction)
{
   return getInputJoyPad(direction);
}


/**
 * @brief This function checks if the two passed objects are colliding.
 * 
 * @param pObj1 pointer to the first object 
 * @param pObj2 pointer to the second object
 * @return vector2 specifies in x and y direction how large the overlap of the two objects. If one or both values are 0,
 *                 there is no collision.
 */
vector2 MICROGAMEATZERO::getCollision(Object* pObj1, Object* pObj2)
{
   return PHYSICENGINE::collisionRect(pObj1->getCollisionWindow(),pObj2->getCollisionWindow());
}


/**
 * @brief This function saves the passed data to the selected file.
 * 
 * @param pFileName name of the save file (max length MAX_LENGTH_NAME)
 * @param pData pointer to the data to be saved
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 */
microGameAtZero_err MICROGAMEATZERO::saveFile(char *pFileName, char *pData)
{
   return sendDataSd(pFileName,  pData);
}


/**
 * @brief This function loads the selected file.
 * 
 * @param pFileName name of the file (max length MAX_LENGTH_NAME)
 * @param pBuffer pointer to the buffer where the data should be loaded
 * @param sizeBuffer size of the buffer
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error 
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM invalid parameter ( e.g fileName > MAX_LENGTH_NAME, pBuff == NULL ...)
 */
microGameAtZero_err MICROGAMEATZERO::loadFile(char *pFileName, char *pBuffer, uint32_t sizeBuffer)
{
   return readDataSd(pFileName, pBuffer, sizeBuffer);
}

/**
 * @brief This function returns the name of the existed files.
 * 
 * @param ppFileName pointer to the existed files
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INIT_ERROR in the event of a hardware initialization error   
 */
microGameAtZero_err MICROGAMEATZERO::getFileList(char **ppFileName)
{
   return existedFiles(ppFileName);
}


/**
 * @brief This function writes data to the UART interface. (/0 terminiert)
 * 
 * @param pData pointer to the data to be write
 * @return the number of transferred bytes,
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM error
 */
microGameAtZero_err MICROGAMEATZERO::sendSerial(char* pData)
{
   return sendMsgUart(pData);
}