#include "RTCS.h"

RTCS::RTCS() : QObject()
{
	main_window = new RTCSMainWindow();
	pid_heater = new PID("Heater");
	pid_cooler = new PID("Cooler");

	QObject::connect(&Log::getInstance(), SIGNAL(logged(QString)), main_window, SLOT(setWindowTitle(QString)));
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