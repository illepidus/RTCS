#include "M7054P.h"

uint8_t modbus_buf[MODBUS_BUFFER_SIZE];

void processModbus() {
	int n = Serial.readBytes(modbus_buf, MODBUS_BUFFER_SIZE);
	if (!Modbus::check(modbus_buf, n)) return;
	if (!modbus_buf[0] != MODBUS_ID) return;

	uint8_t fn = modbus_buf[1];

	if (fn == 0x0F) {
		//WRITE MULTIPLE COILS
		//IFAAQQN[DATA]CC
		Modbus::swapByteOrder(modbus_buf, 2, 4); //to LittleEndian
		uint16_t A; memcpy(&A, &modbus_buf[2], sizeof(uint16_t)); //Starting Address
		uint16_t Q; memcpy(&Q, &modbus_buf[4], sizeof(uint16_t)); //Quantity of Outputs
		uint8_t  N; memcpy(&N, &modbus_buf[6], sizeof(uint8_t));  //Byte count
		if ((A > 7) || (A + Q > 8) || (N != 1) || (n != 10)) {
			//ILLEGAL DATA ADDRESS
			//IFECC
			n = 5;
			modbus_buf[1] = fn | 0x80;
			modbus_buf[2] = 0x02;
		}
		else {
			//WRITING COILS
			//IFAAQQCC
			n = 8; //IFAAQQ part of response equals IFAAQQ part of request (sic!)
			uint8_t data = modbus_buf[7];
			PORTC = PORTC & (~(0xFF >> (8 - Q) << A)) | ((data & (0xFF >> (8 - Q))) << A);
		}
	}
	else {
		//ILLEGAL FUNCTION
		//IFECC
		n = 5;
		modbus_buf[1] = fn | 0x80;
		modbus_buf[2] = 0x01;
	}

	Modbus::sign(modbus_buf, n);
	ModbusWrite(modbus_buf, n);
}

void ModbusWrite(uint8_t *buf, int n) {
	digitalWrite(MCP, HIGH);
	Serial.write(buf, n);
	delay(ceil(MODBUS_DELAY_A * n / MODBUS_BAUDRATE + MODBUS_DELAY_B / MODBUS_BAUDRATE));
	digitalWrite(MCP, LOW);
}

void setup() {
	DDRC = B00000000; // Set whole port C as output [A0..A7]
	pinMode(MCP, OUTPUT); digitalWrite(MCP, LOW); //Init MAX485 control pin
	Serial.setTimeout(MODBUS_TIMEOUT);
	Serial.begin(MODBUS_BAUDRATE);
	wdt_enable(WDTO_4S);
}

void loop() {
	wdt_reset();
	if (Serial.available()) {
		processModbus();
	}
}
