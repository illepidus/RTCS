#ifndef DEVICE_H
#define DEVICE_H
#include "global.h"
#include <QObject>
#include <QSettings>

class Device : public QObject
{
	Q_OBJECT

	public:
		Device(QString name, QObject *parent = nullptr);

	public:
		enum StateFlag {
			Disabled    = 0b00000001, //Any device can be disabled in config file or programmaticly.
			Running     = 0b00000100  //Not that obvious
		};
		Q_DECLARE_FLAGS(State, StateFlag)

	public slots:
		QString name() {return m_name;};
		State state(){return m_state;};
		void setState(State s);
		bool stateFlag(StateFlag f);
		void setStateFlag(StateFlag f, bool v);
		void loadSettings();
		QString settingsKey(QString k);

	signals:
		void stateChanged(State);

	protected:
		QString m_name;
		State m_state;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(Device::State)

#endif