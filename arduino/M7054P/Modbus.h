#ifndef MODBUS_H
#define MODBUS_H
#include <inttypes.h>
#include <Arduino.h>

class Modbus {
public:
	static uint16_t crc16(uint8_t*, uint8_t);
	static bool check(uint8_t*, uint8_t);
	static void sign(uint8_t*, uint8_t);
	static void swapByteOrder(uint8_t*, uint8_t, uint8_t);
private:
	Modbus() = delete;
	static const uint16_t wCRCTable[304];
};

#endif