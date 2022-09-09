#ifndef RTCS_H
#define RTCS_H

#include "global.h"
#include "RTCSMainWindow.h"
#include "PIDDevice.h"
#include "ModbusServerDevice.h"

#include <QObject>

class RTCS : public QObject
{
Q_OBJECT
private:
	RTCSMainWindow *main_window;
	PIDDevice *pid_heater;
	PIDDevice *pid_cooler;
	ModbusServerDevice *modbus_server;
public:
	RTCS();
public slots:
	void showMainWindow(bool = true);
	void hideMainWindow();
};

#endif
