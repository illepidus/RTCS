#include "ModbusDevice.h"

ModbusDevice::ModbusDevice(QString n, ModbusServerDevice *p) : Device(n, p), m_modbusServer(p)
{
	loadSettings();
}

void ModbusDevice::loadSettings()
{
	QSettings s;
	qDebug() << s.fileName();
	setAddress(s.value(settingsKey("address"), 0).toInt());
}

bool ModbusDevice::setAddress(int address)
{
	if (m_address == address) {
		return false;
	}
	m_address = address;
	emit addressChanged(address);
	return ((address > 0) && (address < 248));
}

bool ModbusDevice::addRoutineRequest(QModbusRequest request)
{
	if (!request.isValid()) {
		qWarning() << name() << "trying to add invalid routine request";
		return false;
	}
	m_modbusServer->addRoutineRequest(address(), request, this);
	return true;
}

bool ModbusDevice::request(QModbusRequest request)
{
	if (!request.isValid()) {
		qWarning() << name() << "trying to prerform invalid request";
		return false;
	}
	m_modbusServer->request(address(), request, this);
	return true;
}

bool ModbusDevice::isEqual(const QModbusPdu &p1, const QModbusPdu &p2)
{
	return
		((
			p1.data() == p2.data()
		) && (
			p1.functionCode() == p2.functionCode()
		));
}