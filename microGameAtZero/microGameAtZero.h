#ifndef _MICROGAMEATZERO_
#define _MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "Audio/audioEngine.h"
#include "Timer/timerEngine.h"
#include "configMicroGameAtZero.h"
#include "microGameAtZeroError.h"
#include "Scene/scene.h"
#include "Object/Object.h"
#include "Object/KinectBody.h"
#include "Object/RigidBody.h"
#include "Object/StaticBody.h"
#include "Camera2d/camera2d.h"
#include "UI/ui.h"
#include "Physic/vector2.h"
#include "Driver/microGameAtZeroTargetSettings.h"
#include "core/coreEngine.h"



/**
 * @brief MICROGAMEATZERO class
 * 
 */
class MICROGAMEATZERO {

public:

    /**
    * @brief This function returns the pointer to the MICROGAMEATZERO instance. If no instance exists, 
    *        the function creates an instance of the MICROGAMEATZERO.
    *
    * @return pointer to the MICROGAMEATZERO instance
    */
    static MICROGAMEATZERO* getInstance()
    {
        if (! instance)
        {
            instance = new MICROGAMEATZERO();
        }
        return instance;
    }
    ~MICROGAMEATZERO();

    microGameAtZero_err initMicroGameAtZero(settingsEngine settings);
    microGameAtZero_err addNewScene(SCENE *scene);
    microGameAtZero_err loadScene(uint16_t position);   
    microGameAtZero_err saveFile(char *fileName,  char *data);
    char* loadFile(char *fileName);
    microGameAtZero_err getFileList(char **fileName);
    microGameAtZero_err sendSerial(char* data);    
    bool getButton(uint8_t  selectButton);
    bool getJoyPad(uint8_t direction);
    vector2 getCollision(Object* obj1, Object* obj2);
    void startGame();

private:
    static MICROGAMEATZERO* instance;
    MICROGAMEATZERO();
    static COREENGINE* core;
    static TIMERENGINE* timer;
    static AUDIOENGINE* audio;
};

#endif