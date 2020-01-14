#ifndef _TARGET_SETTINGS_MICROGAMEATZERO_
#define _TARGET_SETTINGS_MICROGAMEATZERO_

#include "../configMicroGameAtZero.h"
#include <stdint.h>

/**
 * @brief structure of the engine settings (fps, x size, and y size)
 * 
 */
struct settingsEngine {
    uint16_t screenX = 0;
    uint16_t screenY = 0;
    uint8_t maxFps = 0;
};


typedef void(*timerCallback)(uint32_t deltaTime);
typedef void(*timerCoreCallback)();

#if (ODROIDGO == ENABLE)
#include "esp_attr.h"
#define MAX_HEIGHT_DISPLAY 240
#define MAX_WIDHT_DISPLAY  320
#define MIN_HEIGHT_DISPLAY 120
#define MIN_WIDHT_DISPLAY  160
#define SPI_SPEED	   40000000 //MAX 40000000
#define ATTR_RAM		IRAM_ATTR
#define DRAM		  	DRAM_ATTR 
#define MAX_PIXEL_SCREEN 76800


/**
 * @brief enumeration of the Odroid go audio sample rate
 * 
 */
enum audioSampleRate_t
{
	SAMPLE_16_KHZ = 0,
	SAMPLE_22_KHZ = 1,
	SAMPLE_44_KHZ = 2,
	MAX_SAMPLE_RATE
};


/**
 * @brief enumeration of the Odroid go joypad direction
 * 
 */
enum direction_t
{
	UP = 1,
	DOWN,
	LEFT,
	RIGHT
};


/**
 * @brief enumeration of the Odroid go buttons
 * 
 */
enum button_t
{
	MENU = 0,
	VOLUME,
	SELECT,
	START,
	B_BUTTON,
	A_BUTTON,
	MAX_INPUT
};


/**
 * @brief enumeration of the Odroid go external buttons
 * 
 */
enum externalButton_t
{
	EXTERNAL_A = 0,
	EXTERNAL_B,
	EXTERNAL_C
};
#endif

#endif