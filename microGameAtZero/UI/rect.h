#ifndef _RECT_MICROGAMEATZERO_
#define _RECT_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


/**
 * @brief structure of the rectangle settings
 * 
 */
struct rect_ui {
    bool hidden = false;
    uint8_t colorFill = 0;
    uint8_t colorLine = 0;
    uint8_t lineWidth = 1;
    uint16_t fillArea = 0;
    vector2 size;
    vector2 position;
};


/**
 * @brief RECT class
 * 
 */
class RECT {

public: 
    RECT(rect_ui setting);
    ~RECT();
    microGameAtZero_err setFillSize(uint8_t percent);
    void setFillColor(uint8_t color);
    void setLineColor(uint8_t color);
    rect_ui getRectSettings();
    void setHidden(bool hidden);
    bool getHidden();

private:
    rect_ui rectSetting;
};


#endif