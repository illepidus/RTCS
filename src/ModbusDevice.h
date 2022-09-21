#ifndef MODBUSDEVICE_H
#define MODBUSDEVICE_H

#include "global.h"
#include "Device.h"
#include "Modbus.h"
#include "ModbusServerDevice.h"

#include <QModbusRtuSerialMaster>

class ModbusDevice : public Device
{
Q_OBJECT
public:
	ModbusDevice(QString name, ModbusServerDevice *parent);
public slots:
	virtual bool processResponse(QModbusRequest request, QModbusResponse response) = 0;
	int address() {return m_address;};
	bool setAddress(int address);
	void loadSettings();
public:
	static bool isEqual(const QModbusPdu &p1, const QModbusPdu &p2);
protected slots:
	bool addRoutineRequest(QModbusRequest);
	bool request(QModbusRequest);
signals:
	void addressChanged(int);
protected:
	ModbusServerDevice *m_modbusServer;
	int m_address;
};

#endif

