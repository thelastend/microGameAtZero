#ifndef _TIMERODRID_MICROGAMEATZERO_
#define _TIMERODROID_MICROGAMEATZERO_

#include <driver/dac.h> 
#include <driver/timer.h>
#include "driver/gpio.h"
#include <stdint.h>
#include "esp_err.h"
#include "../../microGameAtZeroError.h"
#include "../microGameAtZeroTargetSettings.h"


#define MUTE 125
#define IN_MINUS	25
#define HIGH	1
#define MAXVALUE	255

#define DIVIDER_FOR_US	8
#define START_VALUE		0
#define GROUP	        TIMER_GROUP_0
#define TIMER_AUDIO	    0
#define TIMER_TIMER 	1
#define ONE_MILLISECONDS	10000


microGameAtZero_err initTimer(timerCoreCallback timerFunction);
microGameAtZero_err startMainTimer();
microGameAtZero_err initAudio(audioSampleRate_t sampleRate, timerCoreCallback audioCallback);
microGameAtZero_err startAudio();
microGameAtZero_err setValue(uint8_t value);
microGameAtZero_err setSampleRate(audioSampleRate_t sampleRate);

#endif


