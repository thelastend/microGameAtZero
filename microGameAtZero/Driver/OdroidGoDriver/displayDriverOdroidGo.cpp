#include "displayDriverOdroidGo.h"
#include <Arduino.h>


static void sendCmd(const uint8_t cmd);
static void sendData(const uint8_t *data,uint8_t len);
static void setupDisplay();
static void   cmdDataMode(bool cmdData);
static microGameAtZero_err setupBrightness();

static SPIClass *spi = NULL;
static bool connect = false;
static bool initFinish = false;
static displaySettings settings;
static uint32_t lineLength;
static uint8_t lineMultiplier;
static uint8_t brightnessSetting;
static ledc_channel_config_t brightnessChannel;
static ledc_timer_config_t brightnessTimer;



static ili9341_init init_cmd[] = {
	{POWER_CONTROL_B,{0x00,0xC1,0x30},3},
	{POWER_SEQUENCE,{0x64,0x03,0x12,0x81},4},
	{DRIVER_TIMING_A,{0x85, 0x01, 0x78}, 3},
	{POWER_CONTROL_A,{0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
	{PUMP_RATIO, {0x20}, 1},
	{DRIVER_TIMING_B,{0x00, 0x00}, 2},
	{POWER_CONTROL_1,{0x23}, 1},
	{POWER_CONTROL_2,{0x10}, 1},
	{VCOM_CONTROL_1,{0x3e, 0x28}, 2},
	{VCOM_CONTROL_2,{0x86}, 1},
	{MEMORY_ACCESS,{0xe8}, 1},
	{PIXEL_FORMAT,{0x55}, 1},
	{FRAME_RATE_NORM,{0x00, 0x13}, 2},
	{ENABLE_3G,{0x00}, 1},
	{GAMMA_SET,{0x01}, 1},
	{GAMMA_CORRECTION_P,{0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0Xf1, 0x37, 0x07, 0x10, 0x03, 0x0e, 0x09, 0x00}, 15},
	{GAMMA_CORRECTION_N, {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xc1, 0x48, 0x08, 0x0f, 0x0c, 0x31, 0x36, 0x0f}, 15},
	{PAGE_ADDRESS_SET, {0x00, 0x00, 0x00, 0xEF}, 4},
	{COLUMN_ADDRESS_SET,{0x00, 0x00, 0x01, 0x3F}, 4},
	{MEMORY_WRITE, {0}, 0},
	{ENTRY_MODE_SET,{0x07}, 1},
	{DISPLAY_FUNCTION,{0x08, 0x82, 0x27, 0x00}, 4},
	{SLEEP_OUT, {0}, 0},
	{DISPLAY_ON,{0}, 0},
};


microGameAtZero_err initDisplay(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY,
							 uint32_t speed, uint8_t brightness)
{
		
	microGameAtZero_err spiInit = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	brightnessSetting = 0;
	if(startX >= MIN_X && startX <= MAX_X && startY >= MIN_Y && startY <= MAX_Y &&
	   endX >= MIN_X && endX <= MAX_X && endY >= MIN_Y && endY <= MAX_Y  &&
	   startX < endX && startY < endY)
	{
		settings.startX = startX;
		settings.startY = startY;
		settings.endX = endX;
		settings.endY = endY;
		lineLength = (settings.endX - settings.startX);
		lineMultiplier = 1;
	
		if(speed <= MAX_CLOCK_SPEED && speed >= MIN_CLOCK_SPEED)
		{
			spi = new SPIClass(VSPI);
			settings.speed = speed;
			settings.brightness = brightness;
			initFinish = true;
			if(displayConnect() != 0)
			{
				connect = false;
				spiInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
			}
		}
		else
		{
			spiInit = MICRO_GAME_AT_ZERO_INVALID_PARAM;
		}

		gpio_pad_select_gpio(CS0_PIN);
		gpio_set_pull_mode((gpio_num_t)CS0_PIN,GPIO_PULLUP_ONLY);
		gpio_set_direction((gpio_num_t)CS0_PIN,GPIO_MODE_OUTPUT);

		gpio_pad_select_gpio(DATA_CMD_PIN);
		gpio_set_pull_mode((gpio_num_t)DATA_CMD_PIN,GPIO_PULLUP_ONLY);
		gpio_set_direction((gpio_num_t)DATA_CMD_PIN,GPIO_MODE_OUTPUT);		
		
		setupDisplay();
		#if (DEBUG == DISABLE)
		setupBrightness();

		if( setBrightness(5) < 0)
		{
			spiInit = -4;	
		}
		#endif
		
		spiInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
		if(fillArea(MIN_X, MIN_Y, MAX_X, MAX_Y, 0x125) == MICRO_GAME_AT_ZERO_OK)
		{
			if(setArea(startX,startY,endX,endY, SET_AREA_SAVE) == MICRO_GAME_AT_ZERO_OK)
			{
				spiInit = MICRO_GAME_AT_ZERO_OK;
			}
		}
	}
	return spiInit;
}


microGameAtZero_err displayConnect()
{
	microGameAtZero_err connectErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(connect == false && initFinish)
	{		
		spi->begin(SCK_PIN,MISO_PIN,MOSI_PIN);
		gpio_set_level((gpio_num_t)CS0_PIN,0);
		connect = true;
		connectErr = MICRO_GAME_AT_ZERO_OK;
	}
	return connectErr;
}



microGameAtZero_err displayDisconnect()
{
	microGameAtZero_err disconnectErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(connect == true && initFinish)
	{
		spi->end();
		gpio_set_level((gpio_num_t)CS0_PIN,1);
		connect = false;
		disconnectErr = MICRO_GAME_AT_ZERO_OK;
	}
	return disconnectErr;
}

bool isDisplayConnected()
{
	return connect;
}

static inline void cmdDataMode(bool cmdData)
{
	gpio_set_level((gpio_num_t)DATA_CMD_PIN,cmdData);
}

static void setupDisplay()
{
	uint8_t cmd  = 0;

	sendCmd(SOFT_RESET);
	delay_(150);
	do
	{
		sendCmd(init_cmd[cmd].cmd);
		if(init_cmd[cmd].cmd == SLEEP_OUT || init_cmd[cmd].cmd == DISPLAY_ON)
		{
			delay_(150);
		}
		else
		{
			sendData(init_cmd[cmd].data,init_cmd[cmd].numbData);
		}
		cmd++;
	}
	while(cmd < SETTINGS);
}


microGameAtZero_err updateDisplay(uint8_t *data, uint32_t length)
{
	microGameAtZero_err sendError = MICRO_GAME_AT_ZERO_INVALID_PARAM;

	if(data != NULL && length > 0 && connect)
	{
		sendCmd(MEMORY_WRITE);
		cmdDataMode(DATA_MODE);
		
		
		uint8_t  blue[] = {0, 11, 21, 31}; // blue lookup table		
		uint16_t lines = settings.endY-settings.startY;
		uint16_t lineBuffer[MAX_X];
		spi->beginTransaction(SPISettings(settings.speed, 1, SPI_MODE0));
		for(uint16_t index = 0; index < (lines);index++)
		{



			uint8_t* pData = data;
			uint8_t* pLine = (uint8_t*)lineBuffer;
			uint8_t msbColor = 0;
			uint8_t lsbColor = 0;
			for(uint16_t len = 0; len < lineLength;len++)
			{
				uint32_t color = *pData;

				pData++;
				//          =====Green=====     ===============Red==============
				msbColor = (color & 0x1C)>>2 | (color & 0xC0)>>3 | (color & 0xE0);
				//          =====Green=====    =======Blue======
				lsbColor = (color & 0x1C)<<3 | blue[color & 0x03];
				
				*pLine++ = msbColor;
				*pLine++ = lsbColor;

			}
			data += lineLength;
			spi->writeBytes((uint8_t*)lineBuffer,lineLength<<1);

			sendError = MICRO_GAME_AT_ZERO_OK;
		}
		spi->endTransaction();
	}

	return sendError;
}

static inline void sendCmd(const uint8_t cmd)
{
	if(connect)
	{
		spi->beginTransaction(SPISettings(settings.speed, 1, SPI_MODE0));
		cmdDataMode(CMD_MODE);
		spi->write(cmd);
		spi->endTransaction();
	}
}

static inline void sendData(const uint8_t *data,uint8_t len)
{
	if(connect)
	{
		spi->beginTransaction(SPISettings(settings.speed, 1, SPI_MODE0)); 
		cmdDataMode(DATA_MODE);
		spi->writeBytes(data,len);
		spi->endTransaction();
	}
}


void delay_(uint16_t ms)
{
	uint32_t nopTime = 240000*ms;
	for(uint32_t ii = 0;ii < nopTime;ii++)
	{
		//nop
	}
}


static microGameAtZero_err setupBrightness()
{
	microGameAtZero_err brightnessError = MICRO_GAME_AT_ZERO_INIT_ERROR;	
	
    brightnessTimer.duty_resolution = (ledc_timer_bit_t)BRIGHTNESS_RESOLUTION;
    brightnessTimer.freq_hz = BRIGHTNESS_FREQUENZ;   
    brightnessTimer.speed_mode = LEDC_HIGH_SPEED_MODE;  
    brightnessTimer.timer_num = LEDC_TIMER_1;   
    
    
    brightnessChannel.channel    = LEDC_CHANNEL_0;
    brightnessChannel.duty       = 0;
    brightnessChannel.gpio_num   = BRIGHT_PIN;
    brightnessChannel.speed_mode = LEDC_HIGH_SPEED_MODE;
    brightnessChannel.hpoint     = 0;
    brightnessChannel.timer_sel  = LEDC_TIMER_1;

	if(ledc_timer_config(&brightnessTimer) == ESP_OK)
	{
		if(ledc_channel_config(&brightnessChannel) == ESP_OK)
		{
			brightnessError = MICRO_GAME_AT_ZERO_OK;
		}
	}

	
	return brightnessError;
}


microGameAtZero_err setBrightness(uint8_t brightness)
{
	microGameAtZero_err brightnessError = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(brightness >= MIN_BRIGHTNESS && brightness <= MAX_BRIGHTNESS)
	{	
        if(ledc_set_duty(brightnessChannel.speed_mode, brightnessChannel.channel, (uint32_t)brightness) == ESP_OK)
		{
			if(ledc_update_duty(brightnessChannel.speed_mode, brightnessChannel.channel) == ESP_OK)
			{
				settings.brightness = brightness;
				brightnessError = MICRO_GAME_AT_ZERO_OK;
			}
		}
	}
	return brightnessError;
}

uint8_t getBrightness()
{
	return settings.brightness;
}

microGameAtZero_err setArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY,  uint8_t mode)
{
	microGameAtZero_err errorView = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	uint8_t data[] = {0,0,0,0};
	uint8_t cmd[] = {COLUMN_ADDRESS_SET,PAGE_ADDRESS_SET};
	uint16_t size[] = {startX,startY,endX,endY};

	if(mode == SET_AREA_NO_SAVE || mode == SET_AREA_SAVE)
	{
		if(startX >= MIN_X && startX <= MAX_X && startY >= MIN_Y && startY <= MAX_Y &&
		endX >= MIN_X && endX <= MAX_X && endY >= MIN_Y && endY <= MAX_Y &&
		startX < endX && startY < endY)
		{
			size[2] -= 1;
			size[3] -= 1;
			for(uint8_t ii = 0; ii < SET_VIEW_SIZE;ii++)
			{
				sendCmd(cmd[ii]);

				data[0] = HIGH_VALUE(size[ii]);
				data[1] = LOW_VALUE(size[ii]);
				data[2] = HIGH_VALUE(size[ii+2]);
				data[3] = LOW_VALUE(size[ii+2]);
				sendData(data,4);
			}
			errorView = MICRO_GAME_AT_ZERO_OK;
			if(mode)
			{
				settings.startX = startX;
				settings.startY = startY;
				settings.endX = endX;
				settings.endY = endY;
				lineLength = (settings.endX - settings.startX);
			}
		}
	}
	else
	{
		errorView = MICRO_GAME_AT_ZERO_NO_SAVE;
	}
	

	return errorView;
}



microGameAtZero_err fillArea(uint16_t startX, uint16_t startY, uint16_t endX, uint16_t endY, uint16_t color)
{
	microGameAtZero_err errFill = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	uint16_t lineLength = endX - startX;
	uint16_t colorFill[MAX_X];

	for(uint16_t ii = 0;ii < lineLength;ii++)
	{
		colorFill[ii] = color;
	}
	
	if(startX >= MIN_X && startX <= MAX_X && startY >= MIN_Y && startY <= MAX_Y &&
	   endX >= MIN_X && endX <= MAX_X && endY >= MIN_Y && endY <= MAX_Y  &&
	   startX < endX && startY < endY && connect)
	{
		uint32_t size = (endY - startY);
		setArea(startX,startY,endX,endY, SET_AREA_NO_SAVE);
		sendCmd(MEMORY_WRITE);
		cmdDataMode(DATA_MODE);
		spi->beginTransaction(SPISettings(settings.speed, 1, SPI_MODE0));
		for(uint32_t step = 0; step < size; step++)
		{
			spi->writeBytes((const uint8_t*)colorFill,lineLength<<1);
			errFill = MICRO_GAME_AT_ZERO_OK;
		}
		spi->endTransaction();
		setArea(settings.startX,settings.startY,settings.endX,settings.endY, SET_AREA_SAVE);
	}

	return errFill;
}