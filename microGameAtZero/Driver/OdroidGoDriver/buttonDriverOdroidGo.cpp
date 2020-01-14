#include "buttonDriverOdroidGo.h"


microGameAtZero_err initButton()
{
	uint8_t button[] = {BTN_MENU,BTN_VOLUME,BTN_SELECT,BTN_START,BTN_B,BTN_A};
	uint8_t initBut = 0;
	int8_t retInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
	//init buttons
	#if (DEBUG == ENABLE)
		for(initBut = B_BUTTON;initBut < sizeof(button);initBut++)
	#else
		for(initBut = MENU;initBut < sizeof(button);initBut++)
	#endif
	{
		gpio_pad_select_gpio(button[initBut]);
		if(gpio_set_pull_mode((gpio_num_t)button[initBut],GPIO_PULLUP_ONLY) != ESP_OK)
		{
			retInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
			break;
		}
		if(gpio_set_direction((gpio_num_t)button[initBut],GPIO_MODE_INPUT) != ESP_OK)
		{
			retInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
			break;
		}
	}

	//init joypad
	if(adc1_config_width(ADC_WIDTH_BIT_12) == ESP_OK &&
	   adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_11) == ESP_OK &&
	   adc1_config_channel_atten(ADC1_CHANNEL_7,ADC_ATTEN_DB_11) == ESP_OK)
	{
		retInit = MICRO_GAME_AT_ZERO_OK;
	}
	
	return retInit;
}

bool getButton(uint8_t selectedButton)
{
	bool press = false;
	uint8_t button[] = {BTN_MENU,BTN_VOLUME,BTN_SELECT,BTN_START,BTN_B,BTN_A};
	if(	(DEBUG == ENABLE) && selectedButton == MENU)
		return press;

	if(selectedButton >= MENU && selectedButton < MAX_INPUT)
	{
		if(gpio_get_level((gpio_num_t)button[selectedButton]))
		{
			press = false;
		}
		else
		{
			press = true;
		}
		
	}
	return press;
}

bool getJoyPad(uint8_t xy)
{
	bool press = false;
	uint16_t value = 0;
	
	if(xy == LEFT || xy == RIGHT)
	{
		value = adc1_get_raw(ADC1_CHANNEL_6);
		if(value > 3300 && xy == LEFT)
		{
			press = true;
		}
		else if(value > 1300 && value < 3300 && xy == RIGHT)
		{
			press = true;
		}
		
	}
	else if (xy == UP || xy == DOWN)
	{
		value = adc1_get_raw(ADC1_CHANNEL_7);
		if(value > 3300 && xy == UP)
		{
			press = true;
		}
		else if(value > 1300 && value < 3300 && xy == DOWN)
		{
			press = true;
		}		
	}
	
	return press;
}