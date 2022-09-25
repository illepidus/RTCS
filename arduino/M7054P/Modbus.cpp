extern "C" {
  #include <stdlib.h>
  #include <string.h>
  #include <inttypes.h>
}
#include "Modbus.h"

Modbus::Modbus()
{

}

uint16_t Modbus::crc16(uint8_t *du, uint8_t len)
{
	uint8_t nTemp;
	uint16_t wCRCWord = 0xFFFF;
	while (len--)
	{
		nTemp = *du++ ^ wCRCWord;
		wCRCWord >>= 8;
		wCRCWord ^= wCRCTable[nTemp];
	}
	return wCRCWord;
}

bool Modbus::check(uint8_t *du, uint8_t len)
{
	if (len < 4) 
		return false;
	if (crc16(du, len) == 0)
		return true;
	return false;
}

void Modbus::sign(uint8_t *du, uint8_t len)
{
	du[len-2] = crc16(du, len-2) & 0xFF;
	du[len-1] = crc16(du, len-2) >> 8 & 0xFF;
}

void Modbus::swapByteOrder(uint8_t *du, uint8_t start, uint8_t len)
{
	if (len < 2) return;
	if (len%2 == 1) return;

	for (int i=start; i < (start + len); i+=2) {
		uint8_t buf = du[i];
		du[i] = du[i+1];
		du[i+1] = buf;
	}
}
