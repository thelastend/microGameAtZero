#include "externaIOdroidGo.h"


microGameAtZero_err initExternal()
{
	uint8_t button[] = {INPUT_0,INPUT_1,INPUT_2};
	uint8_t initBut = 0;
	int8_t retInit = MICRO_GAME_AT_ZERO_INIT_ERROR;
	//init buttons
	#if (DEBUG == ENABLE)
		for(initBut = INPUT_2;initBut < sizeof(button);initBut++)
	#else
		for(initBut = INPUT_0;initBut < sizeof(button);initBut++)
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
	return retInit;
}

bool getExternal(uint8_t selectedButton)
{
	bool press = false;
	uint8_t button[] = {INPUT_0,INPUT_1,INPUT_2};
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

