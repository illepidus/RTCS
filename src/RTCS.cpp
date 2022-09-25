#include "RTCS.h"

RTCS::RTCS() : QObject()
{
	main_window = new RTCSMainWindow();
	pid_heater = new PIDDevice("Heater", this);
	pid_cooler = new PIDDevice("Cooler", this);
	modbus_server = new ModbusServerDevice("Modbus", this);
	m7015p = new M7015Device("M7015P", modbus_server);
	pid_heater->saveSettings();

	QObject::connect(m7015p->sensor(0), &ThermometerDevice::newValue, main_window->process_widget, &ProcessWidget::setT1);
	QObject::connect(m7015p->sensor(1), &ThermometerDevice::newValue, main_window->process_widget, &ProcessWidget::setT2);
}

void RTCS::showMainWindow(bool fullscreen) {
	if (fullscreen)
		main_window->setWindowState(Qt::WindowFullScreen);
	else
		main_window->setWindowState(Qt::WindowMaximized);
	main_window->show();
}

void RTCS::hideMainWindow() {
	main_window->hide();
}