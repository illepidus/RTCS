#include "ThermometerDevice.h"

ThermometerDevice::ThermometerDevice(QString n, QObject *p) : Device(n, p)
{
	
}

bool ThermometerDevice::setRawValue(QByteArray val)
{
	m_rawValue = val;
	return true;
}

bool ThermometerDevice::setValue(double val)
{
	qDebug() << name() << val;
	m_value = val;
	emit newValue(val);
	return true;
}
