#ifndef _BUTTON_MICROGAMEATZERO_
#define _BUTTON_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


/**
 * @brief structure of the button settings
 * 
 */
struct button_ui {
    bool Hidden = false;
    uint8_t buttonColor = 0;
    uint8_t highLightColor = 0;
    uint8_t highLightWidth = 0;
    bool highLightOn = false;
    vector2 position ;
    vector2 size;
    uint8_t textColor = 0;
    fontType font;
    char *pText; 
};


/**
 * @brief BUTTON class
 * 
 */
class BUTTON {

public: 
    BUTTON(button_ui settings);
    ~BUTTON();
    microGameAtZero_err setText(char text[MAX_BUTTON_TEXT]);
    button_ui getButtonSettings();
    void setHidden(bool hidden);
    bool getHidden();
    void setHighLight(bool light);
    bool getHighLight();
private:
    button_ui buttonSettings;
};


#endif