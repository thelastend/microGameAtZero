#ifndef _EXTERNODROID_MICROGAMEATZERO_
#define _EXTERNODROID_MICROGAMEATZERO_

#include "driver/gpio.h"
#include <stdint.h>
#include "esp_err.h"
#include "../../microGameAtZeroError.h"
#include "../microGameAtZeroTargetSettings.h"

#define INPUT_0 12
#define INPUT_1 15
#define INPUT_2  4


microGameAtZero_err initExternal();

bool getExternal(uint8_t selectedButton);

#endif
