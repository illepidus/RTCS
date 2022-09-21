#include "M7015Device.h"

M7015Device::M7015Device(QString n, ModbusServerDevice *p) : ModbusDevice(n, p)
{
	m_sensors.append(new ThermometerDevice(name() + "_T1", this));
	m_sensors.append(new ThermometerDevice(name() + "_T2", this));
	m_sensors.append(new ThermometerDevice(name() + "_T3", this));
	m_sensors.append(new ThermometerDevice(name() + "_T4", this));
	m_sensors.append(new ThermometerDevice(name() + "_T5", this));
	m_sensors.append(new ThermometerDevice(name() + "_T6", this));

	m_firmwareVersion = "Unknown";
	m_channelsEnabled = 0x3F; // 00111111
	m_sensorsRequest  = QModbusRequest(QModbusPdu::FunctionCode(0x04), QByteArray::fromHex("00000006"));
	m_statusRequest   = QModbusRequest(QModbusPdu::FunctionCode(0x02), QByteArray::fromHex("00800006"));
	m_settingsRequest = QModbusRequest(QModbusPdu::FunctionCode(0x03), QByteArray::fromHex("01E0000B"));
	addRoutineRequest(m_sensorsRequest);
	addRoutineRequest(m_statusRequest);
	request(m_settingsRequest);
}

bool M7015Device::processResponse(QModbusRequest req, QModbusResponse res)
{
	if (!res.isValid()) {
		qWarning() << name() << "Received invalid response";
		return false;
	}

	if (isEqual(req, m_sensorsRequest)) {
		if ((res.dataSize() != 13) || res.data().at(0) != res.dataSize() - 1) {
			qWarning() << name() << "Received bad read sensors response";
			return false;
		}

		/*
		qDebug() << name()
			<< "T1 =" << ((double)Modbus::decodeInt16(res.data().mid(1,  2)) / 100) 
			<< "T2 =" << ((double)Modbus::decodeInt16(res.data().mid(3,  2)) / 100)
			<< "T3 =" << ((double)Modbus::decodeInt16(res.data().mid(5,  2)) / 100)
			<< "T4 =" << ((double)Modbus::decodeInt16(res.data().mid(7,  2)) / 100)
			<< "T5 =" << ((double)Modbus::decodeInt16(res.data().mid(9,  2)) / 100)
			<< "T6 =" << ((double)Modbus::decodeInt16(res.data().mid(11, 2)) / 100);
		*/
		for (int i = 0; i < 6; i++) {
			QByteArray chunk = res.data().mid(i * 2 + 1, 2);
			if (sensor(i) != nullptr) {
				sensor(i)->setRawValue(chunk);
				sensor(i)->setValue((double)Modbus::decodeInt16(chunk) / 100);
			}
		}

		return true;
	}

	if (isEqual(req, m_statusRequest)) {
		if ((res.dataSize() != 2) || res.data().at(0) != res.dataSize() - 1) {
			qWarning() << name() << "Received bad read status response";
			return false;
		}

		m_channelsStatus = res.data().at(1);

		/*
		qDebug() << name()
			<< "T1 =" << (((m_channelsStatus >> 0) & 1) ? "ERROR" : "OK")
			<< "T2 =" << (((m_channelsStatus >> 1) & 1) ? "ERROR" : "OK")
			<< "T3 =" << (((m_channelsStatus >> 2) & 1) ? "ERROR" : "OK")
			<< "T4 =" << (((m_channelsStatus >> 3) & 1) ? "ERROR" : "OK")
			<< "T5 =" << (((m_channelsStatus >> 4) & 1) ? "ERROR" : "OK")
			<< "T6 =" << (((m_channelsStatus >> 5) & 1) ? "ERROR" : "OK");
		*/

		return true;
	}

	if (isEqual(req, m_settingsRequest)) {
		if ((res.dataSize() != 23) || res.data().at(0) != res.dataSize() - 1) {
			qWarning() << name() << "Received bad read settings response";
			return false;
		}

		quint8 a = res.data().at(10);
		if (a != address()) {
			qWarning() << name() << "Received read settings response device address != device address";
			return false;
		}

		m_firmwareVersion = QByteArray().append(res.data().at(3)).append(res.data().at(1)).toHex();
		m_channelsEnabled = res.data().at(20);

		return true;
	}

	qWarning() << name() << "Received response for unknown request:" << res.data().toHex();
	return false;
}


ThermometerDevice* M7015Device::sensor(int i)
{
	if ((i < 0) || (i >= m_sensors.size()))
		return nullptr;
	return m_sensors.at(i);
}