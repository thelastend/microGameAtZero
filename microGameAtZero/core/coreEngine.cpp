//  This code is released under GPLv3 license.
//  see: https://www.gnu.org/licenses/gpl-3.0.en.html and https://www.fsf.org/

#include "coreEngine.h"
#include "middleware.h"
#include "../Physic/physicEngine.h"

COREENGINE* COREENGINE::instance;
uint16_t  COREENGINE::dT;
RENDERING2D* COREENGINE::renderingEngine;
AUDIOENGINE* COREENGINE::audio;
std::list<SCENE*> COREENGINE::sceneList;
SCENE * COREENGINE::loadedScene;
bool COREENGINE::update;
uint8_t COREENGINE::framePerSeconds;
uint8_t COREENGINE::fpsValue;
settingsEngine COREENGINE::settings;
MENUSYSTEM* COREENGINE::menuSys;
SCENE * COREENGINE::systemMenuScene;
uint8_t COREENGINE::volume;
bool COREENGINE::soundNotPress;
bool COREENGINE::soundCheck;
bool COREENGINE::menuSysButtonPress;
bool COREENGINE::checkMenuPress;
bool COREENGINE::menuButtonCheck;



/**
 * @brief Construct a new COREENGINE::COREENGINE object
 * 
 * @param setting settings of the engine (size in x, y and max fps)
 */
COREENGINE::COREENGINE(settingsEngine setting)
{
    dT = 0;
    volume = 10;
    soundNotPress = true;
    framePerSeconds = 0;
    settings = setting;
    fpsValue = 0;
    update = false;
    uint16_t x = setting.screenX;
    uint16_t y = setting.screenY;
    renderingEngine = RENDERING2D::getInstance(x, y);
    menuSys = MENUSYSTEM::getInstance();
    systemMenuScene = menuSys->getScene();
    audio = AUDIOENGINE::getInstance();
    setupButton();
    initBattery();
    loadedScene = NULL;
    menuSysButtonPress = false;
    checkMenuPress = true; 
    menuButtonCheck = true;

}


/**
 * @brief Destroy the COREENGINE::COREENGINE object
 * 
 */
COREENGINE::~COREENGINE()
{
  sceneList.clear();
  loadedScene = NULL;
}



/**
 * @brief This function is called by the timer interrupt and handles the fps control and 
 *        delta time determination.
 * 
 * @param deltaT The time has elapsed since the last call. (ms)
 */
void ATTR_RAM COREENGINE::timerUpdate(uint32_t deltaT)
{
    static uint8_t count = 0;
    count++;
    if(count == settings.maxFps)
    {
      count = 0;
      fpsValue = framePerSeconds;
      framePerSeconds = 0;
    }
    dT += deltaT;
    if(!update)
      update = true;

}


/**
 * @brief This function adds a new scene to the scene list.
 * 
 * @param scene new scene
 */
void COREENGINE::addScene(SCENE *scene)
{
  sceneList.push_back(scene);
}


/**
 * @brief This function loads the selected scene.
 * 
 * @param position index of the scene to be load
 * @return MICRO_GAME_AT_ZERO_OK everything is OK
 * @return MICRO_GAME_AT_ZERO_INVALID_PARAM there is no scene at this position 
 */
microGameAtZero_err COREENGINE::loadScene(uint16_t position)
{
  microGameAtZero_err loadErr = MICRO_GAME_AT_ZERO_INVALID_PARAM;

  std::list<SCENE*>::iterator toLoad = sceneList.begin();

  if(position < sceneList.size())
  {
    std::advance(toLoad,position);
    loadedScene = *toLoad;
    loadErr = MICRO_GAME_AT_ZERO_OK;
  }

  return loadErr; 
}


/**
 * @brief This function controls the game flow.
 * 
 */
void ATTR_RAM COREENGINE::gameLoop()
{
  static bool fpsShow = false;
  if(update)
  {
    framePerSeconds++;
    if(!menuSysButtonPress)
    {
      loadedScene->sceneLogic(dT);
      renderingEngine->renderingScreen(loadedScene,fpsValue, fpsShow,false,dT); 

    }
    else
    {
      fpsShow = menuSys->menuSystemLogic();
      renderingEngine->renderingScreen(systemMenuScene,fpsValue,fpsShow,true,dT);
    }
    update = false;
    menuButtonCheck = getInputButton(MENU);
    if(menuButtonCheck && checkMenuPress)
    {
      menuSysButtonPress = !menuSysButtonPress;
      checkMenuPress = false;
    }
    else if(!menuButtonCheck)
    {
      checkMenuPress = true;
    }
    
    soundCheck = getInputButton(VOLUME);
    if(soundCheck && soundNotPress)
    {
      soundNotPress = false;
      volume = audio->getMainVolume();
      if(volume <= MAX_VOLUME)
      {
        volume += VOLUME_STEP;
      }
      if(volume > MAX_VOLUME)
      {
        volume = 0;
      }
      audio->setMainVolume(volume);
    }
    else if(!soundCheck)
    {
      soundNotPress = true;
    }
    
    dT = 0;

  }
}


