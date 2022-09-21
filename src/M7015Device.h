#ifndef M7015DEVICE_H
#define M7015DEVICE_H

#include "global.h"
#include "ModbusServerDevice.h"
#include "ModbusDevice.h"
#include "ThermometerDevice.h"

class M7015Device : public ModbusDevice
{
Q_OBJECT
public:
	M7015Device(QString name, ModbusServerDevice *parent);
public slots:
	bool processResponse(QModbusRequest request, QModbusResponse response);
	QString firmwareVersion() {return m_firmwareVersion;};
	ThermometerDevice* sensor(int i);
private:
	QModbusRequest m_sensorsRequest;
	QModbusRequest m_statusRequest;
	QModbusRequest m_settingsRequest;

	QString        m_firmwareVersion;
	quint8         m_channelsEnabled; // 0: (disabled)           1: (enabled)
	quint8         m_channelsStatus;  // 0: (disabled || normal) 1: (enabled) && (over-range || under-range || wire opening)

	QList<ThermometerDevice*> m_sensors;
};

#endif
