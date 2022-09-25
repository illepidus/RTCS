#include "Device.h"

Device::Device(QString n, QObject *p) : QObject(p)
{
	m_name = n;
	loadSettings();
}

//+++ SETTINGS

QString Device::settingsKey(QString k)
{
	return (QString("devices/%1/%2").arg(name()).arg(k));
}

void Device::loadSettings()
{
	QSettings s;
	setDisabled(s.value(settingsKey("disabled"), false).toBool());
}

//+++ STATE FLAGS

void Device::setState(State s)
{
	if (s != m_state) {
		m_state = s;
		emit stateChanged(s);
	}
}

void Device::setStateFlag(StateFlag f, bool v)
{
	setState(m_state.setFlag(f, v));
}