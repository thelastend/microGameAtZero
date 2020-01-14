#ifndef _BUTTONODROID_MICROGAMEATZERO_
#define _BUTTONODROID_MICROGAMEATZERO_

#include <driver/adc.h>
#include "driver/gpio.h"
#include <stdint.h>
#include "esp_err.h"
#include "../../microGameAtZeroError.h"
#include "../microGameAtZeroTargetSettings.h"

#define BTN_MENU	13
#define BTN_VOLUME	0
#define BTN_SELECT	27
#define BTN_START	39
#define BTN_B		33
#define BTN_A		32

microGameAtZero_err initButton();

bool getButton(uint8_t selectedButton);

bool getJoyPad(uint8_t xy);

#endif