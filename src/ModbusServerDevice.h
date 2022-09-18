#ifndef MODBUSSERVERDEVICE_H
#define MODBUSSERVERDEVICE_H

#include "global.h"
#include "Device.h"
#include "Modbus.h"

#include <QSerialPort>
#include <QModbusRtuSerialMaster>

#define MODBUS_BUFFER_OVERFLOW_SIZE      100
#define MODBUS_READ_BUFFER_SIZE          256

class ModbusServerDevice : public Device
{
Q_OBJECT
public:
	ModbusServerDevice(QString name, QObject *parent = nullptr);
public slots:
	void loadSettings();
	bool start();
	bool stop();
	void onReadReady();
	void request();
private:
	QModbusRtuSerialMaster *serial_master;
	QString port_name;
	int baud_rate;
	int response_timeout;
};

#endif
