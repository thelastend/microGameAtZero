#ifndef _DISPLAYODROID_MICROGAMEATZERO_
#define _DISPLAYODROID_MICROGAMEATZERO_

#include "SPI.h"
#include <driver/gpio.h>
#include "driver/ledc.h"
#include "soc/spi_periph.h"
#include "soc/spi_struct.h"
#include "esp_system.h"
#include "esp_err.h"
#include <stdint.h>
#include <string.h>
#include "esp32-hal-ledc.h"
#include "../../microGameAtZeroError.h"
#include "../microGameAtZeroTargetSettings.h"


#define DEBUGGER

//VSPI
#define MISO_PIN				19
#define MOSI_PIN				23
#define SCK_PIN					18
#define CS0_PIN					5
#define DATA_CMD_PIN			21
#define BRIGHT_PIN				14
#define MAX_Y					MAX_HEIGHT_DISPLAY
#define MIN_Y					0
#define MAX_X					MAX_WIDHT_DISPLAY
#define MIN_X					0
#define MAX_CLOCK_SPEED			40000000
#define MIN_CLOCK_SPEED 		10000000
#define CMD_MODE				false
#define DATA_MODE				true
#define WIDTH					0
#define HEIGHT					1
#define BRIGHTNESS_RESOLUTION	8
#define BRIGHTNESS_FREQUENZ		10000
#define BRIGHTNESS_CHANNEL		0

#define SOFT_RESET		0x01
#define POWER_CONTROL_B 0xCF
#define POWER_SEQUENCE	0xED
#define DRIVER_TIMING_A	0xE8
#define POWER_CONTROL_A 0xCB
#define PUMP_RATIO		0xF7
#define DRIVER_TIMING_B 0xEA
#define POWER_CONTROL_1 0xC0
#define POWER_CONTROL_2	0xC1
#define VCOM_CONTROL_1	0xC5
#define VCOM_CONTROL_2	0xC7
#define MEMORY_ACCESS	0x36
#define PIXEL_FORMAT	0x3A
#define FRAME_RATE_NORM	0xB1
#define ENABLE_3G		0xF2
#define GAMMA_SET		0x26
#define GAMMA_CORRECTION_P	0xE0
#define GAMMA_CORRECTION_N	0xE1
#define COLUMN_ADDRESS_SET	0x2A
#define PAGE_ADDRESS_SET	0x2B
#define MEMORY_WRITE	0x2C
#define ENTRY_MODE_SET	0xB7
#define DISPLAY_FUNCTION	0xB6
#define SLEEP_OUT		0x11
#define DISPLAY_ON		0x29
#define SETTINGS		0x18
#define SET_VIEW_SIZE	0x2
#define SET_AREA_SAVE	0x1
#define SET_AREA_NO_SAVE 0x0

#define HIGH_VALUE(a) 		((a >> 8) & 0xFF)
#define LOW_VALUE(a)		((a) & 0xFF)

typedef struct {
	uint8_t cmd;
	uint8_t data[16];
	uint8_t numbData;
}ili9341_init;



typedef struct {
	uint16_t startX;
	uint16_t startY;
	uint16_t endX;
	uint16_t endY;
	uint32_t speed;
	uint8_t brightness;
}displaySettings;


microGameAtZero_err initDisplay(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY,
							 uint32_t speed, uint8_t brightness);

microGameAtZero_err displayConnect();
microGameAtZero_err displayDisconnect();
bool isDisplayConnected();
microGameAtZero_err updateDisplay(uint8_t *data, uint32_t length);
microGameAtZero_err setBrightness(uint8_t brightness);
uint8_t getBrightness();
microGameAtZero_err setArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint8_t mode);

microGameAtZero_err fillArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color);
void delay_(uint16_t ms);

#endif