#ifndef _NUMBER_MICROGAMEATZERO_
#define _NUMBER_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


/**
 * @brief structure of the number object settings
 * 
 */
struct number_ui {
    bool hidden = false;
    vector2 position ;
    uint8_t textColor = 0;
    fontType font;
    uint32_t number = 0; 
};


/**
 * @brief NUMBER class
 * 
 */
class NUMBER {

public: 
    NUMBER(number_ui settings);
    ~NUMBER();
    microGameAtZero_err changeNumber(uint32_t number);
    number_ui getNumberSettings();
    uint32_t getNumber();
    void setHidden(bool hidden);
    bool getHidden();

private:
    number_ui numberSetting;
};


#endif