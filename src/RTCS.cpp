#include "RTCS.h"

RTCS::RTCS() : QObject()
{
	main_window = new RTCSMainWindow();
	pid = new PID();
	pid->start();

	QObject::connect(&Log::getInstance(), SIGNAL(logged(QString)), main_window, SLOT(setWindowTitle(QString)));
}

void RTCS::showMainWindow(bool fullscreen) {
	if (fullscreen)
		main_window->setWindowState(Qt::WindowFullScreen);
	main_window->show();
}

void RTCS::hideMainWindow() {
	main_window->hide();
}