#include "Modbus.h"
#include <avr/wdt.h>

#define MCP 2

#define MODBUS_ID          0x71
#define MODBUS_BAUDRATE    115200
#define MODBUS_TIMEOUT     5
#define MODBUS_DELAY_A     14000.0f
#define MODBUS_DELAY_B     0.0f
#define MODBUS_BUFFER_SIZE 128
