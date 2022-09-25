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
			Disabled    = 0b00000001, //Устройство отключено
			Available   = 0b00000010, //Устройство готово функционировать
			Running     = 0b00000100, //Устройство совершают некую осмысленную деятельность
			Waiting     = 0b00001000  //Устройство чего-то ожидает
		};
		Q_DECLARE_FLAGS(State, StateFlag)

	public slots:
		QString name() {return m_name;};
		State state()  {return m_state;};

		bool isDisabled()  {return stateFlag(Device::Disabled);};
		bool isAvailable() {return stateFlag(Device::Available);};
		bool isRunning()   {return stateFlag(Device::Running);};
		bool isWaiting()   {return stateFlag(Device::Waiting);};

		virtual void disable() {setDisabled(true);};
		virtual void enable() {setDisabled(false);};

	protected slots:
		void setDisabled (bool f){setStateFlag(Device::Disabled,  f);};
		void setAvailable(bool f){setStateFlag(Device::Available, f);};
		void setRunning  (bool f){setStateFlag(Device::Running,   f);};
		void setWaiting  (bool f){setStateFlag(Device::Waiting,   f);};

		void setState(State s);
		bool stateFlag(StateFlag f) {return m_state.testFlag(f);};
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