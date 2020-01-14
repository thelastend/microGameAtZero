#ifndef _ILI9341_MICROGAMEATZERO_
#define _ILI9341_MICROGAMEATZERO_

#include <stdint.h>


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



typedef struct {
	uint8_t cmd;
	uint8_t data[16];
	uint8_t numbData;
}ili9341_init;

#endif
