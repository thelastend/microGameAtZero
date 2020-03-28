#ifndef _IMAGE_MICROGAMEATZERO_
#define _IMAGE_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "font.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


/**
 * @brief structure of the image settings
 * 
 */
struct image_ui {
    bool hidden = false;
    uint8_t *pSprite;
    int32_t transparentColor = -1;
    vector2 size;
    vector2 position;
};


/**
 * @brief IMAGE class
 * 
 */
class IMAGE {

public: 
    IMAGE(image_ui setting);
    ~IMAGE();
    microGameAtZero_err changeImage(uint8_t *pSprite);
    image_ui getImageSettings();
    void setHidden(bool hidden);
    bool getHidden();

private:
    image_ui imageSetting;
};


#endif