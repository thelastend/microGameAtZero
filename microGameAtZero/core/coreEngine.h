#ifndef _COREENGINE_MICROGAMEATZERO_
#define _COREENGINE_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include <list>
#include <iterator>
#include "../2DRendering/rendering2DEngine.h"
#include "../Audio/audioEngine.h"
#include "../Timer/timerEngine.h"
#include "../configMicroGameAtZero.h"
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"
#include "../Scene/scene.h"
#include "../MenuSystem/menuSystem.h"


/**
 * @brief Core engine class
 * 
 */
class COREENGINE {

public: 
    static COREENGINE* getInstance(settingsEngine setting, TIMERENGINE *timer)
    {
        if (! instance)
        {
            instance = new COREENGINE(setting);
            timer->setupCoreTimer(instance->timerUpdate,setting.maxFps);
        }
        return instance;
    }
    ~COREENGINE();
	static void ATTR_RAM timerUpdate(uint32_t deltaT);
    static uint16_t addScene(SCENE *scene);
    static microGameAtZero_err loadScene(uint16_t position);
    static void gameLoop();

private:
    COREENGINE(settingsEngine setting);
    static settingsEngine settings;
    static COREENGINE* instance;
    static AUDIOENGINE* audio;
    volatile static uint16_t  dT;
    static RENDERING2D *renderingEngine;
    static std::list<SCENE*> sceneList;
    static SCENE *loadedScene;
    static SCENE *systemMenuScene;
    static int16_t sceneCounter;
    volatile static bool update;
    static uint8_t framePerSeconds;
    volatile static uint8_t fpsValue;
    static MENUSYSTEM* menuSys;
    static uint8_t volume;
    static bool soundNotPress;
    static bool soundCheck;
    static bool menuSysButtonPress;
    static bool checkMenuPress;
    static bool menuButtonCheck;
};


#endif