#ifndef _MENUSYSTEM_MICROGAMEATZERO_
#define _MENUSYSTEM_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include <list>
#include <iterator>
#include "../UI/ui.h"
#include "../Scene/scene.h"
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"
#include "../Audio/audioEngine.h"



#define CURSOR_X_MIN         0
#define CURSOR_X_MAX         284
#define CURSOR_X_UPDATE      284
#define CURSOR_Y_MIN         53
#define CURSOR_Y_MAX         213
#define CURSOR_Y_UPDATE      40
#define VOLUME_STEP          5
#define BRIGHTNESS_STEP      5


/**
 * @brief menu system class
 * 
 */
class MENUSYSTEM {

public: 
    static MENUSYSTEM* getInstance()
    {
        if (! instance)
        {
            instance = new MENUSYSTEM();
        }
        return instance;
    }
    ~MENUSYSTEM();
    static SCENE* getScene();
	static bool menuSystemLogic();

private:
    MENUSYSTEM();
    static MENUSYSTEM* instance;
    static AUDIOENGINE* audio;
    static uint16_t sizeW;
    static uint16_t sizeH;
    static vector2  cursorPos;
    static cursor_ui cursorSettings;
    static UI*      menuUi;
    static BUTTON*   volumMinusButton;  
    static BUTTON*   volumPLusButton;
    static BUTTON*   brightnessMinusButton;  
    static BUTTON*   brightnessPLusButton;
    static BUTTON*   soundButton;
    static TEXT*     title; 
    static TEXT*     volumeText;
    static NUMBER*   volumeValue;
    static TEXT*     brightnessText;
    static NUMBER*   brightnessValue;
    static TEXT*     batteryText;
    static NUMBER*   batteryLevel;
    static IMAGE*    muteOnOff;
    static RECT*     batteryBar;
    static RECT*     volumeBar;
    static RECT*     brightnessBar;
    static SCENE*    menuScene;
    static CHECKBOX* fpsCheck;
    static TEXT*     fpsText;
    static uint8_t   display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
    static bool joyCheck;
    static bool A_BCheck;
    static int16_t xCurs;
    static int16_t yCurs;
    static bool soundOnOffCheck;
    static bool fpsChangeCheck;
};


#endif