#ifndef _KEYBOARD_MICROGAMEATZERO_
#define _KEYBOARD_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"
#include "ui.h"
#include "../Scene/scene.h"

#define KEY_ROW_LINE        12
#define SHIFT_NUM           46
#define SPACE_NUM           47
#define DEL_NUM             48
#define ENTER_NUM           49
#define AMOUNT_KEYS         46
#define MAX_TITLE_LENGTH    32


/**
 * @brief KEYBOARD class
 * 
 */
class KEYBOARD {

public: 
    static KEYBOARD* getInstance()
    {
        if (! instance)
        {
            instance = new KEYBOARD();
        }
        return instance;
    }
    ~KEYBOARD();
    static SCENE* getScene();
	static void keyBoardLogic();
    static void setMaxInput(uint8_t max);
    static void setTitle(char* pText);
    static void setInputText(char * pInput);
    static char* getInputText();
    static void showCursor(bool show);

private:
    KEYBOARD();
    static void inputJoyPad();
    static KEYBOARD* instance;
    static UI*       keyBoardUi;
    static TEXT*     title;
    static TEXT*     inputText;
    static SCENE*    keyBoardScene;
    static BUTTON*   buttonList[50];
    static uint8_t   display[MAX_WIDHT_DISPLAY*MAX_HEIGHT_DISPLAY];
    static char      inputArray[MAX_KEYBOARD_INPUT];
    static char      saveInput[MAX_KEYBOARD_INPUT];
    static bool      shiftCheck;
    static bool      toChangCheck;
    static uint8_t   onKeyBoardPos;
    static uint16_t   arrayPos;
    static bool      joyPadCheck;
    static vector2   cursorPosition;
    static uint8_t   maxInput;
    static uint8_t   cursorPosBlick;

};


#endif