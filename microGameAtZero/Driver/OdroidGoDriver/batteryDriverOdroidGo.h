#ifndef _BATTERYODROID_MICROGAMEATZERO_
#define _BATTERYODROID_MICROGAMEATZERO_

#include <driver/adc.h>
#include <esp_adc_cal.h>
#include "../../microGameAtZeroError.h"

#define MAX_SAMPLE 12
#define MAX_VOLTAGE 4200
#define MIN_VOLTAGE 3400


microGameAtZero_err initBattery();

uint8_t getBatteryValue();

#endif