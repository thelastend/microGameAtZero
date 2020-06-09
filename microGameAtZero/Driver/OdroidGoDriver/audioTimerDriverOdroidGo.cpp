#include "audioTimerDriverOdroidGo.h"

timerCoreCallback callbackAudio;
timerCoreCallback callbackTimer;


static microGameAtZero_err setupTimer(timer_idx_t timer, uint16_t value);
void IRAM_ATTR timerInterrupt(void *para);



microGameAtZero_err initTimer(timerCoreCallback timerFunction)
{
	int8_t timerinit = MICRO_GAME_AT_ZERO_INIT_ERROR;
//	timer_config_t config;
	if(timerFunction != NULL)
	{
		callbackTimer = timerFunction;
		if(setupTimer((timer_idx_t)TIMER_TIMER, ONE_MILLISECONDS) == 0)
		{
			timerinit = MICRO_GAME_AT_ZERO_OK;
		}

	} 
	return timerinit;
}



microGameAtZero_err initAudio(audioSampleRate_t sampleRate, timerCoreCallback audioCallback)
{
	
	int8_t init = MICRO_GAME_AT_ZERO_INIT_ERROR;

	gpio_pad_select_gpio(IN_MINUS);
	gpio_set_direction((gpio_num_t)IN_MINUS,GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t)IN_MINUS,HIGH);
	if(dac_output_enable(DAC_CHANNEL_2) == ESP_OK)
	{
		init = MICRO_GAME_AT_ZERO_OK;
		setValue(MUTE);
	}

	
	if((audioCallback != NULL) && (init == MICRO_GAME_AT_ZERO_OK) )
	{
		callbackAudio = audioCallback;
		init = setSampleRate(sampleRate);
	}

		
	return init;
}

microGameAtZero_err setSampleRate(audioSampleRate_t sampleRate)
{
	microGameAtZero_err error = MICRO_GAME_AT_ZERO_OK;
	uint16_t rate = 0;

	switch(sampleRate)
	{
		case SAMPLE_16_KHZ:
			rate = 624;
			break;
		case SAMPLE_22_KHZ:
			rate = 452;
			break;
		case SAMPLE_44_KHZ:
			rate = 226;
			break;
		default:
			error = MICRO_GAME_AT_ZERO_INVALID_PARAM;
	}
	
	if(error == MICRO_GAME_AT_ZERO_OK)
	{
		if(setupTimer((timer_idx_t)TIMER_AUDIO, rate) != MICRO_GAME_AT_ZERO_OK)
		{
			error = MICRO_GAME_AT_ZERO_INIT_ERROR;
		}
	}
	return error;
}

microGameAtZero_err setValue(uint8_t value)
{
	int8_t set = MICRO_GAME_AT_ZERO_INVALID_PARAM;

	if(dac_output_voltage(DAC_CHANNEL_2,value) == ESP_OK)
	{
		set = MICRO_GAME_AT_ZERO_OK;
	}
	
	return set;
}


microGameAtZero_err startAudio()
{
	int8_t startErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(timer_start(GROUP,(timer_idx_t)TIMER_AUDIO) == ESP_OK)
	{
		startErr =MICRO_GAME_AT_ZERO_OK;
	}

	return startErr;
}

microGameAtZero_err startMainTimer()
{
	int8_t startErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(timer_start(GROUP,(timer_idx_t)TIMER_TIMER) == ESP_OK)
	{
		startErr = MICRO_GAME_AT_ZERO_OK;
	}

	return startErr;
}

microGameAtZero_err setupTimer(timer_idx_t timer, uint16_t value)
{
	int8_t initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	timer_config_t config;
	
	config.divider = DIVIDER_FOR_US;
	config.counter_dir = TIMER_COUNT_UP;
	config.counter_en = TIMER_PAUSE;
	config.alarm_en = TIMER_ALARM_EN;
	config.intr_type = TIMER_INTR_LEVEL;
	config.auto_reload = true;
		
	if(timer_init(GROUP,timer,&config) != ESP_OK )
	{
		initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	}
	else if(timer_set_counter_value(GROUP,timer,0) != ESP_OK )
	{
		initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	}
	else if(timer_set_alarm_value(GROUP,timer,value) != ESP_OK)
	{
		initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	}
	else if(timer_enable_intr(GROUP,timer) != ESP_OK)
	{
		initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	}
	else if(timer_isr_register(GROUP,timer, &timerInterrupt, 
						(void*)timer, ESP_INTR_FLAG_IRAM, NULL) != ESP_OK)
	{
		initErr = MICRO_GAME_AT_ZERO_INIT_ERROR;
	}
	else
	{
		initErr = MICRO_GAME_AT_ZERO_OK;
	}
	
	

		
	return initErr;
}


void IRAM_ATTR timerInterrupt(void *para)
{
	if((int)para == TIMER_AUDIO)
	{
		TIMERG0.int_clr_timers.t0 = 1;
		callbackAudio();
		TIMERG0.hw_timer[TIMER_AUDIO].config.alarm_en = 1;
	}
	else if ((int)para == TIMER_TIMER)
	{
		TIMERG0.int_clr_timers.t1 = 1;
		callbackTimer();
		TIMERG0.hw_timer[TIMER_TIMER].config.alarm_en = 1;
		
	}
}