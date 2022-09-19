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
	setStateFlag(Device::Disabled, s.value(settingsKey("disabled"), false).toBool());
}

//+++ STATE FLAGS

void Device::setState(State s)
{
	if (s != m_state) {
		m_state = s;
		emit stateChanged(s);
	}
}

bool Device::stateFlag(StateFlag f)
{
	return m_state.testFlag(f);
}

void Device::setStateFlag(StateFlag f, bool v)
{
	setState(m_state.setFlag(f, v));
}
