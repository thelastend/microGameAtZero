#ifndef _CHECKBOX_MICROGAMEATZERO_
#define _CHECKBOX_MICROGAMEATZERO_
  

#include <stdint.h>
#include <stddef.h>
#include "../microGameAtZeroError.h"
#include "../configMicroGameAtZero.h"
#include "../Physic/vector2.h"


#define SIZE_CHECKBOX   16
#define TRANS_COLOR     0x00


/**
 * @brief structure of the checkbox settings
 * 
 */
struct checkBox_ui {
    bool hidden = false;
    bool check = false;
    uint8_t *checkBox;
    vector2 position ;
};


/**
 * @brief CHECKBOX class
 * 
 */
class CHECKBOX {

public: 
    CHECKBOX(checkBox_ui settings);
    ~CHECKBOX();
    void changeCheck(bool check);
    checkBox_ui getCheckSettings();
    void setHidden(bool hidden);
    bool getHidden();

private:
    checkBox_ui checkSettings;
};


#endif