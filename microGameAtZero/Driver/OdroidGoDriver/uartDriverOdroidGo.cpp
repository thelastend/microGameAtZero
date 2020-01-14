#include "uartDriverOdroidGo.h"



microGameAtZero_err initUart()
{
	int8_t uartSetup = MICRO_GAME_AT_ZERO_INIT_ERROR;
	uart_config_t config;
    config.baud_rate = BAUD_RATE;
    config.data_bits = UART_DATA_8_BITS;
    config.parity = UART_PARITY_DISABLE;
    config.stop_bits = UART_STOP_BITS_1;
    config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
	config.rx_flow_ctrl_thresh = 122;
	
	if(uart_param_config(UART_PORT,&config) == ESP_OK)
		uartSetup = MICRO_GAME_AT_ZERO_OK;
	
	if(uart_set_pin(UART_PORT, UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK)
		uartSetup = MICRO_GAME_AT_ZERO_INIT_ERROR;
	
	if(uart_driver_install(UART_PORT, BUFFER_SIZE*2, 0,0,NULL,0) != ESP_OK)
		uartSetup = MICRO_GAME_AT_ZERO_INIT_ERROR;
	
	return uartSetup;
}

microGameAtZero_err sendUart( const char *msg)
{//need /r/n for new line and start on the beginning
	return uart_write_bytes(UART_PORT, msg, strlen(msg));
}