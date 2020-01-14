#ifndef _UARTODROID_MICROGAMEATZERO_
#define _UARTODROID_MICROGAMEATZERO_

#include <driver/uart.h>
#include <string.h>
#include <stdint.h>
#include "esp_err.h"
#include "../../microGameAtZeroError.h"

#define BAUD_RATE	115200
#define UART_PORT	UART_NUM_0
#define BUFFER_SIZE	254

microGameAtZero_err initUart();

microGameAtZero_err sendUart( const char *msg);

#endif
