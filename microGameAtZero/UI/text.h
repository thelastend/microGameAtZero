#ifndef _TEXT_MICROGAMEATZERO_
#define _TEXT_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


/**
 * @brief structure of the text object settings
 * 
 */
struct text_ui {
    bool hidden = 0;
    vector2 position ;
    uint8_t textColor = 0xFF;
    fontType font;
    char *pText; 
};


/**
 * @brief TEXT class
 * 
 */
class TEXT {

public: 
    TEXT(text_ui settings);
    ~TEXT();
    microGameAtZero_err changeText(char *pText);
    text_ui getTextSettings();
    void setHidden(bool hidden);
    bool getHidden();

private:
    text_ui textSetting;
};


#endif