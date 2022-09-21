#ifndef THERMOMETERDEVICE_H
#define THERMOMETERDEVICE_H

#include "global.h"
#include "Device.h"

class ThermometerDevice : public Device
{
Q_OBJECT
public:
	ThermometerDevice(QString name, QObject *parent = nullptr);
public slots:
	bool setValue(double val);
	bool setRawValue(QByteArray val);
signals:
	void newValue(double val);
private:
	double     m_value;
	QByteArray m_rawValue;
};

#endif
