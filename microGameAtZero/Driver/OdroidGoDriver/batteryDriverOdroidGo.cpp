#include "batteryDriverOdroidGo.h"

static esp_adc_cal_characteristics_t characteristic;

microGameAtZero_err initBattery()
{
	int8_t initBattery = MICRO_GAME_AT_ZERO_INIT_ERROR;
	if(adc1_config_width(ADC_WIDTH_BIT_12) == ESP_OK &&
	   adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_11) == ESP_OK)
	{
	esp_adc_cal_characterize(ADC_UNIT_1,ADC_ATTEN_DB_11,ADC_WIDTH_BIT_12,ESP_ADC_CAL_VAL_EFUSE_TP,&characteristic);
		initBattery = MICRO_GAME_AT_ZERO_OK;
	}
	
	return initBattery;
}


uint8_t getBatteryValue()
{
	uint8_t prozent = 0;
	uint32_t value = 0;
	for(uint8_t ii = 0; ii < MAX_SAMPLE;ii++)
	{
		value += adc1_get_raw(ADC1_CHANNEL_0);
	}
	value /= MAX_SAMPLE;
	value = esp_adc_cal_raw_to_voltage(value,&characteristic) *2;

	uint16_t oneProzent = (MAX_VOLTAGE-MIN_VOLTAGE)/100;
	prozent = ((MAX_VOLTAGE-MIN_VOLTAGE)-((MAX_VOLTAGE-value)>0 ? value : 0))/oneProzent;
	
	return prozent;
}