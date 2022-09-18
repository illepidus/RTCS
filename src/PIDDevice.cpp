#include "PIDDevice.h"

PIDDevice::PIDDevice(QString n, QObject *p) : Device(n, p)
{
	loadSettings();
	reset();
}

void PIDDevice::loadSettings()
{
	QSettings s;
	setR(s.value(settingsKey("r"),  80.0).toDouble());
	setDT(s.value(settingsKey("dt"), 1.0 ).toDouble());
	setKp(s.value(settingsKey("Kp"), 0.05).toDouble());
	setKi(s.value(settingsKey("Ki"), 0.01).toDouble());
	setKd(s.value(settingsKey("Kd"), 10  ).toDouble());
}

bool PIDDevice::reset()
{
	if (getStateFlag(Device::Running)) {
		qWarning() << name << "Cannot reset PID while it is running";
		return false;
	}

	u  = 0;
	P  = 0;
	I  = 0;
	D  = 0;
	e  = 0;
	de = 0;
	t  = 0;
	Se = 0;
	_e = 0;
	k  = 0;
	
	return true;
}

bool PIDDevice::saveSettings()
{
	QSettings s;
	if (!s.isWritable()) {
		qCritical() << name << "Settings not writable";
		return false;
	}

	s.setValue(settingsKey("r"),   r);
	s.setValue(settingsKey("dt"), dt);
	s.setValue(settingsKey("Kp"), Kp);
	s.setValue(settingsKey("Ki"), Ki);
	s.setValue(settingsKey("Kd"), Kd);
	return true;
}

bool PIDDevice::start()
{
	if (getStateFlag(Device::Disabled)) {
		qWarning() << name << "Cannot start PID while it is disabled";
		return false;
	}

	if (getStateFlag(Device::Running)) {
		qWarning() << name << "Cannot start PID while it is running";
		return false;
	}

	reset();
	setStateFlag(Device::Running, true);

	return step();
}

bool PIDDevice::stop()
{
	if (!getStateFlag(Device::Running)) {
		qInfo() << name << "Nothing to stop as PID is not running";
		return false;
	}
	setStateFlag(Device::Running, false);
	return true;
}

bool PIDDevice::step()
{
	if (getStateFlag(Device::Disabled)) {
		qWarning() << name << "PID disabled on step" << k;
		return false;
	}

	if (!getStateFlag(Device::Running)) {
		qInfo() << name << "PID stopped on step" << k;
		return false;
	}

	t += dt;
	e = r - y;

	Se += e * dt;
	de = (k == 0) ? 0 : e - _e;

	P = Kp * e;
	I = Kp * Ki * Se;
	D = Kp * Kd * de / dt;

	u = P + I + D;
	U = (u < 0) ? 0 : (u > 1) ? 1 : u;

	_e = e;
	k++;

	QTimer::singleShot(dt * 1000, this, SLOT(step()));
	return true;
}

bool PIDDevice::setR(double v)
{
	if (qIsFinite(v)) {
		r = v;
		return true;
	}
	qWarning() << name << "Unable to set r to " << v;
	return false;
}

bool PIDDevice::setDT(double v)
{
	if (v >= 0.001) {
		dt = v;
		return true;
	}
	qWarning() << name << "Unable to set dt to " << v;
	return false;
}

bool PIDDevice::setKp(double v)
{
	if (qIsFinite(v)) {
		Kp = v;
		return true;
	}
	qWarning() << name << "Unable to set Kp to " << v;
	return false;
}

bool PIDDevice::setKi(double v)
{
	if (qIsFinite(v)) {
		Ki = v;
		return true;
	}
	qWarning() << name << "Unable to set Ki to " << v;
	return false;
}

bool PIDDevice::setKd(double v)
{
	if (qIsFinite(v)) {
		Kp = v;
		return true;
	}
	qWarning() << name << "Unable to set Kp to " << v;
	return false;
}

bool PIDDevice::setY(double v)
{
	if (qIsFinite(v)) {
		y = v;
		return true;
	}
	qWarning() << name << "Unable to set y to " << v;
	return false;
}