#ifndef _RENDERING2D_MICROGAMEATZERO_
#define _RENDERING2D_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../configMicroGameAtZero.h"
#include "../microGameAtZeroError.h"
#include "../Driver/microGameAtZeroTargetSettings.h"
#include "../Scene/scene.h"
#include "../UI/keyboard.h"


#define FPS_X_POSITION  30
#define FPS_Y_POSITION  30
#define FPS_TEXT_COLOR  0xFF

/**
 * @brief 2D rendering class
 * 
 */
class RENDERING2D {

public: 
    static RENDERING2D* getInstance(uint16_t x, uint16_t y)
    {
        if (! instance)
        {
            instance = new RENDERING2D(x, y);
            
        }
        return instance;
    }
    ~RENDERING2D();
	void renderingScreen(SCENE* loadedScene, uint8_t fps, bool showFPS, bool systemMenu, uint32_t deltaT);

private:
    RENDERING2D(uint16_t x, uint16_t y);
    static void drawChars(char *text, uint16_t length, fontType font, uint8_t color, vector2 position);
    static RENDERING2D *instance;
    static uint16_t xPixelSizeScreen;
    static uint16_t yPixelSizeScreen;
    static uint16_t xSave;
    static uint16_t ySave;
    static uint8_t display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
    static KEYBOARD *keyBoard;
    static SCENE *keyScene;
    static bool collisionWindowShow;
};


#endif